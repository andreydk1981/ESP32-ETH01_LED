#include "artnet.h"
#include "leds.h"
#include "config.h"

ArtnetReceiver artnet;
uint8_t net = 0;        // 0 - 127
uint8_t subnet = 0;     // 0 - 15
uint16_t universe0 = 0; // 0 - 32767
uint16_t universe1 = 1; // 0 - 32767
uint16_t universe2 = 2; // 0 - 32767
uint16_t universe3 = 3; // 0 - 32767

uint16_t universe4 = 4; // 0 - 32767
uint16_t universe5 = 5; // 0 - 32767
uint16_t universe6 = 6; // 0 - 32767
uint16_t universe7 = 7; // 0 - 32767

uint16_t universe8 = 8;   // 0 - 32767
uint16_t universe9 = 9;   // 0 - 32767
uint16_t universe10 = 10; // 0 - 32767
uint16_t universe11 = 11; // 0 - 32767

uint16_t universe12 = 12;    // 0 - 32767
uint16_t universe13 = 13;    // 0 - 32767
uint16_t universe14 = 14;    // 0 - 32767
uint16_t universe15 = 15;    // 0 - 32767
uint16_t universeTotal = 16; // 0 - 32767

uint16_t start;
uint16_t end;
uint16_t lastUniverse = 0;
uint16_t countUniverse = 0;
uint16_t lastSEQ = 0;
uint16_t nowSEQ = 0;

void artnetInit()
{
    artnet.begin();
}

void artnetParse()
{
    artnet.parse();
}

void artnetSubscribe()
{
    artnet.subscribeArtDmxUniverse(universe0, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = metadata.universe * 170;
    end = (metadata.universe + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds1Set(pixel, idx, data);
    } });
    artnet.subscribeArtDmxUniverse(universe1, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = metadata.universe * 170;
    end = (metadata.universe + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){
        uint16_t idx = (pixel - start) * 3;
        leds1Set(pixel, idx, data);

    } });

    artnet.subscribeArtDmxUniverse(universe2, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = metadata.universe * 170;
    end = (metadata.universe + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds1Set(pixel, idx, data);

    } });
    artnet.subscribeArtDmxUniverse(universe3, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = metadata.universe * 170;
    end = (metadata.universe + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds1Set(pixel, idx, data);
    } });
    artnet.subscribeArtDmxUniverse(universe4, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = (metadata.universe-4) * 170;
    end = (metadata.universe-4 + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 

        uint16_t idx = (pixel - start) * 3;
        leds2Set(pixel, idx, data);
        } });
    artnet.subscribeArtDmxUniverse(universe5, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = (metadata.universe-4) * 170;
    end = (metadata.universe-4 + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds2Set(pixel, idx, data);
    } });
    artnet.subscribeArtDmxUniverse(universe6, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = (metadata.universe-4) * 170;
    end = (metadata.universe-4 + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds2Set(pixel, idx, data);
    } });

    artnet.subscribeArtDmxUniverse(universe7, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                                   {
    start = (metadata.universe-4) * 170;
    end = (metadata.universe-4 + 1) * 170;

    for (uint16_t pixel = start; pixel < end; ++pixel){ 
        uint16_t idx = (pixel - start) * 3;
        leds2Set(pixel, idx, data);
    }
    FastLED.show(); });
}

void artnetSubscribeAll()
{
    artnet.subscribeArtDmx([&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
                           {
                               if (metadata.universe < 4)
                               {
                                   start = metadata.universe * 170;
                                   end = (metadata.universe + 1) * 170;

                                   for (uint16_t pixel = start; pixel < end; ++pixel)
                                   {
                                       uint16_t idx = (pixel - start) * 3;
                                       leds1Set(pixel, idx, data);
                                   }
                               }

                               if (metadata.universe >= 4 && metadata.universe < 8)
                               {
                                   start = (metadata.universe - 4) * 170;
                                   end = (metadata.universe - 3) * 170;

                                   for (uint16_t pixel = start; pixel < end; ++pixel)
                                   {
                                       uint16_t idx = (pixel - start) * 3;
                                       leds2Set(pixel, idx, data);
                                   }
                               }

                               if (metadata.universe >= 8 && metadata.universe < 12)
                               {
                                   start = (metadata.universe - 8) * 170;
                                   end = (metadata.universe - 7) * 170;

                                   for (uint16_t pixel = start; pixel < end; ++pixel)
                                   {
                                       uint16_t idx = (pixel - start) * 3;
                                       leds3Set(pixel, idx, data);
                                   }
                               }

                               if (metadata.universe >= 12 && metadata.universe < 16)
                               {
                                   start = (metadata.universe - 12) * 170;
                                   end = (metadata.universe - 11) * 170;

                                   for (uint16_t pixel = start; pixel < end; ++pixel)
                                   {
                                       uint16_t idx = (pixel - start) * 3;
                                       leds4Set(pixel, idx, data);
                                   }
                               }

#ifdef DEBUG
                               Serial.print(" sequence ");
                               Serial.print(metadata.sequence);
                               Serial.print(" lastSEQ ");
                               Serial.print(lastSEQ);
                            //    Serial.print(" count ");
                            //    Serial.print(countUniverse);
                               Serial.print(" uni ");
                               Serial.print(metadata.universe);
                               Serial.println();
#endif
                               if (metadata.sequence != lastSEQ)
                               {
                                   FastLED.show();
                                   lastSEQ = metadata.sequence;

#ifdef DEBUG
                                   Serial.print(" SHOW ");
#endif
                               }
                           });
}

void callback(const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
{
    if (metadata.universe < 4)
    {
        start = metadata.universe * 170;
        end = (metadata.universe + 1) * 170;

        for (uint16_t pixel = start; pixel < end; ++pixel)
        {
            uint16_t idx = (pixel - start) * 3;
            leds1Set(pixel, idx, data);
        }
    }

    if (metadata.universe >= 4 && metadata.universe < 8)
    {
        start = (metadata.universe - 4) * 170;
        end = (metadata.universe - 3) * 170;

        for (uint16_t pixel = start; pixel < end; ++pixel)
        {
            uint16_t idx = (pixel - start) * 3;
            leds2Set(pixel, idx, data);
        }
    }

    if (metadata.universe >= 8 && metadata.universe < 12)
    {
        start = (metadata.universe - 8) * 170;
        end = (metadata.universe - 7) * 170;

        for (uint16_t pixel = start; pixel < end; ++pixel)
        {
            uint16_t idx = (pixel - start) * 3;
            leds3Set(pixel, idx, data);
        }
    }

    if (metadata.universe >= 12 && metadata.universe < 16)
    {
        start = (metadata.universe - 12) * 170;
        end = (metadata.universe - 11) * 170;

        for (uint16_t pixel = start; pixel < end; ++pixel)
        {
            uint16_t idx = (pixel - start) * 3;
            leds4Set(pixel, idx, data);
        }
    }

    if (metadata.universe > lastUniverse)
        lastUniverse = metadata.universe;

    if (metadata.universe == 0)
    {
        countUniverse = 0;
#ifdef DEBUG
        Serial.print(" DROP ");
#endif
    }

    if (metadata.universe == lastUniverse)
    {
        FastLED.show();
        lastUniverse = countUniverse;
#ifdef DEBUG
        Serial.print(" SHOW ");
#endif
    }

#ifdef DEBUG
    Serial.print(" universe ");
    Serial.print(metadata.universe);
    Serial.print(" count ");
    Serial.print(countUniverse);
    Serial.print(" last ");
    Serial.print(lastUniverse);
    Serial.println();
#endif
    countUniverse += 1;
}

void artnetSubscribeAll_2()
{
    for (uint16_t i = 0; i < universeTotal; i++)
    {
        artnet.subscribeArtDmxUniverse(i, callback);
        Serial.print("subscribeArtDmxUniverse");
        Serial.println(i);
    }
}