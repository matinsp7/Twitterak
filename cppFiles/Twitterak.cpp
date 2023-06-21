#include "../headerFiles/Twitterak.h"
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <map>
#include <chrono>

#include "../headerFiles/splashScreen.h"
#include "../headerFiles/User.h"
#include "../headerFiles/tweet.h"


using namespace std;

map<string, User> Twitterak::accounts;
map <string, map<int, vector<int>> > Twitterak::sharps;

void Twitterak::signup (Terminal t , string un = "signup"){
    User new_user;

    t.sendMessage("Thank you for your choice.\n");

    string username = un;
    if (username == "signup"){
        username = t.getStringValue("Username ");
    }
    else {
        username = un;
    }
    while (1) {
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
            username = t.getStringValue("Username ");
        }
    }

    // string name = t.getStringValue("Name ");
    // new_user.set_name(name);

    string gender = t.getStringValue("Gender (man/woman) ");
    gender = t.toLower(gender);
    try{
        new_user.set_gender(gender);
    }
    catch (invalid_argument &err){
        t.throwError(err.what());
        return ;
    }

    string password = t.getStringValue("Password");
    new_user.set_password(password);

    // string Phonenumber = t.getStringValue("Phone number");
    // try {
    //     new_user.set_phoneNumber(Phonenumber);
    // }
    // catch (invalid_argument &err){
    //     t.throwError (err.what());
    //     return ;
    // }

    accounts[username] =  new_user;

    t.sendSuccessMessage("Registration was successful.");

    login (username , t);
}


//--------------------------------------------------------------------------------------------------


void Twitterak::check_validation (Terminal t , string username = "", string password = ""){
    
    if (username.empty()){
        username = t.getStringValue("username");
    }

    if (password.empty()){
        password = t.getStringValue("password");
    }

    if (username[0] == '@'){    //to remove @
            username.erase(0 , 1);
    }
    username = t.toLower(username);

    if (accounts.find(username) != accounts.end())
    {
        if (accounts[username].get_password() == password)
        {
            login (username , t);
        }
        else
        {
            t.throwError("Usename or Password is incorrect.");
        }
    }
    else
    {
        t.throwError("Usename or Password is incorrect.");
    }

}


// --------------------------------------------------------------------------------------------------


inline void profile (string& username , map<string, User> accounts, Terminal t){
    User user = accounts[username];
    t.sendMessage("Name : " + user.get_name()+'\n');
    t.sendMessage("Gender : " + user.get_gender()+'\n');
    t.sendMessage("Username : " + user.get_username()+'\n');
    t.sendMessage("Bio : " + user.get_bio()+'\n');
    t.sendMessage("Country : " + user.get_country()+'\n');
    t.sendMessage("Link : " + user.get_link()+'\n');
    t.sendMessage("Date of birth : " + to_string(user.get_DateOfBirth().get_year()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_month()) + "/");
    t.sendMessage(to_string(user.get_DateOfBirth().get_day())+'\n');
    t.sendMessage("Phone number : " + user.get_phoneNumber()+'\n');
    t.sendMessage("Header color : " + user.get_header()+'\n');
}

//argument0: the text that contains sharps
//returns a vector of sharps without sharp character(#)
inline vector<string> findSharpsInText(string text)
{
    vector<string> sharps;
    unsigned begin{0};
    int textsize = text.length();
    for(int i{0}; i < textsize; i++)
    {
        if(text[i] == '#')
        {
            begin = i+1;
            for(int j{i+1}; j < textsize; j++)
            {
                if(text[j] == '#')
                {
                    begin = j+1;
                }
                else if(text.at(j) == ' ')
                {
                    string sharp = text.substr(begin, j-begin);       
                    sharps.push_back(sharp);
                    i = j;
                    break;

                }
                else if(j == textsize-1)
                {
                    string sharp = text.substr(begin, j-begin+1);       
                    sharps.push_back(sharp);
                }
            }
        }
    }

    int sharpsize = sharps.size();
    for(int i{0}; i < sharpsize; i++)
    {
        for(int j{i+1}; j < sharpsize; j++)
        {
            if(sharps.at(i) == sharps.at(j))
            {
                sharps.erase( sharps.begin() + j );
            }
        }
    }

    return sharps;
}

//this function gets a tweet in type of called by reference and edits it
//argument0: the tweet that you want to edit
//argument1: the new text of tweet
//argument2: username of who tweeted
//argument3: map of sharps(because this function will add new sharps or delete some sharps)
//returns 1
bool Twitterak::editTweet(Tweet& tweet, unsigned index, string newText, User& user, map < string, map< int,vector<int> > >& sharps)
{
    vector<string> newSharps = findSharpsInText(newText);
    vector<string> lastSharps = findSharpsInText(tweet.getText());

    
    //check added sharps
    for(int i{0}; i < newSharps.size(); i++)
    {
        bool foundSharp{0};
        for(int j{0}; j < lastSharps.size(); j++)
        {
            if(newSharps[i] == lastSharps[j]){
                foundSharp = 1;
                break;
            }
        }

        if(foundSharp == 0)
        {
            //add tweet.getIndex() to sharp vector
            sharps[newSharps.at(i)][user.get_ID()].push_back(index);
        }
    }
    // //check deleted sharps
    for(int i{0}; i < lastSharps.size(); i++)
    {
        bool foundSharp{0};
        for(int j{0}; j < newSharps.size(); j++)
        {
            if(newSharps[i] == lastSharps[j]){
                foundSharp = 1;
                break;
            }
        }

        if(foundSharp == 0)
        {
            //delete tweet.getIndex() from sharp vector
            vector<int>& tweetIndexes = sharps[lastSharps.at(i)][user.get_ID()];
            unsigned size{tweetIndexes.size()};

            for(int x{0}; x < size; x++)
            {
                if(tweetIndexes.at(x) == index)
                {
                    tweetIndexes.erase(tweetIndexes.begin() + x);
                    break;
                }
            }

            if(tweetIndexes.size() == 0)
            {
                sharps[lastSharps.at(i)].erase(user.get_ID());
            }

            if(sharps[lastSharps.at(i)].size() == 0)
            {
                sharps.erase(lastSharps.at(i));
            }
        }
    }

    //change text of tweet
    tweet.setText(newText);
    return 1;
}

//this function creates a tweet by input information and returns it
//argument0: text of tweet
//argument1: the username of who tweeted
//argument2: the index of tweet
//argument3: the sharps
//returns a object of tweet class 
Tweet Twitterak::tweet(string& text,User& user, unsigned& tweetIndex)
{
    //current date and time
    const auto now = chrono::system_clock::now();
    const time_t t_c = chrono::system_clock::to_time_t(now);
    string time = ctime(&t_c);
    time.erase(time.length() -1, 1);
    
    vector<string> textSharps = findSharpsInText(text);
    int txtsize = textSharps.size();
    for(int i{0}; i < txtsize; i++)
    {
        sharps[textSharps.at(i)][user.get_ID()].push_back(tweetIndex);
    }

    Tweet newTweet(text, time);
    return newTweet;
}

//delete a tweet
bool Twitterak::deleteTweet(User& user, unsigned index, map < string, map< int,vector<int> > >& sharps)
{
    if(user.tweets.find(index) != user.tweets.end())
    {
        vector <string> textSharps = findSharpsInText(user.tweets.at(index).getText());
        int sharpsize = textSharps.size();
        for(int i{0}; i < sharpsize ; i++)
        {
            vector<int>& tweetIndexes = sharps[textSharps[i]][user.get_ID()];
            unsigned size{tweetIndexes.size()};

            for(int x{0}; x < size; x++)
            {
                if(tweetIndexes[x] == index)
                {
                    tweetIndexes.erase(tweetIndexes.begin() + x);
                    break;
                }
            }

            if(tweetIndexes.size() == 0)
            {
                sharps[textSharps.at(i)].erase(user.get_ID());
            }

            if(sharps[textSharps.at(i)].size() == 0)
            {
                sharps.erase(textSharps.at(i));
            }
        }

        user.tweets.erase(index);
        return 1;
    }
    return 0;
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

    User* user = &accounts[username];

    vector<string> args;
    while (1) {

        args.clear();
        args = t.getCommand("> @" + (*user).get_username() + " > ");

        if (args[0][0] != '#'){
            args.at(0) = t.toLower(args.at(0));
        }





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
            else if (args.size() == 2)
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
            else {
                t.throwError("Undefined command.");
            }
        }


        else if ( args.at(0) == "edit")
        {
            if (args.size() >= 2)
            {
                args.at(1) = t.toLower(args.at(1));
                if (args.at(1) == "profile")
                {
                    string editP;
                    string newP;
                    if (args.size() == 2)  //this mode is just for the command edit profile
                    {
                        profile(username , accounts, t);
                        editP = t.getStringValue("What do you want to change ? ");
                        editP = t.toLower(editP);
                        if (editP != "date of birth" && editP != "header"){
                            newP = t.getStringValue ("Enter the new change. ");
                        }
                    }
                    else if (args.size() == 4)
                    {
                        editP = args.at(2);
                        editP = t.toLower(editP);
                        newP = args.at(3);
                    }

                    if (editP == "name")
                    {
                        user -> set_name(newP);
                        t.sendSuccessMessage ("Your name has been successfully changed.");
                    }

                    else if (editP == "gender"){
                        try {
                            user -> set_gender(newP);
                            t.sendSuccessMessage ("Your gender has been successfully changed.");
                        }
                        catch (invalid_argument &err) {
                            t.throwError (err.what());
                        }
                    }


                    else if (editP == "username")
                    {
                        if (newP[0] == '@') //to remove @
                        {    
                            newP.erase(0 , 1);
                        }
                        newP = t.toLower(newP); //tolowercase username
                        try{
                            user -> set_username (newP , accounts);
                            accounts[newP] = accounts [username];
                            accounts.erase(username);
                            username = newP;
                            user = &accounts[username];
                            t.sendSuccessMessage ("Your username has been successfully changed.");
                        
                        }
                        catch(invalid_argument &err){
                            t.throwError(err.what());
                        }
                    }
                    

                    else if (editP == "bio")
                    {
                        try {
                            user -> set_bio (newP , t);
                            t.sendSuccessMessage ("Your bio has been successfully changed.");
                        }
                        catch (invalid_argument &a) {
                            t.throwError(a.what());
                        }
                    }

                    else if (editP == "country"){
                        user -> set_country(newP);
                        t.sendSuccessMessage ("Your country has been successfully changed.");
                    }

                    else if (editP == "link"){
                        user -> set_link(newP);
                    }


                    else if (editP == "date of birth")
                    {
                        int d , m , y;
                        d = t.getIntValue("Day");
                        m = t.getIntValue("Month");
                        y = t.getIntValue("Year");
                        user -> set_dateOfBirth (d , m , y , t);
                    }


                    else if (editP == "phoneumber")
                    {
                        try {
                            user -> set_phoneNumber(newP);
                            t.sendSuccessMessage ("Your phonenumber has been successfully changed.");
                        }
                        catch (invalid_argument &err) {
                            t.throwError(err.what());
                        }
                    }


                    else if  (editP == "password")
                    {                        
                        string currentPass = t.getStringValue("Enter your current password : ");
                        if (currentPass == user -> get_password())
                        {
                            user -> set_password(newP);
                             t.sendSuccessMessage ("Your password has been successfully changed.");
                        }
                        else 
                        {
                            t.throwError ("The password is not correct.");
                        }
                    }

                    else if (editP == "header")
                    {
                        if (newP.empty()){
                            t.sendMessage ("Select header color between : \n");
                            newP = t.getStringValue ("White / Red / Orange / Yellow / Green / Blue / Purple / Black");
                            newP = t.toLower(newP);
                        }
                        try {
                            user -> set_header(newP);
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

                else if(args.at(1) == "tweet" && args.size() == 3)
                {
                    unsigned index = stoi(args.at(2));
                    if((*user).tweets.find(index) != (*user).tweets.end())
                    {
                        t.sendMessage((*user).get_username() + " " + to_string(index)+ " :" + (*user).tweets.at(index).getText() + "\n");
                        t.sendSuccessMessage("Enter new text for tweet " + to_string(index) + " :");
                        vector<string> input = t.getCommand("");
                        string tweetText;
                        for(unsigned i{0}; i < input.size(); i++)
                        {
                            tweetText += input[i];
                            tweetText += ' ';
                        }

                        editTweet((*user).tweets.at(index), index, tweetText, (*user), sharps);
                        t.sendSuccessMessage("Your tweet has been successfully edit.");
                    }
                } 
                else {
                    t.throwError("Undefined command.");
                }
            }
            else {
                t.throwError("Undefined command.");
            }
        }


        else if( args.at(0) == "tweet")
        {
            if(args.size() > 1)
            {
                string tweetText;
                int argsize = args.size();
                for(int i{1}; i < argsize ; i++)
                {
                    tweetText += args[i];
                    tweetText += ' ';
                }

                unsigned tweetIndex = user -> tweets.size() == 0 ?  1 : user -> tweets.rbegin() -> first+1;

                user -> tweets.insert({tweetIndex, tweet(tweetText, *user, tweetIndex)});

            }
            else
            {
                t.throwError("Text of tweet can not be empty.");
            }

        }


        else if(args.at(0) == "delete" && args.size() == 3 && args.at(1) == "tweet")
        {
            if(deleteTweet((*user), stoi(args.at(2)), sharps))
            {
                t.sendSuccessMessage("Tweet deleted successful.");
            }
            else
            {
                t.throwError("The tweet deletation proccess failed.");
            }
        }

        else if( args.at(0).at(0) == '@' && args.size() == 1)
        {
            //its @username command
            args.at(0).erase(0 , 1);

            if(accounts.find(args.at(0)) != accounts.end())
            {
                
                map<unsigned, Tweet> tweets = accounts[args.at(0)].tweets;

                string message;
                for (auto itr = (tweets).begin(); itr != (tweets).end(); ++itr) {
                    ostringstream o;
                    o << itr->first
                    << " ("
                    << itr->second.getTime()
                    << ") : "
                    << itr->second.getText()
                    << '\n';
                    message = o.str();
                    t.sendMessage(message);
                }

                if(message.length() == 0)
                {
                    t.sendMessage("This user has not shared a tweet yet.\n");
                }
            }
            else
            {
                t.throwError("User not found.");
            }
        }

        else if( args.at(0).at(0) == '@' && args.size() == 2)
        {
            //its @username:index command
            args.at(0).erase(0,1);

            string usernameOfPost = args.at(0);
            int index = stoi(args.at(1));
            
            if(accounts.find(usernameOfPost) != accounts.end())
            {
                if(accounts.at(usernameOfPost).tweets.find(index) != accounts.at(usernameOfPost).tweets.end())
                {
                    ostringstream o;
                    o << to_string(index)
                    << " ("
                    << accounts.at(usernameOfPost).tweets.at(index).getTime()
                    << ") : "
                    << accounts.at(usernameOfPost).tweets.at(index).getText()
                    << '\n';
                    t.sendMessage(o.str());
                }
                else
                {
                    t.throwError("couldnt find any tweet with this index.");
                }
            }
            else
            {
                t.throwError("User not found.");
            }
        }

        else if( args.at(0).at(0) == '@' && args.size() == 3)
        {
            //its @username:index:likes command
            args.at(0).erase(0,1);

            string usernameOfPost = args.at(0);
            int index = stoi(args.at(1));
            if(accounts.find(usernameOfPost) != accounts.end())
            {
                if(accounts.at(usernameOfPost).tweets.find(index) != accounts.at(usernameOfPost).tweets.end())
                {
                    vector<int>& likes = accounts.at(usernameOfPost).tweets.at(index).likes;
                    t.sendMessage("likes : " + to_string(likes.size()) + '\n');
                    for (int i=0 ; i < likes.size() ; i++){
                        for(auto it = accounts.begin(); it != accounts.end(); it++)
                        {
                            if(it->second.get_ID() == likes[i])
                            {
                                t.sendMessage('@' + it->second.get_username() + '\n');
                            }
                        }
                    }
                }
                else {
                    t.sendMessage("The user has no post with this index.");
                }
            }
            else
            {
                t.throwError("User not found.");
            }
        }

        else if( args.at(0).at(0) == '#')
        {
            string hashtag = args.at(0).erase(0,1);

            if(sharps.find(hashtag) != sharps.end())
            {
                for(auto it = sharps[hashtag].begin(); it != sharps[hashtag].end(); it++)
                {
                    //find user
                    User tmp;
                    for(auto itA = accounts.begin(); itA != accounts.end(); itA++)
                    {
                        if(itA->second.get_ID() == it->first)
                        {
                            tmp = itA->second;
                        }
                    }

                    int size = it->second.size();
                    for(int i{0}; i < size; i++) //vector size
                    {
                        
                        string message = tmp.get_username() + " " +  to_string(it->second.at(i)) + " :" + tmp.tweets.at(it->second.at(i)).getText() + '\n';
                        
                        t.sendMessage(message);
                    }
                }
            }
            else
            {
                t.sendMessage("No tweets were found contain this hashtag.\n");
            }
        }

        else if(args.at(0) == "like")
        {
            //its like @username:index command
            if(args.size() == 3)
            {
                args.at(1).erase(0,1);

                string usernameOfPost = args.at(1);
                int index = stoi(args.at(2));
                
                if(accounts.find(usernameOfPost) != accounts.end())
                {
                    if(accounts.at(usernameOfPost).tweets.find(index) != accounts.at(usernameOfPost).tweets.end())
                    {
                        if(accounts.at(usernameOfPost).tweets.at(index).likeTweet(&accounts.at(username)))
                        {
                            t.sendSuccessMessage("Liked successfully.");
                        }
                        else
                        {
                            t.sendMessage("You have already liked this tweet.\n");
                        }
                    }
                    else
                    {
                        t.sendMessage("Could not find any tweet with this index.\n");
                    }
                }
                else
                {
                    t.throwError("User not found.");
                }
                
            }
            else
            {
                t.throwError("the syntax of this command is:\nlike @username:index");
            }
        }

        else if(args.at(0) == "dislike")
        {
            //its like @username:index command
            if(args.size() == 3)
            {
                args.at(1).erase(0,1);

                string usernameOfPost = args.at(1);
                int index = stoi(args.at(2));
                
                if(accounts.find(usernameOfPost) != accounts.end())
                {
                    if(accounts.at(usernameOfPost).tweets.find(index) != accounts.at(usernameOfPost).tweets.end())
                    {
                        if(accounts.at(usernameOfPost).tweets.at(index).dislikeTweet(&accounts.at(username)))
                        {
                            t.sendSuccessMessage("Disiked successfully.");
                        }
                        else
                        {
                            t.sendMessage("You have not liked this post.\n");
                        }
                    }
                    else
                    {
                        t.sendMessage("Could not find any tweet with this index.\n");
                    }
                }
                else
                {
                    t.throwError("User not found.");
                }
                
            }
            else
            {
                t.throwError("the syntax of this command is:\ndislike @username:index");
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
        
        else if (args[0] == "exit"){
            exit (0);
        }

        else 
        {
            t.throwError("Undefined command.");
        }
    
        args.clear();
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
            else if (args.size() == 2){
                signup (t , args[1]);
            }
        }
        else if (args[0] == "login")
        {
            int argsize = args.size();
            if (argsize == 1){
                check_validation(t);
            }
            else if (argsize == 2){
                check_validation(t , args[1]);
            }
            else if (argsize == 3){
                check_validation(t , args[1] , args[2]);
            }
        }
        else if(args.at(0) == "help")
        {
            help(t);
        }
        else if (args[0] == "cls")
        {
            system("cls");
        }
        else if (args[0] == "exit"){
            exit (0);
        }
        else {
            t.throwError("Undefined command.");
        }
    }
}
