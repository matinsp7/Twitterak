#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
#include "../headerFiles/terminal.h"


    Terminal::Terminal( std::istream& iStream, std::ostream& oStream )
    : input{iStream}, output{oStream} {}
    
    std::vector<std::string> Terminal::getCommand(std::string prefix)
    {
        print(prefix);

        std::vector<std::string> args;

        std::string line;

        getline(input, line);

        std::string letter;
        bool inQuotation{0};
        int begin{-1};
        int size = line.length();

        for(unsigned i{0}; i < size; i++)
        {
            if(inQuotation)
            {                       //i points to a element that is in quotation
                if(line[i] == '"' || line[i] == '\'')
                {                        //its the end of text in quotation
                    inQuotation = 0;
                    letter = line.substr(begin+1, i-begin-1);
                    args.push_back(letter);
                    begin = -1;
                }
                else if(i == size-1)
                {                         //line ends but quotation is still open
                    letter = line.substr(begin+1, i-begin);
                    letter += '\n';
                    std::string tmp;
                    getline(input, tmp, '"');
                    input.ignore();
                    letter += tmp;
                    args.push_back(letter);
                }

            }
            else
            {                         //i points to a element that is Not in quotation
                if(line[i] == '"' || line[i] == '\'')
                {
                    inQuotation = 1;
                    begin = i;
                }
                else if(line[i] == ' ')
                {
                    if(begin != -1)
                    {
                        letter = line.substr(begin, i-begin);
                        args.push_back(letter);
                        begin = -1;
                    }

                }
                else if(i == size-1)
                {
                    if(begin != -1)
                    {
                        letter = line.substr(begin, i-begin+1);
                        args.push_back(letter);
                        begin = -1;
                    }
                    else if(args.size() == 0)
                    {
                        letter = line[i];
                        args.push_back(letter);
                    }
                }
                else if(begin == -1)
                {
                    begin = i;
                }
            }
        }

        if(args.size() > 0)
            return args;
        else
        {
            return getCommand(prefix);
        }

    }

    void Terminal::print(std::string text)
    {
        if(smooth)
        {
            unsigned stop = 1;

            for(unsigned i{0}; i < text.length(); ++i)
            {
                output << text[i];
                if(stop % 2 == 0)
                    Sleep(1);
                stop++;
            }
        }
        else
        {
            output << text;
        }

    }

    std::string Terminal::getStringValue(std::string valueName)
    {
        print("$ " + valueName + " ");

        std::string val;
        getline(input, val);

        return val;
    }

    int Terminal::getIntValue(std::string valueName){

        print("$ " + valueName + " ");

        int val;
        input >> val;

        return val;
    }

    void Terminal::throwError(std::string message)
    {
        print("! " + message);
        output << std::endl;
    }

    void Terminal::sendSuccessMessage(std::string message)
    {
        print("* " + message);
        output << std::endl;
    }

    std::string Terminal::sendQuestion(std::string message)
    {
        print("? " + message + ": ");

        std::string ans;
        input >> ans;
        return ans;
    }

    void Terminal::sendMessage(std::string message)
    {
        print(message);
    }

    std::string Terminal::toLower(std::string text) const 
    {
        for( unsigned i{0}; i < text.length(); ++i )
        {
            text[i] = tolower(text[i]);
        }

        return text;
    }

   

    void Terminal::setSmooth(bool value){
        smooth = value;
    }