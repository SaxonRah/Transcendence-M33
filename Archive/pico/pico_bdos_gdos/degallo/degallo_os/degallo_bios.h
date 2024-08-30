#ifndef DEGALLO_BIOS_H
#define DEGALLO_BIOS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void bios_init();
void bios_write_display(const char *message);
void bios_read_sd(const char *filename, uint8_t *buffer, size_t size);
void bios_write_sd(const char *filename, const uint8_t *data, size_t size);

#endif // DEGALLO_BIOS_H
