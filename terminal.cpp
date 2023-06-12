#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "terminal.h"


    Terminal::Terminal( std::istream& iStream, std::ostream& oStream )
    : input{iStream}, output{oStream} {}

    
    std::vector<std::string> Terminal::getCommand()
    {
        print("> ");

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
            return getCommand();
        }

    }

    std::string Terminal::getValue(std::string valueName)
    {
        print("$ " + valueName + ": ");


        std::string val;
        getline(input, val);

        return val;
    }

    void Terminal::throwEror(std::string messege)
    {
        print("! " + messege);
        output << std::endl;
    }

    void Terminal::sendSuccessMessege(std::string messege)
    {
        print("* " + messege);
        output << std::endl;
    }

    std::string Terminal::sendQuestion(std::string messege)
    {
        print("? " + messege + ": ");

        std::vector<std::string> answer = getCommand();

        std::string ans;
        for( unsigned i{0}; i < answer.size(); ++i )
        {
            ans += answer[i];
        }

        return ans;
    }

    void Terminal::sendMessege(std::string messege)
    {
        print(messege);
        output << std::endl;
    }

    std::string Terminal::toLower(std::string text) const 
    {
        for( unsigned i{0}; i < text.length(); ++i )
        {
            text[i] = tolower(text[i]);
        }

        return text;
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

    void Terminal::setSmooth(bool value){
        smooth = value;
    }