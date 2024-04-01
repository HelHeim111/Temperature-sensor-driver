#ifndef DRIVER_H
#define DRIVER_H

#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>

#define TSR_DATA_MASK       0xFF
#define TSR_DATA(x)         ((uint32_t)(x < 0 ? (uint32_t)(x & TSR_DATA_MASK) : (uint32_t)(x)) | (device_register & (~TSR_DATA_MASK)))
#define TSR_PWR_MASK        0x100
#define TSR_PWR_SHIFT       8
#define TSR_PWR(x)          (((uint32_t)x << TSR_PWR_SHIFT)|(device_register & (~TSR_PWR_MASK)))
#define TSR_ERR_MASK        0x600
#define TSR_ERR_SHIFT       9
#define TSR_ERR(x)          (((uint32_t)x << TSR_ERR_SHIFT)|(device_register & (~TSR_ERR_MASK)))
#define TSR_RDF_MASK        0x800
#define TSR_RDF_SHIFT       11
#define TSR_RDF(x)          (((uint32_t)x << TSR_RDF_SHIFT)|(device_register & (~TSR_RDF_MASK)))

/**
 * @brief   Initializing device register
*/
void device_init();

/**
 * @brief   Reads data from the regiter
 * @return  int8_t temperature
*/
int8_t get_temperature();

/**
 * @brief   Getting current state of the register
 * @return  uint32_t current state of the register
*/
uint32_t get_register();

/**
 * @brief   Writes mock data to the register
 * @param   int32_t val: mock value
*/
void write_mock_temperature(int32_t val);

/**
 * @brief   Checks power status flag
*/
bool is_device_powered_on();

/**
 * @brief   Checks pdata ready flag
*/
bool is_data_ready();

/**
 * @brief   Checks error flag
*/
bool is_error();

#endif //DRIVER_H