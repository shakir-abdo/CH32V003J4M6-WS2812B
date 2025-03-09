#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip

int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, 4);  // Using PC4

    // Set brightness to full
    RGBLED_SetBrightness(255);

    // Define amber/orange color for turn signals
    RGBLED_Color TURN_SIGNAL_ORANGE = RGBLED_RGB(255, 80, 0);

    // Turn signal parameters
    const uint16_t sequential_delay =
        120;                           // Delay between each LED activating (ms)
    const uint16_t hold_time = 250;    // Time all LEDs remain on (ms)
    const uint16_t off_time = 350;     // Time all LEDs remain off (ms)
    const uint8_t sequence_count = 1;  // Number of sequences before pausing
    const uint16_t pause_time = 1000;  // Pause between sets (ms)

    while (1) {
        // Run through several sequences
        for (uint8_t seq = 0; seq < sequence_count; seq++) {
            // Clear all LEDs first
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);

            // Sequential turn-on pattern (one LED at a time)
            for (uint8_t i = 0; i < NUM_LEDS; i++) {
                RGBLED_SetPixel(i, TURN_SIGNAL_ORANGE);
                RGBLED_Show(NUM_LEDS);
                Delay_Ms(sequential_delay);
            }
            // Hold all LEDs on
            Delay_Ms(hold_time);

            // Turn all LEDs off simultaneously
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);

            // Wait before next sequence
            Delay_Ms(off_time);
        }

        // Longer pause between sets of sequences
        Delay_Ms(pause_time);

        for (uint8_t seq = 0; seq < sequence_count; seq++) {
            // Clear all LEDs first
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);

            // Sequential turn-on pattern in reverse (right to left)
            for (int8_t i = NUM_LEDS - 1; i >= 0; i--) {
                RGBLED_SetPixel(i, TURN_SIGNAL_ORANGE);
                RGBLED_Show(NUM_LEDS);
                Delay_Ms(sequential_delay);
            }
            // Hold all LEDs on
            Delay_Ms(hold_time);

            // Turn all LEDs off simultaneously
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);

            // Wait before next sequence
            Delay_Ms(off_time);
        }

        // Longer pause between sets of sequences
        Delay_Ms(pause_time);
    }
}
