#pragma once

#include <sys/ioctl.h>
#include <stdint.h>

typedef enum {
    AZURE_SPHERE_DEFAULT_LOG_STORAGE = 0,
    AZURE_SPHERE_TELEMETRY_LOG_STORAGE = 1
} azure_sphere_log_storage_type;

struct azure_sphere_get_log_data {
    // Offset into the data
    uint32_t offset;
    // Buffer to load to
    void *buffer;
    // Size of buffer
    uint32_t buffer_size;
    // Total size to read
    uint32_t total_size;
    // Storage to read from
    azure_sphere_log_storage_type storage_type;
};

struct azure_sphere_write_log_data {
    // Data size
    uint32_t size;
    // Data to write
    const void *data;
};

struct azure_sphere_enable_peripheral_driver {
    // type of peripheral
    uint16_t peripheral_type;
    // logical index of peripheral instance
    uint16_t peripheral_index;
    // enable or disable?
    uint16_t enable;
};


enum azure_sphere_peripheral_type {
    AZURE_SPHERE_INVALID = 0,
    AZURE_SPHERE_GPIO = 1,
    AZURE_SPHERE_PWM = 2,
    AZURE_SPHERE_INT = 3,
    AZURE_SPHERE_UART = 4,
    AZURE_SPHERE_SPI_MASTER = 5,
    AZURE_SPHERE_I2C_MASTER = 6,
    AZURE_SPHERE_ADC = 7,
    AZURE_SPHERE_I2S_SLAVE = 8,
};



#define SECURITY_MONITOR_WRITE_LOG _IOWR('p', 0x02, struct azure_sphere_write_log_data)
#define SECURITY_MONITOR_GET_LOG_DATA _IOWR('p', 0x03, struct azure_sphere_get_log_data)
#define SECURITY_MONITOR_SMAPI_COMMAND _IOWR('p', 0x04, struct azure_sphere_smapi_command_request)
#define SECURITY_MONITOR_DERIVE_KEY _IOWR('p', 0x05, struct azure_sphere_derive_key)
// 0x06 - 0x08 are reserved
#define SECURITY_MONITOR_ENABLE_PERIPHERAL_DRIVER _IOWR('p', 0x09, struct azure_sphere_enable_peripheral_driver)
#define SECURITY_MONITOR_IO_CORE_CONTROL _IOWR('p', 0x0A, struct azure_sphere_io_core_control)
#define SECURITY_MONITOR_RECORD_TELEMETRY_EVENT_DATA _IOW('p', 0x0B, struct azure_sphere_telemetry_record_event_data)
#define SECURITY_MONITOR_GET_TELEMETRY _IOWR('p', 0x0C, struct azure_sphere_get_telemetry)
#define SECURITY_MONITOR_RESET_RETAIN_TELEMETRY _IOW('p', 0x0D, struct azure_sphere_reset_retain_telemetry)
