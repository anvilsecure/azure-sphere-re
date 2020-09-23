/// \file deviceauth_curl_internal.h
/// \brief This header contains internal functions of Device Authentication Curl API and should
/// not be included directly; include tlsutils/deviceauth_curl.h instead.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

static inline CURLcode DeviceAuth_CurlSslFunc(CURL *curl, void *sslctx, void *userCtx)
{
    (void)curl;    // unused
    (void)userCtx; // unused

    return (DeviceAuth_SslCtxFunc(sslctx) == DeviceAuthSslResult_Success) ? CURLE_OK
                                                                          : CURLE_SSL_CERTPROBLEM;
}

#ifdef __cplusplus
}
#endif
