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

<<<<<<< HEAD:cpp files/User.cpp
void User::set_username(string username , vector <User> accounts, Terminal t){
=======
string User::get_name(){
    return name;
}


void User::set_username(string username , vector <User> accounts){
>>>>>>> e1728afadd55aa8f9b102378cb4d16b8436cffc7:User.cpp

    int accsize = accounts.size();
    for (int i=0 ; i<accsize ; i++){
        if (accounts.at(i).get_username() == username){
            t.throwEror("Username already taken! Please try again :");
        }
    }

    int usersize = username.size();
    if (usersize < 5){
        t.throwEror("Username must have at least 5 characters! Please try again :");
    }

    for (int i=0 ; i<usersize ; i++){
        if (!isalnum(username[i]))
            t.throwEror("Username can only contains letters and numbers! Please try again :")
        }
    }

    if (isdigit(username[0])){
        throw invalid_argument (
            t.throwEror("The beginning of the username cannot be a number! Please try again :")
        );
    }
    this -> username = username;
}

string User::get_username(){
    return username;
}

void User::set_bio(string bio){
    if (bio.size()<160){
        this -> bio = bio;
    }
    else {
        throw invalid_argument (
            "! Username can be a maximum of 160 characters !"
        );
    }
}

string User::get_bio (){
    return bio;
}

void User::set_DateOfBirth(){
    bool flag = 0;
    int d , m , y;
    while (!flag){
        cout << "Day : ";
        cin >> d;
        cout << "Month : ";
        cin >> m;
        cout << "Year : ";
        cin >> y;
        Date a(d , m , y , flag);
    }
}

Date User::get_DateOfBirth(){
    return DateOfBirth;
}

void User::set_PhoneNumber(string phone){
    PhoneNumber = phone;
}

string User::get_PhoneNumber(){
    return PhoneNumber;
}

void User::set_password(std::string password){
    this -> password = password;
}

string User::get_password(){
    return password;
}

void User::set_header(string color){
    header = color;
}

string User::get_header(){
    return header;
}