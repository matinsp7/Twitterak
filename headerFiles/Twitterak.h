#include <iostream>
#include <vector>
#include "user.h"
#include "terminal.h"
#ifndef Twitterak_h
#define Twitterak_h
class Twitterak {
    public:
    void signup (Terminal);
    void check_validation(Terminal);
    void login(int& , Terminal  ); // int is the index of accvec
    void run ();
    private:
    static std::vector<User> accounts;
};
#endif