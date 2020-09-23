/// \file powermanagement_internal.h
/// \brief This header contains internal functions for the PowerManagement library.
#pragma once

#include <stddef.h>
#include <stdint.h>

#include <applibs/applibs_internal_api_traits.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///     Defines the set of possible power management states the system can be placed into.
///
///     Note: A PowerManagement_System_PowerState enum beginning with the prefix "Force" indicates
///     that the system will override any deferral, immediately sending a SIGTERM to running apps,
///     then proceeding to the power state.
/// </summary>
typedef uint32_t PowerManagement_System_PowerState;
enum {
    /// <summary>
    /// The forced version of the Reboot system power state. This state results in the system
    /// stopping and resuming execution the same as if it entered
    /// PowerManagement_System_PowerState_ForcePowerDown and immediately woke back up.
    /// Requires an app to have the "ForceReboot" value in the PowerControls manifest capability.
    /// </summary>
    PowerManagement_System_PowerState_ForceReboot,

    /// <summary>
    /// The forced version of the Power Down system power state. Power Down is the lowest
    /// power-consuming state the system is capable of entering while still being able
    /// to wake from limited external interrupts or from an RTC alarm.
    /// Requires an app to have the "ForcePowerDown" value in the PowerControls manifest capability.
    /// </summary>
    PowerManagement_System_PowerState_ForcePowerDown
};

/// <summary>
///     The struct containing the parameters for the transition to the PowerDown state.
///
///     maximum_residency_in_seconds - the maximum time, in seconds, the system may be resident in
///     this state before transitioning back to active. The actual residency may be shorter than
///     the maximum if a wake event occurs sooner.
/// </summary>
struct z__PowerManagement_PowerDownStateTransitionParams {

    // <summary>
    //      The maximum number of seconds the system should remain in the power-down state.
    // </summary>
    unsigned int maximum_residency_in_seconds;
};

/// <summary>
///     Initiates a transition to the specified power state.
///     Depending on the system state requested, entry may not have occurred when this routine
///     returns; instead notification of entry into the state occurs via the Event Loop framework
///     in the same manner as device updates.
///
///     type - the system power state to transition to.
///
///     power_state_transition_params_ptr - a pointer to the struct containing the necessary
///         parameters for the given PowerManagement_System_PowerState type
///         (i.e. z__PowerManagement_PowerDownStateTransitionParams).
///
///     **Errors**
///     If an error is encountered, returns -1 and sets errno to the error value.
///         EACCES: access to <paramref name="state"/> is not permitted as the required entry is
///         not listed in the application manifest.
///         EINVAL: the <paramref name="state"/> is invalid or the
///              <paramref name="power_state_transition_params_ptr"/> contain invalid data.
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <returns>
///     Zero on success, or -1 for failure, in which case errno will
///     be set to the error value.
/// </returns>
int z__PowerManagement_TransitionToSystemPowerState(PowerManagement_System_PowerState type,
                                                    void *power_state_transition_params_ptr);

static inline int PowerManagement_ForceSystemReboot()
{
    return z__PowerManagement_TransitionToSystemPowerState(
        PowerManagement_System_PowerState_ForceReboot, NULL);
}

static inline int PowerManagement_ForceSystemPowerDown(unsigned int maximum_residency_in_seconds)
{
    struct z__PowerManagement_PowerDownStateTransitionParams params;
    params.maximum_residency_in_seconds = maximum_residency_in_seconds;

    return z__PowerManagement_TransitionToSystemPowerState(
        PowerManagement_System_PowerState_ForcePowerDown, (void *)&params);
}

#ifdef __cplusplus
}
#endif
