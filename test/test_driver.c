#include "unity.h"
#include "../lib/driver.h"

void setUp() {
    device_init();
}

void tearDown() {
    return;
}

void test_device_init() {
        
    uint32_t expected_register_value = 0x00000900;
    uint32_t actual_register_value =  get_register();

    actual_register_value &= 0x00000FFF;

    TEST_ASSERT_EQUAL_INT32(expected_register_value, actual_register_value);
}

void test_get_temperature_positive() {
    uint32_t expected_value = 35;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_get_temperature_negative() {
    uint32_t expected_value = -12;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_get_temperature_max() {
    uint32_t expected_value = 127;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_get_temperature_min() {
    uint32_t expected_value = -128;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_get_temperature_zero() {
    uint32_t expected_value = 0;
    write_mock_temperature(expected_value);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_data_overflow() {
    write_mock_temperature(150);
    uint32_t expected_value = (((uint32_t)0b01 << TSR_ERR_SHIFT)|(get_register() & (~TSR_ERR_MASK)));
    TEST_ASSERT_EQUAL_UINT32(expected_value, get_register());
} 

void test_data_underflow() {
    write_mock_temperature(-600);
    uint32_t expected_value = (((uint32_t)0b10 << TSR_ERR_SHIFT)|(get_register() & (~TSR_ERR_MASK)));
    TEST_ASSERT_EQUAL_UINT32(expected_value, get_register());
}

void test_error_recovery() {
    write_mock_temperature(150);
    uint32_t expected_value = 50;
    write_mock_temperature(50);
    uint32_t actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(expected_value, actual_value);
}

void test_get_same_temperature() {
    write_mock_temperature(35);
    uint32_t actual_value = get_temperature();
    actual_value = get_temperature();
    TEST_ASSERT_EQUAL_INT32(0, actual_value);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_device_init);
    RUN_TEST(test_get_temperature_positive);
    RUN_TEST(test_get_temperature_negative);
    RUN_TEST(test_get_temperature_max);
    RUN_TEST(test_get_temperature_min);
    RUN_TEST(test_get_temperature_zero);
    RUN_TEST(test_data_overflow);
    RUN_TEST(test_data_underflow);
    RUN_TEST(test_error_recovery);
    RUN_TEST(test_get_same_temperature);
    return UNITY_END();
}