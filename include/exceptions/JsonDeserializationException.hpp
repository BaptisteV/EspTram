#pragma once
#include "CustomException.hpp"

class JsonDeserializationException : public CustomException
{
public:
    JsonDeserializationException(const char *format, ...) : CustomException("")
    {
        va_list args;
        va_start(args, format);
        std::string formatted = formatMessage(format, args);
        setMessage("JsonDeserializationException " + formatted);
        va_end(args);
    }
};