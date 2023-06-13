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

void User::set_username(string username , vector <User> accounts, Terminal t){

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

void User::set_password(std::string password){
    this -> password = password;
}

string User::get_password(){
    return password;
}