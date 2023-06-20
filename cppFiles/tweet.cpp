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
bool Tweet::likeTweet(User* user)
{
    int size = likes.size();
    int Id = user->get_ID();
    for(int i{0}; i < size ; i++)
    {
        if(likes[i]->get_ID() == Id)
        {
            return 0;
        }
    }

    likes.push_back(user);
    return 1;
}

//arguments: username of who disliked tweet
//returns true if tweet disliked
bool Tweet::dislikeTweet(User* user)
{
    for(int i{0}; i < likes.size(); i++)
    {
        if(likes[i] == user)
        {
            likes.erase(likes.begin() + i);
            return 1;
        }
    }

    return 0;
}