#ifndef DRIVER_H
#define DRIVER_H

#include "stdio.h"
#include <stdint.h>

#define TSR_DATA_MASK       0xFF
#define TSR_DATA(x)         (((uint32_t)x)|(device_register & (~TSR_DATA_MASK)))
#define TSR_PWR_MASK        0x100
#define TSR_PWR_SHIFT       8
#define TSR_PWR(x)          (((uint32_t)x << TSR_PWR_SHIFT)|(device_register & (~TSR_PWR_MASK)))
#define TSR_ERR_MASK        0x200
#define TSR_ERR_SHIFT       9
#define TSR_ERR(x)          (((uint32_t)x << TSR_ERR_SHIFT)|(device_register & (~TSR_ERR_MASK)))
#define TSR_RDF_MASK        0x400
#define TSR_RDF_SHIFT       10
#define TSR_RDF(x)          (((uint32_t)x << TSR_RDF_SHIFT)|(device_register & (~TSR_RDF_MASK)))

void device_init();

void read_temperature();

void write_mock_temperature(uint32_t val);

#endif //DRIVER_H