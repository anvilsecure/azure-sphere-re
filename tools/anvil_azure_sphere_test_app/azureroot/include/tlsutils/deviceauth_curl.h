#pragma once

#include <stdint.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Enumeration of the possible results from <see cref="DeviceAuth_SslCtxFunc"/>.
/// </summary>
typedef enum DeviceAuthSslResult {
    /// <summary> Success. </summary>
    DeviceAuthSslResult_Success = 0,
    /// <summary> Failed to access the current application's tenant id. </summary>
    DeviceAuthSslResult_GetTenantIdError = 1,
    /// <summary> Failed to load the device authentication certificate for the tenant. </summary>
    DeviceAuthSslResult_GetTenantCertificateError = 2,
    /// <summary> Failed to enable hardware signing. </summary>
    DeviceAuthSslResult_EnableHwSignError = 3,
} DeviceAuthSslResult;

/// <summary>
/// This is the minimal SSL function that can be invoked from within a custom libcurl SSL callback
/// for device authentication of SSL connections. It allows an application to provide a custom
/// callback for the CURLOPT_SSL_CTX_FUNCTION libcurl option, in which the application can perform
/// additional operations on the CURL object as well as handle errors on finer grained basis.
/// </summary>
/// <param name="sslctx">pointer to the SSL context taken by CURLOPT_SSL_CTX_FUNCTION
/// callback</param>
/// <returns>
/// Returns a <see cref="DeviceAuthSslResult"/> indicating the result of the operation.
/// </returns>
DeviceAuthSslResult DeviceAuth_SslCtxFunc(void *sslctx);

/// <summary>
/// Simple libcurl SSL callback that can be set as the CURLOPT_SSL_CTX_FUNCTION option for CURL
/// objects that use device authentication. When invoked by libcurl on a SSL connection, the
/// function sets the CURL object to do mutual authentication with the endpoint using the current
/// application's device authentication credentials. The function's signature matches that of a
/// libcurl callback for the CURLOPT_SSL_CTX_FUNCTION option.
/// </summary>
/// <param name="curl">CURL handle</param>
/// <param name="sslctx">pointer to the SSL context taken by CURLOPT_SSL_CTX_FUNCTION
/// callback</param>
/// <param name="userCtx">userCtx argument set with the CURLOPT_SSL_CTX_DATA option</param>
/// <returns>Returns CURLE_SSL_CERTPROBLEM on error or CURLE_OK on success</returns>
static inline CURLcode DeviceAuth_CurlSslFunc(CURL *curl, void *sslctx, void *userCtx);

#include <tlsutils/deviceauth_curl_internal.h>

#ifdef __cplusplus
}
#endif
