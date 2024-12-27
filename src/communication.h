#pragma once

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

void onOTAStart();
void onOTAProgress(size_t, size_t);
void onOTAEnd(bool);
void communicationInit ();
boolean checkOTAProgress();