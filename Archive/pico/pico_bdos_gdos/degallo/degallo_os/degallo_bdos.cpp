#include "degallo_bdos.h"
#include "degallo_bios.h"

void bdos_init() {
    bios_init();
}

void bdos_print(const char *message) {
    bios_write_display(message);
}

void bdos_load_application(const char *filename) {
    uint8_t buffer[8192]; // Adjust size as needed
    bios_read_sd(filename, buffer, sizeof(buffer));
    
    void (*app_entry)() = (void (*)())buffer;
    app_entry();
}
