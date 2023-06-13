#ifndef User_h
#define User_h

#include <string>
#include <vector>
#include "Date.h"
#include "terminal.h"

class User {
    public:
    void set_name(std::string);
<<<<<<< HEAD:header files/User.h
    void set_username(std::string , std::vector<User>, Terminal);
    std::string get_username();
    void set_bio(std::string);
    std::string get_bio();
    void set_DateOfBirth(std::string);
    std::string get_DateOfBirth();
    void set_phoneNumber(std::string);
    std::string get_phoneNumber();
=======
    std::string get_name();
    void set_username(std::string , std::vector<User>);
    std::string get_username();
    void set_bio(std::string);
    std::string get_bio();
    void set_DateOfBirth ();
    Date get_DateOfBirth ();
    void set_PhoneNumber(std::string);
    std::string get_PhoneNumber();
>>>>>>> e1728afadd55aa8f9b102378cb4d16b8436cffc7:User.h
    void set_password(std::string);
    std::string get_password();
    void set_header(std::string);
    std::string get_header();
<<<<<<< HEAD:header files/User.h
    int get_number_of_users();
    
=======

>>>>>>> e1728afadd55aa8f9b102378cb4d16b8436cffc7:User.h
    private:
    std::string name;
    std::string username;
    std::string bio;
    Date DateOfBirth;
    std::string PhoneNumber;
    std::string password;
    std::string header;
<<<<<<< HEAD:header files/User.h
=======
    //static int number_of_users;
>>>>>>> e1728afadd55aa8f9b102378cb4d16b8436cffc7:User.h
};
#endif