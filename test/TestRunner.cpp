#include <Arduino.h>
#include <unity.h>
#include "FochResponseTest.hpp"
#include "DebouncerTest.hpp"

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_client_deserialize_ok);
    RUN_TEST(test_client_deserialize_empty_body);
    RUN_TEST(test_client_deserialize_empty_json);

    RUN_TEST(test_debouncer_initial_trigger);
    RUN_TEST(test_debouncer_no_double_trigger);
    RUN_TEST(test_debouncer_retrigger);
    RUN_TEST(test_debouncer_10ms);
    UNITY_END();
}

void loop()
{
}