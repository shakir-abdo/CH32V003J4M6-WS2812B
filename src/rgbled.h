/**
 * @file rgbled.h
 * @brief Simple WS2812B RGB LED Library for CH32V003
 */

#ifndef RGBLED_H
#define RGBLED_H

#include <stdint.h>

#include "ch32v003fun.h"

// Maximum number of LEDs supported by the library
#define RGBLED_MAX_LEDS 16

// RGB color structure
typedef struct {
    uint8_t r;  // Red component (0-255)
    uint8_t g;  // Green component (0-255)
    uint8_t b;  // Blue component (0-255)
} RGBLED_Color;

// Pre-defined colors
#define RGBLED_RED (RGBLED_Color){255, 0, 0}
#define RGBLED_GREEN (RGBLED_Color){0, 255, 0}
#define RGBLED_BLUE (RGBLED_Color){0, 0, 255}
#define RGBLED_WHITE (RGBLED_Color){255, 255, 255}
#define RGBLED_BLACK (RGBLED_Color){0, 0, 0}
#define RGBLED_PURPLE (RGBLED_Color){128, 0, 128}
#define RGBLED_YELLOW (RGBLED_Color){255, 255, 0}
#define RGBLED_CYAN (RGBLED_Color){0, 255, 255}
#define RGBLED_ORANGE (RGBLED_Color){255, 165, 0}
#define RGBLED_PINK (RGBLED_Color){255, 20, 147}

/**
 * @brief Initialize the WS2812B LED library
 *
 * @param port GPIO port (GPIOA, GPIOC, GPIOD)
 * @param pin Pin number (0-7)
 */
void RGBLED_Init(GPIO_TypeDef* port, uint8_t pin);

/**
 * @brief Set the brightness scaling factor
 *
 * @param brightness Brightness value (0-255)
 */
void RGBLED_SetBrightness(uint8_t brightness);

/**
 * @brief Set the color of a specific LED
 *
 * @param index LED index (0 to number of LEDs - 1)
 * @param color Color to set
 */
void RGBLED_SetPixel(uint8_t index, RGBLED_Color color);

/**
 * @brief Fill all LEDs with the same color
 *
 * @param color Color to set
 */
void RGBLED_Fill(RGBLED_Color color);

/**
 * @brief Clear all LEDs (set to black/off)
 */
void RGBLED_Clear(void);

/**
 * @brief Update the LED strip with current colors
 *
 * @param count Number of LEDs to update
 */
void RGBLED_Show(uint8_t count);

/**
 * @brief Create a color from RGB components
 *
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 * @return RGBLED_Color constructed color
 */
RGBLED_Color RGBLED_RGB(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Create a color from HSV components
 *
 * @param hue Hue value (0-255)
 * @param sat Saturation value (0-255)
 * @param val Value/brightness (0-255)
 * @return RGBLED_Color constructed color
 */
RGBLED_Color RGBLED_HSV(uint8_t hue, uint8_t sat, uint8_t val);

/**
 * @brief Get a color from RGB components
 *
 * @return led_buffer
 */
RGBLED_Color RGBLED_GetPixel(uint8_t index);

#endif /* RGBLED_H */
