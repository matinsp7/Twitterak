#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#else

#endif

#include "../header files/terminal.h"
#include "../header files/splashScreen.h"

splashScreen::splashScreen(){}

void splashScreen::printLine(std::ifstream& Reader,int color,Terminal t){
    std::string tempLine;                  //Temp line
    std::getline (Reader , tempLine);        //Get temp line
    tempLine += '\n';                      //Add newline character
    
    SetConsoleTextAttribute(hOutput,color);
    t.sendMessage(tempLine);
    Sleep(100);
}

void splashScreen::printSplashTextUpDownAnimation(std::string address,int color, Terminal t){
    std::ifstream Reader(address);                      //Open file

    if (Reader)                                        //Check if everything is good
    {
        t.setSmooth(0);
        while (Reader.good())
        {
            printLine(Reader,color,t);
        }
    }
    else                                              //Return error
    {
	    t.throwError("SplashText File does not exist.");
    }
    t.setSmooth(1);
    Reader.close ();                                  //close file
}

void splashScreen::printGuideMessage(std::string messageTxt,int messageTxtColor, Terminal t){
    SetConsoleTextAttribute(hOutput,messageTxtColor);
    t.sendMessage(messageTxt +'\n');
}

void splashScreen::runSplashScreen(std::string address,int splashTextColor,std::string messageTxt,int messageTxtColor, Terminal t){
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    printSplashTextUpDownAnimation(address,splashTextColor, t);
    printGuideMessage(messageTxt,messageTxtColor, t);
    SetConsoleTextAttribute(hOutput,7);

}