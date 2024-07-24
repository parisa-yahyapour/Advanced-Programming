#include "Admin.hpp"
using namespace std;

bool Admin :: check_username_password_admin(std :: string name, std :: string pass)
{
    return (name == username) && (pass == password);
}