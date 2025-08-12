#pragma once
#include <Arduino.h>

class Debouncer
{
private:
    unsigned long lastTriggerTime;
    unsigned long intervalMs;

public:
    Debouncer(unsigned long intervalMs)
        : lastTriggerTime(0), intervalMs(intervalMs) {}

    bool shouldTrigger()
    {
        unsigned long currentTime = millis();
        bool shouldUpdate = (currentTime - lastTriggerTime >= intervalMs);

        if (shouldUpdate)
        {
            lastTriggerTime = currentTime;
        }

        return shouldUpdate;
    }

    void triggerNextTime()
    {
        lastTriggerTime = millis() - intervalMs * 2; // Reset to ensure the next call will trigger immediately
    }
};