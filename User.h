#include <string>
#include <vector>
#include "Date.h"


#ifndef User_h
#define User_h
class User {
    public:
    void set_name(std::string);
    void set_username(std::string , std::vector<User>);
    std::string get_username();
    void set_password(std::string);
    std::string get_password();
    private:
    std::string name;
    std::string username;
    std::string bio;
    Date DateOfBirth;
    std::string phoneNumber;
    std::string password;
    std::string header;
    static int number_of_users;
};
#endif