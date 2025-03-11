#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip

int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, 4);  // Using PC4

    // Set brightness to 100% for bright flashes
    RGBLED_SetBrightness(255);

// Number of LEDs in your strip
#define NUM_LEDS 3

    // Define flash patterns
    const uint8_t flash_count = 3;      // Number of flashes per cycle
    const uint16_t flash_on_time = 50;  // Flash on duration (ms)
    const uint16_t flash_off_time =
        50;  // Flash off duration between flashes (ms)
    const uint16_t cycle_pause = 500;  // Pause between flash cycles (ms)

    while (1) {
        // Police car white flashing effect
        for (uint8_t i = 0; i < flash_count; i++) {
            // Flash on (bright white)
            RGBLED_Fill(RGBLED_WHITE);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(flash_on_time);

            // Flash off
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(flash_off_time);
        }

        // Pause between flash cycles
        Delay_Ms(cycle_pause);
    }
}
