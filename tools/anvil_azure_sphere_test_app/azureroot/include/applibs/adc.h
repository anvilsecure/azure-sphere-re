/// \file adc.h
/// \brief This header contains functionality for interacting with Industrial ADC devices/channels.
/// Access to individual ADC channels is restricted based on the Adc field of the application's
/// manifest.
///
/// ADC functions are thread-safe when accessing different ADC channels concurrently. However, the
/// caller must ensure thread safety when accessing the same ADC channel.
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif
