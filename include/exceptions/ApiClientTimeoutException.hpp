
#pragma once
#include <typeinfo>
#include "CustomException.hpp"

class ApiClientTimeoutException : public CustomException
{
public:
    ApiClientTimeoutException(const char *format, ...) : CustomException("")
    {
        va_list args;
        va_start(args, format);
        std::string formatted = formatMessage(format, args);
        setMessage("ApiClientTimeoutException " + formatted);
        va_end(args);
    }
};