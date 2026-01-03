#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
using namespace std;

void addUser(string &);
void postadd(string &, string &);
void postlist(string &, int);
void addFriend(string &, string &);
void friendlist(string &);
void DegreeofSeparation(string &, string &);
void suggestFriends(string &, int);

#endif
