#pragma once
#include <exception>
#include <string>

class Exception: public std::exception{
    std::string message;

    const char* what() const noexcept override{
        return message.c_str();
    }

public:
    Exception(std::string text): message(text){}
};