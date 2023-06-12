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

        for (int i=0 ; i<username.size() ; i++){    //touppercase username
            username[i] = toupper(username[i]);
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

    accounts.push_back (new_user);

    cout << "* Registration was successful." << endl;
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
        for (int i=0 ; i<Username.size() ; i++){    //touppercase username
            Username[i] = toupper(Username[i]);
        }
        cout << "$ Password : ";
        cin >> Password;
        int accsize = accounts.size();
        for (int i=0 ; i<accsize ; i++){
            if (Username == accounts.at(i).get_username()){
                if (Password == accounts.at(i).get_password()){
                    cout << "Excelent" << endl;
                    flag = 1;
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