#ifndef Tweet_H
#define Tweet_H
#include <vector>

class User;

class Tweet{
public:

    //arguments: text of tweet
    Tweet(std::string& text);

    //set tweet text
    void setText(std::string& text);

    //returns tweet text
    std::string getText() const;

    //arguments: username of who liked tweet
    //returns true if tweet liked
    //returns false if tweet unliked
    bool likeTweet(User* username);


    //vector of usernames that liked tweet
    std::vector<User*> likes;
    
private:

    //the complete text of tweet
    std::string tweetText;
};
#endif