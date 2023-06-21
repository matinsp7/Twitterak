#ifndef Tweet_H
#define Tweet_H
#include <vector>

class User;

class Tweet{
public:

    //arguments: text of tweet
    Tweet(std::string& text, std::string time);

    //set tweet text
    void setText(std::string& text);

    //returns tweet text
    std::string getText() const;

    std::string getTime() const;

    //arguments: username of who liked tweet
    //returns true if tweet liked
    //returns false if tweet unliked
    bool likeTweet(User* user);

    bool dislikeTweet(User* user);
    //vector of ID that liked tweet
    std::vector<int> likes;
    
private:

    //the complete text of tweet
    std::string tweetText;

    std::string tweetTime;
};
#endif