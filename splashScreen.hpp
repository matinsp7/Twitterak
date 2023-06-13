#include <iostream>
#include <fstream>
#include <Windows.h>

HANDLE hOutput;
void printLine(std::ifstream& Reader,int color){
    std::cout << "\t\t\t\t\t";
    std::string tempLine;                  //Temp line
    std::getline (Reader , tempLine);        //Get temp line
    tempLine += '\n';                      //Add newline character
    
    SetConsoleTextAttribute(hOutput,color);
    std::cout << tempLine;
    Sleep(100);
}

void printSplashTextUpDownAnimation(std::string address,int color){
    std::ifstream Reader(address);                      //Open file

    if (Reader)                                        //Check if everything is good
    {
        while (Reader.good())
        {
            printLine(Reader,color);
        }
    }
    else                                              //Return error
    {
	    std::cout <<  "! SplashText File does not exist.";
    }
    
    Reader.close ();                                  //close file
}

void printMessageText(std::string messegeTxt,int messegeTxtColor){
    SetConsoleTextAttribute(hOutput,messegeTxtColor);
    std::cout << "\t\t\t\t\t\t\t\t";
    std::cout << messegeTxt << '\n';
}

void runSplashScreen(std::string address,int splashTextColor,std::string messegeTxt,int messegeTxtColor){
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    printSplashTextUpDownAnimation(address,splashTextColor);
    printMessageText(messegeTxt,messegeTxtColor);
    Sleep(1000);
    system("cls");
}