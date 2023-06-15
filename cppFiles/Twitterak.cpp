#include "../header files/Twitterak.h"
#include <iostream>
#include <string>
#include <Windows.h>

#include "../header files/splashScreen.h"
#include "../header files/User.h"


using namespace std;

vector <User> Twitterak::accounts;

void Twitterak::signup (Terminal t){
    User new_user;

    t.sendMessage("Thank you for your choice.\n");

    string name = t.getStringValue("Name ");
    new_user.set_name(name);

    string gender = t.getStringValue("Gender (man/woman) ");
    gender = t.toLower(gender);
    try{
        new_user.set_gender(gender);
    }
    catch (invalid_argument &err){
        t.throwError(err.what());
        return ;
    }

    while (1) {
        string username = t.getStringValue("Username ");

        if (username.at(0) == '@'){    //to remove @
            username.erase(0 , 1);
        }

        username = t.toLower(username);


        try{
            new_user.set_username(username , accounts);
            break;
        }
        catch(invalid_argument &err){
            cerr << err.what() << endl;
        }
    }

    string password = t.getStringValue("Password");
    new_user.set_password(password);

    string Phonenumber = t.getStringValue("Phone number");
    try {
        new_user.set_phoneNumber(Phonenumber);
    }
    catch (invalid_argument &err){
        t.throwError (err.what());
        return ;
    }

    accounts.push_back (new_user);

    t.sendSuccessMessage("Registration was successful.");

    int accsize = accounts.size() -1;
    login (accsize , t);
}




void Twitterak::check_validation (Terminal t){
    string username;
    string password;

    username = t.getStringValue("username");

    if (username[0] == '@'){    //to remove @
        username.erase(0);
    }
    username = t.toLower(username);

    password = t.getStringValue("password");
    int accsize = accounts.size();
    for (int i=0 ; i<accsize ; i++){
        if (username == accounts.at(i).get_username()){
            if (password == accounts.at(i).get_password()){
                login (i , t);
                break;
            }
            else {
                t.throwError("Usename or Password is incorrect.");
                break;
            }
        }
        else if (i == accsize-1){
            t.throwError("Usename or Password is incorrect.");
        }
    }

}


// ----------------------------------------------------------------------



inline void profile (int &i , vector <User> accounts, Terminal t){
    User user = accounts.at(i);
    t.sendMessage("Name : " + user.get_name()+'\n');
    t.sendMessage("Username : " + user.get_username()+'\n');
    t.sendMessage("bio : " + user.get_bio()+'\n');
    t.sendMessage("Date of birth : " + to_string(user.get_DateOfBirth().get_year()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_month()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_day())+'\n');
    t.sendMessage("Phone number : " + user.get_phoneNumber()+'\n');
    t.sendMessage("Header : " + user.get_header()+'\n');
}



void Twitterak::login(int &i , Terminal t){

    User &user = accounts.at(i);

    vector<string> args;
    int accsize = accounts.size();
    while (1) {

        args.clear();
        args = t.getCommand("> @" + user.get_username() + " ");

        args.at(0) = t.toLower(args.at(0));





        if (args.at(0) == "me")
        {
           profile( i , accounts, t);
        }


        else if (args.at(0) == "profile")
        {
            if (args.size() == 1)
            {
                profile( i , accounts, t);
            }
            else 
            {
                if (args.at(1).at(0) == '@') // to remove @
                {       
                    args.at(1).erase(0 , 1);
                }
                args.at(1) = t.toLower(args.at(1));   //tolowercase username
                for (int i=0 ; i<accsize ; i++){
                    if (accounts.at(i).get_username() == args.at(1)){
                        string color = accounts.at(i).get_header();
                        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
                        int cl;
                        if (color == "white"){
                            cl = 7;
                        }
                        else if (color == "red"){
                            cl = 4;
                        }
                        else if (color == "orange"){
                            cl = 12;
                        }
                        else if (color == "yellow"){
                            cl = 6;
                        }
                        else if (color == "green"){
                            cl = 10;
                        }
                        else if (color == "blue"){
                            cl = 9;
                        }
                        else if (color == "purple"){
                            cl = 5;
                        }
                        else if (color == "black"){
                            cl = 8;
                        }
                        splashScreen screen;
                        if (accounts.at(i).get_gender() == "man"){
                            screen.runSplashScreen("man.txt",cl,"",cl , t);
                        }
                        else {
                            screen.runSplashScreen("woman.txt",cl,"",cl , t);
                        }
                        profile (i , accounts , t);
                        SetConsoleTextAttribute(hOutput,7);
                        break;
                    }
                }
            }
        }







        else if ( args.at(0) == "edit")
        {
            args.at(1) = t.toLower(args.at(1)); 
            if (args.at(1) == "profile")
            {
                string editP;
                string newP;
                if (args.size() == 2)
                {
                    profile(i , accounts, t);
                    editP = t.getStringValue("What do you want to change? ");
                    editP = t.toLower(editP); // tolowercase edetP
                    if (editP != "date of birth" && editP != "header"){
                        newP = t.getStringValue ("Enter the new change. ");
                    }
                }
                else
                {
                    editP = args.at(2);
                    editP = t.toLower(editP); // tolowercase edetP
                    newP = args.at(3);
                }


                if (editP == "name")
                {
                    user.set_name(newP);
                    t.sendSuccessMessage ("Your name has been successfully changed.");
                }



                else if (editP == "username")
                {
                    if (newP.at(0) == '@') ////to remove @
                    {    
                        newP.erase(0);
                    }
                    newP = t.toLower(newP); //tolowercase username
                    try{
                        user.set_username(newP , accounts);
                        t.sendSuccessMessage ("Your username has been successfully changed.");
                    }
                    catch(invalid_argument &err){
                        t.throwError(err.what());
                    }
                }
                  


                else if (editP == "bio")
                {
                    try {
                        user.set_bio (newP , t);
                        t.sendSuccessMessage ("Your bio has been successfully changed.");
                    }
                    catch (invalid_argument &a) {
                        t.throwError(a.what());
                    }
                }

                else if (editP == "date of birth")
                {
                    user.set_dateOfBirth (t);
                }

                else if (editP == "phoneumber")
                {
                    try {
                        user.set_phoneNumber(newP);
                        t.sendSuccessMessage ("Your phonenumber has been successfully changed.");
                    }
                    catch (invalid_argument &a) {
                        cout << a.what() << endl;
                    }
                }

                else if  (editP == "password")
                {                        
                    string currentPass = t.getStringValue("Enter your current password : ");
                    if (currentPass == user.get_password())
                    {
                        user.set_password(newP);
                    }
                    else 
                    {
                        t.throwError ("The password is not correct.");
                    }
                }

                else if (editP == "header")
                {
                    try {
                        user.set_header(t);
                        t.sendSuccessMessage ("Your header has been successfully changed.");
                    }
                    catch (invalid_argument &err){
                        t.throwError(err.what());
                    }
                }

                else 
                {
                    t.throwError("Undefined command.");
                }
            }
        }

        else if ( args.at(0) == "cls")
        {
            system ("cls");
        }
        else if ( args.at(0) == "logout")
        {
            break;
        }
        else 
        {
            t.throwError("Undefined command.");
        }
    }
}




// ----------------------------------------------------------------------




void Twitterak::run(){

    HWND console = GetConsoleWindow();
    MoveWindow(console, 50, 50, 1200, 700, true);

    Terminal t(cin , cout);

    splashScreen screen;
    screen.runSplashScreen("splashTextAsciiArt.txt",9,"Welcome!",11 , t);

    // HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hOutput,7);

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