#include "leds.h"
#include "communication.h"
#include "artnet.h"

void setup(void)
{
    Serial.begin(115200);
    communicationInit();
    ledsInit();
    artnetInit();
    // artnetSubscribe();
    // artnetSubscribeAll();
    artnetSubscribeAll_2();
}

void loop(void)
{
    ElegantOTA.loop();
    if (!checkOTAProgress())
    {
        artnetParse(); // check if artnet packet has come and execute callback
    }
}
