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
"MIIDWjCCAkKgAwIBAgIVAK01acnKsR3kAnuToGLyowy71lohMA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjAzMjQxMjMx\n"\
"MzZaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC+uCCGTaQfYLCCWzuf\n"\
"9Wq3OGcHzEaXf7XL331RAztX9lUo1NkRT3b7roHjMAHsFJ3oZXelwnE/wfj94jas\n"\
"SZewdKCSoyrLF1vv+wSu/rF2mVYhsjkvR6J0mtCWnYwaRwgEghi9LwLDmvsH7Hbi\n"\
"UgrkXIrp7phPY/3BsVZwuLKcFNHP1nyLwTpqAq8mXUmNfPY9NYYGP5jewL0F4bIf\n"\
"lsmgozoKdtsQtNroyQFdlUpdZsLTinISxTppB4xc65vRfmjvB80LhcxnviDwdSOk\n"\
"6CP+SmXeblpG09lUz1w0ZlD0e1/hAc4xR23faN90jmnJFBs1+VLInKUAXuHBbsAF\n"\
"pxurAgMBAAGjYDBeMB8GA1UdIwQYMBaAFDZXivA3bCN1fKVOtMOtLK5XJR8eMB0G\n"\
"A1UdDgQWBBRoyL80krcjGVfWitD2yEowrOPdpzAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAe27Ef4zDpD4x+evxHwxYcK2Y\n"\
"Rj9LgPjOrnYJf2x1uhNOHwkPrnV/QxSxMNNLuBuueMdgkgqCClmxfKPORRYkvFFJ\n"\
"d7Q8dstDI5rFv/dUikm2QAIA6WC6cPD22hYadOWl6s5CKsoEG6ZRPNX72qKatlJv\n"\
"fT6lHw4bGB2CH+AAvBZVi6NZePje76CS8QfR83xVv10pnEjJ8zUDyKETJz+kM8Ek\n"\
"dYi6SLOM1xCHsiJha4s49yugvmen99zxzCAhOJsv29uOHnszJAxrWCziKEjnMGfZ\n"\
"yF6yP4FiBndFFlLRSejdunP/CaW/uOWgPo83EbFOahzSfAZUBeFCjqmmrASG3A==\n"\
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
"MIIEpAIBAAKCAQEAvrgghk2kH2Cwgls7n/VqtzhnB8xGl3+1y999UQM7V/ZVKNTZ\n"\
"EU92+66B4zAB7BSd6GV3pcJxP8H4/eI2rEmXsHSgkqMqyxdb7/sErv6xdplWIbI5\n"\
"L0eidJrQlp2MGkcIBIIYvS8Cw5r7B+x24lIK5FyK6e6YT2P9wbFWcLiynBTRz9Z8\n"\
"i8E6agKvJl1JjXz2PTWGBj+Y3sC9BeGyH5bJoKM6CnbbELTa6MkBXZVKXWbC04py\n"\
"EsU6aQeMXOub0X5o7wfNC4XMZ74g8HUjpOgj/kpl3m5aRtPZVM9cNGZQ9Htf4QHO\n"\
"MUdt32jfdI5pyRQbNflSyJylAF7hwW7ABacbqwIDAQABAoIBAB+SWYgCGFY9alra\n"\
"AX/UX6sfAidPUKxJru2l/JfJoixIkgZlXd24uuilFclnLBpJu246RdlB2/+C+9YD\n"\
"eauBr0O9ussriaz/G/AZLMhPT09jyNdhKohCIomNC1SzlfrPoWslojTHMHzzDfVc\n"\
"1r1WeYkeLLzXC42w7tP+qGGWobKmklYOfiBvFQt1lAPLJEDxMM1aEOf4VbyEhVTp\n"\
"w7PUGd5uJkjdp2opDrkMO2/MvANSJLke2ywhMoJF7SmjFKhi8Z2koErOKPkMrmDg\n"\
"6LXfRbR76wiZ4KZYsaYgovFmVn+6xZ1dpYNbPzi+bFQBkhVGMf7dzJq28bu4nHcr\n"\
"UBI58IkCgYEA7GaB7uzbzCvkO8snILw50y0gWz9K46OtIRzDBtKvZgrem3ZJRK6c\n"\
"HCXkwN9nVV+UFphAL7Zf3Y9t3msSFKWyqzWy8k47pvVNtvHJFjD8r9RIY6RuYJHI\n"\
"ANYg2EUh9QMFuYWMu7oYpW6gd0y6SD6yGdFGcxM3Pj5WYAyXGuHm5U0CgYEAzogO\n"\
"ocwsWdGbXCz1XKhDr4tg1eAmw2pz3QDnJ8I7JADNT0sx8jnITpSSjIVBJT7N7cbf\n"\
"yMSK9e8WKkMcXs9OcV/9JbIeJM4Ss6Bxow+KPt1yFJ6kRd80ktd+I/1lEQWy+Cnf\n"\
"5aHBuq8WG+GPal0MD2J8SKF3s6rUYJT38XZKqNcCgYA47JIbG1Pt/R+vOkMIwepW\n"\
"rIYfEsWQvSgCUi+wI+lyc+mYm8oWzMjwijtkKidyyloZer3x/0NkUZZOOZAYArJc\n"\
"Qcj+SdJZaLY2+E/IlTEzkbWAsOaXQGNduDIegb8khX7KZps11SD8LQBc2c/9d4Nh\n"\
"biA9s4HY7h/UbxOvuHfl/QKBgQCl7q5C1DV13HAD+KMRVKc87LBaZYL/UhHQqB8P\n"\
"1H+Lh5Fsea+hO0dxyvCLMayLbhApT7UQKsiymuql/dFXYxtU/5f1p0uMqnxgETH7\n"\
"nkqmA2japDK7aH9m0venlriSmo+Vzp7ycamigXUz5V9CR4ue+LN97yyrDz8ecdFb\n"\
"EH0fdQKBgQDMQs9nYyOpQBEy7cJQIgtLBAg4skB/r9T2HbkqDtyCIo6iOfEjFi/H\n"\
"w626kat0bUg71XQljizLu79OA2XdLXV4SJVsPnSKlw1ijzGoiB8SNaMsVKH5P00a\n"\
"ayKdctTWb/MZZfSbRNOcAAV+g73NcoB3pSHwPeSGabohzE+MTu3IvA==\n"\
"-----END RSA PRIVATE KEY-----\n"


#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
