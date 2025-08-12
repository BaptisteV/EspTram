#pragma once
#include <string>
#include <array>
#include <ArduinoJson.h>
#include <chrono>
#include "TramFoch.hpp"
#include "exceptions/JsonDeserializationException.hpp"

class FochResponse
{
public:
    std::array<TramFoch, 2> horairesFoch;
    FochResponse(const std::array<TramFoch, 2> &horairesFoch)
        : horairesFoch(horairesFoch) {};
    FochResponse()
        : horairesFoch() {};

    static void deserialize(const std::string &body, FochResponse &response)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);
        if (error)
        {
            throw JsonDeserializationException("Failed to deserialize JSON: %s", error.c_str());
        }

        JsonObject obj = doc.as<JsonObject>();
        if (!obj["horairesFoch"].is<JsonArray>())
        {
            throw JsonDeserializationException("Missing 'horairesFoch' array in JSON response");
        }

        JsonArray arr = obj["horairesFoch"].as<JsonArray>();
        if (arr.size() != 2)
        {
            throw JsonDeserializationException("JSON property 'horairesFoch' does not contain exactly 2 elements");
        }

        for (size_t i = 0; i < 2; ++i)
        {
            JsonObject h = arr[i];
            response.horairesFoch[i].arrivesAt = h["arrivesAt"] | "";
            response.horairesFoch[i].minutesLeft = h["minutesLeft"] | 0;
            response.horairesFoch[i].secondsLeft = h["secondsLeft"] | 0;
        }
    }
};