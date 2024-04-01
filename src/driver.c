#include "../lib/driver.h"

void device_init() {
    device_register = TSR_DATA(0b0);
    device_register = TSR_ERR(0b00);
    device_register = TSR_PWR(0b1);
    device_register = TSR_RDF(0b1);
}

int8_t get_temperature() {
    int8_t data = 0;
    if(is_device_powered_on() && !is_error() && is_data_ready()) {
        if(device_register & (1 << 7)) {
            data = ((~device_register) + 0x1) & TSR_DATA_MASK;
            data = data* (-1);
        }
        else {
            data = device_register & TSR_DATA_MASK;
        }
        device_register = TSR_RDF(0b0);
    }
    return data;
}

uint32_t get_register() {
    return device_register;
}

void write_mock_temperature(int32_t val) {
    if (val > 127) {
        device_register = TSR_ERR(0b01);
        return;
    }
    
    if (val < -128) {
        device_register = TSR_ERR(0b10);
        return;
    }
    
    if (((get_register() >> TSR_ERR_SHIFT) & 0b11) == 0b01 || ((get_register() >> TSR_ERR_SHIFT) & 0b11) == 0b10 ) {
        device_register = TSR_ERR(0b00);
    }
    
    device_register = TSR_DATA(val);
    device_register = TSR_RDF(0b1);
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