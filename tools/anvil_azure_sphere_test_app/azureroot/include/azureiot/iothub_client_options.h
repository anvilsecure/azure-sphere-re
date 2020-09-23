// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_CLIENT_OPTIONS_H
#define IOTHUB_CLIENT_OPTIONS_H

#include "azure_c_shared_utility/const_defines.h"

#ifdef __cplusplus
extern "C"
{
#endif

    static STATIC_VAR_UNUSED const char* OPTION_LOG_TRACE = "logtrace";
    static STATIC_VAR_UNUSED const char* OPTION_X509_CERT = "x509certificate";
    static STATIC_VAR_UNUSED const char* OPTION_X509_PRIVATE_KEY = "x509privatekey";
    static STATIC_VAR_UNUSED const char* OPTION_KEEP_ALIVE = "keepalive";
    static STATIC_VAR_UNUSED const char* OPTION_CONNECTION_TIMEOUT = "connect_timeout";

    static STATIC_VAR_UNUSED const char* OPTION_SAS_TOKEN_LIFETIME = "sas_token_lifetime";

    static STATIC_VAR_UNUSED const char* OPTION_MESSAGE_TIMEOUT = "messageTimeout";
    static STATIC_VAR_UNUSED const char* OPTION_PRODUCT_INFO = "product_info";

    /*
    * @brief    Turns on automatic URL encoding of message properties + system properties. Only valid for use with MQTT Transport
    */
    static STATIC_VAR_UNUSED const char* OPTION_AUTO_URL_ENCODE_DECODE = "auto_url_encode_decode";

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_CLIENT_OPTIONS_H */
