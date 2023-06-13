#include <fstream>
#include <vector>

#ifndef Terminal_h
#define Terminal_h
class Terminal{
public:
    Terminal(std::istream& iStream, std::ostream& oStream);
    std::vector<std::string> getCommand();
    std::string getStringValue(std::string valueName);
    int getIntValue(std::string valueName);
    void throwError(std::string message);
    void sendSuccessMessage(std::string message);
    std::string sendQuestion(std::string message);
    void sendMessage(std::string message);
    std::string toLower(std::string text) const;
    void setSmooth(bool value);
    
private:
    std::istream& input;
    std::ostream& output;
    bool smooth;
    void print(std::string text);
};

#endif