#ifndef _ERROR_HPP_
#define _ERROR_HPP_

#include <iostream>
using namespace std;
enum ERRORS
{
    INVALID_ARGUMENT,
    DUPLICATE_MISSION_ID,
    MISSION_NOT_FOUND,
    DUPLICATE_DRIVER_MISSION,
    DRIVER_MISSION_NOT_FOUND
};

class ErrorHandler
{
private:
    int error_code;
public:
    ErrorHandler(int error)
    {
        error_code = error;
    }
    void handle_error() const;
};

#endif