#include <string.h>

#include "string_util.h"

int string_tokenize(char *str, char **tokens, int max_tokens, const char *sep) {
    size_t i;

    tokens[0] = strtok(str, sep);
    
    for(i = 1; i < max_tokens && tokens[i-1] != NULL; i++) {
        tokens[i] = strtok(NULL, sep);
    }

    return i - 1;
}

void print_guid(struct azure_sphere_guid* guid) {
    printf("%08x-%04x-%04x-", guid->data1, guid->data2, guid->data3);
    print_hex(guid->data4, sizeof(guid->data4));
}

void print_hex(uint8_t *data, int count) {
    for(int i = 0; i < count; i++) {
        printf("%02x", data[i]);
    }
}
