#include <vector>
#include <iostream>
#include "../headerFiles/tweet.h"
#include "../headerFiles/user.h"

using namespace std;

//arguments: text of tweet
Tweet::Tweet(string& text)
{
tweetText = text;
}

void Tweet::setText(string& text){
    tweetText = text;
}

string Tweet::getText() const{
    return tweetText;
}

//arguments: username of who liked tweet
//returns true if tweet liked
//returns false if tweet unliked
bool Tweet::likeTweet(User* user)
{
    for(int i{0}; i < likes.size(); i++)
    {
        if(likes[i] == user)
        {
            likes.erase(likes.begin() + i);
            return 0;
        }
    }

    likes.push_back(user);
    return 1;
}
