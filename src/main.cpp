

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
bool otaInProgress = false;

#include <FastLED.h> // include FastLED *before* Artnet
#include <ArtnetETH.h>

ArtnetReceiver artnet;
uint16_t universe0 = 0; // 0 - 32767
size_t data0;
uint16_t universe1 = 1; // 0 - 32767
uint8_t data1;
uint16_t universe2 = 2; // 0 - 32767
uint16_t universe3 = 3; // 0 - 32767
uint8_t net = 0;        // 0 - 127
uint8_t subnet = 0;     // 0 - 15

// FastLED
#define NUM_LEDS 680
#define BRIGHTNESS 10
CRGB leds0[NUM_LEDS];
const uint8_t PIN_LED_DATA_1 = 5;

uint16_t start;
uint16_t end;
uint8_t univ;

void callback(const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
{
    start = univ * 170;
    end = (univ + 1) * 170;
    // Serial.print("uni ");
    // Serial.print(univ);
    // Serial.print(" start ");
    // Serial.print(start);
    // Serial.print(" end ");
    // Serial.print(end);
    // Serial.print("\n");

    for (uint16_t pixel = start; pixel < end; ++pixel)
    {
        uint16_t idx = (pixel - start) * 3;
        leds0[pixel].r = data[idx + 0];
        leds0[pixel].g = data[idx + 1];
        leds0[pixel].b = data[idx + 2];
    }
    FastLED.show();
}

// WIFI
const char *ssid = "Villa_Beringkit";
const char *password = "1234567890";
AsyncWebServer server(80);
unsigned long ota_progress_millis = 0;
const uint8_t attempts = 1;
uint8_t attemptCount = 0;

// Ethernet stuff
const IPAddress ip(192, 168, 1, 200);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet_mask(255, 255, 255, 0);

void onOTAStart()
{
    Serial.println("OTA update started!");
    otaInProgress = true;
    FastLED.clear();
}

void onOTAProgress(size_t current, size_t final)
{
    if (millis() - ota_progress_millis > 1000 / 16)
    {
        size_t K = final / 64;
        ota_progress_millis = millis();
        Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
        leds0[current / K].b = CRGB::Blue;
        FastLED.show();
    }
}

void onOTAEnd(bool success)
{
    if (success)
    {
        Serial.println("OTA update finished successfully!");
    }
    else
    {
        Serial.println("There was an error during OTA update!");
    }
    otaInProgress = false;
}

void setup(void)
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    ETH.begin();
    ETH.config(ip, gateway, subnet_mask);
    Serial.println("");

    FastLED.addLeds<NEOPIXEL, PIN_LED_DATA_1>(leds0, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED && attemptCount < attempts)
    {
        delay(500);
        Serial.print(attemptCount);
        Serial.print("\n");
        attemptCount++;
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("WIFI address: ");
    Serial.println(WiFi.localIP());
    Serial.print("ETH address: ");
    Serial.println(ETH.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo."); });

    ElegantOTA.begin(&server); // Start ElegantOTA
    ElegantOTA.onStart(onOTAStart);
    ElegantOTA.onProgress(onOTAProgress);
    ElegantOTA.onEnd(onOTAEnd);

    server.begin();
    Serial.println("HTTP server started");

    artnet.begin();
    artnet.setLogger(&Serial);
    // artnet.subscribeArtDmxUniverse(universe0, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
    //                        {
    //                         data0 = data;
    //         for (size_t pixel = 0; pixel < 170; ++pixel) {
    //         size_t idx = (pixel) * 3;
    //         leds0[pixel].r = data[idx + 0];
    //         leds0[pixel].g = data[idx + 1];
    //         leds0[pixel].b = data[idx + 2];
    //     } });
    univ = 1;
    artnet.subscribeArtDmxUniverse(net, subnet, universe1, callback);

    // artnet.subscribeArtDmxUniverse(universe1, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
    //                                {
    //         for (size_t pixel = 170; pixel < 340; ++pixel) {
    //         size_t idx = (pixel - 170) * 3;
    //         leds0[pixel].r = data[idx + 0];
    //         leds0[pixel].g = data[idx + 1];
    //         leds0[pixel].b = data[idx + 2];
    //     } });

    // artnet.subscribeArtDmxUniverse(universe2, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
    //                                {
    //         for (size_t pixel = 340; pixel < 510; ++pixel) {
    //         size_t idx = (pixel - 340) * 3;
    //         leds0[pixel].r = data[idx + 0];
    //         leds0[pixel].g = data[idx + 1];
    //         leds0[pixel].b = data[idx + 2];
    //     } });

    // artnet.subscribeArtDmxUniverse(universe3, [&](const uint8_t *data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote)
    //                                {
    //         for (size_t pixel = 510; pixel < 680; ++pixel) {
    //         size_t idx = (pixel - 510) * 3;
    //         leds0[pixel].r = data[idx + 0];
    //         leds0[pixel].g = data[idx + 1];
    //         leds0[pixel].b = data[idx + 2];
    //     } });
}

void loop(void)
{
    ElegantOTA.loop();
    if (!otaInProgress)
    {
        artnet.parse(); // check if artnet packet has come and execute callback
    }
}
