#pragma once
#include <Arduino.h>
#include <unity.h>
#include <chrono>
#include "Debouncer.hpp"

void test_debouncer_initial_trigger()
{
    Debouncer debouncer(std::chrono::milliseconds(10));
    TEST_ASSERT_TRUE_MESSAGE(debouncer.shouldTrigger(), "Should initially trigger");
}

void test_debouncer_no_double_trigger()
{
    Debouncer debouncer(std::chrono::milliseconds(10));
    debouncer.shouldTrigger();
    TEST_ASSERT_FALSE_MESSAGE(debouncer.shouldTrigger(), "Should not trigger right after first trigger");
}

void test_debouncer_retrigger()
{
    Debouncer debouncer(std::chrono::milliseconds(10));
    debouncer.shouldTrigger();
    TEST_ASSERT_FALSE_MESSAGE(debouncer.shouldTrigger(), "When trigger is waiting");

    debouncer.triggerNextTime();
    TEST_ASSERT_TRUE_MESSAGE(debouncer.shouldTrigger(), "Should be unlocked by triggerNextTime");
}

void test_debouncer_10ms()
{
    auto interval = std::chrono::milliseconds(10);
    auto start = std::chrono::steady_clock::now();
    Debouncer debouncer(interval);

    TEST_ASSERT_TRUE(debouncer.shouldTrigger());
    while (std::chrono::steady_clock::now() - start < interval)
    {
        TEST_ASSERT_FALSE_MESSAGE(debouncer.shouldTrigger(), "Should not trigger when interval is not over");
        delay(1);
    }
    TEST_ASSERT_TRUE_MESSAGE(debouncer.shouldTrigger(), "Should trigger after interval is over");
}
