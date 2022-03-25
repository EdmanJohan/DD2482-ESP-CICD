/*
 * FreeRTOS V201906.00 Major
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAJfCohKyj2dApP21lplsdz9de57TMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjAzMjUxNTE2\n"\
"MDdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDSTWel4/H/Gkygs9WR\n"\
"3fkxyJ+mQM1EILei5HYuHo9gc0IJttmPT0kMT921ZcuvV8P/HuxPO2cTLgDlAyYe\n"\
"i+kV4STbIKCh9ijHoK3FgMBVch6gInFJjpGFw4jlRXiVvAH5P1Pfzm0DiBnQ4jA8\n"\
"sd54Q2iEXhXq2htmP/Qke/P/4+ZiVgRpQZ4f3QhLUi17kH0pJTaB9oxcj8HevLe9\n"\
"DCmF56dqIUvAReDm9u3fi8puPuzg7PQeGEJinGI4uZ1p0m+pnnn8nR3ulPEwL7QU\n"\
"29o6At6mCbVh3Jp//FlCH9MZdNkh633ghqWZdBoJANMsqUq7RgxGnq1bdZfpPoUk\n"\
"9EUrAgMBAAGjYDBeMB8GA1UdIwQYMBaAFGH2drc/3bAUNXMr0VACk3ZZgOmAMB0G\n"\
"A1UdDgQWBBQahQtcLvPE8PLIzM5qYraLUplLeDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAuXhIddX6rEE8dBxp0obp9LtU\n"\
"ZllMeZ6UCoptaBvJoH2RALAq3zRtVYXVFFNryyEMww7cYYCQA5Wee4txJz3NNvlz\n"\
"fLXEBkXmNx+eOJb2usAie4CFQXIjyghDqrHiSOCr+9jpW/7ClIbXbBiq4GUVqA/+\n"\
"DkH4MWwXD6qsdo5Hackht6UyRQMk/+/HoalFD7kdclS9PVoN1HjYc4uM/JoW5WTm\n"\
"N8lPmYGT/s7GR+jDdxxps3AuGICsJqMep2nxJCnk3QndR4O1eQhbh2nFZrDHqmPW\n"\
"ND3IcVtr+QUIGp9teTYDL/NcdUpQjgXmmjYdmf7/pTpBdLGRJqA2FAUNI+4jmg==\n"\
"-----END CERTIFICATE-----\n"

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate 
 * Authority) of the client certificate is used by the server for routing the 
 * device's initial request. (The device client certificate must always be 
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html, 
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 * 
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  NULL

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEogIBAAKCAQEA0k1npePx/xpMoLPVkd35McifpkDNRCC3ouR2Lh6PYHNCCbbZ\n"\
"j09JDE/dtWXLr1fD/x7sTztnEy4A5QMmHovpFeEk2yCgofYox6CtxYDAVXIeoCJx\n"\
"SY6RhcOI5UV4lbwB+T9T385tA4gZ0OIwPLHeeENohF4V6tobZj/0JHvz/+PmYlYE\n"\
"aUGeH90IS1Ite5B9KSU2gfaMXI/B3ry3vQwpheenaiFLwEXg5vbt34vKbj7s4Oz0\n"\
"HhhCYpxiOLmdadJvqZ55/J0d7pTxMC+0FNvaOgLepgm1Ydyaf/xZQh/TGXTZIet9\n"\
"4IalmXQaCQDTLKlKu0YMRp6tW3WX6T6FJPRFKwIDAQABAoIBAGX8T7VtU6Ao+tw8\n"\
"GehBQ2XXK0UOy/yr+SIvtPgsrc9SVcYsPFl5U6161cPwd9SytUP1lRffcN8mQhzN\n"\
"aCEMLJ8Frj/uFLg2jhQxYdQT2jIVw7BYw6OuVfgOmUbGZ/IFWNes1FoG22sJB6v6\n"\
"5PWqNH8SAY+fqPVZjEwL27QNwIho9fUnvqV10ncLbEkJofu1zSj2iZgVa2PNLHb6\n"\
"Oa3lgLl587V6bR0QHL1brsgGsmVxAtYdASygA7PJ/bHggejD9n1U++F/vMkV3JsC\n"\
"ViPDZcjJyxGzo2X2tmtgu8gu3qCvxhCaY6ksqMb6MSwvetrGFLu8LU4/RN33y0jG\n"\
"5f+Ex/ECgYEA6czAdIAonJz+rjz5fdNPAnPcpJ+F8pJ8g7J9j+ZU8m2T9b8iMKrS\n"\
"cZ/5sguyf4WzO2c0OFJ3OV7e+H8CQt/3xYxGmlSVHGa6fWlNcqpeo3d9iWV2Inx2\n"\
"CFMXUX38tz9vU3EPYH+xJ7yArsMq6oW7OJjAlIKVoL+kWvmcgf9Izx0CgYEA5kV5\n"\
"DKu7XEx7ovstLn6dIwRBgmHHfB8ZDmwdxVvejNr93irsRMvJivlmuB3YVrc472ys\n"\
"i1L9W4fDAdnSQjf4Jr7MpLkYNci42Y0fblyCdAYSiT4S4VqQ42JF568sUSmRekg5\n"\
"LbuwusbnqF/AO5lfxwQ+alvp1fA2ArHZust/SucCgYAkzUIOFI5P+LZuHtL252gs\n"\
"bqhwkVu4Ty6iXFo/aHY+otkDec6b8oelsxTO3eB/CkCoPRqPMwvpT/GxE+z7Md4C\n"\
"jo4ehOnjypfYXdb/EapL+Ocd1Ya+7vB1Zv7oqPg6sBWKAOX2vqLYKmfnGnmK6PoL\n"\
"cp/9wIBlCUWJvHjSTajcUQKBgFYyI0HO9u9x4cX8Z8lDs+ZrrWn02AtqSKLRbcN2\n"\
"xDPNtcH4J0EJV4QiH4VEBrtPEoztDRmKEzSz+Rc0RjRrZwR533i5oIphfHBTFzTk\n"\
"hCCSNVYSWlbo49t56dj0BY7MFJzFdEHeRCVmV0j7rqWgn+2LdSGzDjD7HfycPnhh\n"\
"vGB5AoGAGZKHga9nZ16RJUkhp9GrAZiqY2YYVQGH7JRtIBvRgr5nHM2YkHgY0zGa\n"\
"aXluqQIkz1mJA366kulFKNV8Uqs/s6EGpTkrUAbbqHxyIcHMZR/mklsr12b8He4I\n"\
"IqU2OkIWlHASAPAilXOoh5IekNRk6pSW57c1dMJZMhXfEdiRGA0=\n"\
"-----END RSA PRIVATE KEY-----\n"


#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
