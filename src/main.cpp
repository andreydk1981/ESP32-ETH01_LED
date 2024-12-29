#include "config.h"

#include "leds.h"
#include "communication.h"
#ifdef OTA
#include "ota.h"
#endif
#include "artnet3.h"

void setup(void)
{
    Serial.begin(115200);

    communicationInit();
#ifdef OTA
    otaInit();
#endif
    ledsInit();
    artnet3Init();
    // artnet3Subscribe();
    // artnetSubscribeAll();
    // artnet3SubscribeAll_2();
}

void loop(void)
{
#ifdef OTA
    ElegantOTA.loop();
#endif
}
