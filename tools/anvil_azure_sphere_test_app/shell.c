#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "string_util.h"
#include "sm.h"
#include "az_types.h"
#include "my_libc.h"

#include <applibs/storage.h>

#define MAX_CMD_TOKENS  20

void help(int argc, char **argv);
void busybox(int argc, char **argv);
void handle_peripheral(int argc, char **argv);
void handle_localfile(int argc, char **argv);
void handle_creds(int argc, char **argv);
void handle_caps(int argc, char **argv);
void handle_azspio(int argc, char **argv);

struct Command {
    const char *name;
    const char *help;
    void (*handler)(int, char **);
};

struct Command g_cmds[] = {
    {
        "help",
        "Displays commands and descriptions",
        help
    },
    {
        "busybox",
        "Execs a busybox ash shell (no pty, so no prompt and no ^C or ^Z)",
        busybox
    },
    {
        "peripheral",
        "Calls the security-manager to enable/disable peripherals",
        handle_peripheral
    },
    {
        "local_file",
        "Reads/Writes/Deletes the local mutable file",
        handle_localfile
    },
    {
        "creds",
        "Reads and displays the cred information at /proc/self/attr/exec",
        handle_creds
    },
    {
        "caps",
        "Looks up the capability bits for a given pid",
        handle_caps
    },
    {
        "azspio",
        "Some simple tests on an azspio socket",
        handle_azspio
    },
    {
        NULL,
        NULL,
        NULL
    }
};

void run_shell(void) {
    printf("\n");
    printf("=========================================\n");
    printf("Welcome to Anvil's Azure Sphere Test App!\n");
    printf("=========================================\n");

    while (1) {
        char cmd[512];
        char *argv[MAX_CMD_TOKENS];
        int argc;

        printf("> ");
        // lets read in the command
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            // connection probably closed
            exit(-1);
        }
        // tokenize it
        argc = string_tokenize(cmd, argv, MAX_CMD_TOKENS, WHITESPACE);
        if (argc > 0) {
            struct Command *cmd;
            for(cmd = g_cmds; cmd->name != NULL; cmd++) {
                if (strcmp(cmd->name, argv[0]) == 0) {
                    break;
                }
            }
            if (cmd->name != NULL) {
                cmd->handler(argc, argv);
            } else {
                printf("Unknown command: %s\n", argv[0]);
            }
        } else {
            printf("No command...\n");
        }
    }
}

void help(int argc, char **argv) {
    for(struct Command *cmd = g_cmds; cmd->name != NULL; cmd++) {
        printf("%s - %s\n", cmd->name, cmd->help);
    }
}

void busybox(int argc, char **argv) {
    int r = execl(
                "/mnt/apps/61ae5c57-98cd-4a0a-8b60-9509505c7617/bin/busybox",
                "ash",
                NULL);
    perror("Failed to exec the busybox shell");
}

void handle_peripheral(int argc, char **argv) {
    int sm_fd = open("/dev/security-monitor", O_RDWR);
    if (sm_fd < 0) {
        perror("Failed to open security-monitor");
        return;
    }

    if (argc == 2 && strcmp(argv[1], "all") == 0) {
        struct azure_sphere_enable_peripheral_driver perf_enable;
        uint16_t valid_perfs[] = {AZURE_SPHERE_UART, AZURE_SPHERE_I2C_MASTER, AZURE_SPHERE_SPI_MASTER, AZURE_SPHERE_PWM, AZURE_SPHERE_ADC, 0};
        perf_enable.enable = 1;
        for (uint16_t i = 0; valid_perfs[i] != 0; i++) {
            for (uint16_t j = 0; j < 20; j++) {
                perf_enable.peripheral_type = valid_perfs[i];
                perf_enable.peripheral_index = j;
                if (ioctl(sm_fd, SECURITY_MONITOR_ENABLE_PERIPHERAL_DRIVER, &perf_enable) < 0) {
                    // shell_send_error("Failed to set %d:%d to %d", perf_enable.peripheral_type, perf_enable.peripheral_index, perf_enable.enable);
                } else {
                    printf("set %d:%d to %d\n", perf_enable.peripheral_type, perf_enable.peripheral_index, perf_enable.enable);
                }
            }
        }
    } else if (argc >= 3) {
        int type = atoi(argv[1]);
        int index = atoi(argv[2]);

        struct azure_sphere_enable_peripheral_driver perf_enable;

        perf_enable.peripheral_type = atoi(argv[1]);
        perf_enable.peripheral_index = atoi(argv[2]);
        perf_enable.enable = (argc >= 4) ? atoi(argv[3]) : 1;

        if (ioctl(sm_fd, SECURITY_MONITOR_ENABLE_PERIPHERAL_DRIVER, &perf_enable) < 0) {
            perror("Failed to set peripheral enable");
        }
    } else {
        printf("Usage: %s all\n", argv[0]);
        printf("Usage: %s <type> <index> (0|1)\n", argv[0]);
    }


    close(sm_fd);
}

void handle_localfile(int argc, char **argv) {

    if (argc == 2 && strcmp(argv[1], "read") == 0) {
        int fd = Storage_OpenMutableFile();
        char data[100];

        while(1) {
            int len = read(fd, data, sizeof(data));
            if (len <= 0) {
                break;
            }
            write(0, data, len);
        }

        close(fd);

    } else if (argc >= 3 && strcmp(argv[1], "write") == 0) {
        int fd = Storage_OpenMutableFile();
        char data[100];

        for(int i = 2; i < argc; i++) {
            write(fd, argv[i], strlen(argv[i]));
            write(fd, " ", 1);
        }

        close(fd);
    } else if (argc == 2 && strcmp(argv[1], "delete") == 0) {
        Storage_DeleteMutableFile();
    } else if (argc == 2 && strcmp(argv[1], "path") == 0) {
        int fd = Storage_OpenMutableFile();
        char path[512];
        
        sprintf(path, "/proc/self/fd/%d", fd);

        if (readlink(path, path, sizeof(path)) < 0) {
            perror("Failed to read proc entry for the fd");
        } else {
            printf("%s\n", path);
        }

        close(fd);
    } else {
        printf("Usage: %s read\n", argv[0]);
        printf("Usage: %s write data\n", argv[0]);
        printf("Usage: %s delete\n", argv[0]);
        printf("Usage: %s path\n", argv[0]);
        return;
    } 
}

void handle_creds(int argc, char **argv) {
    struct azure_sphere_task_cred creds;

    int fd = open("/proc/self/attr/exec", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /proc/self/attr/exec");
        return;
    }

    int read_bytes = read(fd, &creds, sizeof(creds));
    if (read_bytes != sizeof(creds)) {
        printf("Warning... only read %d of expected %d bytes, the following data is probably not complete.", read_bytes, sizeof(creds));
    } else if (read_bytes < 0) {
        perror("Failed to read from the /proc/self/attr/exec file");
        close(fd);
        return;
    }

    printf("azure sphere creds:\n");
    printf("\tGUID: ");
    print_guid(&creds.component_id.guid);
    printf("\n");
    printf("\tdaa_tenant_id: ");
    print_hex((void*)creds.daa_tenant_id, sizeof(creds.daa_tenant_id));
    printf("\n");
    printf("\tis_app_man: %d\n", creds.is_app_man);
    printf("\tjob_control_allowed: %d\n", creds.job_control_allowed);
    printf("\tcapabilities: 0x%08x\n", creds.capabilities);
    close(fd);
}

void handle_caps(int argc, char **argv) {
    int pid;

    struct __user_cap_header_struct cap_hdr;
    struct __user_cap_data_struct cap_data[2];

    if (argc < 2) {
        pid = getpid();
    } else {
        pid = atoi(argv[1]);
    }

    cap_hdr.version = _LINUX_CAPABILITY_VERSION_3;
    cap_hdr.pid = pid;

    if (capget(&cap_hdr, cap_data) < 0) {
        perror("capget");
        return;
    }

    printf("effective = %08x:%08x permitted = %08x:%08x inheritable = %08x:%08x\n",
        cap_data[0].effective, cap_data[1].effective, cap_data[0].permitted, cap_data[1].permitted, cap_data[0].inheritable, cap_data[1].inheritable);
}

#define AZSPIO_COMPONENT_ID_LENGTH 16
struct sockaddr_azspio {
	uint16_t sa_family; // AF_AZSPIO
	uint16_t sa_port; // Must be zero.
	uint8_t sa_component_id[AZSPIO_COMPONENT_ID_LENGTH];
};

void handle_azspio(int argc, char **argv) {
    int s = socket(43, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("Failed to create an AZSPIO socket");
        return;
    }

    struct sockaddr_azspio addr;
    socklen_t addr_len = sizeof(addr);
    if (getsockname(s, (struct sockaddr*)&addr, &addr_len) < 0) {
        perror("Failed to get our sockname");
        return;
    } 
    printf("Our Sockname:");
    print_hex(addr.sa_component_id, AZSPIO_COMPONENT_ID_LENGTH);
    printf("\n");

    uint32_t foo = 0x48174927;

    printf("Null addr length:\n");
    if (getsockname(s, (struct sockaddr*)&addr, NULL) < 0) {
        perror("Failed with null adrr length");
    } 

    printf("Random addr length: %08x\n", foo);
    if (getsockname(s, (struct sockaddr*)&addr, (void*)foo) < 0) {
        perror("Failed with random adrr length");
    } 

    printf("Null addr:\n");
    if (getsockname(s, (struct sockaddr*)NULL, &addr_len) < 0) {
        perror("Failed with null addr");
    } 

    printf("Random addr: %08x\n", foo);
    if (getsockname(s, (struct sockaddr*)(void*)foo, &addr_len) < 0) {
        perror("Failed with random adrr");
    } 

    close(s);
}
