#pragma once

#include <stdint.h>

#define _LINUX_CAPABILITY_VERSION_1  0x19980330
#define _LINUX_CAPABILITY_U32S_1     1

        /* V2 added in Linux 2.6.25; deprecated */
#define _LINUX_CAPABILITY_VERSION_2  0x20071026
#define _LINUX_CAPABILITY_U32S_2     2

        /* V3 added in Linux 2.6.26 */
#define _LINUX_CAPABILITY_VERSION_3  0x20080522
#define _LINUX_CAPABILITY_U32S_3     2

typedef struct __user_cap_header_struct {
    uint32_t version;
    int pid;
} *cap_user_header_t;

typedef struct __user_cap_data_struct {
    uint32_t effective;
    uint32_t permitted;
    uint32_t inheritable;
} *cap_user_data_t;

int capget(cap_user_header_t hdrp, cap_user_data_t datap);
int capset(cap_user_header_t hdrp, const cap_user_data_t datap);
