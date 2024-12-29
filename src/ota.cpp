#include "ota.h"
#include "config.h"
#include "leds.h"

AsyncWebServer server(80);
unsigned long ota_progress_millis = 0;
const uint8_t attempts = 1;
uint8_t attemptCount = 0;
bool otaInProgress = false;

void onOTAStart()
{
    Serial.println("OTA update started!");
    otaInProgress = true;
    FastLED.clear();
}

boolean checkOTAProgress()
{
    return otaInProgress;
}

void onOTAProgress(size_t current, size_t final)
{
    CRGB colorBlue = CRGB::Blue;
    CRGB colorRed = CRGB::Red;
    if (millis() - ota_progress_millis > 1000 / 16)
    {
        size_t K = final / 64;
        ota_progress_millis = millis();
        Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
        leds1Set(K, current, colorBlue);
        leds2Set(K, current, colorRed);
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
    // otaInProgress = false;
}

void otaInit()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo."); });

    ElegantOTA.begin(&server); // Start ElegantOTA
    ElegantOTA.onStart(onOTAStart);
    ElegantOTA.onProgress(onOTAProgress);
    ElegantOTA.onEnd(onOTAEnd);

    server.begin();
    Serial.println("HTTP server started");
}