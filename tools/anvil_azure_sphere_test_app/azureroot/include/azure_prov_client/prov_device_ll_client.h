// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PROV_DEVICE_LL_CLIENT_H
#define PROV_DEVICE_LL_CLIENT_H

#include "azure_c_shared_utility/umock_c_prod.h"
#include "azure_c_shared_utility/macro_utils.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PROV_DEVICE_RESULT_VALUE            \
    PROV_DEVICE_RESULT_OK,                  \
    PROV_DEVICE_RESULT_INVALID_ARG,         \
    PROV_DEVICE_RESULT_SUCCESS,             \
    PROV_DEVICE_RESULT_MEMORY,              \
    PROV_DEVICE_RESULT_PARSING,             \
    PROV_DEVICE_RESULT_TRANSPORT,           \
    PROV_DEVICE_RESULT_INVALID_STATE,       \
    PROV_DEVICE_RESULT_DEV_AUTH_ERROR,      \
    PROV_DEVICE_RESULT_TIMEOUT,             \
    PROV_DEVICE_RESULT_KEY_ERROR,           \
    PROV_DEVICE_RESULT_ERROR,               \
    PROV_DEVICE_RESULT_HUB_NOT_SPECIFIED,   \
    PROV_DEVICE_RESULT_UNAUTHORIZED,        \
    PROV_DEVICE_RESULT_DISABLED

DEFINE_ENUM(PROV_DEVICE_RESULT, PROV_DEVICE_RESULT_VALUE);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // PROV_DEVICE_LL_CLIENT_H
