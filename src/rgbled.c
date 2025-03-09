/**
 * @file rgbled.c
 * @brief Simple WS2812B RGB LED Library for CH32V003
 */

#include "rgbled.h"

// Buffer for LED colors
static RGBLED_Color led_buffer[RGBLED_MAX_LEDS];

// GPIO port and pin
static GPIO_TypeDef* led_port;
static uint8_t led_pin;
static uint32_t led_pin_mask;

// Global brightness (0-255)
static uint8_t global_brightness = 255;

// Initialize the LED library
void RGBLED_Init(GPIO_TypeDef* port, uint8_t pin) {
    // Store configuration
    led_port = port;
    led_pin = pin;
    led_pin_mask = 1 << pin;

    // Enable GPIO clock
    if (port == GPIOA) {
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
    } else if (port == GPIOC) {
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
    } else if (port == GPIOD) {
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;
    }

    // Configure pin as output (50MHz, push-pull)
    uint32_t pin_config = (GPIO_Speed_50MHz | GPIO_CNF_OUT_PP) << (pin * 4);
    uint32_t pin_mask = 0xF << (pin * 4);

    port->CFGLR = (port->CFGLR & ~pin_mask) | pin_config;

    // Initial state is low
    port->BCR = led_pin_mask;

    // Clear all LEDs
    RGBLED_Clear();
}

// Set global brightness
void RGBLED_SetBrightness(uint8_t brightness) {
    global_brightness = brightness;
}

// Set color of a specific LED
void RGBLED_SetPixel(uint8_t index, RGBLED_Color color) {
    if (index < RGBLED_MAX_LEDS) {
        led_buffer[index] = color;
    }
}

// Fill all LEDs with the same color
void RGBLED_Fill(RGBLED_Color color) {
    for (uint8_t i = 0; i < RGBLED_MAX_LEDS; i++) {
        led_buffer[i] = color;
    }
}

// Clear all LEDs (set to black/off)
void RGBLED_Clear(void) { RGBLED_Fill(RGBLED_BLACK); }

// Send a single bit to WS2812B
static inline void send_bit(uint8_t bit) {
    if (bit) {
        // Send a 1 bit (high for about 0.8us, low for about 0.45us)
        led_port->BSHR = led_pin_mask;  // Set high
        asm volatile(
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
        led_port->BCR = led_pin_mask;  // Set low
        asm volatile(
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    } else {
        // Send a 0 bit (high for about 0.4us, low for about 0.85us)
        led_port->BSHR = led_pin_mask;  // Set high
        asm volatile(
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\n");
        led_port->BCR = led_pin_mask;  // Set low
        asm volatile(
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"
            "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    }
}

// Apply brightness to a color component
static uint8_t apply_brightness(uint8_t color) {
    return (uint16_t)color * global_brightness / 255;
}

// Send a byte to WS2812B
static void send_byte(uint8_t byte) {
    for (int8_t bit = 7; bit >= 0; bit--) {
        send_bit((byte >> bit) & 0x01);
    }
}

// Update LED strip with current colors
void RGBLED_Show(uint8_t count) {
    if (count > RGBLED_MAX_LEDS) {
        count = RGBLED_MAX_LEDS;
    }

    // Disable interrupts for accurate timing
    uint32_t oldmask;
    asm volatile("csrr %0, mstatus" : "=r"(oldmask));
    asm volatile("csrci mstatus, 8");

    // Send data for each LED in GRB order
    for (uint8_t i = 0; i < count; i++) {
        uint8_t r = apply_brightness(led_buffer[i].r);
        uint8_t g = apply_brightness(led_buffer[i].g);
        uint8_t b = apply_brightness(led_buffer[i].b);

        // WS2812B expects data in GRB order
        send_byte(g);
        send_byte(r);
        send_byte(b);
    }

    // Reset pulse (>50us low)
    led_port->BCR = led_pin_mask;
    Delay_Us(60);

    // Restore interrupt state
    if (oldmask & 0x8) {
        asm volatile("csrsi mstatus, 8");
    }
}

// Create RGB color
RGBLED_Color RGBLED_RGB(uint8_t r, uint8_t g, uint8_t b) {
    RGBLED_Color color = {r, g, b};
    return color;
}

// Create color from HSV values
RGBLED_Color RGBLED_HSV(uint8_t hue, uint8_t sat, uint8_t val) {
    RGBLED_Color color = {0, 0, 0};

    // Handle special case of zero saturation (grayscale)
    if (sat == 0) {
        color.r = color.g = color.b = val;
        return color;
    }

    // Convert hue to 0-5 range with fractional part
    uint8_t h_section = (hue * 6) / 256;
    uint8_t h_fraction = ((hue * 6) % 256) * 255 / 256;

    uint8_t p = (uint16_t)val * (255 - sat) / 255;
    uint8_t q =
        (uint16_t)val * (255 - ((uint16_t)sat * h_fraction) / 255) / 255;
    uint8_t t = (uint16_t)val *
                (255 - ((uint16_t)sat * (255 - h_fraction)) / 255) / 255;

    switch (h_section) {
        case 0:
            color.r = val;
            color.g = t;
            color.b = p;
            break;
        case 1:
            color.r = q;
            color.g = val;
            color.b = p;
            break;
        case 2:
            color.r = p;
            color.g = val;
            color.b = t;
            break;
        case 3:
            color.r = p;
            color.g = q;
            color.b = val;
            break;
        case 4:
            color.r = t;
            color.g = p;
            color.b = val;
            break;
        case 5:
        default:
            color.r = val;
            color.g = p;
            color.b = q;
            break;
    }

    return color;
}
