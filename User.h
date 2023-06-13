#include <string>
#include <vector>
#include "Date.h"


#ifndef User_h
#define User_h
class User {
    public:
    void set_name(std::string);
    std::string get_name();
    void set_username(std::string , std::vector<User>);
    std::string get_username();
    void set_bio(std::string);
    std::string get_bio();
    void set_DateOfBirth ();
    Date get_DateOfBirth ();
    void set_PhoneNumber(std::string);
    std::string get_PhoneNumber();
    void set_password(std::string);
    std::string get_password();
    void set_header(std::string);
    std::string get_header();

    private:
    std::string name;
    std::string username;
    std::string bio;
    Date DateOfBirth;
    std::string PhoneNumber;
    std::string password;
    std::string header;
    //static int number_of_users;
};
#endif