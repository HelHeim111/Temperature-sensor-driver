#include "../lib/driver.h"

/*
* 31-16 reserved
* 15-11 status flags, reserved for future use
* 10 data ready flag (0 - not ready, 1 - ready)
* 9 error (0 - ok, 1 - error)
* 8 power status (0 - off, 1 - on)
* 7-0 data
*/
static uint32_t device_register = 0;

void device_init() {
    device_register = TSR_DATA(0);
    device_register = TSR_ERR(0);
    device_register = TSR_PWR(1);
    device_register = TSR_RDF(1);
}

uint32_t get_temperature() {
    uint32_t data = 0;
    if(is_device_powered_on() && !is_error() && is_data_ready()) {
        if(device_register & (1 << 7)) {
            data = ((~device_register) + 0x1) & TSR_DATA_MASK;
            data = data* (-1);
        }
        else {
            data = device_register & TSR_DATA_MASK;
        }
        device_register = TSR_RDF(0);
    }
    return data;
}

uint32_t get_register() {
    return device_register;
}

void write_mock_temperature(uint32_t val) {
    if (val > 127 || val <= -128) {
        device_register = TSR_ERR(1);
        return;
    }
    device_register = TSR_DATA(val);
    device_register = TSR_RDF(1);
}

bool is_device_powered_on() {
    return 1 & (device_register >> TSR_PWR_SHIFT);
}

bool is_error() {
    return 1 & (device_register >> TSR_ERR_SHIFT);
}

bool is_data_ready() {
    return 1 & (device_register >> TSR_RDF_SHIFT);
}

void main () {
    device_register = 0xFFFF4411;
    device_init();
    if(is_device_powered_on()) {
        printf("on\n");
    }

    return 0;
}