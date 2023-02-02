#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

bool is_valid_hex_color(const char* hex) {
    int len = strlen(hex);
    if (len != 6 && len != 8) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        char c = hex[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) {
            return false;
        }
    }
    return true;
}

uint16_t hex_24_to_16_rgb565(const char* hex) {
    uint32_t hex_int = (uint32_t)strtol(hex, NULL, 16);
    uint8_t r = (hex_int >> 16) & 0xff;
    uint8_t g = (hex_int >> 8) & 0xff;
    uint8_t b = hex_int & 0xff;
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

uint16_t hex_24_to_16_rgb555(const char* hex) {
    uint32_t hex_int = (uint32_t)strtol(hex, NULL, 16);
    uint8_t r = (hex_int >> 16) & 0xff;
    uint8_t g = (hex_int >> 8) & 0xff;
    uint8_t b = hex_int & 0xff;
    return ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);
}

int main(int argc, char *argv[]) {
    // Verifica se foi passado algum argumento
    if (argc < 2) {
        printf("Favor passar uma cor hexadecimal como argumento sem o caracter '#'.\n");
        return 1;
    }

     if (!is_valid_hex_color(argv[1])){
        printf("A cor %s não é válida!\n", argv[1]);
        return -1;
    }

    // Pega o argumento passado (cor hexadecimal) e remove o '#' caso exista
    char hex[8];
    strcpy(hex, argv[1]);
    if (hex[0] == '#') {
        for (int i = 0; i < 7; i++) {
            hex[i] = hex[i + 1];
        }
    }


    uint16_t _color = hex_24_to_16_rgb555(hex);
    printf("color RGB555: %x\n", (uint16_t)_color);
    _color = hex_24_to_16_rgb565(hex);
    printf("color RGB565: %x\n", (uint16_t)_color);

    return 0;
}

