#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#else

#endif

#ifndef splashScreen_H
#define splashScreen_H

class splashScreen{

public:
    splashScreen();
    void runSplashScreen(std::string address,int splashTextColor,std::string messageTxt,int messageTxtColor);
    void printSplashTextUpDownAnimation(std::string address,int color);
    void printMessageText(std::string messageTxt,int messageTxtColor);
    void printLine(std::ifstream& Reader,int color);

private:

    HANDLE hOutput;

};

#endif