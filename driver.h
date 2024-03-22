#ifndef DRIVER_H
#define DRIVER_H

#include "stdio.h"
#include <stdint.h>

#define TSR_DATA_MASK       0xFFFFFF00
#define TSR_DATA(x)         (((uint32_t)x)|(device_register & TSR_DATA_MASK))
#define TSR_PWR_MASK        0xFFFFFEFF
#define TSR_PWR_SHIFT       8
#define TSR_PWR(x)          (((uint32_t)x << TSR_PWR_SHIFT)|(device_register & TSR_PWR_MASK))
#define TSR_ERR_MASK        0xFFFFFDFF
#define TSR_ERR_SHIFT       9
#define TSR_ERR(x)          (((uint32_t)x << TSR_ERR_SHIFT)|(device_register & TSR_ERR_MASK))

void device_init();

void read_temperature();

void write_mock_temperature();

#endif //DRIVER_H