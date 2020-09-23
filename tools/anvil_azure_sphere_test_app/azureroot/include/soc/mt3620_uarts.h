/// \file mt3620_uarts.h
/// \brief This header lists the available UARTs for a MT3620 device.
#pragma once

#include <applibs/uart.h>

// To use one of these UARTs, you will need to specify e.g. "ISU0" in the app_manifest.json Uart
// capabilities array.
#define MT3620_UART_ISU0 ((UART_Id)4)
#define MT3620_UART_ISU1 ((UART_Id)5)
#define MT3620_UART_ISU2 ((UART_Id)6)
#define MT3620_UART_ISU3 ((UART_Id)7)
#define MT3620_UART_ISU4 ((UART_Id)8)
