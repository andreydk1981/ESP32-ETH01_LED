#include "artnet.h"
#include "leds.h"

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
uint16_t universeTotal = 7; // 0 - 32767

uint16_t start;
uint16_t end;

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

                               if (metadata.universe >= 4)
                               {
                                   start = (metadata.universe - 4) * 170;
                                   end = (metadata.universe - 3) * 170;

                                   for (uint16_t pixel = start; pixel < end; ++pixel)
                                   {
                                       uint16_t idx = (pixel - start) * 3;
                                       leds2Set(pixel, idx, data);
                                   }
                               }

                               if (metadata.universe == 7)
                               {
                                   FastLED.show();
                               } });
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

    if (metadata.universe >= 4)
    {
        start = (metadata.universe - 4) * 170;
        end = (metadata.universe - 3) * 170;

        for (uint16_t pixel = start; pixel < end; ++pixel)
        {
            uint16_t idx = (pixel - start) * 3;
            leds2Set(pixel, idx, data);
        }
    }

    if (metadata.universe == universeTotal)
    {
        FastLED.show();
    }
}

void artnetSubscribeAll_2()
{   for (uint16_t i = 0; i < 8; i++)
{
    artnet.subscribeArtDmxUniverse(i, callback);
    Serial.print("subscribeArtDmxUniverse");
    Serial.println(i);
}

}