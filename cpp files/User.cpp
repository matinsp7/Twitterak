#include <iostream>
#include <vector>
#include <string>

#include "../header files/Date.h"
#include "../header files/User.h"
#include "terminal.cpp"

using namespace std;

void User::set_name(string name){
    this->name = name;
}

string User::get_name() const{
    return name;
}
void User::set_username(string username , vector <User> accounts, Terminal t)
{

    int accsize = accounts.size();
    for (int i=0 ; i<accsize ; i++){
        if (accounts.at(i).get_username() == username){
            throw invalid_argument(
                "Username already taken! Please try again :"
            );
        }
    }

    int usersize = username.size();
    if (usersize < 5){
        throw invalid_argument(
            "Username must have at least 5 characters! Please try again :"
        );
    }

    for (int i=0 ; i<usersize ; i++){
        if (!isalnum(username[i])){
            throw invalid_argument(
                "Username can only contains letters and numbers! Please try again :"
            );
        }
    }

    if (isdigit(username[0])){
        throw invalid_argument (
            "The beginning of the username cannot be a number! Please try again :"
        );
    }

    this -> username = username;
}

string User::get_username() const{
    return username;
}

void User::set_bio(string bio, Terminal t){
    if (bio.size()<160){
        this -> bio = bio;
    }
    else {
        throw invalid_argument(
            "Username can be a maximum of 160 characters !"
        );
    }
}

string User::get_bio () const{
    return bio;
}

void User::set_DateOfBirth(Terminal t){
    bool flag = 0;
    int d , m , y;
    while (!flag){
        d = t.getIntValue("Day");
        m = t.getIntValue("Month");
        y = t.getIntValue("Year");

        Date a(d , m , y , flag, t);
    }
}

Date User::get_DateOfBirth() const{
    return DateOfBirth;
}

void User::set_PhoneNumber(string phone){
    PhoneNumber = phone;
}

string User::get_PhoneNumber() const {
    return PhoneNumber;
}

void User::set_password(std::string password){
    this -> password = password;
}

string User::get_password()const {
    return password;
}

void User::set_header(string color){
    header = color;
}

string User::get_header() const{
    return header;
}