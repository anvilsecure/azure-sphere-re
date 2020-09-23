/// \file mt3620_spi.h
/// \brief This header lists the available SPI interfaces for a MT3620 device.
#pragma once

// To use one of these interfaces as a SPI master, you will need to specify e.g. "ISU0" in the
// app_manifest.json 'SpiMaster' capabilities array.
#define MT3620_SPI_ISU0 (0)
#define MT3620_SPI_ISU1 (1)
#define MT3620_SPI_ISU2 (2)
#define MT3620_SPI_ISU3 (3)
#define MT3620_SPI_ISU4 (4)

#define MT3620_SPI_CHIP_SELECT_A (-1)
#define MT3620_SPI_CHIP_SELECT_B (-2)
