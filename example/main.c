#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip

int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, LED_PIN);

    // Set brightness (0-255)
    RGBLED_SetBrightness(50);

    while (1) {
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
        for (uint8_t i = 0; i < 255; i++) {
            RGBLED_Fill(RGBLED_HSV(i, 255, 255));
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(10);
        }
    }
}
