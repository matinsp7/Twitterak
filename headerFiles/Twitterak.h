#ifndef Twitterak_h
#define Twitterak_h
#include <iostream>
#include <vector>
#include <map>
#include "user.h"
#include "terminal.h"
class Twitterak {
    public:
    void signup (std::vector<std::string>&, Terminal&);
    void check_validation(std::vector<std::string>&, Terminal&);
    void login(std::string& , Terminal&); // int is the index of accvec
    void help(Terminal&);
    void profile(std::string& username, Terminal& t);
    void editProfile(std::vector<std::string>& args, std::string& username, Terminal& t);
    void editTweet();
    void run ();
    private:
    static std::map<std::string, User> accounts;
};
#endif