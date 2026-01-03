#include <iostream>
#include <string>
#include <sstream>
#include "Commands.hpp"
#include "User.hpp"
#include "Utils.hpp"
using namespace std;


// this is the main file that handles input and calls appropriate command functions.

struct ParsedInput {
    string command;
    string arg1;
    string arg2;
    string content; // for ADD_POST
};

ParsedInput parse_input(const string &line) {
    ParsedInput res;
    istringstream ss(line);

    ss>>res.command;
    if (res.command.empty()) return res;
    ss>>res.arg1; // username or user1
    ss>>res.arg2; // user2 or N or empty

    // rest is content (for ADD_POST)
    getline(ss, res.content);
    if (!res.content.empty() && res.content.front() == ' ')
        res.content.erase(0, 1);
    return res;
}

int main() {
    string input_line;

    while (true) {
        if (!getline(cin, input_line)) break;
        if (input_line.empty()) continue;
        // parse input line
        ParsedInput in = parse_input(input_line);
        string cmd = in.command;
        string u1  = in.arg1;
        string u2  = in.arg2;
        string txt = in.content;

        if (cmd == "EXIT") {
            break;
        }
        // error handling and command calls
        else
        if (cmd == "ADD_USER") {
            if (u1.empty()) {
                cout << "Error: ADD_USER requires a username" <<endl;
            }else{
                addUser(u1);
            }
        }
        else if (cmd == "ADD_FRIEND") {
            if (u1.empty() || u2.empty()) {
                cout << "Error: ADD_FRIEND requires two usernames" <<endl;
            }else{
                addFriend(u1, u2);
            }
        }
        else if (cmd == "ADD_POST") {
            if (u1.empty()) {
                cout<<"Error: ADD_POST requires a username" <<endl;
            } else if (usermap.find(convert_lower(u1)) == usermap.end()) {
                cout<<"Error: User not found" << endl << endl;
            }
            else if (u2.empty()) {
                cout<<"Error: ADD_POST requires content" <<endl;
            } else {
                string s=u2+" "+txt;
                postadd(u1,s);
            }
        }
        else if (cmd == "LIST_FRIENDS") {
            if (u1.empty()) {
                cout<<"Error: LIST_FRIENDS requires a username" <<endl;
            }else{
                friendlist(u1);
            }
        }
        else if (cmd == "OUTPUT_POSTS") {
            if (u1.empty() || u2.empty()) {
                cout << "Error: OUTPUT_POSTS requires a username and N" <<endl;
            }else{
                string key = convert_lower(u1);
                if (usermap.find(key) == usermap.end()) {
                    cout << "Error: User not found" <<endl;
                }else{
                    try {
                        int N = stoi(u2); // to make sure u2 is integer
                        postlist(key, N);
                    } catch (invalid_argument&) {
                        cout << "Error: N must be an integer" <<endl;
                    } catch (out_of_range&) {
                        cout << "Error: N out of range" <<endl;
                    }
                }
            }
        }

        else if (cmd=="DEGREES_OF_SEPARATION") {
            if (u1.empty() || u2.empty()) {
                cout<<"Error: DEGREES_OF_SEPARATION requires two usernames" <<endl;
            }else{
                DegreeofSeparation(u1, u2);
            }
        }
        else if (cmd == "SUGGEST_FRIENDS") {
            if (u1.empty() || u2.empty()) {
                cout << "Error: SUGGEST_FRIENDS requires username and N"<<endl;
            }else{
                try {
                    int N = stoi(u2); // to make sure u2 is integer
                    suggestFriends(u1,N);
                } catch (...) {
                    cout << "Error: N must be an integer"<<endl;
                }
            }
        }

        else {
            // unknown command
            cout<<"Error: Unknown command \"" << cmd << "\"" <<endl;
        }
    }
    // cleanup usermap
    for (auto &p : usermap) {
        delete p.second;
    }
    usermap.clear();
    return 0;
}