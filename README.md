# Temperature-sensor-driver

## **Table of context**
1. Introduction
1. Project structure
1. Usage
1. Device Specifications
1. Implementation Details
1. Testing and Validation

## **Introduction**
This document outlines the implementation details and specifications for the mock temperature sensor device driver. The driver simulates reading data from the register as well as writing mock values to the register. The driver is developed in the C programming language and utilizes the Unity test framework for testing.

## **Project Structure**
Temperature-sensor-driver/  
│  
├── src/                  # Source files directory  
│   └── driver.c            # Main source file  
│  
├── tests/                # Test files directory  
│   ├── test_driver.c       # Main test file  
|   ├── unity_internals.h
│   ├── unity.c   
|   └── unity.h 
│  
├── lib/                  # Header files directory  
│   └── driver.h   # Header file for the temperature sensor driver  
│  
├── build/                # Build directory (object files, executables)  
│  
├── Makefile              # Makefile for building the project  
├── README.md  

## **Usage**
To run the temperature sensor driver and its tests, follow these steps:

1. **Clone the repository:**

   ```bash
   git clone <repository_url>
1. **Navigate to the projects directory**
1. **Build the project using Makefile**
    ```bash
    make
1. **Run the tests**
    ```bash
    make test
1. **(Optional) Clean up the build files**
    ```bash
    make clean

## **Device Specifications**
The temperature sensor device provides temperature readings through a memory-mapped I/O register.
Device register is 32 bits wide and structured as follows :
- Bits 31-12: Reserved for future use.
- Bit 11: Data Ready Flag. Determines whether the device data is ready to be read, so the old data would not be read twice (0 - not ready, 1 - ready).
- Bits 10-9: Error Flags. Shows the error that occured during usage of the device (00 - no error, 01 - data overflow, 10 - data underflow, 11 - sensor malfunctioning)
- Bit 8: Power Status Flag. Shows whether the device is turned on (0 - off, 1 - on).
- Bits 7-0: Temperature data encoded as an 8-bit signed integer.

## **Implementation Details**
The implementation of the mock device driver consists of the following key components:
- Helper Functions 
    ```c
    is_device_powered_on(); 
    is_error(); 
    is_data_ready();
    ```
    These helper functions check the status of specific flags in the device register:

    1. is_device_powered_on(): Checks if the device power status flag is set (1) or not (0).
    1. is_error(): Checks if any error flags are set in the device register.
    1. is_data_ready(): Checks if the data ready flag is set, indicating that new data is available for reading.

- Device Initialization: Initializes the device, sets initial states, and clears any errors.
    ```c
    void device_init();
    ```
    Set the initial temperature data to 0.  
    Set the error state to "no error" (00).  
    Turn on the device power by setting the power status flag to 1 (on).  
    Set the data ready flag to 1 (ready) to indicate that the device data is ready to be read.  

- Read Temperature: Reads the temperature value from the device register, performs necessary bit operations to extract status flags and temperature data, converts temperature data to a standard format, and handles error checking based on status flags.
    ```c
    int8_t get_temperature();
    ```
    Check if the device is powered on (is_device_powered_on()), no error is present (!is_error()), and data is ready (is_data_ready()).  
    If all conditions are met, extract the temperature data from the device register.  
    If the temperature data is stored in two's complement format (sign bit is set), convert it to a signed integer and return the result.  
    If the sign bit is not set, simply return the temperature data as is.  
    Clear the data ready flag after reading the temperature data to indicate that the data has been read.

- Write Mock Values: Simulates receiving data from the sensor, controls for any possible errors, such as overflow or underflow of the data. Driver recovers from those errors by receiving new temperature value that does not cause an error.
    ```c
    void write_mock_temperature(int32_t val);
    ```
    Check if the input temperature value (val) exceeds the allowable range of -128 to 127.  
    If the temperature value exceeds the maximum range, set the appropriate error flag (overflow) in the device register.  
    If the temperature value is below the minimum range, set the appropriate error flag (underflow) in the device register.  
    If the temperature value is within the allowable range and the device is not already in an error state, clear any existing error flags in the device register.  
    Write the temperature value to the device register and set the data ready flag to indicate that new data is available.  

## **Testing and Validation**
A test suite using the Unity framework is written to simulate various device states and temperature readings. Unity provides a lightweight and flexible testing framework for C programming language, making it suitable for unit testing embedded systems.
**Type of Tests**
- Device Initialization Test: Verifies that the device initialization function sets the expected initial state of the device register. This ensures that the device is properly initialized before any operations are performed.
- Temperature Reading Tests: These tests validate the correctness of temperature readings extracted from the device register. Test cases cover positive, negative, maximum, minimum, and zero temperature values to ensure the driver handles various temperature scenarios correctly.
- Error Handling Tests: Verify that error states and status flags are correctly interpreted and handled by the driver. Test cases simulate error conditions such as data overflow and underflow, ensuring the driver responds appropriately to error situations.
- Error Recovery Test: Validates the driver's ability to recover from error conditions. This test case ensures that the driver can recover and continue normal operation after encountering an error.