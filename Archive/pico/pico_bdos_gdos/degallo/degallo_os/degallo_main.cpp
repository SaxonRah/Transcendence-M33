#include "degallo_bdos.h"

int main() {
    bdos_init();
    bdos_print("DeGallo OS Initialized\n");
    
    // Load and execute the application from the SD card
    bdos_load_application("degallo_app.bin");

    return 0;
}
