#ifndef Twitterak_h
#define Twitterak_h
#include <iostream>
#include <vector>
#include <map>
#include "user.h"
#include "terminal.h"
#include "tweet.h"
class Twitterak {
    public:
    void signup (Terminal t , std::string);
    void check_validation (Terminal t);
    void help(Terminal&);
    Tweet tweet(std::string& text,User& user, unsigned& tweetIndex);
    bool deleteTweet(User& user, unsigned index, std::map < std::string, std::map< int,std::vector<int> > >& sharps);
    bool editTweet(Tweet& tweet, unsigned index, std::string newText, User& user, std::map < std::string, std::map< int,std::vector<int> > >& sharps);
    void login(std::string& username , Terminal t); // int is the index of accvec
    void run ();
    private:
    static std::map<std::string, User> accounts;
    static std::map<std::string, std::map<int, std::vector<int>> > sharps;
};
#endif
