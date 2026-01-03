#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <set>
#include <unordered_map>
#include "PostAVL.hpp"
using namespace std;


// This is the User class representing each user in the social network
class User {
private:
    string username;
    PostAVL* posttree;

public:
    set<string> friendlist; // set to store friends' usernames in sorted order

    User(string name);
    ~User();
    string getName();
    void listfriends();
    void addpost(const string &s);
    void outputpost(int N);
    void friendname(const string &name);
};

extern unordered_map<string, User*> usermap; // global usermap declaration

#endif
