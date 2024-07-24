#include "ErrorHandler.hpp"
using namespace std;

void ErrorHandler :: handle_error() const
{
    switch (status)
    {
    case BAD_REQUEST:
        cout << "Bad Request" << endl;
        break;
    case NOT_FOUND:
        cout << "Not Found" << endl;
        break;
    case PERMISSION_DENIED:
        cout << "Permission Denied" << endl;
        break;
    case EMPTY_ERROR:
        cout << "Empty" << endl;
        break;
    case NOT_AVAILABLE_FOR_NEXT_WEEK:
        cout << "This player is not available for next week" << endl;
        break;
    default:
        break;
    }
}