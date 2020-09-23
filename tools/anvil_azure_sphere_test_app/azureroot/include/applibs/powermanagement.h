/// file powermanagement.h
/// \brief This header contains functionality for interacting with power management.
/// Access to and control of different kinds of power management is restricted
/// based on the fields of the application's manifest.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <applibs/powermanagement_internal.h>

/// <summary>
///     Asynchronously initiates the process of a forced system reboot.
///
///     Reboot results in the system stopping and resuming execution the same as if it entered
///     system power-down and immediately woke back up.
///
///     Note: Successful return of this routine only indicates the reboot was initiated.
///         In response to invocation of this routine, this application, as well as all others on
///         the system, will receive a SIGTERM, followed by the system rebooting.
///         Due to the asynchronous nature of this request, it is possible that the application
///         receives the SIGTERM before this routine returns.
///
///     **Errors**
///     If an error is encountered, returns -1 and sets errno to the error value.
///         EACCES: access to system reboot is not permitted as the required entry is not listed
///                 in the application manifest.
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <returns>
///     0 for success if the forced system reboot was successfully initiated, or -1 for failure, in
///     which case errno will be set to the error value.
/// </returns>
static int PowerManagement_ForceSystemReboot();

/// <summary>
///     Asynchronously initiates the process of forcing the system to transition to the power-down
///     state for up to maximum_residency_in_seconds amount of time.
///
///     System power down is the lowest power-consuming state the system is capable of entering
///     while still being able to wake from limited external interrupts or automatically after a
///     time-out.
///
///     The time spent in the state may be shorter if an external wakeup interrupt occurs,
///     or if internal system services require system execution sooner than the specified maximum
///     residency.
///
///     Note: Successful return of this routine only indicates the power-down was initiated.
///         In response to invocation of this routine, this application, as well as all others on
///         the system, will receive a SIGTERM, followed by the system powering down.
///         Due to the asynchronous nature of this request, it is possible that the application
///         receives the SIGTERM before this routine returns.
///
///     maximum_residency_in_seconds - the maximum time, in seconds, the system may be resident in
///         this state before transitioning back to active. The actual residency may be shorter than
///         the maximum for the reasons specified in this routine's description.
///
///     **Errors**
///     If an error is encountered, returns -1 and sets errno to the error value.
///         EACCES: access to force system power-down is not permitted as the required entry is not
///                 listed in the application manifest.
///         EINVAL: an invalid value was specified for maximum_residency_in_seconds.
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <returns>
///     0 for success if the forced power-down was successfully initiated, or -1 for failure, in
///     which case errno will be set to the error value.
/// </returns>
static int PowerManagement_ForceSystemPowerDown(unsigned int maximum_residency_in_seconds);

#ifdef __cplusplus
}
#endif
