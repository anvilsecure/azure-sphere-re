/// \file networking.h
/// \brief This header contains functions and types that interact with the networking subsystem to
/// query the network state, and to get and set the network service configuration.
///
/// The function summaries include any required application manifest settings.
///
/// The default version of the networking structs(NETWORKING_STRUCTS_VERSION) is 1. Currently this
/// is the only valid version. These functions are not thread safe.
#pragma once

#include <stdbool.h>
#include <applibs/networking_structs_v1.h>

// Default the NETWORKING_STRUCTS_VERSION version to 1
#ifndef NETWORKING_STRUCTS_VERSION
#define NETWORKING_STRUCTS_VERSION 1
#endif

#if NETWORKING_STRUCTS_VERSION == 1
/// <summary>
///     Alias to the z__Networking_NetworkInterface_v1 structure. After you define
///     NETWORKING_STRUCTS_VERSION, you can refer to z__Networking_NetworkInterface_v1
///     structures with this alias.
/// </summary>
typedef struct z__Networking_NetworkInterface_v1 Networking_NetworkInterface;

#else // NETWORKING_STRUCTS_VERSION
#error NETWORKING_STRUCTS_VERSION is set to an unsupported value. Only version 1 is currently supported.
#endif // NETWORKING_STRUCTS_VERSION

#include <applibs/networking_internal.h>
#include <applibs/applibs_internal_api_traits.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///     Verifies whether networking is ready and time is synced.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the provided <paramref name="outIsNetworkingReady"/> parameter is NULL.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outIsNetworkingReady">
///      A pointer to a boolean that returns the result. The return value is true if:
///      - the network interface, e.g. wlan0 or eth0 is enabled
///      - the interface is connected to a networking access point, e.g. Wi-Fi access point
///        or Ethernet router,
///      - the interface has obtained an IP address, and
///      - the device time is synced.
///      Otherwise, return false.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_IsNetworkingReady(bool *outIsNetworkingReady);

/// <summary>
///     A bit mask that specifies the connection status of a network interface.
/// </summary>

typedef uint32_t Networking_InterfaceConnectionStatus;
enum {
    /// <summary>The interface is enabled.</summary>
    Networking_InterfaceConnectionStatus_InterfaceUp = 1 << 0,
    /// <summary>The interface is connected to a network.</summary>
    Networking_InterfaceConnectionStatus_ConnectedToNetwork = 1 << 1,
    /// <summary>The interface has an IP address assigned to it.</summary>
    Networking_InterfaceConnectionStatus_IpAvailable = 1 << 2,
    /// <summary>The interface is connected to the internet.</summary>
    Networking_InterfaceConnectionStatus_ConnectedToInternet = 1 << 3
};

/// <summary>
///     Gets the number of network interfaces in the Azure Sphere device.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <returns>
///     The number of network interfaces, or -1 for failure, in which case errno is set to the error
///     value.
/// </returns>
ssize_t Networking_GetInterfaceCount(void);

/// <summary>
///     Gets the list of network interfaces in the Azure Sphere device. If
///     <paramref name="outNetworkInterfaces"/> is too small to hold all network interfaces in the
///     system, this function fills the array and returns the number of array elements. The number
///     of interfaces in the system will not change within a boot cycle.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outNetworkInterfacesArray"/> parameter is NULL.</para>
///     <para>ERANGE: the <paramref name="networkInterfacesArrayCount"/> parameter is 0.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outNetworkInterfacesArray">
///      A pointer to an array of <see cref="Networking_NetworkInterface"/> structs to fill with
///      network interface properties. The caller must allocate memory for the array after calling
///      Networking_GetInterfacesCount to retrieve the number of interfaces on the device.
/// </param>
/// <param name="networkInterfacesArrayCount">
///      The number of elements <paramref name="outNetworkInterfacesArray"/> can hold.
/// </param>
/// <returns>
///     The number of network interfaces added to <paramref name="outNetworkInterfacesArray"/>.
///     Otherwise -1 for failure, in which case errno is set to the error value.
/// </returns>
static ssize_t Networking_GetInterfaces(Networking_NetworkInterface *outNetworkInterfacesArray,
                                        size_t networkInterfacesArrayCount);

/// <summary>
///     Enables or disables a network interface. The application manifest must include the
///     NetworkConfig capability.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the NetworkConfig capability.</para>
///     <para>ENOENT: the network interface does not exist.</para>
///     <para>EPERM: this function is not allowed on the interface.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The name of the network interface to update.
/// </param>
/// <param name="isEnabled">
///      true to enable the interface, false to disable it.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_SetInterfaceState(const char *networkInterfaceName, bool isEnabled);

/// <summary>
///     Initializes a <see cref="Networking_IpConfig"/> struct with the default IP
///     configuration. The default IP configuration enables dynamic IP.
/// </summary>
/// <remarks>
///     When the <see cref="Networking_IpConfig"/> struct is no longer needed, the
///     <see cref="Networking_IpConfig_Destroy"/> function must be called on the struct to avoid
///     resource leaks.
/// </remarks>
/// <param name="ipConfig">
///     A pointer to the <see cref="Networking_IpConfig"/> struct that receives the default IP
///     configuration.
/// </param>
void Networking_IpConfig_Init(Networking_IpConfig *ipConfig);

/// <summary>
///     Destroys a <see cref="Networking_IpConfig"/> struct.
/// </summary>
/// <remarks>It's unsafe to call <see cref="Networking_IpConfig_Destroy"/> on a struct that hasn't
///     been initialized. After <see cref="Networking_IpConfig_Destroy"/> is called, the
///     <see cref="Networking_IpConfig"/> struct must not be used until it is re-initialized
///     with the <see cref="Networking_IpConfig_Init"/> function.
/// </remarks>
/// <param name="ipConfig">
///     A pointer to the <see cref="Networking_IpConfig"/> struct to destroy.
/// </param>
void Networking_IpConfig_Destroy(Networking_IpConfig *ipConfig);

/// <summary>
///     Enables dynamic IP and disables static IP for a <see cref="Networking_IpConfig"/> struct.
/// </summary>
/// <param name="ipConfig">
///     A pointer to the <see cref="Networking_IpConfig"/> struct to update.
/// </param>
void Networking_IpConfig_EnableDynamicIp(Networking_IpConfig *ipConfig);

/// <summary>
///     Enables static IP and disables dynamic IP for a <see cref="Networking_IpConfig"/> struct.
/// </summary>
/// <param name="ipConfig">
///     A pointer to the <see cref="Networking_IpConfig"/> struct to update.
/// </param>
/// <param name="ipAddress"> The static IP address. </param>
/// <param name="subnetMask"> The static subnet mask. </param>
/// <param name="gatewayAddress"> The static gateway address. </param>
void Networking_IpConfig_EnableStaticIp(Networking_IpConfig *ipConfig, struct in_addr ipAddress,
                                        struct in_addr subnetMask, struct in_addr gatewayAddress);

/// <summary>
///     Applies an IP configuration to a network interface. The application manifest must include
///     the NetworkConfig capability.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the calling application doesn't have the NetworkConfig capability.</para>
///     <para>ENOENT: the <paramref name="networkInterfaceName"/> parameter refers to an interface
///     that does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EFAULT: the <paramref name="networkInterfaceName"/> or <paramref name="ipConfig"/>
///      parameter is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     <para>EFBIG: out of space to store the configuration.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behavior will be retained through system updates.
/// </summary>
/// <remarks>
///     <para>This function does not verify whether the static IP address is compatible with the
///     dynamic IP addresses received through an interface using a DHCP client.</para>
///     <para>This function does not verify whether a DHCP server is available on the network and if
///     a dynamic IP address is configured.</para>
///     <para>If overlapping IP address configurations are present on a device, the behavior of this
///     function is undefined.</para>
/// </remarks>
/// <param name="networkInterfaceName">
///      The name of the interface to configure.
/// </param>
/// <param name="ipConfig">
///      The pointer to the <see cref="Networking_IpConfig" /> struct that contains the IP
///      configuration to apply.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_IpConfig_Apply(const char *networkInterfaceName,
                              const Networking_IpConfig *ipConfig);

/// <summary>
///     Enables or disables the time-sync service.
///     <para>The changes take effect immediately without a device reboot and persist through device
///     reboots. The time-sync service is then configured as requested at boot time. This function
///     allows applications to override the default behavior, which is to enable time-sync at boot
///     time.</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the calling application doesn't have the TimeSyncConfig capability.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="enabled">
///      true to enable the time-sync service; false to disable it.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_TimeSync_SetEnabled(bool enabled);

/// <summary>
///     Indicates whether the time-sync service is enabled. The application manifest must include
///     the TimeSyncConfig capability.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outIsEnabled"/> parameter provided is null.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outIsEnabled">
///      A pointer to a boolean value that receives the state of the time-sync service. The value
///      is set to true if the time-sync service is enabled, otherwise false.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_TimeSync_GetEnabled(bool *outIsEnabled);

/// <summary>
///     Gets the network connection status for a network interface.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outStatus"/> parameter is NULL.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName"/> interface does not exist.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The name of the network interface.
/// </param>
/// <param name="outStatus">
///      A pointer to the <see cref="Networking_InterfaceConnectionStatus"/> enum that receives the
///      network connection status.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_GetInterfaceConnectionStatus(const char *networkInterfaceName,
                                            Networking_InterfaceConnectionStatus *outStatus);

/// <summary>
///     Initializes a <see cref="Networking_SntpServerConfig"/> struct with the default SNTP
///     Server configuration.
/// </summary>
/// <remarks>
///     When the <see cref="Networking_SntpServerConfig"/> struct is no longer needed, the
///     <see cref="Networking_SntpServerConfig_Destroy"/> function must be called on the struct to
///     avoid resource leaks.
/// </remarks>
/// <param name="sntpServerConfig">
///     A pointer to the <see cref="Networking_SntpServerConfig"/> struct that receives the
///     default SNTP server configuration.
/// </param>
void Networking_SntpServerConfig_Init(Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Destroys a <see cref="Networking_SntpServerConfig"/> struct.
/// </summary>
/// <remarks>
///     It's unsafe to call <see cref="Networking_SntpServerConfig_Destroy"/> on a struct that
///     hasn't been initialized. After <see cref="Networking_SntpServerConfig_Destroy"/> is called,
///     the <see cref="Networking_SntpServerConfig"/> struct must not be used until it is
///     re-initialized with the <see cref="Networking_SntpServerConfig_Init"/> function.
/// </remarks>
/// <param name="sntpServerConfig">
///     A pointer to the <see cref="Networking_SntpServerConfig"/> struct to destroy.
/// </param>
void Networking_SntpServerConfig_Destroy(Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Registers an SNTP server for a network interface. The application manifest must include the
///     SntpService capability.
///     <remarks>
///     If the SNTP server is already running and attached to the interface, this function returns
///     success. If the <see cref="networkInterfaceName"/> interface is down or disabled, this
///     function registers the SNTP server for the interface without starting the server.
///     </remarks>
///     <para>**Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the calling application doesn't have the SntpService capability.</para>
///     <para>EFAULT: the <paramref name="networkInterfaceName"/> parameter is NULL.</para>
///     <para>EFAULT: the <paramref name="sntpServerConfig"/> parameter is NULL.</para>
///     <para>ENOENT: the <paramref name="networkInterfaceName"/> parameter refers to an interface
///     that does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The name of the network interface to configure.
/// </param>
/// <param name="sntpServerConfig">
///      The pointer to the <see cref="Networking_SntpServerConfig"/> struct that represents the
///      SNTP server configuration.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_SntpServer_Start(const char *networkInterfaceName,
                                const Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Initializes a <see cref="Networking_DhcpServerConfig"/> struct with the default DHCP
///     server configuration.
/// </summary>
/// <remarks>
///     When the <see cref="Networking_DhcpServerConfig"/> struct is no longer needed, the
///     <see cref="Networking_DhcpServerConfig_Destroy"/> function must be called on the struct to
///     avoid resource leaks.
/// </remarks>
/// <param name="dhcpServerConfig">
///     A pointer to the <see cref="Networking_DhcpServerConfig"/> struct that receives the
///     default DHCP server configuration.
/// </param>
void Networking_DhcpServerConfig_Init(Networking_DhcpServerConfig *dhcpServerConfig);

/// <summary>
///     Destroys a <see cref="Networking_DhcpServerConfig"/> struct.
/// </summary>
/// <remarks>
///     It's unsafe to call <see cref="Networking_DhcpServerConfig_Destroy"/> on a struct that
///     hasn't been initialized. After <see cref="Networking_DhcpServerConfig_Destroy"/> is called,
///     the <see cref="Networking_DhcpServerConfig"/> struct must not be used until it is
///     re-initialized with the <see cref="Networking_DhcpServerConfig_Init"/> function.
/// </remarks>
/// <param name="dhcpServerConfig">
///     A pointer to the <see cref="Networking_DhcpServerConfig"/> struct to destroy.
/// </param>
void Networking_DhcpServerConfig_Destroy(Networking_DhcpServerConfig *dhcpServerConfig);

/// <summary>
///     Applies lease information to a <see cref="Networking_DhcpServerConfig"/> struct.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> parameter is NULL.</para>
///     <para>EINVAL: the parameter values are invalid or conflict with each other.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to the <see cref="Networking_DhcpServerConfig"/> struct to update.
/// </param>
/// <param name="startIpAddress">The starting IP address in the address range to lease.</param>
/// <param name="ipAddressCount">The number of IP addresses the server can lease.</param>
/// <param name="subnetMask">The subnet mask for the IP addresses.</param>
/// <param name="gatewayAddress">The gateway address for the network interface.</param>
/// <param name="leaseTimeInHours">The duration of the lease, in hours.</param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServerConfig_SetLease(Networking_DhcpServerConfig *dhcpServerConfig,
                                         struct in_addr startIpAddress, uint8_t ipAddressCount,
                                         struct in_addr subnetMask, struct in_addr gatewayAddress,
                                         uint32_t leaseTimeInHours);

/// <summary>
///     Applies a set of NTP server IP addresses to a <see cref="Networking_DhcpServerConfig"/>
///     struct.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> parameter is NULL.</para>
///     <para>EFAULT: the <paramref name="ntpServerAddresses"/> parameter is NULL.</para>
///     <para>EINVAL: more than three IP addresses were provided or the addresses are
///     invalid.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to the <see cref="Networking_DhcpServerConfig"/> struct to update.
/// </param>
/// <param name="ntpServerAddresses">A pointer to an array of NTP server IP addresses.</param>
/// <param name="serverCount">The number of IP addresses in the
///     <paramref name="ntpServerAddresses"/> array.</param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServerConfig_SetNtpServerAddresses(Networking_DhcpServerConfig *dhcpServerConfig,
                                                      const struct in_addr *ntpServerAddresses,
                                                      size_t serverCount);

/// <summary>
///     Registers, configures, and starts the DHCP server for a network interface. The configuration
///     specified by this function call overwrites the existing configuration. The application
///     manifest must include the DhcpService capability.
/// <remarks>
///     <para>If the network interface is up when this function is called, the DHCP server will be
///     shut down, configured, and started. If the interface is down, the server will start when the
///     interface is up.</para>
///     <para>The interface must be configured with a static IP address before this function is
///     called; otherwise, the EPERM error is returned.</para>
/// </remarks>
///     <para> **Errors** </para> If an error is encountered, returns -1 and sets errno to the error
///     value.
///     <para>EACCES: the application manifest does not include the DhcpService capability.</para>
///     <para>ENOENT: the <paramref name="networkInterfaceName"/> parameter refers to an interface
///     that does not exist.</para>
///     <para>EPERM:  the operation is not allowed on the network interface.</para>
///     <para>EFAULT: the <paramref name="networkInterfaceName"/> parameter is NULL.</para>
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> parameter is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready.</para>
///     <para>EINVAL: the configuration struct has invalid parameters.</para>
///     <para>EFBIG: out of space to store the configuration.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The name of the network interface to configure.
/// </param>
/// <param name="dhcpServerConfig">
///      The pointer to the <see cref="Networking_DhcpServerConfig"/> struct that represents the
///      DHCP server configuration
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServer_Start(const char *networkInterfaceName,
                                const Networking_DhcpServerConfig *dhcpServerConfig);

#ifdef __cplusplus
}
#endif
