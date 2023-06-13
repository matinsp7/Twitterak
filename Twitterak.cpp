#include "Twitterak.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include "splashScreen.hpp"
#include "User.h"

using namespace std;

vector <User> Twitterak::accounts;


//------------------------------------------------------------


void Twitterak::signup (){
    User new_user;

    cout << "Thank you for your choice." << endl;

    cout << "$ Name : ";
    string name;
    cin >> name;
    new_user.set_name(name);

    while (1) {
        cout << "$ Username : ";
        string username;
        cin >> username;
        if (username[0] == '@'){    //to remove @
            username.erase(0);
        }

        for (int i=0 ; i<username.size() ; i++){    //tolowercase username
            username[i] = tolower(username[i]);
        }

        try{
            new_user.set_username(username , accounts);
            break;
        }
        catch(invalid_argument &err){
            cerr << err.what() << endl;
        }
    }

    cout << "$ password : ";
    string password;
    cin >> password;
    new_user.set_password(password);

    cout << "$ Phone number : ";
    string Phonenumber;
    cin >> Phonenumber;
    new_user.set_PhoneNumber(Phonenumber);

    accounts.push_back (new_user);

    cout << "* Registration was successful." << endl;

    int accsize = accounts.size() -1;
    login (accsize);
}

//-----------------------------------------------------------------

void Twitterak::check_validation (){
    string Username;
    string Password;
    bool flag = 0;
    while (!flag){
        cout << "$ Username : ";
        cin >> Username;
        if (Username[0] == '@'){    //to remove @
            Username.erase(0);
        }
        for (int i=0 ; i<Username.size() ; i++){    //tolowercase username
            Username[i] = tolower(Username[i]);
        }
        cout << "$ Password : ";
        cin >> Password;
        int accsize = accounts.size();
        for (int i=0 ; i<accsize ; i++){
            if (Username == accounts.at(i).get_username()){
                if (Password == accounts.at(i).get_password()){
                    flag = 1;
                    login (i);
                    break;
                }
                else {
                    cout << "! Usename or Password is incorrect !" << endl;
                    break;
                }
            }
            else if (i == accsize-1){
                cout << "! Usename or Password is incorrect !" << endl;
            }
        }

    }
}

//---------------------------------------------------------------------

void Twitterak::login(int &i){
    while (true) {
        User user = accounts.at(i);
        string option;
        cout << ">@" << user.get_username() << " ";
        cin >> option;
        int size = option.size();
        for (int i=0 ; i<size ; i++){   //to uppercase option
            option[i] = toupper(option[i]);
        }



        if (option == "PROFILE" || option == "ME"){
            cout << "Name : " << user.get_name() << endl;
            cout << "Username : " << user.get_username() << endl;
            cout << "bio : " << user.get_bio() << endl;
            cout << "Date of birth : " << user.get_DateOfBirth().get_year() << "/";
            cout << user.get_DateOfBirth().get_month() << "/";
            cout << user.get_DateOfBirth().get_day() << endl;
            cout << "Phone number : " << user.get_PhoneNumber() << endl;
            cout << "Header : " << user.get_header() << endl;
        }


        else if (option == "CLEAR"){
            system ("cls");
        }


        else if (option == "LOGOUT"){
            break;
        }



    }
}

//----------------------------------------------------------------------


void Twitterak::run(){
    HWND console = GetConsoleWindow();
    MoveWindow(console, 50, 50, 1200, 700, true);

    runSplashScreen("splashTextAsciiArt.txt",9,"Welcome!",11);

    cout <<  tolower('A');

    system("cls");

    string option;
    while (1){
        cout << "> ";
        cin >> option;
        int size = option.size();
        for (int i=0 ; i<size ; i++){   //to uppercase option
            option[i] = toupper(option[i]);
        }

        if (option == "SIGNUP"){
            signup();
        }

        else if (option == "LOGIN"){
            check_validation();
        }

        else if (option == "CLEAR"){
            system("cls");
        }
    }
}