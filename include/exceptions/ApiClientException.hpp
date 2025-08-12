
#pragma once
#include "CustomException.hpp"

class ApiClientException : public CustomException
{
public:
    ApiClientException(const char *format, ...) : CustomException("")
    {
        va_list args;
        va_start(args, format);
        std::string formatted = formatMessage(format, args);
        setMessage("ApiClientException " + formatted);
        va_end(args);
    }
};