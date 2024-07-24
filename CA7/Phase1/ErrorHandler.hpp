#ifndef _ERROR_HANDLER_HPP_
#define _ERROR_HANDLER_HPP_
#include "magic_number.hpp"
#include <iostream>
class ErrorHandler
{
public:
    ErrorHandler(const int request)
    {
        status = request;
    }
    void handle_error() const;

private:
    int status;
};

#endif