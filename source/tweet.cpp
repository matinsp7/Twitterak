#include <vector>
#include <iostream>
#include "../include/tweet.h"
#include "../include/user.h"

using namespace std;

//arguments: text of tweet
Tweet::Tweet(string& text, string time)
{
    tweetText = text;
    tweetTime = time;
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
        if(likes[i] == Id)
        {
            return 0;
        }
    }

    likes.push_back(Id);
    return 1;
}

//arguments: username of who disliked tweet
//returns true if tweet disliked
bool Tweet::dislikeTweet(User* user)
{
    int size = likes.size();
    int Id = user->get_ID();
    for(int i{0}; i < size ; i++)
    {
        if(likes[i] == Id)
        {
            likes.erase(likes.begin() + i);
            return 1;
        }
    }

    return 0;
}

std::string Tweet::getTime() const
{
    return tweetTime;
}
