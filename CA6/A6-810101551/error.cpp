#include "error.hpp"
void ErrorHandler ::handle_error() const
{
    switch (error_code)
    {
    case INVALID_ARGUMENT:
        cout << "INVALID_ARGUMENTS" << endl;
        break;
    case DUPLICATE_MISSION_ID:
        cout << "DUPLICATE_MISSION_ID" << endl;
        break;
    case MISSION_NOT_FOUND:
        cout << "MISSION_NOT_FOUND" << endl;
        break;
    case DUPLICATE_DRIVER_MISSION:
        cout << "DUPLICATE_DRIVER_MISSION" << endl;
        break;
    case DRIVER_MISSION_NOT_FOUND:
        cout << "DRIVER_MISSION_NOT_FOUND" << endl;
        break;
    default:
        break;
    }
}