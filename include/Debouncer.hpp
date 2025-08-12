#pragma once
#include <Arduino.h>

class Debouncer
{
private:
    std::chrono::steady_clock::time_point lastTriggerTime;
    std::chrono::microseconds interval;

public:
    Debouncer(const std::chrono::milliseconds &intervalMs)
        : lastTriggerTime(std::chrono::steady_clock::now() - intervalMs), interval(std::chrono::microseconds(intervalMs)) {}

    bool shouldTrigger()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = now - lastTriggerTime;
        bool shouldUpdate = elapsed >= interval;

        if (shouldUpdate)
        {
            lastTriggerTime = now;
        }
        return shouldUpdate;
    }

    void triggerNextTime()
    {
        lastTriggerTime = std::chrono::steady_clock::now() - interval;
    }
};