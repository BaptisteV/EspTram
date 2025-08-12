#include <Arduino.h>
#include <unity.h>
#include <string>
#include <vector>
#include "TramFoch.hpp"
#include "ArduinoJson.h"
#include "FochResponse.hpp"

TramFoch tramFoch1{"2025-08-11T19:34:00", 1, 1};
TramFoch tramFoch2{"2025-08-11T19:44:01", 11, 2};

// /!\ tramFoch1 and tramFoch2 values must match the those in jsonOk
std::string jsonOk = R"({
"horairesFoch" : [
    {
        "arrivesAt" : "2025-08-11T19:34:00",
        "minutesLeft" : 1,
        "secondsLeft": 1
    },
    {
        "arrivesAt" : "2025-08-11T19:44:01",
        "minutesLeft" : 11,
        "secondsLeft" : 2
    }
]
})";

void test_deserialize_ok()
{
    FochResponse response;
    FochResponse::deserialize(jsonOk, response);

    TEST_ASSERT_EQUAL_STRING(response.horairesFoch[0].arrivesAt.c_str(), tramFoch1.arrivesAt.c_str());
    TEST_ASSERT_EQUAL_INT(response.horairesFoch[0].minutesLeft, tramFoch1.minutesLeft);
    TEST_ASSERT_EQUAL_INT(response.horairesFoch[0].secondsLeft, tramFoch1.secondsLeft);
    TEST_ASSERT_EQUAL_STRING(response.horairesFoch[1].arrivesAt.c_str(), tramFoch2.arrivesAt.c_str());
    TEST_ASSERT_EQUAL_INT(response.horairesFoch[1].minutesLeft, tramFoch2.minutesLeft);
    TEST_ASSERT_EQUAL_INT(response.horairesFoch[1].secondsLeft, tramFoch2.secondsLeft);
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_deserialize_ok);
    UNITY_END();
}

void loop()
{
}