# Gas Detection and Alert System - STM32F4 Project

## Project Overview

This project implements a gas detection and alert system using the STM32F4 microcontroller. The system monitors gas concentration levels using an MQ-2 gas sensor and provides visual and audible alerts based on the detected gas levels. It features multiple system states, LCD display output, UART communication, and interrupt-based button controls.

## Hardware Components

- STM32F4 microcontroller
- MQ-2 Gas Sensor (connected to PB0/ADC1_IN8)
- I2C LCD Display (connected to PB6/SCL and PB7/SDA)
- LEDs (Red, Yellow, Blue, Green)
- Buzzer
- Relay
- Push buttons (Stop and Reset)
- UART interface (USART2)

## System Features

1. **Gas Concentration Monitoring**:
   - Reads analog values from MQ-2 sensor
   - Converts readings to PPM (parts per million) values
   - Implements logarithmic conversion from sensor resistance to PPM

2. **Alert System**:
   - Four alert levels: Safe, Alert, Danger, Critical
   - Visual indicators using different colored LEDs
   - Audible alerts with buzzer (in critical state)
   - Relay control for external devices

3. **User Interface**:
   - I2C LCD display showing system status and gas levels
   - Two control buttons (Stop/Shutdown and Reset)

4. **Communication**:
   - UART output for sending gas level data when in danger state

5. **System States**:
   - Working mode (normal operation)
   - Shutdown mode (paused state)

## Software Architecture

### Main Modules

1. **ADC (Analog-to-Digital Converter)**:
   - Initializes and reads from ADC channel connected to MQ-2 sensor
   - Converts raw ADC values to voltage and then to PPM values

2. **GPIO**:
   - Manages all digital I/O (LEDs, buzzer, relay, buttons)
   - Provides system state functions (Safe, Alert, Danger, Critical)

3. **I2C**:
   - Handles communication with I2C LCD display
   - Implements I2C protocol for data transmission

4. **LCD**:
   - Provides high-level LCD control functions
   - Displays system status and gas concentration information

5. **EXTI (External Interrupts)**:
   - Handles button interrupts for system control
   - Implements pause/resume and reset functionality

6. **UART**:
   - Initializes and manages USART2 communication
   - Sends gas concentration data when in danger state

7. **TIMER**:
   - Provides delay functions
   - Used for timing control in critical state blinking

### Key Configuration Parameters

- **Gas Level Thresholds** (defined in lcd.h):
  - SAFE_LEVEL: 300 PPM
  - ALERT_LEVEL: 700 PPM
  - DANGER_LEVEL: 1000 PPM

- **MQ-2 Sensor Parameters** (defined in adc.h):
  - VREF: 3.3V (reference voltage)
  - RL: 1.0Ω (load resistance)
  - R0: 1.9Ω (sensor resistance in clean air)
  - A, B: Calibration coefficients for PPM conversion

## Usage Instructions

1. **System Startup**:
   - The system initializes all peripherals and displays "SYSTEM WORKING" on the LCD
   - The blue LED turns on indicating normal operation

2. **Normal Operation**:
   - The system continuously monitors gas concentration
   - LCD displays current state (SAFE, ALERT, DANGER, CRITICAL)
   - LEDs and buzzer activate according to gas levels

3. **Button Controls**:
   - **Stop Button (PA0)**: Toggles between working and shutdown modes
   - **Reset Button (PA1)**: Resets gas concentration reading to 0

4. **Alert States**:
   - **Safe (<300 PPM)**: Blue LED on
   - **Alert (300-700 PPM)**: Yellow LED on
   - **Danger (700-1000 PPM)**: Red LED blinks, relay activates, UART sends data
   - **Critical (>1000 PPM)**: Red LED blinks rapidly, buzzer sounds, relay activates

## Project Structure

```
project_root/
├── Core/
│   ├── Inc/         # Header files
│   │   ├── adc.h
│   │   ├── exti.h
│   │   ├── gpio.h
│   │   ├── i2c.h
│   │   ├── lcd.h
│   │   ├── main.h
│   │   ├── timer.h
│   │   └── uart.h
│   └── Src/         # Source files
│       ├── adc.c
│       ├── exti.c
│       ├── gpio.c
│       ├── i2c.c
│       ├── lcd.c
│       ├── main.c
│       ├── timer.c
│       ├── uart.c
└── (other project files)
```

## Building and Deployment

1. Open the project in your preferred STM32 development environment (STM32CubeIDE, Keil, etc.)
2. Build the project
3. Connect your STM32F4 discovery board or custom hardware
4. Flash the compiled binary to the microcontroller
5. The system should start automatically after programming

## Dependencies

- STM32F4xx HAL library
- Standard C library (for math functions and string operations)

## Notes

- The system uses direct register access for peripheral control rather than HAL functions for optimal performance
- The MQ-2 sensor calibration values (A, B, R0) may need adjustment based on your specific sensor and environment
- Ensure proper power supply for the MQ-2 sensor heater element

## Future Enhancements

1. Add calibration routine for the MQ-2 sensor
2. Implement data logging to external memory
3. Add wireless communication module for remote monitoring
4. Implement temperature/humidity compensation for gas readings
5. Add more sophisticated alert patterns and sequences
