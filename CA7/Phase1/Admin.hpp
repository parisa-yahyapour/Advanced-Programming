#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include <string>
#include "magic_number.hpp"

class Admin
{
public:
    bool check_username_password_admin(std ::string name, std ::string pass);

private:
    std ::string username = DEFAULT_ADMIN_USERNAME;
    std ::string password = DEFAULT_ADMIN_PASSWORD;
};

#endif