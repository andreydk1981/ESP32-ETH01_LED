#pragma once

#include <FastLED.h> // include FastLED *before* Artnet

#define NUM_LEDS 680
#define BRIGHTNESS 5

void ledsInit();

void leds1Set(size_t K, size_t current, CRGB color);
void leds2Set(size_t K, size_t current, CRGB color);

void leds1Set(uint16_t pixel, uint16_t idx, const uint8_t *data);
void leds2Set(uint16_t pixel, uint16_t idx, const uint8_t *data);
void leds3Set(uint16_t pixel, uint16_t idx, const uint8_t *data);
void leds4Set(uint16_t pixel, uint16_t idx, const uint8_t *data);