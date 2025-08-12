
#pragma once
#include <exception>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <iostream>

class CustomException : public std::exception
{
private:
    std::string message;

public:
    const char *what() const noexcept override
    {
        return message.c_str();
    }

    virtual ~CustomException() = default;

protected:
    CustomException(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        message = formatMessage(format, args);
        va_end(args);
    }
    static std::string formatMessage(const char *format, va_list args)
    {
        va_list args_copy;
        va_copy(args_copy, args);
        int size = std::vsnprintf(nullptr, 0, format, args_copy);
        va_end(args_copy);

        if (size > 0)
        {
            std::unique_ptr<char[]> buffer(new char[size + 1]);
            std::vsnprintf(buffer.get(), size + 1, format, args);
            return std::string(buffer.get());
        }
        return "Exception occurred";
    }

    void setMessage(const std::string &msg)
    {
        message = msg;
    }
};