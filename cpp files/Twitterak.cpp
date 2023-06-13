#include "../header files/Twitterak.h"
#include <iostream>
#include <string>
#include <Windows.h>

#include "../header files/splashScreen.h"
#include "../header files/user.h"


using namespace std;

vector <User> Twitterak::accounts;

void Twitterak::signup (Terminal t){
    User new_user;

    t.sendMessage("Thank you for your choice.\n");

    string name = t.getStringValue("Name");
    new_user.set_name(name);

    while (1) {
        string username = t.getStringValue("Username");

        if (username[0] == '@'){    //to remove @
            username.erase(0);
        }

        for (int i=0 ; i<username.size() ; i++){    //tolowercase username
            username[i] = tolower(username[i]);
        }

        try{
            new_user.set_username(username , accounts, t);
            break;
        }
        catch(invalid_argument &err){
            cerr << err.what() << endl;
        }
    }

    string password = t.getStringValue("Password");
    new_user.set_password(password);

    string Phonenumber = t.getStringValue("Phone number");
    new_user.set_PhoneNumber(Phonenumber);

    accounts.push_back (new_user);

    t.sendSuccessMessage("Registration was successful.");

    int accsize = accounts.size() -1;
    login (accsize , t);
}

void Twitterak::check_validation (Terminal t){
    string username;
    string password;
    bool flag = 0;
    while (!flag){

        username = t.getStringValue("Username");

        if (username[0] == '@'){    //to remove @
            username.erase(0);
        }

        password = t.getStringValue("Password");
        int accsize = accounts.size();
        for (int i=0 ; i<accsize ; i++){
            if (username == accounts.at(i).get_username()){
                if (password == accounts.at(i).get_password()){
                    flag = 1;
                    login (i , t);
                    break;
                }
                else {
                    t.throwError("Usename or Password is incorrect !");
                    break;
                }
            }
            else if (i == accsize-1){
                t.throwError("Usename or Password is incorrect !");
            }
        }

    }
}



inline void profile (int &i , vector <User> accounts, Terminal t){
    User user = accounts.at(i);
    t.sendMessage("Name : " + user.get_name()+'\n');
    t.sendMessage("Username : " + user.get_username()+'\n');
    t.sendMessage("bio : " + user.get_bio()+'\n');
    t.sendMessage("Date of birth : " + to_string(user.get_DateOfBirth().get_year()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_month()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_day())+'\n');
    t.sendMessage("Phone number : " + user.get_PhoneNumber()+'\n');
    t.sendMessage("Header : " + user.get_header()+'\n');
}



void Twitterak::login(int &i , Terminal t){

    User user = accounts.at(i);

    vector<string> args;
    while (1) {

        args.clear();
        args = t.getCommand("> @" + user.get_username() +" >");

        args.at(0) = t.toLower(args.at(0));

        if ( args.at(0) == "profile" || args.at(0) == "me")
        {
           profile( i , accounts, t);
        }
        else if ( args.at(0) == "edit")
        {
            profile(i , accounts, t);
        }
        else if ( args.at(0) == "cls")
        {
            system ("cls");
        }
        else if ( args.at(0) == "logout"){
            break;
        }
    }
}


void Twitterak::run(){

    HWND console = GetConsoleWindow();
    MoveWindow(console, 50, 50, 1200, 700, true);

    Terminal t(cin , cout);

    splashScreen screen;
    screen.runSplashScreen("res/splashTextAsciiArt.txt",9,"Welcome!",11 , t);

    vector<string> args;
    while (1){
        
        args.clear();
        args = t.getCommand("> ");

        args.at(0) = t.toLower(args.at(0));

        if (args[0] == "signup")
        {
            signup(t);
        }
        else if (args[0] == "login")
        {
            check_validation(t);
        }
        else if (args[0] == "cls")
        {
            system("cls");
        }
    }
}