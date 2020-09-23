// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SHARED_UTIL_OPTIONS_H
#define SHARED_UTIL_OPTIONS_H

#include "azure_c_shared_utility/const_defines.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct HTTP_PROXY_OPTIONS_TAG
    {
        const char* host_address;
        int port;
        const char* username;
        const char* password;
    } HTTP_PROXY_OPTIONS;

    static STATIC_VAR_UNUSED const char* const OPTION_HTTP_PROXY = "proxy_data";

    static STATIC_VAR_UNUSED const char* const OPTION_TRUSTED_CERT = "TrustedCerts";

    static STATIC_VAR_UNUSED const char* const OPTION_X509_ECC_CERT = "x509EccCertificate";
    static STATIC_VAR_UNUSED const char* const OPTION_X509_ECC_KEY = "x509EccAliasKey";

    static STATIC_VAR_UNUSED const char* const OPTION_TLS_VERSION = "tls_version";

#ifdef __cplusplus
}
#endif

#endif /* SHARED_UTIL_OPTIONS_H */
