#include "artnet2.h"
#include "leds.h"
#include "config.h"

ArtnetWifi artnet2;
WiFiUDP UdpSend2;

const int startUniverse = 0;       // CHANGE FOR YOUR SETUP most software this is 1, some software send2 out artnet2 first universe as 0.
const char host[] = "192.168.1.6"; // CHANGE FOR YOUR SETUP your destination

uint16_t start2;
uint16_t end2;
uint16_t lastUniverse2 = 0;
uint16_t countUniverse2 = 0;

void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t *data)
{
    countUniverse2 +=1;
    if (universe < 4)
    {
        start2 = universe * 170;
        end2 = (universe + 1) * 170;

        for (uint16_t pixel = start2; pixel < end2; ++pixel)
        {
            uint16_t idx = (pixel - start2) * 3;
            leds1Set(pixel, idx, data);
        }
    }

    if (universe >= 4)
    {
        start2 = (universe - 4) * 170;
        end2 = (universe - 3) * 170;

        for (uint16_t pixel = start2; pixel < end2; ++pixel)
        {
            uint16_t idx = (pixel - start2) * 3;
            leds2Set(pixel, idx, data);
        }
    }
    
    if (universe > lastUniverse2)
        lastUniverse2 = universe;
    if (universe == lastUniverse2)
    {
        FastLED.show();
        countUniverse2 = 0;
    }
    if (countUniverse2 - 1 > lastUniverse2)
    {
        // Serial.print("countUniverse2 > lastUniverse2 ");
        // Serial.print(countUniverse2);
        lastUniverse2 -= 1;
        countUniverse2 = 0;
        
    }
    
    

#ifdef DEBUG
    Serial.print(" universe ");
    Serial.print(universe);
    Serial.print(" count ");
    Serial.print(countUniverse2);
    Serial.print(" last ");
    Serial.print(lastUniverse2);
    Serial.println();

    if (universe == lastUniverse2)
    {
        bool tail = false;

        Serial.print("DMX: Univ: ");
        Serial.print(universe, DEC);
        Serial.print(", Seq: ");
        Serial.print(sequence, DEC);
        Serial.print(", Data (");
        Serial.print(length, DEC);
        Serial.print("): ");

        if (length > 16)
        {
            length = 16;
            tail = true;
        }
        // send2 out the buffer
        for (uint16_t i = 0; i < length; i++)
        {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
        if (tail)
        {
            Serial.print("...");
        }
        Serial.println();
    }
#endif
}

void artnet2Init()
{
    artnet2.setArtDmxCallback(onDmxFrame);
    artnet2.begin();
}

void artnet2Parse()
{
    artnet2.read();
}
