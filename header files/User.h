#ifndef User_h
#define User_h

#include <string>
#include <vector>
#include "Date.h"
#include "terminal.h"

class User {
    public:
    void set_name(std::string);
    std::string get_name() const;
    void set_username(std::string , std::vector<User>, Terminal);
    std::string get_username() const;
    void set_bio(std::string, Terminal);
    std::string get_bio() const;
    void set_DateOfBirth(Terminal);
    Date get_DateOfBirth() const;
    void set_PhoneNumber(std::string);
    std::string get_PhoneNumber() const;
    void set_password(std::string);
    std::string get_password() const;
    void set_header(std::string);
    std::string get_header() const;

private:
    std::string name;
    std::string username;
    std::string bio;
    Date DateOfBirth;
    std::string PhoneNumber;
    std::string password;
    std::string header;
};
#endif