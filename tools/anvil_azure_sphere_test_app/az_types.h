#pragma once

#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uint8_t bool;

struct azure_sphere_guid {
    u32 data1;
    u16 data2;
    u16 data3;
    u8 data4[8];
};

struct azure_sphere_task_cred {
    union {
        u8     raw_bytes[16];
        struct azure_sphere_guid guid;
    } component_id;
    char   daa_tenant_id[64];
    bool   is_app_man : 1;
    bool   job_control_allowed : 1;
    unsigned int : 0;
    u32 capabilities;
};
