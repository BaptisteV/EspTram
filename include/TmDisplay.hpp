#pragma once
#include <TM1637Display.h>
#include <string>
#include <memory>
#include "TramFoch.hpp"

#define CLK 22 // Pin for Clock Input
#define DIO 23 // Pin for Data Input/Output

class TmDisplay
{
public:
    TmDisplay()
    {
        display = std::unique_ptr<TM1637Display>(new TM1637Display(CLK, DIO));
        display->setBrightness(4, true);
        display->setSegments(fourUnderscores);
    };

    void showNextTram(const std::array<TramFoch, 2> &horaires)
    {
        int indexHoraire = tramHasLeft(horaires[0]) ? 0 : 1;
        auto newHoraire = horaires[indexHoraire];
        if (tooFarInFuture(newHoraire))
        {
            display->setSegments(fourUnderscores);
            return;
        }

        showTime(newHoraire.minutesLeft, newHoraire.secondsLeft);
    };

private:
    void showTime(int minute, int second)
    {
        uint8_t segments[4] = {
            display->encodeDigit(minute / 10), // Tens of minutes
            display->encodeDigit(minute % 10), // Units of minutes
            display->encodeDigit(second / 10), // Tens of seconds
            display->encodeDigit(second % 10)  // Units of seconds
        };
        display->setSegments(segments);
    };

    bool tooFarInFuture(const TramFoch &tram)
    {
        return tram.minutesLeft > 99;
    };

    bool tramHasLeft(const TramFoch &tram)
    {
        return tram.minutesLeft >= 0 && tram.secondsLeft >= 0;
    };

    std::unique_ptr<TM1637Display> display;
    uint8_t fourUnderscores[4] = {0x08, 0x08, 0x08, 0x08};
};