#include <iostream>
#include <string>
#include <Windows.h>
#include <map>

#include "Twitterak.h"
#include "splashScreen.h"
#include "user.h"


using namespace std;

map<string, User> Twitterak::accounts;

//#sharps
map < string, map<string,int> > sharps;


//signup function called when "signup" command entered
void Twitterak::signup (vector<string>& args, Terminal& t)
{
    User new_user;

    string username;
    while (1) {
        if(args.size() == 2){                                       //check if username and
            username = args[1];                                     //signup command has been
            args.resize(1);                                         //entered in a single line
        }else{                                                      //signup @Banana
            username = t.getStringValue("Username");
        }

        try{
            new_user.set_username(username , accounts, t);
            break;
        }
        catch(invalid_argument &e){
            t.throwError(e.what());
        }
    }

    string name = t.getStringValue("Name");
    new_user.set_name(name);
    
    string password = t.getStringValue("Password");
    new_user.set_password(password);

    string phoneNumber = t.getStringValue("Phone number");
    new_user.set_PhoneNumber(phoneNumber);

    accounts[username] =  new_user;

    t.sendSuccessMessage("Registration was successful.");

    login (username , t);
}

//called when "login" command entered
void Twitterak::check_validation (vector<string>& args, Terminal& t)
{
    string username;
    string password;

    if(args.size() > 1){                            //check if username has been entered
        username = args.at(1);                      //in shape of :
    }else{                                          //login @Banana
        username = t.getStringValue("Username");    //login @Banana password
    }


    if (username[0] == '@')                        //to remove @
    {
        username.erase(0);
    }

    if(args.size() == 2)                            //check if password has been entered
    {                                               //in shape of :
        password = args.at(2);                      //login @Banana password
    }
    else
    {                                               
        password = t.getStringValue("Password");
    }
    

    if (accounts.find(username) != accounts.end())
    {
        if (accounts[username].get_password() == password)
        {
            login (username , t);
        }
        else
        {
            t.throwError("Usename or Password is incorrect !");
        }
    }
    else
    {
        t.throwError("Usename or Password is incorrect !");
    }
}

//called when "help" command entered
void Twitterak::help(Terminal& t)
{
    fstream reader("res/help.txt");

    if(reader){
        std::string allText, tmp;
        while(getline(reader,tmp)){
            allText += tmp;
            allText += '\n';
        }
        t.sendMessage(allText);
    }else{
        t.throwError("help file not found!");
    }

}

//called when "profile" or "me" command entered entered
void Twitterak::profile (string& username, Terminal& t)
{
    User user = accounts[username];

    t.sendMessage("Name : " + user.get_name()+'\n');
    t.sendMessage("Username : " + user.get_username()+'\n');
    t.sendMessage("bio : " + user.get_bio()+'\n');
    t.sendMessage("Date of birth : " + to_string(user.get_DateOfBirth().get_year()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_month()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_day())+'\n');
    t.sendMessage("Phone number : " + user.get_PhoneNumber()+'\n');
    t.sendMessage("Header : " + user.get_header()+'\n');
}


void Twitterak::editProfile(vector<string>& args, string& username, Terminal& t)
{
    User user = accounts[username];

    if(args.size() >= 4)
    {
        args[2] = t.toLower(args[2]);
        if(args[2] == "username")
        {
            try{
                user.set_username(args[3] , accounts, t);
                t.sendSuccessMessage("your username has been successfully changed");
            }
            catch(invalid_argument &e){
                t.throwError(e.what());
            }
        }
        else if(args[2] == "password")
        {
            user.set_password(args[3]);
            t.sendSuccessMessage("your password has been successfully changed");
        }
        else if(args[2] == "name")
        {
            string tmp;
            for(int i{0}; i < args.size(); i++){
                tmp += args[i];
            }
            user.set_name(tmp);
            t.sendSuccessMessage("your name has been successfully changed");
        }
        else if(args[2] == "bio")
        {
            string tmp;
            for(int i{3}; i < args.size(); i++){
                tmp += args[i];
            }
            user.set_bio(tmp, t);
            t.sendSuccessMessage("your bio has been successfully changed");
        }
        else if(args[2] == "phone" && t.toLower(args[3]) == "number")
        {
            if(args.size() == 5){
                user.set_PhoneNumber(args[4]);
                t.sendSuccessMessage("your phone number has been successfully changed");
            }
            else
            {
                t.throwError("invalid input for phone number.");
            }
        }
        else if(args[2] == "header")
        {
            user.set_header(args[3]);
            t.sendSuccessMessage("your header has been successfully changed");
        }
        else if(args[2] == "date")
        {
            if(args.size() >= 5 && t.toLower(args[3]) == "of" && t.toLower(args[4]) == "birth")
            {
                if(args.size() == 5)
                {
                    int y = t.getIntValue("Year");
                    int m = t.getIntValue("Month");
                    int d = t.getIntValue("Day");
                    if(user.set_DateOfBirth(y,m,d,t)){
                        t.sendSuccessMessage("your date of birth has been successfully changed");
                    }
                }
                else if(args.size() == 6)
                {

                }
                else
                {
                    t.throwError("the syntax of this command is:\nedit profile date of birth year/month/day");
                }
            }else
            {
                t.throwError("the syntax of this command is:\nedit profile date of birth");
            }
            user.set_header(args[3]);
        }
    }
    else
    {
        t.throwError("could not find property with name \"" + args.at(2) + "\"");
    }
    accounts[username] = user;
}

void Twitterak::editTweet()
{

}
//runs a while(1) loop when user is logged in.
//called from check_validation func when username and password was valid.
//called from signup func when regstration was successful. 
void Twitterak::login(string& username , Terminal& t)
{

    User user = accounts[username];

    vector<string> args;
    while (1) {

        args.clear();
        args = t.getCommand("> @" + user.get_username() +" >");

        args.at(0) = t.toLower(args.at(0));

        if ( args.at(0) == "profile" || args.at(0) == "me")
        {
            if(args.size() == 2)
            {
                if(args[1][0] == '@')
                    args[1].erase(1);

                if(accounts.find(args[1]) != accounts.end())
                {
                    profile(args[1], t);
                }
                else
                {
                    t.throwError("username not found.");
                }
            }
            else if(args.size() == 1)
            {
                profile(username, t);
            }
            else
            {
                t.throwError("invalid username.");
            }
        }
        else if ( args.at(0) == "edit")
        {
            if(args.size() < 3){
                t.throwError("invalid input.");
                continue;
            }

            args.at(1) = t.toLower(args.at(1));

            if(args.at(1) == "profile")
            {
                editProfile(args, username, t);
            }
            else if(args.at(1) == "tweet")
            {
                editTweet();
            }
        }
        else if ( args.at(0) == "delete")
        {
            system ("cls");
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

//run func of class
void Twitterak::run()
{

    HWND console = GetConsoleWindow();
    MoveWindow(console, 50, 50, 1200, 700, true);

    Terminal t(cin , cout);

    SplashScreen screen;
    screen.runSplashScreen("res/splashTextAsciiArt.txt",9,"res/welcomeText.txt",11 , t);

    vector<string> args;
    while (1)
    {
        
        args.clear();
        args = t.getCommand("> ");

        args.at(0) = t.toLower(args.at(0));

        if (args[0] == "signup")
        {
            if(args.size() < 3){
                signup(args,t);
            }else{
                t.throwError("invalid username.");
            }
        }
        else if (args[0] == "login")
        {
            if(args.size() < 4){
                check_validation(args, t);
            }else{
                t.throwError("invalid username or password.");
            }
        }
        else if (args[0] == "help")
        {
            if(args.size() < 3){
                help(t);
            }else{
                t.throwError("This command is not supported by the help utility.");
            }
        }
        else if (args[0] == "exit")
        {
            exit(0);
        }
        else if (args[0] == "cls")
        {
            system("cls");
        }else{
            t.throwError('"' + args[0] + "\" is not recognized as an internal or external command");
        }
    }
}