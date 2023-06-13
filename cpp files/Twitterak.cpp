#include "../header files/Twitterak.h"
#include <iostream>
#include <string>
#include <Windows.h>

#include "../header files/splashScreen.h"
#include "../header files/user.h"


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



inline void profile (int &i , vector <User> accounts){
    User user = accounts.at(i);
    cout << "Name : " << user.get_name() << endl;
    cout << "Username : " << user.get_username() << endl;
    cout << "bio : " << user.get_bio() << endl;
    cout << "Date of birth : " << user.get_DateOfBirth().get_year() << "/";
    cout << user.get_DateOfBirth().get_month() << "/";
    cout << user.get_DateOfBirth().get_day() << endl;
    cout << "Phone number : " << user.get_PhoneNumber() << endl;
    cout << "Header : " << user.get_header() << endl;
}



void Twitterak::login(int &i){
    User user = accounts.at(i);
    while (true) {
        vector <string> args = t.getCommand();

        args.at(0) = t.toLower(args.at(0));



        if ( args.at(0) == "PROFILE" || args.at(0) == "ME"){
           profile( i , accounts);
        }


        else if ( args.at(0) == "EDIT"){
            profile(i , accounts);
        }


        else if ( args.at(0) == "CLEAR"){
            system ("cls");
        }


        else if ( args.at(0) == "LOGOUT"){
            break;
        }



    }
}

//----------------------------------------------------------------------


void Twitterak::run(){
    Terminal t(cin , cout);
    HWND console = GetConsoleWindow();
    MoveWindow(console, 50, 50, 1200, 700, true);

    splashScreen screen;
    screen.runSplashScreen("res/splashTextAsciiArt.txt",9,"Welcome!",11 , t);

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