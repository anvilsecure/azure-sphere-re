/// \file azure_sphere_provisioning.h
/// \brief This file contains functionality related to provisioning an
/// Azure Sphere device to an Azure IoT hub using an Azure Device Provisioning
/// Service instance, and the device's client auth certificate.

#pragma once
#include <azure_prov_client/prov_device_ll_client.h>
#include <azureiot/iothub_device_client_ll.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///     Return codes for provisioning an Azure Sphere device and creating the
///     IoT Hub Device Client connection handle.
/// <summary>
typedef enum {
    /// <summary>Device was succesfully provisioned and connection handle created.</sumary>
    AZURE_SPHERE_PROV_RESULT_OK,
    /// <summary>One or more parameters were invalid.</summary>
    AZURE_SPHERE_PROV_RESULT_INVALID_PARAM,
    /// <summary>Device could not be provisioned as network is not ready.</summary>
    AZURE_SPHERE_PROV_RESULT_NETWORK_NOT_READY,
    /// <summary>Device could not be provisioned as device authentication is not ready.</summary>
    AZURE_SPHERE_PROV_RESULT_DEVICEAUTH_NOT_READY,
    /// <summary>Provisioning failed - check prov_device_error for failure details.</summary>
    AZURE_SPHERE_PROV_RESULT_PROV_DEVICE_ERROR,
    /// <summary>IoT hub device client creation failed - check iothub_client_error for
    /// failure details.</summary>
    AZURE_SPHERE_PROV_RESULT_IOTHUB_CLIENT_ERROR,
    /// <summary>Device provisioning failed for any other reason.</summary>
    AZURE_SPHERE_PROV_RESULT_GENERIC_ERROR
} AZURE_SPHERE_PROV_RESULT;

/// <summary>
///     A struct representing the result of IoTHubDeviceClient_LL_CreateWithAzureSphereDeviceAuthProvisioning.
/// </summary>
typedef struct {
    /// <summary>The result of the provisioning operation.</summary>
    AZURE_SPHERE_PROV_RESULT result;
    /// <summary>If result is AZURE_SPHERE_PROV_RESULT_PROV_DEVICE_ERROR, this will be
    /// set to a PROV_DEVICE_RESULT value.</summary>
    PROV_DEVICE_RESULT prov_device_error;
    /// <summary>If result is AZURE_SPHERE_PROV_RESULT_IOTHUB_CLIENT_ERROR, this will be
    /// set to an IOTHUB_CLIENT_RESULT value.</summary>
    IOTHUB_CLIENT_RESULT iothub_client_error;
} AZURE_SPHERE_PROV_RETURN_VALUE;

/// <summary>
///     Provisions the Azure Sphere device using the provisioning service
///     specified by <paramref name="idScope"/> and creates an IoT hub
///     connection handle.
/// </summary>
/// <param name="idScope">
///     The Azure IoT Device Provisioning Service scope ID for this device.
/// </param>
/// <param name="timeout">
///     Time to wait for provisioning (in milliseconds) before timing out.
///     In the event of a timeout, the result field of the return value will be set
///     to AZURE_SPHERE_PROV_RESULT_PROV_DEVICE_ERROR, and the prov_device_error
///     will be PROV_DEVICE_RESULT_TIMEOUT.
/// </param>
/// <param name="handle">
///     (output) On success, the IoT Hub connection handle. On failure, this will be set to
///     NULL
/// </param>
/// <returns>
///     Returns an <see cref="AZURE_SPHERE_PROV_RETURN_VALUE" />. On success, result
///     will be AZURE_SPHERE_PROV_RESULT_OK.
///     On failure, result will be set to an error code indicating the reason for failure.
///     If result is AZURE_SPHERE_PROV_RESULT_PROV_DEVICE_ERROR, prov_device_error will be set to
///     a PROV_DEVICE_RESULT value indicating the reason.
///     If result is AZURE_SPHERE_PROV_RESULT_IOTHUB_CLIENT_ERROR, iothub_client_error will be
///     set to an IOTHUB_CLIENT_RESULT value indicating the reason.
/// </returns>
AZURE_SPHERE_PROV_RETURN_VALUE IoTHubDeviceClient_LL_CreateWithAzureSphereDeviceAuthProvisioning(
        const char* idScope, unsigned int timeout,
        IOTHUB_DEVICE_CLIENT_LL_HANDLE* handle);

#ifdef __cplusplus
}
#endif
