#pragma once
#include <string>

class TramFoch
{
public:
    std::string arrivesAt; // Format ISO 8601, ex: "2025-08-01T17:18:00"
    int minutesLeft;
    int secondsLeft;
    TramFoch(const std::string &arrivesAt, int minutesLeft, int secondsLeft)
        : arrivesAt(arrivesAt), minutesLeft(minutesLeft), secondsLeft(secondsLeft) {};
    TramFoch()
        : arrivesAt(""), minutesLeft(0), secondsLeft(0) {};
};