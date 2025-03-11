#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip
void police_siren_effect() {
    const uint16_t flash_duration = 100;
    const RGBLED_Color police_blue = RGBLED_RGB(0, 0, 255);
    const RGBLED_Color police_red = RGBLED_RGB(255, 0, 0);

    for (uint8_t i = 0; i < 10; i++) {
        // First half red, second half blue
        for (uint8_t j = 0; j < NUM_LEDS / 2; j++) {
            RGBLED_SetPixel(j, police_red);
        }
        for (uint8_t j = NUM_LEDS / 2; j < NUM_LEDS; j++) {
            RGBLED_SetPixel(j, police_blue);
        }
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(flash_duration);

        // Switch: first half blue, second half red
        for (uint8_t j = 0; j < NUM_LEDS / 2; j++) {
            RGBLED_SetPixel(j, police_blue);
        }
        for (uint8_t j = NUM_LEDS / 2; j < NUM_LEDS; j++) {
            RGBLED_SetPixel(j, police_red);
        }
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(flash_duration);
    }
}
void knight_rider_effect() {
    const RGBLED_Color scanner_red = RGBLED_RGB(255, 0, 0);
    const uint16_t scan_speed = 70;
    const uint8_t trail_length = 2;

    // First scan: left to right
    for (int8_t i = -trail_length; i < NUM_LEDS; i++) {
        RGBLED_Clear();

        // Draw the trail with fading brightness
        for (int8_t j = 0; j < trail_length; j++) {
            int8_t pos = i - j;
            if (pos >= 0 && pos < NUM_LEDS) {
                uint8_t brightness = 255 * (trail_length - j) / trail_length;
                RGBLED_SetBrightness(brightness);
                RGBLED_SetPixel(pos, scanner_red);
                RGBLED_SetBrightness(255);  // Reset for next pixel
            }
        }

        RGBLED_Show(NUM_LEDS);
        Delay_Ms(scan_speed);
    }

    // Second scan: right to left
    for (int8_t i = NUM_LEDS - 1 + trail_length; i >= 0; i--) {
        RGBLED_Clear();

        // Draw the trail with fading brightness
        for (int8_t j = 0; j < trail_length; j++) {
            int8_t pos = i - j;
            if (pos >= 0 && pos < NUM_LEDS) {
                uint8_t brightness = 255 * (trail_length - j) / trail_length;
                RGBLED_SetBrightness(brightness);
                RGBLED_SetPixel(pos, scanner_red);
                RGBLED_SetBrightness(255);  // Reset for next pixel
            }
        }

        RGBLED_Show(NUM_LEDS);
        Delay_Ms(scan_speed);
    }
}
void racing_startup_sequence() {
    const RGBLED_Color racing_red = RGBLED_RGB(255, 0, 0);
    const RGBLED_Color racing_green = RGBLED_RGB(0, 255, 0);

    // First: all LEDs off
    RGBLED_Clear();
    RGBLED_Show(NUM_LEDS);
    Delay_Ms(1000);

    // Second: red lights coming on one by one
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        RGBLED_SetPixel(i, racing_red);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(200);
    }

    // Hold all red
    Delay_Ms(1500);

    // Switch to green (race start!)
    RGBLED_Fill(racing_green);
    RGBLED_Show(NUM_LEDS);
    Delay_Ms(2000);
}
void breathing_effect() {
    const RGBLED_Color breath_color = RGBLED_RGB(0, 100, 255);
    const uint8_t breath_cycles = 4;

    for (uint8_t cycle = 0; cycle < breath_cycles; cycle++) {
        // Fade in
        for (uint8_t i = 5; i < 255; i += 5) {
            RGBLED_Fill(breath_color);
            RGBLED_SetBrightness(i);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(25);
        }

        // Fade out
        for (uint8_t i = 255; i > 5; i -= 5) {
            RGBLED_Fill(breath_color);
            RGBLED_SetBrightness(i);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(25);
        }
    }

    // Reset brightness
    RGBLED_SetBrightness(255);
}
void rainbow_wave_effect() {
    const uint8_t cycles = 2;
    const uint16_t cycle_duration = 2000;  // ms
    const uint8_t steps = 20;

    for (uint8_t cycle = 0; cycle < cycles; cycle++) {
        for (uint8_t hue = 0; hue < 255; hue += 255 / steps) {
            for (uint8_t i = 0; i < NUM_LEDS; i++) {
                // Distribute colors across the strip
                uint8_t pixel_hue = hue + (i * 255 / NUM_LEDS);
                RGBLED_SetPixel(i, RGBLED_HSV(pixel_hue, 255, 255));
            }
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(cycle_duration / steps);
        }
    }
}
void sparkle_effect() {
    const RGBLED_Color sparkle_color = RGBLED_RGB(255, 255, 255);
    const uint16_t duration_ms = 3000;
    const uint16_t update_interval = 80;
    const uint8_t density = 2;  // Number of LEDs lit at once

    uint16_t steps = duration_ms / update_interval;

    RGBLED_Clear();
    RGBLED_Show(NUM_LEDS);

    for (uint16_t i = 0; i < steps; i++) {
        // Turn off all lights first
        RGBLED_Clear();

        // Turn on random LEDs
        for (uint8_t j = 0; j < density; j++) {
            uint8_t random_led =
                i %
                NUM_LEDS;  // Not truly random - use ADC and timer if available
            RGBLED_SetPixel(random_led, sparkle_color);
        }

        RGBLED_Show(NUM_LEDS);
        Delay_Ms(update_interval);
    }
}
void engine_rev_effect() {
    const RGBLED_Color low_rpm = RGBLED_RGB(0, 255, 0);    // Green
    const RGBLED_Color mid_rpm = RGBLED_RGB(255, 255, 0);  // Yellow
    const RGBLED_Color high_rpm = RGBLED_RGB(255, 0, 0);   // Red

    // Simulate engine revving up
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        RGBLED_Clear();

        // Light up all LEDs up to current position
        for (uint8_t j = 0; j <= i; j++) {
            if (j < NUM_LEDS / 3) {
                RGBLED_SetPixel(j, low_rpm);
            } else if (j < 2 * NUM_LEDS / 3) {
                RGBLED_SetPixel(j, mid_rpm);
            } else {
                RGBLED_SetPixel(j, high_rpm);
            }
        }

        RGBLED_Show(NUM_LEDS);
        Delay_Ms(150 - (i * 10));  // Speed up as RPMs increase
    }

    // Hold at max RPM
    Delay_Ms(500);

    // RPMs drop quickly
    RGBLED_Clear();
    RGBLED_Show(NUM_LEDS);
}
void headlight_mode() {
    const RGBLED_Color headlight = RGBLED_RGB(255, 255, 180);  // Warm white
    const RGBLED_Color foglight = RGBLED_RGB(255, 255, 255);   // Cool white

    // Main headlights (center LEDs)
    for (uint8_t i = 1; i < NUM_LEDS - 1; i++) {
        RGBLED_SetPixel(i, headlight);
    }

    // Fog lights/DRLs (outer LEDs)
    if (NUM_LEDS >= 3) {
        RGBLED_SetPixel(0, foglight);
        RGBLED_SetPixel(NUM_LEDS - 1, foglight);
    }

    RGBLED_Show(NUM_LEDS);
    Delay_Ms(2000);  // Just keep lights on for a while
}
void emergency_vehicle_effect() {
    const RGBLED_Color warning_amber = RGBLED_RGB(255, 120, 0);
    const uint8_t pattern_repeats = 5;

    for (uint8_t i = 0; i < pattern_repeats; i++) {
        // Odd LEDs flash
        RGBLED_Clear();
        for (uint8_t j = 1; j < NUM_LEDS; j += 2) {
            RGBLED_SetPixel(j, warning_amber);
        }
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(80);

        // All off
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(80);

        // Even LEDs flash
        for (uint8_t j = 0; j < NUM_LEDS; j += 2) {
            RGBLED_SetPixel(j, warning_amber);
        }
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(80);

        // All off
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(80);
    }
}
void underglow_effect() {
    const uint8_t cycles = 2;

    for (uint8_t cycle = 0; cycle < cycles; cycle++) {
        // Cycle through colors for underglow effect
        for (uint8_t hue = 0; hue < 255; hue += 5) {
            RGBLED_Fill(RGBLED_HSV(hue, 255, 255));
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(50);
        }
    }
}
int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, 4);  // Using PC4

    // Set brightness to full
    RGBLED_SetBrightness(50);
    while (1) {
        police_siren_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        knight_rider_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        racing_startup_sequence();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        breathing_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        underglow_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        sparkle_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        engine_rev_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        headlight_mode();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        emergency_vehicle_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        rainbow_wave_effect();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =
    }
}
