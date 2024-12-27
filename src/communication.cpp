#include "communication.h"
#include "leds.h"
#include "artnet.h"

bool otaInProgress = false;

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

boolean checkOTAProgress(){
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
    otaInProgress = false;
}

void communicationInit()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    ETH.begin();
    ETH.config(ip, gateway, subnet_mask);

    // Wait for WIFI connection
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
}