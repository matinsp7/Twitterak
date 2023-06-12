#include <iostream>
#include <vector>
#include "User.h"

#ifndef Twitterak_h
#define Twitterak_h
class Twitterak {
    public:
    void signup ();
    void check_login();
    void run ();
    private:
    static std::vector<User> accounts;
};
#endif