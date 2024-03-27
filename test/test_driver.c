#include "unity.h"
#include "../lib/driver.h"

void setup() {
    device_init();
}

void test_device_init() {
    setup();
        
    uint32_t expected_register_value = 0x00000500;
    uint32_t actual_register_value =  get_register();

    actual_register_value &= 0x000007FF;

    TEST_ASSERT_EQUAL_INT32(expected_register_value, actual_register_value);
}

void test_get_temperature() {
    setup();
    uint32_t expected_value = 35;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

int main() {
    UNITY_BEGIN();
    return UNITY_END();
}