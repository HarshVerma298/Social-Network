#include "Commands.hpp"
#include "Utils.hpp"
#include "User.hpp"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;


// Function implementations for command handling
// usernames are always converted to lowercase before processing

void addUser(string &newuser){
    newuser=convert_lower(newuser);
    if (usermap.find(newuser)!=usermap.end()){
        cout<<" Username "<<newuser<<" already exists. Try another name"<<endl;
        cout<<endl;
        return;
    }
    else{
        User* userpointer = new User(newuser);
        usermap[newuser]=userpointer;
    } 
}

void postadd(string &user, string &content){
    user=convert_lower(user);
    if (usermap.find(user)==usermap.end()){
        cout<<" User not found"<<endl;
        cout<<endl;
        return;
    }
    usermap[user]->addpost(content);
}

void postlist(string &user, int N){
    user=convert_lower(user);
    if (usermap.find(user)==usermap.end()){
        cout<<" User not found"<<endl;
        cout<<endl;
        return;
    }
    usermap[user]->outputpost(N); 
}

void addFriend(string &user1, string &user2){
    user1=convert_lower(user1);
    user2=convert_lower(user2);
    if (usermap.find(user1)==usermap.end() || usermap.find(user2)==usermap.end()){
        cout<<" Invalid User"<<endl;
        cout<<endl;
        return;
    }
    if (user1==user2){
        cout<<" Same user"<<endl;
        cout<<endl;
        return;  // same user
    }
    if (usermap[user1]->friendlist.find(user2)!=usermap[user1]->friendlist.end()){
        cout<<" They are friends to each other already"<<endl;
        cout<<endl;
        return;
    }
    else{
        usermap[user1]->friendname(user2);
        usermap[user2]->friendname(user1);
    }
}

void friendlist(string &user){
    user=convert_lower(user);
    if (usermap.find(user)==usermap.end()){
        cout<<" User not found"<<endl;
        cout<<endl;
        return;
    }
    usermap[user]->listfriends();
}


void DegreeofSeparation(string &user1, string &user2){
    user1=convert_lower(user1);
    user2=convert_lower(user2);
   
    if (usermap.find(user1)==usermap.end() || usermap.find(user2)==usermap.end()){
        cout<<" Invalid User"<<endl;
        cout<<endl;
        return;
    }
    if (user1==user2){
        cout<<"0"<<endl;
        cout<<endl;
        return;  // same user
    }
    unordered_map<string,int> dist; // will keep track of distances as well as visited status
    queue<string> vert; // applying BFS to find shortest path

    dist[user1]=0;
    vert.push(user1);

    while(!vert.empty()){
        string cur=vert.front(); 
        vert.pop();
        int d=dist[cur];

        for(const string &edge: usermap[cur]->friendlist){
            if(dist.find(edge)==dist.end()){
                dist[edge]=d+1;
                if(edge==user2) {
                    cout<<dist[edge]<<endl; // found target 
                    cout<<endl;
                    return;
                }
                vert.push(edge);
            }
        }
    }
    cout<<"-1"<<endl;
    cout<<endl;
     // no connection

}

void suggestFriends(string &name, int N){
    name=convert_lower(name);
    if(usermap.find(name)==usermap.end()){
        cout<<" User not found"<<endl;
        cout<<endl;
        return;
    }

    unordered_map<string,int> mutual_count; // candidate to mutual count

    // explore friends of friends
    for(const string &f:usermap[name]->friendlist){
        for(const string &x:usermap[f]->friendlist){
            if(usermap[name]->friendlist.count(x)) continue; // skip existing friend. 
            if(x == name) continue; // skip yourself
            mutual_count[x]++; // increment mutual friend count
        }
    }

    // build a sortable vector
    vector<pair<string,int>> candidates;
    for(auto &p :mutual_count){
        candidates.push_back({p.first, p.second});
    }
    //custom sort : mutuals desc, name asc
    sort(candidates.begin(), candidates.end(),[](auto &a, auto &b){
        if(a.second != b.second) {
            return a.second>b.second; // mutuals desc
        }
        return a.first<b.first; // alphabetical asc
    });
    
    for(int i=0;i<candidates.size() && (N==-1 || i<N);i++){
        cout<<candidates[i].first<<"("<<candidates[i].second<<")"<<endl;
    }
    cout<<endl;
}