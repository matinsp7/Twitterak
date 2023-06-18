#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../headerFiles/date.h"
#include "../headerFiles/User.h"
#include "../headerFiles/terminal.h"

using namespace std;

void User::set_name(string name){
    this->name = name;
}

string User::get_name() const{
    return name;
}

void User::set_gender(string gender){
    if (gender == "man" || gender == "woman"){
        this -> gender = gender;
    }
    else {
        throw invalid_argument(
            "Invalid input"
        );
    }
}

string User::get_gender (){
    return gender;
}
void User::set_username(string username , map<string, User> accounts)
{

    if (accounts.find(username) != accounts.end()){
        throw invalid_argument(
            "Username already taken! Please try again :"
        );
    }

    int usersize = username.size();
    if (usersize < 5){
        throw invalid_argument(
            "! Username must have at least 5 characters. Please try again :"
        );
    }

    for (int i=0 ; i<usersize ; i++){
        if (!isalnum(username[i])){
            throw invalid_argument(
                "! Username can only contains letters and numbers. Please try again :"
            );
        }
    }

    if (isdigit(username[0])){
        throw invalid_argument (
            "! The beginning of the username cannot be a number. Please try again :"
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

void User::set_dateOfBirth(Terminal t){
    bool flag = 0;
    int d , m , y;
    d = t.getIntValue("Day");
    m = t.getIntValue("Month");
    y = t.getIntValue("Year");
    try {
        dateOfBirth.set_day (d);
        dateOfBirth.set_month (m);
        dateOfBirth.set_year (y);
        t.sendSuccessMessage ("Your birthdate has been successfully changed.");
    }
    catch (out_of_range &a) {
        cout << a.what() << endl;
    }
}

Date User::get_DateOfBirth() const{
    return dateOfBirth;
}

void User::set_phoneNumber(string phone){
    ins size = phone.size();
    /*if (phone.size() == 12){
        phoneNumber = phone;
    }
    else {
        throw invalid_argument (
            "The phone number is incorrect."
        );
    }*/
    for (size_t i=0 ; i<size ; i++){
        if ( !isalnum(phone(i)) ){
            throw invalid_argument (
            "The phone number is incorrect."
            );
        }
    }
}

string User::get_phoneNumber() const {
    return phoneNumber;
}

void User::set_password(std::string password){
    this -> password = password;
}

string User::get_password()const {
    return password;
}

void User::set_header(string color){
    if (color == "white" || color == "red" || color == "orange" || color == "yellow" || color == "green" || color == "blue" || color == "purple" || color == "black"){
        header = color;
    }
    else {
        throw invalid_argument (
            "Invalid argumnt."
        );
    }
}

string User::get_header() const{
    return header;
}