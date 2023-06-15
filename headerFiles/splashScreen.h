
#ifndef splashScreen_H
#define splashScreen_H

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#else

#endif

#include "terminal.h"

class splashScreen{

public:
    splashScreen();
    void runSplashScreen(std::string address,int splashTextColor,std::string messageTxt,int messageTxtColor, Terminal t);
    void printSplashTextUpDownAnimation(std::string address,int color, Terminal t);
    void printGuideMessage(std::string messageTxt,int messageTxtColor, Terminal t);
    void printLine(std::ifstream& Reader,int color, Terminal t);

private:

    HANDLE hOutput;

};

#endif