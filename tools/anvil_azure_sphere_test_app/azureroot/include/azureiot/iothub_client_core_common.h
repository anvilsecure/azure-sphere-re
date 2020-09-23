// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/* Shared structures and enums for iothub convenience layer and LL layer */

#ifndef IOTHUB_CLIENT_CORE_COMMON_H
#define IOTHUB_CLIENT_CORE_COMMON_H

#include "azure_c_shared_utility/macro_utils.h"
#include "azure_c_shared_utility/umock_c_prod.h"

#include "iothub_transport_ll.h"
#include "iothub_message.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define IOTHUB_CLIENT_RESULT_VALUES       \
    IOTHUB_CLIENT_OK,                     \
    IOTHUB_CLIENT_INVALID_ARG,            \
    IOTHUB_CLIENT_ERROR,                  \
    IOTHUB_CLIENT_INVALID_SIZE,           \
    IOTHUB_CLIENT_INDEFINITE_TIME

    /** @brief Enumeration specifying the status of calls to various APIs in this module.
    */

    DEFINE_ENUM(IOTHUB_CLIENT_RESULT, IOTHUB_CLIENT_RESULT_VALUES);

#define IOTHUB_CLIENT_RETRY_POLICY_VALUES     \
    IOTHUB_CLIENT_RETRY_NONE,                   \
    IOTHUB_CLIENT_RETRY_IMMEDIATE,                  \
    IOTHUB_CLIENT_RETRY_INTERVAL,      \
    IOTHUB_CLIENT_RETRY_LINEAR_BACKOFF,      \
    IOTHUB_CLIENT_RETRY_EXPONENTIAL_BACKOFF,                 \
    IOTHUB_CLIENT_RETRY_EXPONENTIAL_BACKOFF_WITH_JITTER,                 \
    IOTHUB_CLIENT_RETRY_RANDOM

    /** @brief Enumeration passed in by the IoT Hub when the event confirmation
    *           callback is invoked to indicate status of the event processing in
    *           the hub.
    */
    DEFINE_ENUM(IOTHUB_CLIENT_RETRY_POLICY, IOTHUB_CLIENT_RETRY_POLICY_VALUES);

#define IOTHUBMESSAGE_DISPOSITION_RESULT_VALUES \
    IOTHUBMESSAGE_ACCEPTED, \
    IOTHUBMESSAGE_REJECTED, \
    IOTHUBMESSAGE_ABANDONED

    /** @brief Enumeration returned by the callback which is invoked whenever the
    *           IoT Hub sends a message to the device.
    */
    DEFINE_ENUM(IOTHUBMESSAGE_DISPOSITION_RESULT, IOTHUBMESSAGE_DISPOSITION_RESULT_VALUES);

#define IOTHUB_CLIENT_CONFIRMATION_RESULT_VALUES     \
    IOTHUB_CLIENT_CONFIRMATION_OK,                   \
    IOTHUB_CLIENT_CONFIRMATION_BECAUSE_DESTROY,      \
    IOTHUB_CLIENT_CONFIRMATION_MESSAGE_TIMEOUT,      \
    IOTHUB_CLIENT_CONFIRMATION_ERROR                 \

    /** @brief Enumeration passed in by the IoT Hub when the event confirmation
    *           callback is invoked to indicate status of the event processing in
    *           the hub.
    */
    DEFINE_ENUM(IOTHUB_CLIENT_CONFIRMATION_RESULT, IOTHUB_CLIENT_CONFIRMATION_RESULT_VALUES);

#define IOTHUB_CLIENT_CONNECTION_STATUS_VALUES             \
    IOTHUB_CLIENT_CONNECTION_AUTHENTICATED,                \
    IOTHUB_CLIENT_CONNECTION_UNAUTHENTICATED               \


    /** @brief Enumeration passed in by the IoT Hub when the connection status
    *           callback is invoked to indicate status of the connection in
    *           the hub.
    */
    DEFINE_ENUM(IOTHUB_CLIENT_CONNECTION_STATUS, IOTHUB_CLIENT_CONNECTION_STATUS_VALUES);

#define IOTHUB_CLIENT_CONNECTION_STATUS_REASON_VALUES      \
    IOTHUB_CLIENT_CONNECTION_EXPIRED_SAS_TOKEN,            \
    IOTHUB_CLIENT_CONNECTION_DEVICE_DISABLED,              \
    IOTHUB_CLIENT_CONNECTION_BAD_CREDENTIAL,               \
    IOTHUB_CLIENT_CONNECTION_RETRY_EXPIRED,                \
    IOTHUB_CLIENT_CONNECTION_NO_NETWORK,                   \
    IOTHUB_CLIENT_CONNECTION_COMMUNICATION_ERROR,          \
    IOTHUB_CLIENT_CONNECTION_OK                            \

    /** @brief Enumeration passed in by the IoT Hub when the connection status
    *           callback is invoked to indicate status of the connection in
    *           the hub.
    */
    DEFINE_ENUM(IOTHUB_CLIENT_CONNECTION_STATUS_REASON, IOTHUB_CLIENT_CONNECTION_STATUS_REASON_VALUES);

#define DEVICE_TWIN_UPDATE_STATE_VALUES \
    DEVICE_TWIN_UPDATE_COMPLETE, \
    DEVICE_TWIN_UPDATE_PARTIAL

    DEFINE_ENUM(DEVICE_TWIN_UPDATE_STATE, DEVICE_TWIN_UPDATE_STATE_VALUES);

    typedef void(*IOTHUB_CLIENT_EVENT_CONFIRMATION_CALLBACK)(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback);
    typedef void(*IOTHUB_CLIENT_CONNECTION_STATUS_CALLBACK)(IOTHUB_CLIENT_CONNECTION_STATUS result, IOTHUB_CLIENT_CONNECTION_STATUS_REASON reason, void* userContextCallback);
    typedef IOTHUBMESSAGE_DISPOSITION_RESULT (*IOTHUB_CLIENT_MESSAGE_CALLBACK_ASYNC)(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback);

    typedef void(*IOTHUB_CLIENT_DEVICE_TWIN_CALLBACK)(DEVICE_TWIN_UPDATE_STATE update_state, const unsigned char* payLoad, size_t size, void* userContextCallback);
    typedef void(*IOTHUB_CLIENT_REPORTED_STATE_CALLBACK)(int status_code, void* userContextCallback);
    typedef int(*IOTHUB_CLIENT_DEVICE_METHOD_CALLBACK_ASYNC)(const char* method_name, const unsigned char* payload, size_t size, unsigned char** response, size_t* response_size, void* userContextCallback);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_CLIENT_CORE_COMMON_H */
