#include "leds.h"

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
const uint8_t PIN_LED_DATA_1 = 5;
const uint8_t PIN_LED_DATA_2 = 17;

void ledsInit()
{
    FastLED.addLeds<NEOPIXEL, PIN_LED_DATA_1>(leds1, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, PIN_LED_DATA_2>(leds2, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

void leds1Set(size_t K, size_t current, CRGB color)
{
    leds1[current / K] = color;
}

void leds1Set(uint16_t pixel, uint16_t idx, const uint8_t *data)
{
    leds1[pixel].r = data[idx + 0];
    leds1[pixel].g = data[idx + 1];
    leds1[pixel].b = data[idx + 2];
}
void leds2Set(uint16_t pixel, uint16_t idx, const uint8_t *data)
{
    leds2[pixel].r = data[idx + 0];
    leds2[pixel].g = data[idx + 1];
    leds2[pixel].b = data[idx + 2];
}



void leds2Set(size_t K, size_t current, CRGB color)
{
    leds2[current / K] = color;
}