// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_TRANSPORT_LL_H
#define IOTHUB_TRANSPORT_LL_H

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
extern "C"
{
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "azure_c_shared_utility/umock_c_prod.h"

typedef void* METHOD_HANDLE;

struct TRANSPORT_PROVIDER_TAG;
typedef struct TRANSPORT_PROVIDER_TAG TRANSPORT_PROVIDER;

typedef const TRANSPORT_PROVIDER*(*IOTHUB_CLIENT_TRANSPORT_PROVIDER)(void);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_TRANSPORT_LL_H */

