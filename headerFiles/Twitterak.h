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
    void signup (Terminal t);
    void check_validation (Terminal t);
    Tweet tweet(std::string& text,std::string& username, unsigned& tweetIndex);
    void help(Terminal&);
    void login(std::string& username , Terminal t); // int is the index of accvec
    void run ();
    private:
    static std::map<std::string, User> accounts;
    static std::map<std::string, std::map<std::string, std::vector<int>> > sharps;
};
#endif