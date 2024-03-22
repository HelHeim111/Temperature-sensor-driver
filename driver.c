#include "driver.h"

/*
* 31-16 reserved
* 15-10 status flags, reserved for future use
* 9 error (0 - ok, 1 - error)
* 8 power status (0 - off, 1 - on)
* 7-0 data
*/
static uint32_t device_register = 0;

void device_init() {
    device_register = TSR_DATA(0);
    device_register = TSR_ERR(0);
    device_register = TSR_PWR(1);
}

void main () {
    device_register = 0xFFFF4411;
    device_init();
    printf("%x\n", device_register);
    return 0;
}