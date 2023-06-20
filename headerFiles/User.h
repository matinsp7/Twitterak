#ifndef User_h
#define User_h

#include <string>
#include <vector>
#include <map>
#include "Date.h"
#include "terminal.h"
#include "tweet.h"

class User {
    public:
    User();
    void set_name(std::string);
    std::string get_name() const;
    void set_gender(std::string);
    std::string get_gender();
    void set_username(std::string , std::map<std::string, User>);
    std::string get_username() const;
    void set_bio(std::string, Terminal);
    std::string get_bio() const;
    void set_dateOfBirth(Terminal);
    Date get_DateOfBirth() const;
    void set_phoneNumber(std::string);
    std::string get_phoneNumber() const;
    void set_password(std::string);
    std::string get_password() const;
    void set_header(std::string);
    std::string get_header() const;
    int get_ID () const;

    std::map<unsigned, Tweet> tweets;

private:
    std::string name;
    std::string gender;
    std::string username;
    std::string bio;
    Date dateOfBirth;
    std::string phoneNumber;
    std::string password;
    std::string header {"white"};
    int ID;
};
#endif