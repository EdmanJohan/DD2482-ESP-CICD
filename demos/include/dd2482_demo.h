#ifndef _DD2482_DEMO_H_
#define _DD2482_DEMO_H_

#include "aws_demo_config.h"

// MEANING OF LIFE
#define MEANING_OF_LIFE     "40"

// IotThreadRoutine_t runTestDemo ()
void runTestDemo( void * pArgument );

/* Ensure that config macros, required for TLS connection, have been defined. */
#ifndef SERVER_HOST_NAME
    #define SERVER_HOST_NAME    "jenkins.midgaard.nu"
#endif

/* Check that TLS port of the server is defined. */
#ifndef HTTPS_PORT
    #define HTTPS_PORT    443
#endif

/* Use Starfield Root CA as the default Root CA because the TI C3220 Launchpad board
 * requires that the Root CA certificate have its certificate self-signed. The Amazon Root CAs
 * are cross-signed by Starfield Root CA.*/
#ifndef ROOT_CA_CERT
    #define ROOT_CA_CERT \
"-----BEGIN CERTIFICATE-----\n" \
"MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw\n" \
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
"cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4\n" \
"WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu\n" \
"ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY\n" \
"MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc\n" \
"h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+\n" \
"0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U\n" \
"A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW\n" \
"T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH\n" \
"B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC\n" \
"B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv\n" \
"KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn\n" \
"OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn\n" \
"jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw\n" \
"qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI\n" \
"rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV\n" \
"HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq\n" \
"hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL\n" \
"ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ\n" \
"3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK\n" \
"NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5\n" \
"ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur\n" \
"TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC\n" \
"jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc\n" \
"oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq\n" \
"4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA\n" \
"mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d\n" \
"emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=\n" \
"-----END CERTIFICATE-----\n"
#endif

/* Check that size of the user buffer is defined. */
#ifndef USER_BUFFER_LENGTH
    #define USER_BUFFER_LENGTH    ( 2048 )
#endif

/**********************End Configurations********************************/

/**
 * @brief Length of HTTP server host name.
 */
#define SERVER_HOST_LENGTH                       ( ( sizeof( SERVER_HOST_NAME ) - 1 ) )

/**
 * @brief The maximum number of connection retries with server.
 */
#define CONNECTION_RETRY_MAX_ATTEMPTS            ( 5U )

/**
 * @brief The maximum back-off delay (in milliseconds) for retry connection attempts
 * with server.
 */
#define CONNECTION_RETRY_MAX_BACKOFF_DELAY_MS    ( 5000U )

/**
 * @brief The base back-off delay (in milliseconds) to use for connection retry attempts.
 */
#define CONNECTION_RETRY_BACKOFF_BASE_MS         ( 500U )

/**
 * @brief AWS IoT HTTP server endpoint.
 * Clients can publish messages to an MQTT topic by making HTTP requests to the
 * AWS IoT core REST API. Please see
 * https://docs.aws.amazon.com/iot/latest/developerguide/http.html for more
 * information.
 */
// #define AWS_IOT_SERVER_HOST_NAME                 clientcredentialMQTT_BROKER_ENDPOINT

/**
 * @brief Length of the AWS IoT HTTP server host name.
 */
// #define AWS_IOT_SERVER_HOST_LENGTH               ( ( sizeof( AWS_IOT_SERVER_HOST_NAME ) - 1U ) )

/**
 * @brief Port number for the AWS IoT HTTP server.
 * Port 8443 does not need an ALPN protocol, for AWS IoT Core. Please see
 * https://docs.aws.amazon.com/iot/latest/developerguide/protocols.html for more
 * information.
 */
// #define AWS_IOT_HTTPS_PORT                       ( 8443 )

/**
 * @brief The maximum number of retries to attempt on network error.
 */
#define MAX_RETRY_COUNT                          ( 3U )

/**
 * @brief Paths for different HTTP methods for the specified host.
 */
#define GET_PATH                                 "/webhook-step/esp_callback"
#define HEAD_PATH                                "/webhook-step/esp_callback"
#define PUT_PATH                                 "/webhook-step/esp_callback"
#define POST_PATH                                "/webhook-step/esp_callback"
// #define AWS_IOT_POST_PATH                        "/topics/topic?qos=1"

/**
 * @brief Transport timeout in milliseconds for transport send and receive.
 */
#define TRANSPORT_SEND_RECV_TIMEOUT_MS           ( 5000U )

/**
 * @brief Request body to send for PUT and POST requests.
 */
#define REQUEST_BODY                             MEANING_OF_LIFE

/**
 * @brief Length of the request body.
 */
#define REQUEST_BODY_LENGTH                      ( sizeof( REQUEST_BODY ) - 1 )

/**
 * @brief The total length, of the chunked HTTP response body, to test receiving.
 * This length is inserted as a string into the request path, so avoid putting
 * parenthesis around it.
 */
#define CHUNKED_BODY_LENGTH                      128

/**
 * @brief The path used for testing receiving a transfer encoding chunked
 * response.
 */
#define STR_HELPER( x )    # x
#define TO_STR( x )        STR_HELPER( x )
#define GET_CHUNKED_PATH    "/stream-bytes/" TO_STR( CHUNKED_BODY_LENGTH )

/**
 * @brief A test response for http-parser that ends header lines with linefeeds
 * only.
 */
/**
 * #define HTTP_TEST_RESPONSE_LINE_FEEDS_ONLY \
 *      "HTTP/1.1 200 OK\n"                   \
 *     "Content-Length: 27\n"                 \
 *     "\n"                                   \
 *     "HTTP/0.0 0\n"                         \
 *     "test-header0: ab"
 * #define HTTP_TEST_RESPONSE_LINE_FEEDS_ONLY_BODY_LENGTH       ( 27U )
 * #define HTTP_TEST_RESPONSE_LINE_FEEDS_ONLY_HEADERS_LENGTH    ( 18U )
 */
/*-----------------------------------------------------------*/

#endif /* ifndef _DD2482_DEMO_H_ */