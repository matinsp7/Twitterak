#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../include/date.h"
#include "../include/User.h"
#include "../include/terminal.h"

using namespace std;

User::User(){
    static int id{0};
    ID = id++;
}

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
    int usersize = username.length();
    if (usersize < 5){
        throw invalid_argument(
            "! Username must have at least 5 characters. Please try again :"
        );
    }

    if (accounts.find(username) != accounts.end()){
        throw invalid_argument(
            "Username already taken! Please try again :"
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

    if (username == "signup" || username =="login" || username == "logout" || username == "tweet"
    || username == "profile"|| username == "retweet" || username == "usernamr" || username == "password"
    || username =="country" || username == "birthdate" || username == "account" || username == "tweet"
    || username == "tweets"){
        throw invalid_argument ("This is a reserved word. You can not choos it as your username.");
    }

    this -> username = username;
}

string User::get_username() const{
    return username;
}

void User::set_bio(string bio){
    if (bio.size()<160){
        this -> bio = bio;
    }
    else {
        throw invalid_argument(
            "Username can be a maximum of 160 characters."
        );
    }
}

string User::get_bio () const{
    return bio;
}

void User::set_country (string country){
    this -> country = country;
}

string User:: get_country () const{
    return country;
} 

void User::set_link (string link){
    if(link.substr(0,4) != "http")
    {
        string prefix = "https://";
        link = prefix + link;
    }else if(link.substr(0,5) == "http:")
    {
        link.insert(4,"s");
    }
    this -> link = link;
}

 
string User::get_link () const{
    return link;
}

void User::set_dateOfBirth(int d , int m , int y , Terminal t){
    Date birthdate(d , m , y , t);
}

Date User::get_DateOfBirth() const{
    return dateOfBirth;
}

void User::set_phoneNumber(string phone){
    int size = phone.size();
    if (phone.size() == 12){
        phoneNumber = phone;
    }
    else {
        throw invalid_argument (
            "The phone number is incorrect.The phone number must be 12 digits."
        );
    }
    for (size_t i=0 ; i<size ; i++){
        if ( !isdigit(phone[i]) ){
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

int User::get_ID () const{
    return ID;
}
