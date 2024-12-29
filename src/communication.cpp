#include "communication.h"
#include "leds.h"
#include "artnet.h"
// #include "artnet2.h"
#include "config.h"


const char *ssid = "Villa_Beringkit";
const char *password = "1234567890";

// Ethernet stuff
const IPAddress ip(192, 168, 1, 200);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet_mask(255, 255, 255, 0);

void communicationInit()
{
#ifdef WIFI
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
#endif

#ifdef ETHERNET
    ETH.begin();
    ETH.config(ip, gateway, subnet_mask);
    ETH.setHostname("esp32-ArtnNet");
#endif

#ifdef WIFI
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
#endif
#ifdef ETHERNET
    if (ETH.fullDuplex())
    {
        Serial.print("FULL_DUPLEX ");
    } 
    Serial.print(ETH.linkSpeed());
    Serial.println("Mbps");
    Serial.print("ETH address: ");
    Serial.println(ETH.localIP());
    
#endif
}