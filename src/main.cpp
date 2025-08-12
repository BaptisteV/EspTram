#include <Arduino.h>
#include <WiFi.h>
#include "TmDisplay.hpp"
#include "FochApiClient.hpp"
#include "exceptions/ApiClientTimeoutException.hpp"
#include "Debouncer.hpp"
#include "Config.cpp"

FochApiClient apiClient(DIVIA_API_URL, 250);
TmDisplay tmDisplay;
Debouncer apiDebouncer(1000);

void setup()
{
    Serial.begin(115200);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.printf("Wifi connected %s\n", WiFi.localIP().toString().c_str());
}

void loop()
{
    if (!apiDebouncer.shouldTrigger())
    {
        return;
    }

    try
    {
        FochResponse fochResponse;
        apiClient.fetchFochResponse(fochResponse);
        tmDisplay.showNextTram(fochResponse.horairesFoch);
        Serial.print('|');
    }
    catch (const ApiClientTimeoutException &e)
    {
        Serial.println();
        Serial.println(e.what());
        apiDebouncer.triggerNextTime();
    }
    catch (const std::exception &e)
    {
        Serial.println();
        Serial.printf("Error: %s\n", e.what());
    }
}