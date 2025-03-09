# CH32V003J4M6-WS2812B

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: CH32V003](https://img.shields.io/badge/Platform-CH32V003-blue.svg)](http://www.wch-ic.com/products/CH32V003.html)


A lightweight library for controlling WS2812B RGB LEDs with CH32V003J4M6 microcontrollers.

## Features

- Simple API for controlling individual or multiple LEDs
- Global brightness control
- RGB and HSV color spaces support
- Optimized for CH32V003's limited resources
- Direct bit-banging implementation (no SPI/DMA required)
- Compatible with any GPIO pin on the CH32V003J4M6

## Installation

### PlatformIO

1. Add the library to your `platformio.ini`:
```ini
lib_deps =
    shakir-abdo/CH32V003J4M6-WS2812B
```

### Manual Installation

1. Copy `rgbled.c` and `rgbled.h` to your project's include path
2. Include `rgbled.h` in your source files

## Hardware Connections

Connect your WS2812B LED strip to the CH32V003J4M6:

1. VCC: Connect to 5V
2. GND: Connect to GND
3. DIN: Connect to any GPIO pin (through a 330-470Ω resistor)

**Note:** It's recommended to use a level shifter between the 3.3V GPIO and the WS2812B data line for reliable operation.

## Basic Usage

```c
#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN     4   // Using PC4
#define NUM_LEDS    3   // Number of LEDs in your strip

int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, LED_PIN);

    // Set brightness (0-255)
    RGBLED_SetBrightness(50);

    while(1) {
        // Fill all LEDs with red
        RGBLED_Fill(RGBLED_RED);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(500);

        // Set individual LED colors
        RGBLED_SetPixel(0, RGBLED_RED);
        RGBLED_SetPixel(1, RGBLED_GREEN);
        RGBLED_SetPixel(2, RGBLED_BLUE);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(500);

        // Create custom colors
        RGBLED_Color purple = RGBLED_RGB(128, 0, 128);
        RGBLED_Fill(purple);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(500);

        // Use HSV color space for rainbow effects
        for(uint8_t i = 0; i < 255; i++) {
            RGBLED_Fill(RGBLED_HSV(i, 255, 255));
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(10);
        }
    }
}
```

## API Reference

### Initialization

```c
void RGBLED_Init(GPIO_TypeDef* port, uint8_t pin);
```

### Color Control

```c
void RGBLED_SetPixel(uint8_t index, RGBLED_Color color);
void RGBLED_Fill(RGBLED_Color color);
void RGBLED_Clear(void);
void RGBLED_Show(uint8_t count);
```

### Brightness Control

```c
void RGBLED_SetBrightness(uint8_t brightness);
```

### Color Creation

```c
RGBLED_Color RGBLED_RGB(uint8_t r, uint8_t g, uint8_t b);
RGBLED_Color RGBLED_HSV(uint8_t hue, uint8_t sat, uint8_t val);
```

### Predefined Colors

The library includes several predefined colors:
- `RGBLED_RED`
- `RGBLED_GREEN`
- `RGBLED_BLUE`
- `RGBLED_WHITE`
- `RGBLED_BLACK` (off)
- `RGBLED_PURPLE`
- `RGBLED_YELLOW`
- `RGBLED_CYAN`
- `RGBLED_ORANGE`
- `RGBLED_PINK`

## Configuration

You can modify `RGBLED_MAX_LEDS` in rgbled.h to change the maximum number of supported LEDs (default is 16).

## Tips & Troubleshooting

1. **Power Supply:** Ensure sufficient power for your LED strip. Each LED can draw up to 60mA at full brightness.
2. **Level Shifting:** For reliable operation, use a level shifter to convert the 3.3V GPIO signal to 5V.
3. **Series Resistor:** Always use a 330-470Ω resistor in series with the data line to protect the first LED.
4. **Direction:** WS2812B strips have a direction. Make sure to connect to the "input" end.
5. **Brightness:** For battery-powered applications, lower the brightness to reduce power consumption.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Inspired by the FastLED and Adafruit NeoPixel libraries
- Special thanks to the CH32V003fun framework developers
