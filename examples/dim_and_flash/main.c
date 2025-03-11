#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip

int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, 4);  // Using PC4

    // Effect parameters
    const uint8_t dim_level = 20;     // Standing light brightness level (0-255)
    const uint8_t flash_level = 255;  // Flash brightness level (0-255)
    const uint16_t flash_duration = 70;  // Duration of each flash (ms)
    const uint16_t flash_gap = 100;      // Gap between flashes (ms)
    const uint16_t cycle_pause = 1000;   // Pause before repeating effect (ms)

    while (1) {
        // 1. Start with dim white standing light
        RGBLED_SetBrightness(dim_level);
        RGBLED_Fill(RGBLED_WHITE);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(cycle_pause);

        // 2. First flash
        RGBLED_SetBrightness(flash_level);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(flash_duration);

        // 3. Back to dim
        RGBLED_SetBrightness(dim_level);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(flash_gap);

        // 4. Second flash
        RGBLED_SetBrightness(flash_level);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(flash_duration);

        // 5. Back to dim and continue
        RGBLED_SetBrightness(dim_level);
        RGBLED_Show(NUM_LEDS);
    }
}
