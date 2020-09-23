/// \file mt3620_i2c.h
/// \brief This header lists the available I2C master interfaces for a MT3620 device.
#pragma once

// To use one of these interfaces as an I2C master, you will need to specify e.g. "ISU0" in the
// app_manifest.json 'I2cMaster' capabilities array.
#define MT3620_I2C_ISU0 (0)
#define MT3620_I2C_ISU1 (1)
#define MT3620_I2C_ISU2 (2)
#define MT3620_I2C_ISU3 (3)
#define MT3620_I2C_ISU4 (4)
