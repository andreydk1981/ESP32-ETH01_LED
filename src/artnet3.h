#define NUM_LEDS_PER_STRIP 170
#define NUMSTRIPS 3
#define NB_CHANNEL_PER_LED 3 //Should be 4 if your sending tool is sending RGBW
#define COLOR_GRB
#define UNIVERSE_SIZE_IN_CHANNEL  (170 * 3)  //here we define a universe of 170 pixels each pixel is composed of 3 channels
#define START_UNIVERSE 0
//#define USE_PIXELSLIB
#include "I2SClocklessLedDriver.h"
#include "Arduino.h"
#include "artnetESP32V2.h"

void artnet3Init();
void artnet3Parse();