#include "artnet3.h"
#include "communication.h"
#include "leds.h"

artnetESP32V2 artnet3 = artnetESP32V2();

void uni_0(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = subartnet->subArtnetNum * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds1Set(pixel + K, idx, subartnet->data);
    }
    FastLED.show();
}

void uni_1(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = subartnet->subArtnetNum * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds1Set(pixel + K, idx, subartnet->data);
    }
}
void uni_2(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = subartnet->subArtnetNum * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds1Set(pixel + K, idx, subartnet->data);
    }
}
void uni_3(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = subartnet->subArtnetNum * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds1Set(pixel + K, idx, subartnet->data);
    }
}

void uni_4(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = (subartnet->subArtnetNum - 4) * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds2Set(pixel + K, idx, subartnet->data);
    }
}

void uni_5(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = (subartnet->subArtnetNum - 4) * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds2Set(pixel + K, idx, subartnet->data);
    }
}

void uni_6(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = (subartnet->subArtnetNum - 4) * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds2Set(pixel + K, idx, subartnet->data);
    }
}

void uni_7(void *param)
{
    subArtnet *subartnet = (subArtnet *)param;
    uint16_t K = (subartnet->subArtnetNum - 4) * 170;
    for (uint16_t pixel = 0; pixel < (subartnet->len) / 3; ++pixel)
    {
        uint16_t idx = pixel * 3;
        leds2Set(pixel + K, idx, subartnet->data);
    }
}

void artnet3Init()
{
    artnet3.addSubArtnet(0, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_0);
    artnet3.addSubArtnet(1, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_1);
    artnet3.addSubArtnet(2, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_2);
    artnet3.addSubArtnet(3, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_3);

    artnet3.addSubArtnet(4, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_4);
    artnet3.addSubArtnet(5, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_5);
    artnet3.addSubArtnet(6, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_6);
    artnet3.addSubArtnet(7, 510, UNIVERSE_SIZE_IN_CHANNEL, &uni_7);

    artnet3.setNodeName("Arnet Node esp32");
    if (artnet3.listen(6454))
    {
        Serial.print("artnet3 Listening on IP: ");
        Serial.println(ETH.localIP());
    }
}

void artnet3Parse()
{

}
