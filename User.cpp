#include "User.hpp"
#include "Utils.hpp"
#include <iostream>
#include <ctime>
using namespace std;

unordered_map<string,User*> usermap;


// implementation of User class methods

User::User(string name){
    username=name;
    posttree=new PostAVL();

}
User::~User(){
    delete posttree;
}
string User::getName(){
    return username;
} 
void User::listfriends(){
    for(const string &f: friendlist){
        cout<<f<<endl; //Sorted order
    }
    cout<<endl;
}

void User::addpost(const string &s){
    GLOBAL_POST_TIME++; // increment global post time. Note: this is a simple way to ensure unique increasing keys
    time_t realtime=time(NULL); // get current real time. store as metadata
    Post p(GLOBAL_POST_TIME,realtime,s);
    posttree->insert(p);
    cout<<endl;
}

void User::outputpost(int N){
    posttree->printLatest(N);
    cout<<endl;
}

void User::friendname(const string &name){
    friendlist.insert(name);
}