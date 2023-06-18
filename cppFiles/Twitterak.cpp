#include "../headerFiles/Twitterak.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <map>

#include "../headerFiles/splashScreen.h"
#include "../headerFiles/User.h"
#include "../headerFiles/tweet.h"


using namespace std;

map<string, User> Twitterak::accounts;
map <string, map<User*, vector<int>> > Twitterak::sharps;

void Twitterak::signup (Terminal t , string un = nullptr){
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

    if (un.empty()){
        string username;
        while (1) {
            username = t.getStringValue("Username ");

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

    accounts[username] =  new_user;

    t.sendSuccessMessage("Registration was successful.");

    login (username , t);
}


//------------------------------------------------------------------------


void Twitterak::check_validation (Terminal t){
    string username;
    string password;

    username = t.getStringValue("username");

    if (username[0] == '@'){    //to remove @
        username.erase(0);
    }
    username = t.toLower(username);

    password = t.getStringValue("password");

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


// ----------------------------------------------------------------------


inline void profile (string& username , map<string, User> accounts, Terminal t){
    User user = accounts[username];
    t.sendMessage("Name : " + user.get_name()+'\n');
    t.sendMessage("Username : " + user.get_username()+'\n');
    t.sendMessage("bio : " + user.get_bio()+'\n');
    t.sendMessage("Date of birth : " + to_string(user.get_DateOfBirth().get_year()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_month()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_day())+'\n');
    t.sendMessage("Phone number : " + user.get_phoneNumber()+'\n');
    t.sendMessage("Header : " + user.get_header()+'\n');
}

//argument0: the text that contains sharps
//returns a vector of sharps without sharp character(#)
inline vector<string> findSharpsInText(string& text)
{
    vector<string> sharps;
    unsigned begin{0};
    for(int i{0}; i < text.length(); i++)
    {
        if(text.at(i) == '#')
        {
            begin = i+1;
            for(int j{i+1}; j < text.length(); j++)
            {
                if(text.at(j) == '#')
                {
                    begin = j+1;
                }
                else if(text.at(j) == ' ')
                {
                    if(j == 0)
                        break;
                    string sharp = text.substr(begin, j-begin);       
                    sharps.push_back(sharp);
                    i = j;
                    break;

                }else if(j == text.length()-1)
                {
                    string sharp = text.substr(begin, j-begin+1);       
                    sharps.push_back(sharp);
                }
            }
        }
    }

    for(int i{0}; i < sharps.size(); i++)
    {
        for(int j{i+1}; j < sharps.size(); j++)
        {
            if(sharps.at(i) == sharps.at(j))
            {
                sharps.erase( sharps.begin() + j );
            }
        }
    }

    return sharps;
}

//this function creates a tweet by input information and returns it
//argument0: text of tweet
//argument1: the username of who tweeted
//argument2: the index of tweet
//argument3: the sharps
//returns a object of tweet class 
Tweet Twitterak::tweet(string& text,User& user, unsigned& tweetIndex)
{
    vector<string> textSharps = findSharpsInText(text);
    for(int i{0}; i < textSharps.size(); i++)
    {
        sharps[textSharps.at(i)][&user].push_back(tweetIndex);
    }

    Tweet newTweet(text);
    return newTweet;
}

//called when "help" command entered
void Twitterak::help(Terminal& t)
{
    fstream reader("help.txt");

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

void Twitterak::login(string& username , Terminal t){

    User& user = accounts[username];

    vector<string> args;
    while (1) {

        args.clear();
        args = t.getCommand("> @" + user.get_username() + " > ");

        args.at(0) = t.toLower(args.at(0));





        if (args.at(0) == "me")
        {
           profile( username , accounts, t);
        }


        else if (args.at(0) == "profile")
        {
            if (args.size() == 1)
            {
                profile( username , accounts, t);
            }
            else 
            {
                if (args.at(1).at(0) == '@') // to remove @
                {       
                    args.at(1).erase(0 , 1);
                }
                args.at(1) = t.toLower(args.at(1));   //tolowercase username

                if (accounts.find(args.at(1)) != accounts.end()){
                    string color = accounts[args.at(1)].get_header();
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
                    if (accounts[args.at(1)].get_gender() == "man"){
                        screen.runSplashScreen("man.txt",cl,"",cl , t);
                    }
                    else {
                        screen.runSplashScreen("woman.txt",cl,"",cl , t);
                    }
                    profile (args.at(1) , accounts , t);
                    SetConsoleTextAttribute(hOutput,7);
                }
            }
        }




        else if ( args.at(0) == "edit")
        {
            if (args.size() >= 2){
                args.at(1) = t.toLower(args.at(1));
                if (args.at(1) == "profile")
                {
                    string editP;
                    string newP;
                    if (args.size() == 2)
                    {
                        profile(username , accounts, t);
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
                            accounts[newP] = user;
                            accounts.erase(username);
                            username = newP;
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
                        if (!newP.empty()){
                            t.sendMessage ("Select header color between : \n");
                            string color;
                            color = t.getStringValue ("White / Red / Orange / Yellow / Green / Blue / Purple / Black");
                            color = t.toLower(color);
                        }
                        try {
                            user.set_header(newP);
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


            else if( args.at(0) == "tweet")
            {
                if(args.size() > 1)
                {
                    string tweetText;
                    for(int i{1}; i < args.size(); i++)
                    {
                        tweetText += args[i];
                        tweetText += ' ';
                    }

                    unsigned tweetIndex = user.tweets.size() == 0 ?  1 : user.tweets.rbegin()->first+1;

                    user.tweets.insert({tweetIndex, tweet(tweetText, user, tweetIndex)});

                    accounts[username] = user;
                }
                else
                {
                    t.throwError("Text of tweet cant be empty.");
                }
            }
        }

        else if( args.at(0).at(0) == '@')
        {
            
            args.at(0).erase(0 , 1);

            if(accounts.find(args.at(0)) != accounts.end())
            {
                
                map<unsigned, Tweet> tweets = accounts[args.at(0)].tweets;

                for (auto itr = (tweets).begin(); itr != (tweets).end(); ++itr) {
                    string message = to_string(itr->first) + ": "+ itr->second.getText() + '\n';
                    t.sendMessage(message);
                }
            }
            else
            {

            }
        }

        else if( args.at(0).at(0) == '#')
        {
            string hashtag = args.at(0).erase(0,1);

            if(sharps.find(hashtag) != sharps.end())
            {
                for(auto it = sharps[hashtag].begin(); it != sharps[hashtag].end(); it++)
                {
                    vector<int> tweetIndexes = it->second;
                    for(int i{0}; i < tweetIndexes.size(); i++) //vector size
                    {
                        cout << i << '\n';
                        cout << it->second.at(i) << '\n';
                        t.sendMessage((*it->first).get_username() + " " +  to_string(it->second.at(i)) + " :" + (*it->first).tweets.at(it->second.at(i)).getText() + '\n');
                    }
                }
            }
        }

        else if(args.at(0) == "help")
        {
            help(t);
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
    screen.runSplashScreen("splashTextAsciiArt.txt",9,"welcomeText.txt",11 , t);

    // HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hOutput,7);

    vector<string> args;
    while (1){
        
        args.clear();
        args = t.getCommand("> ");

        args.at(0) = t.toLower(args.at(0));

        if (args[0] == "signup")
        {
            if (args.size() == 1){
                signup(t);
            }
            else if (args.size() == 2) {
                User user;
                try {
                    user.set_username(args[1]);
                    signup (t , args[1]);
                }
                catch (invalid_argument &err){
                    t.throwError(err.what() + '\n');
                }
            }
            else {
                 t.throwError("Undefined command.");
            }
        }
        else if (args[0] == "login")
        {
            check_validation(t);
        }
        else if(args.at(0) == "help")
        {
            help(t);
        }
        else if (args[0] == "cls")
        {
            system("cls");
        }
        else {
            t.throwError("Undefined command.");
        }
    }
}