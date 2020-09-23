#pragma once

#include "az_types.h"

#define WHITESPACE " \t\n"

// printf() and the like don't work, so we directly access the fd and use dprintf
int dprintf(int fd, char *fmt, ...);
#define printf(...) dprintf(1, __VA_ARGS__)

int string_tokenize(char *str, char **tokens, int max_tokens, const char *sep);


void print_guid(struct azure_sphere_guid* guid);
void print_hex(uint8_t *data, int count);