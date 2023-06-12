#include <fstream>
#include <vector>

#ifndef Terminal_h
#define Terminal_h
class Terminal{
public:
    Terminal(std::istream& iStream, std::ostream& oStream);
    std::vector<std::string> getCommand();
    std::string getValue(std::string valueName);
    void throwEror(std::string messege);
    void sendSuccessMessege(std::string messege);
    std::string sendQuestion(std::string messege);
    void sendMessege(std::string messege);
    std::string toLower(std::string text) const;
    void setSmooth(bool value);
    
private:
    std::istream& input;
    std::ostream& output;
    bool smooth;
    void print(std::string text);
};

#endif