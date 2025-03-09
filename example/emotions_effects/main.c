#include "ch32v003fun.h"
#include "rgbled.h"

#define LED_PIN 4   // Using PC4
#define NUM_LEDS 3  // Number of LEDs in your strip
void happy_emotion() {
    // Bright yellow/warm colors with energetic bouncing effect
    const RGBLED_Color happy_yellow = RGBLED_RGB(255, 220, 0);
    const RGBLED_Color happy_orange = RGBLED_RGB(255, 165, 0);

    for (uint8_t cycles = 0; cycles < 3; cycles++) {
        // Bounce effect - fast and energetic
        for (int8_t i = 0; i < NUM_LEDS; i++) {
            RGBLED_Clear();
            RGBLED_SetPixel(i, happy_yellow);
            if (i > 0) RGBLED_SetPixel(i - 1, happy_orange);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(70);  // Fast movement
        }

        for (int8_t i = NUM_LEDS - 1; i >= 0; i--) {
            RGBLED_Clear();
            RGBLED_SetPixel(i, happy_yellow);
            if (i < NUM_LEDS - 1) RGBLED_SetPixel(i + 1, happy_orange);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(70);
        }

        // Happy "pulse" effect
        for (uint8_t p = 0; p < 2; p++) {
            // Pulse on
            RGBLED_Fill(happy_yellow);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(150);

            // Pulse off
            RGBLED_Clear();
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(80);
        }
    }
}
void sad_emotion() {
    // Slow, gentle blue fading to represent sadness
    const RGBLED_Color sad_blue = RGBLED_RGB(30, 60, 255);
    const RGBLED_Color deep_blue = RGBLED_RGB(0, 20, 120);

    // Slow breathing effect with blue tones
    for (uint8_t cycle = 0; cycle < 2; cycle++) {
        // Fade in very slowly
        for (uint8_t i = 5; i < 100; i += 3) {
            RGBLED_Fill(sad_blue);
            RGBLED_SetBrightness(i);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(60);  // Slow fade
        }

        // Hold at peak for a moment
        Delay_Ms(700);

        // Fade out even more slowly
        for (uint8_t i = 100; i > 5; i -= 2) {
            RGBLED_Fill(sad_blue);
            RGBLED_SetBrightness(i);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(70);  // Even slower fade out
        }

        // Brief dark blue moment representing melancholy
        RGBLED_Fill(deep_blue);
        RGBLED_SetBrightness(20);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
    }

    // Reset brightness
    RGBLED_SetBrightness(255);
}
void bored_emotion() {
    // Dull gray-green color with repetitive, monotonous pattern
    const RGBLED_Color bored_gray = RGBLED_RGB(100, 120, 100);

    // Monotonous, repetitive ticking
    for (uint8_t repeat = 0; repeat < 7; repeat++) {
        // Dim pulse
        RGBLED_Fill(bored_gray);
        RGBLED_SetBrightness(40);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(300);

        // Slightly dimmer
        RGBLED_SetBrightness(20);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(600);
    }

    // One random blip of activity showing momentary interest
    uint8_t random_led = 1;  // Not truly random but works for demonstration
    RGBLED_Clear();
    RGBLED_SetBrightness(150);
    RGBLED_SetPixel(random_led, RGBLED_RGB(150, 150, 150));
    RGBLED_Show(NUM_LEDS);
    Delay_Ms(100);

    // Back to bored state
    RGBLED_Fill(bored_gray);
    RGBLED_SetBrightness(30);
    RGBLED_Show(NUM_LEDS);
    Delay_Ms(1000);

    // Reset brightness
    RGBLED_SetBrightness(255);
}
void excited_emotion() {
    // Bright, rapidly changing colors at high energy
    const RGBLED_Color excited_magenta = RGBLED_RGB(255, 0, 255);
    const RGBLED_Color excited_cyan = RGBLED_RGB(0, 255, 255);
    const RGBLED_Color excited_yellow = RGBLED_RGB(255, 255, 0);

    // Rapid flashing/strobing with bright colors
    for (uint8_t flash = 0; flash < 5; flash++) {
        // Flash magenta
        RGBLED_Fill(excited_magenta);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(70);

        // Flash cyan
        RGBLED_Fill(excited_cyan);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(70);
    }

    // Rapid chase sequence showing energy
    for (uint8_t chase = 0; chase < 3; chase++) {
        for (uint8_t i = 0; i < NUM_LEDS; i++) {
            RGBLED_Clear();
            RGBLED_SetPixel(i, excited_yellow);
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(40);  // Very fast
        }
    }

    // Energetic all-on pulsing finale
    for (uint8_t pulse = 0; pulse < 3; pulse++) {
        // Pulse on
        RGBLED_Fill(excited_yellow);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(100);

        // Quickly change color
        RGBLED_Fill(excited_magenta);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(100);

        // Quickly change color again
        RGBLED_Fill(excited_cyan);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(100);
    }
}
void calm_emotion() {
    // Gentle, soft colors with slow transitions
    const RGBLED_Color calm_teal = RGBLED_RGB(0, 180, 180);
    const RGBLED_Color calm_lavender = RGBLED_RGB(150, 130, 220);

    // Very gradual crossfade between calming colors
    for (uint8_t cycle = 0; cycle < 3; cycle++) {
        // Fade from teal to lavender
        for (uint8_t i = 0; i <= 20; i++) {
            uint8_t teal_mix = 20 - i;
            uint8_t lavender_mix = i;

            for (uint8_t led = 0; led < NUM_LEDS; led++) {
                RGBLED_Color mixed_color;
                mixed_color.r =
                    (calm_teal.r * teal_mix + calm_lavender.r * lavender_mix) /
                    20;
                mixed_color.g =
                    (calm_teal.g * teal_mix + calm_lavender.g * lavender_mix) /
                    20;
                mixed_color.b =
                    (calm_teal.b * teal_mix + calm_lavender.b * lavender_mix) /
                    20;

                RGBLED_SetPixel(led, mixed_color);
            }
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(120);  // Slow, gentle transition
        }

        // Fade from lavender back to teal
        for (uint8_t i = 0; i <= 20; i++) {
            uint8_t lavender_mix = 20 - i;
            uint8_t teal_mix = i;

            for (uint8_t led = 0; led < NUM_LEDS; led++) {
                RGBLED_Color mixed_color;
                mixed_color.r =
                    (calm_lavender.r * lavender_mix + calm_teal.r * teal_mix) /
                    20;
                mixed_color.g =
                    (calm_lavender.g * lavender_mix + calm_teal.g * teal_mix) /
                    20;
                mixed_color.b =
                    (calm_lavender.b * lavender_mix + calm_teal.b * teal_mix) /
                    20;

                RGBLED_SetPixel(led, mixed_color);
            }
            RGBLED_Show(NUM_LEDS);
            Delay_Ms(120);
        }
    }
}
void angry_emotion() {
    // Intense reds with sharp, abrupt patterns
    const RGBLED_Color angry_red = RGBLED_RGB(255, 0, 0);
    const RGBLED_Color angry_orange = RGBLED_RGB(255, 60, 0);
    const RGBLED_Color dark_red = RGBLED_RGB(120, 0, 0);

    // Initial flash of anger
    for (uint8_t flash = 0; flash < 3; flash++) {
        RGBLED_Fill(angry_red);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(70);

        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(70);
    }

    // Simmering anger effect
    for (uint8_t simmer = 0; simmer < 3; simmer++) {
        // "Boiling" effect with reds and oranges
        for (uint8_t led = 0; led < NUM_LEDS; led++) {
            // Alternate between dark red, angry red and angry orange
            if (led % 3 == 0) {
                RGBLED_SetPixel(led, angry_red);
            } else if (led % 3 == 1) {
                RGBLED_SetPixel(led, angry_orange);
            } else {
                RGBLED_SetPixel(led, dark_red);
            }
        }
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(200);

        // Shift pattern
        RGBLED_Color temp = RGBLED_RGB(0, 0, 0);
        temp.r = RGBLED_GetPixel(0).r;
        temp.g = RGBLED_GetPixel(0).g;
        temp.b = RGBLED_GetPixel(0).b;

        for (uint8_t led = 0; led < NUM_LEDS - 1; led++) {
            RGBLED_Color next_color;
            next_color.r = RGBLED_GetPixel(led + 1).r;
            next_color.g = RGBLED_GetPixel(led + 1).g;
            next_color.b = RGBLED_GetPixel(led + 1).b;
            RGBLED_SetPixel(led, next_color);
        }
        RGBLED_SetPixel(NUM_LEDS - 1, temp);
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(200);
    }

    // Angry "explosion" finale
    RGBLED_Fill(angry_red);
    RGBLED_Show(NUM_LEDS);
    Delay_Ms(500);
}
int main() {
    SystemInit();

    // Initialize the LED strip
    RGBLED_Init(GPIOC, 4);  // Using PC4

    // Set brightness to full
    RGBLED_SetBrightness(50);
    while (1) {
        happy_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        sad_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        bored_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        excited_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        calm_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =

        angry_emotion();
        // = = = wait = = =
        RGBLED_Clear();
        RGBLED_Show(NUM_LEDS);
        Delay_Ms(1000);
        // = = = wait = = =
    }
}
