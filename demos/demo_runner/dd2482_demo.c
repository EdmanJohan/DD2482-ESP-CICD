/**
 * DD2482 Demo File for Cont. testing
 *
 */

/* The config header is always included first. */
#include "iot_config.h"

/* Includes for library initialization. */
#include "dd2482_demo.h"
#include "iot_demo_logging.h"

/* Standard header includes. */
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Include PKCS11 headers. */
#include "core_pkcs11.h"
#include "pkcs11.h"

/* Include connection configurations header. */
// #include "aws_clientcredential.h"

/* Retry parameters. */
#include "backoff_algorithm.h"


/* The logging configuration macros are defined above to ensure they are not
 * superceded by definitions in the following header files. */

/* Include paths for public enums, structures, and macros. */
#include "core_http_client.h"

/* Include Secure Sockets implementation of transport interface. */
#include "transport_secure_sockets.h"

#include "iot_init.h"

/*-----------------------------------------------------------*/

/**
 * @brief Each compilation unit that consumes the NetworkContext must define it.
 * It should contain a single pointer to the type of your desired transport.
 * When using multiple transports in the same compilation unit, define this pointer as void *.
 *
 * @note Transport stacks are defined in amazon-freertos/libraries/abstractions/transport/secure_sockets/transport_secure_sockets.h.
 */
struct NetworkContext
{
    SecureSocketsTransportParams_t * pParams;
};

/*-----------------------------------------------------------*/

/**
 * @brief Represents the network context used for the TLS session with the
 * server.
 */
static NetworkContext_t networkContext;

/**
 * @brief The parameters for the network context using a TLS channel.
 */
static SecureSocketsTransportParams_t secureSocketsTransportParams = { 0 };

/**
 * @brief The transport layer interface used by the HTTP Client library.
 */
static TransportInterface_t transportInterface;

/**
 * @brief Represents the hostname and port of the broker.
 */
static ServerInfo_t serverInfo;

/**
 * @brief A shared buffer used in the tests for storing HTTP request headers and
 * HTTP response headers and body.
 */
static uint8_t userBuffer[ USER_BUFFER_LENGTH ];

/**
 * @brief A HTTPResponse_t to share among the tests. This is used to verify
 * custom expected output.
 */
static HTTPResponse_t response;

/**
 * @brief Network data that is returned in the transportRecvStub.
 */
static uint8_t * pNetworkData = NULL;

/**
 * @brief The length of the network data to return in the transportRecvStub.
 */
static size_t networkDataLen = 0U;

/**
 * @brief The pseudo random number generator to use for exponential backoff with
 * jitter calculation for connection retries.
 * This function is an implementation the #BackoffAlgorithm_RNG_t interface type
 * of the backoff algorithm library API.
 *
 * The PKCS11 module is used to generate the random random number as it allows
 * access to a True Random Number Generator (TRNG) if the vendor platform supports it.
 *
 * @return The generated random number. This function ALWAYS succeeds
 * in generating a random number.
 */
static uint32_t generateRandomNumber();

/**
 * @brief Connect to HTTP server with reconnection retries.
 *
 * If connection fails, retry is attempted after a timeout.
 * Timeout value will exponentially increase until maximum
 * timeout value is reached or the number of attempts are exhausted.
 *
 * @param[out] pNetworkContext The output parameter to return the created network context.
 *
 */
static void connectToServerWithBackoffRetries( NetworkContext_t * pNetworkContext );

/**
 * @brief Send an HTTP request based on a specified method and path, then
 * print the response received from the server.
 *
 * @param[in] pTransportInterface The transport interface for making network calls.
 * @param[in] pMethod The HTTP request method.
 * @param[in] pPath The Request-URI to the objects of interest.
 */
static void sendHttpRequest( const TransportInterface_t * pTransportInterface,
                             const char * pMethod,
                             const char * pPath );

/*-----------------------------------------------------------*/

static uint32_t generateRandomNumber()
{
    UBaseType_t uxRandNum = 0;

    CK_FUNCTION_LIST_PTR pFunctionList = NULL;
    CK_SESSION_HANDLE session = CK_INVALID_HANDLE;

    /* Get list of functions supported by the PKCS11 port. */
    C_GetFunctionList( &pFunctionList );

    /* Initialize PKCS11 module and create a new session. */
    xInitializePkcs11Session( &session );

    /*
     * Seed random number generator with PKCS11.
     * Use of PKCS11 can allow use of True Random Number Generator (TRNG)
     * if the platform supports it.
     */
    pFunctionList->C_GenerateRandom( session, (unsigned char *) &uxRandNum, sizeof( uxRandNum ) );


    /* Close PKCS11 session. */
    pFunctionList->C_CloseSession( session );

    return uxRandNum;
}

static void connectToServerWithBackoffRetries( NetworkContext_t * pNetworkContext )
{
    /* Status returned by the retry utilities. */
    BackoffAlgorithmStatus_t BackoffAlgStatus = BackoffAlgorithmSuccess;
    /* Struct containing Sockets configurations. */
    SocketsConfig_t socketsConfig = { 0 };
    /* Struct containing the next backoff time. */
    BackoffAlgorithmContext_t reconnectParams;
    uint16_t nextRetryBackOff = 0U;
    /* Status returned by transport implementation. */
    TransportSocketStatus_t transportStatus = TRANSPORT_SOCKET_STATUS_SUCCESS;

    /* Initializer server information. */
    serverInfo.pHostName = SERVER_HOST_NAME;
    serverInfo.hostNameLength = SERVER_HOST_LENGTH;
    serverInfo.port = HTTPS_PORT;

    /* Configure credentials for TLS server-authenticated session. */
    socketsConfig.enableTls = true;
    socketsConfig.pAlpnProtos = NULL;
    socketsConfig.maxFragmentLength = 0;
    socketsConfig.disableSni = false;
    socketsConfig.pRootCa = ROOT_CA_CERT;
    socketsConfig.rootCaSize = sizeof( ROOT_CA_CERT );
    socketsConfig.sendTimeoutMs = TRANSPORT_SEND_RECV_TIMEOUT_MS;
    socketsConfig.recvTimeoutMs = TRANSPORT_SEND_RECV_TIMEOUT_MS;

    /* Initialize reconnect attempts and interval. */
    BackoffAlgorithm_InitializeParams( &reconnectParams,
                                       CONNECTION_RETRY_BACKOFF_BASE_MS,
                                       CONNECTION_RETRY_MAX_BACKOFF_DELAY_MS,
                                       CONNECTION_RETRY_MAX_ATTEMPTS );

    /* Attempt to connect to HTTP server. If connection fails, retry after
     * a timeout. Timeout value will exponentially increase until maximum
     * attempts are reached.
     */
    do
    {
        /* Establish a TLS session, on top of TCP connection, with the HTTP server. */
        transportStatus = SecureSocketsTransport_Connect( pNetworkContext,
                                                          &serverInfo,
                                                          &socketsConfig );

        if( transportStatus != TRANSPORT_SOCKET_STATUS_SUCCESS )
        {
            /* Generate random number and get back-off value for the next connection retry. */
            BackoffAlgStatus = BackoffAlgorithm_GetNextBackoff( &reconnectParams,
                                                                generateRandomNumber(),
                                                                &nextRetryBackOff );

            if( BackoffAlgStatus == BackoffAlgorithmRetriesExhausted )
            {
                LogError( ( "Connection to the server failed, all attempts exhausted." ) );
            }

            else if( BackoffAlgStatus == BackoffAlgorithmSuccess )
            {
                LogWarn( ( "Connection to the server failed. Retrying connection after backoff delay." ) );
                vTaskDelay( pdMS_TO_TICKS( nextRetryBackOff ) );
            }
        }
    } while( ( transportStatus != TRANSPORT_SOCKET_STATUS_SUCCESS ) && ( BackoffAlgStatus == BackoffAlgorithmSuccess ) );

}

/*-----------------------------------------------------------*/

static void sendHttpRequest( const TransportInterface_t * pTransportInterface,
                             const char * pMethod,
                             const char * pPath )
{
    /* Status returned by methods in HTTP Client Library API. */
    HTTPStatus_t httpStatus = HTTPNetworkError;
    /* Tracks number of retry requests made to the HTTP server. */
    uint8_t retryCount = 0;

    /* Configurations of the initial request headers that are passed to
     * #HTTPClient_InitializeRequestHeaders. */
    HTTPRequestInfo_t requestInfo;
    /* Represents header data that will be sent in an HTTP request. */
    HTTPRequestHeaders_t requestHeaders;

    assert( pMethod != NULL );
    assert( pPath != NULL );

    /* Initialize all HTTP Client library API structs to 0. */
    ( void ) memset( &requestInfo, 0, sizeof( requestInfo ) );
    ( void ) memset( &response, 0, sizeof( response ) );
    ( void ) memset( &requestHeaders, 0, sizeof( requestHeaders ) );

    /* Initialize the request object. */
    requestInfo.pHost = SERVER_HOST_NAME;
    requestInfo.hostLen = SERVER_HOST_LENGTH;
    requestInfo.pMethod = pMethod;
    requestInfo.methodLen = strlen( pMethod );
    requestInfo.pPath = pPath;
    requestInfo.pathLen = strlen( pPath );

    /* Set "Connection" HTTP header to "keep-alive" so that multiple requests
     * can be sent over the same established TCP connection. */
    requestInfo.reqFlags = HTTP_REQUEST_KEEP_ALIVE_FLAG;

    /* Set the buffer used for storing request headers. */
    requestHeaders.pBuffer = userBuffer;
    requestHeaders.bufferLen = USER_BUFFER_LENGTH;

    /* Initialize the response object. The same buffer used for storing
     * request headers is reused here. */
    response.pBuffer = userBuffer;
    response.bufferLen = USER_BUFFER_LENGTH;

    LogDebug( ( "Sending HTTP %.*s request to %.*s%.*s...",
                ( int32_t ) requestInfo.methodLen, requestInfo.pMethod,
                ( int32_t ) SERVER_HOST_LENGTH, SERVER_HOST_NAME,
                ( int32_t ) requestInfo.pathLen, requestInfo.pPath ) );

    /* Send request to HTTP server. If a network error is found, retry request for a
     * count of MAX_RETRY_COUNT. */
    do
    {
        /* Since the request and response headers share a buffer, request headers should
         * be re-initialized after a failed request. */
        httpStatus = HTTPClient_InitializeRequestHeaders( &requestHeaders,
                                                          &requestInfo );

        LogDebug( ( "Request Headers:\n%.*s\n"
                    "Request Body:\n%.*s\n",
                    ( int32_t ) requestHeaders.headersLen,
                    ( char * ) requestHeaders.pBuffer,
                    ( int32_t ) REQUEST_BODY_LENGTH, REQUEST_BODY ) );

        httpStatus = HTTPClient_Send( pTransportInterface,
                                      &requestHeaders,
                                      ( uint8_t * ) REQUEST_BODY,
                                      REQUEST_BODY_LENGTH,
                                      &response,
                                      0 );

        if( httpStatus == HTTPNetworkError )
        {
            LogDebug( ( "A network error has occured, retrying request." ) );
        }

        retryCount++;
    } while( ( httpStatus == HTTPNetworkError ) && ( retryCount < MAX_RETRY_COUNT ) );


    LogDebug( ( "Received HTTP response from %.*s%.*s...\n"
                "Response Headers:\n%.*s\n"
                "Response Status:\n%u\n"
                "Response Body:\n%.*s\n",
                ( int32_t ) SERVER_HOST_LENGTH, SERVER_HOST_NAME,
                ( int32_t ) requestInfo.pathLen, requestInfo.pPath,
                ( int32_t ) response.headersLen, response.pHeaders,
                response.statusCode,
                ( int32_t ) response.bodyLen, response.pBody ) );
}

/*-----------------------------------------------------------*/

/* Called before each test method. */
void testSetup()
{
    /* Clear the global response before each test. */
    memset( &response, 0, sizeof( HTTPResponse_t ) );
    /* Clear the network context before each test. */
    memset( &networkContext, 0, sizeof( networkContext ) );
    /* Clear thhe parameters TLS channel before each test. */
    memset( &secureSocketsTransportParams, 0, sizeof( SecureSocketsTransportParams_t ) );
    networkContext.pParams = &secureSocketsTransportParams;

    /* Apply defaults and reset the transport receive data globals. */
    pNetworkData = NULL;
    networkDataLen = 0U;

    /* Establish TLS session with HTTP server on top of a newly-created TCP connection. */
    connectToServerWithBackoffRetries( &networkContext );

    /* Define the transport interface. */
    ( void ) memset( &transportInterface, 0, sizeof( transportInterface ) );
    transportInterface.recv = SecureSocketsTransport_Recv;
    transportInterface.send = SecureSocketsTransport_Send;
    transportInterface.pNetworkContext = &networkContext;
}

/*-----------------------------------------------------------*/


/* ==== Main Demo === */

void runTestDemo( void * pArgument )
{
    vTaskDelay( pdMS_TO_TICKS( 5000 ) );
    IotLogInfo( "Hello from runTestDemo!" );
    testSetup();
    sendHttpRequest( &transportInterface,
                     HTTP_METHOD_POST,
                     POST_PATH );
}