#ifndef User_h
#define User_h

#include <string>
#include <vector>
#include "Date.h"
#include "terminal.h"

class User {
    public:
    void set_name(std::string);
    void set_username(std::string , std::vector<User>, Terminal);
    std::string get_username();
    void set_bio(std::string);
    std::string get_bio();
    void set_DateOfBirth(std::string);
    std::string get_DateOfBirth();
    void set_phoneNumber(std::string);
    std::string get_phoneNumber();
    void set_password(std::string);
    std::string get_password();
    void set_header(std::string);
    std::string get_header();
    int get_number_of_users();
    
    private:
    std::string name;
    std::string username;
    std::string bio;
    Date DateOfBirth;
    std::string phoneNumber;
    std::string password;
    std::string header;
};
#endif