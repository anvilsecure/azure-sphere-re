/// \file networking_internal.h
/// \brief This header contains internal functions of the Networking API and should not be included
/// directly; include applibs/networking.h instead.
#pragma once

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///    Version support info for the Networking_NetworkInterface structs. Refer to
///    Networking_NetworkInterface and the appropriate networking_structs_v[n].h header for actual
///    struct fields.
/// </summary>
struct z__Networking_NetworkInterface_Base {
    /// <summary>Internal version field.</summary>
    uint32_t z__magicAndVersion;
};

/// <summary>
///    A magic value that provides version support for the Networking_NetworkInterface struct.
/// </summary>
#define z__NETWORKING_NETWORK_INTERFACE_STRUCT_MAGIC 0xfa9a0000

/// <summary>
///    Adds struct version support to Networking_GetInterfaces. Do not use this directly; use
///    Networking_GetInterfaces instead.
/// </summary>
/// <param name="outNetworkInterfacesArray">
///     A pointer to a Networking_NetworkInterface structure that is type cast to
///     z__Networking_NetworkInterface_Base.
/// </param>
/// <param name="networkInterfacesArrayCount">
///     The number of elements in the outNetworkInterfacesArray.
/// </param>
/// <param name="networkInterfaceStructVersion">
///     The version of the network interface structure.
/// </param>
/// <returns>
///     If the call is successful, the number of network interfaces populated in the <paramref
///     name="outNetworkInterfacesArray"/> is returned. On failure, -1 is returned, in which case
///     errno is set to the error value.
/// </returns>
ssize_t z__Networking_GetInterfaces(
    struct z__Networking_NetworkInterface_Base *outNetworkInterfacesArray,
    size_t networkInterfacesArrayCount, uint32_t networkInterfaceStructVersion);

/// <summary>
///     Gets the list of registered network interfaces in the Azure Sphere device. If <paramref
///     name="outNetworkInterfacesArray"/> is too small to hold all network interfaces in the
///     system, this function uses the available space and returns the total number of interfaces
///     it is able to provide. The number of interfaces in the system will not change within a boot
///     cycle.
///      <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outNetworkInterfacesArray"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="networkInterfacesArrayCount"/> is 0.</para>
///     Any other errno may be specified; such errors aren't deterministic and
///     there's no guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outNetworkInterfacesArray">
///      A pointer to the array, <see cref="Networking_NetworkInterface"/> to populate with
///      network interface properties. The caller needs to allocate memory for this after calling
///      <see cref="Networking_GetInterfacesCount" /> to find out the number of interfaces.
/// </param>
/// <param name="networkInterfacesArrayCount">
///      The number of elements <paramref name="outNetworkInterfacesArray"/> can hold. The array
///      should have one element for each network interface in the device.
/// </param>
/// <returns>
///     If the call is successful, the number of network interfaces populated in the <paramref
///     name="outNetworkInterfacesArray"/> is returned. On failure, -1 is returned, in which case
///     errno is set to the error value.
/// </returns>
static inline ssize_t Networking_GetInterfaces(
    Networking_NetworkInterface *outNetworkInterfacesArray, size_t networkInterfacesArrayCount)
{
    return z__Networking_GetInterfaces(
        (struct z__Networking_NetworkInterface_Base *)outNetworkInterfacesArray,
        networkInterfacesArrayCount, NETWORKING_STRUCTS_VERSION);
}

#ifdef __cplusplus
}
#endif
