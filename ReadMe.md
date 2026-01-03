# Social Network Platform
This project implements a command line simulator for a social network. This supports basic social media functionalities such as user creation, adding friends, posting updates, viewing posts along with the , suggesting friends, and computing degrees of separation in the social graph. AVL trees are used to store and retrieve posts efficiently in reverse-chronological order (latest frist).

### Submission  
Name — Harsh Verma  
Entry No — 2024CS10499


### Sources
AVL trees code was done in our lab assignment. So AVL tree funtions and implementation code for this assignment has its root in that.
Input parsing code has been taken from my last assignemnt. Some parts were also refined by llms.


## Project Structure  
`main1.cpp` serves as the entry point.  

```
.
├── Commands.cpp
├── Commands.hpp
├── PostAVL.cpp
├── PostAVL.hpp
├── User.cpp
├── User.hpp
├── Utils.cpp
├── Utils.hpp
└── main1.cpp
```

## How to Compile & Run  

### Linux / macOS
```sh
g++ -std=c++17 *.cpp -o social
./social
```

### Windows (MinGW)
```sh
g++ -std=c++17 *.cpp -o social.exe
social.exe
```
or(preferred)
 - in the terminal
```bash
g++ main1.cpp PostAVL.cpp User.cpp Utils.cpp Commands.cpp -o a
./a
```

## Features  

### User Management  
- Create users for the social network
- Store friendships through undirected graphs. User are the vertices on the graph.

### Posts with Timestamps  
- Each post stored in an AVL tree (based on the timestamp of the creation).
- Global increasing key ensures ordering. For now I have created a global clock for maintaining the order of the posts and keeping track of their real time as metadata. AVL may crash if user creates two posts at same time. So this 
- Show N latest posts or all (`N = -1`)

### Friendship & Connections  
- Add friend relationships between two users. This is assumed to be bidirectional as graph is undirected. 
- Print sorted (alphabetical order) friend list.
- Compute Degree of Separation using BFS. This represents the minimum path distance between the user in the network graph.
- Suggest friends based on mutual friends. This includes friends of a friend, that are not directly friends or the user itself.

### Data Structures Used  
| Purpose | Structure | 
|--------|----------|
Store users | `unordered_map<string, User*>`  this is to get fast acess to the user's data
Friends list | `set<string>`  this is to store the names of the friends already in sorted order. I could have simply used a vector and then just sort it.
Store posts per user | **AVL Tree**  Mandatory. Allows fast insertion and deletion(not required here) in ordered structure.
Graph search | BFS via queue. For finding the mutuals.

### Why AVL Tree?  
To efficiently maintain posts in **order format**:
- AVL trees allows fast management for insertion and deletion and also storing the data in ordered format
- O(log N) insertion  
- O(k + log N) retrieval of latest k posts  

## Commands Supported 
Below is the command style for the assignment. Note that the commands are case sensitive. 
Appropriate error messages are displayed if commands do not satisfy the criteria. 

| Command | Description |
|--------|-------------|
`ADD_USER <name>` | Registers a new user  
`ADD_FRIEND <u1> <u2>` | Makes users friends if not already
`ADD_POST <user> <content>` | Adds a post for user  
`LIST_FRIENDS <user>` | Lists friends alphabetically  
`OUTPUT_POSTS <user> <N>` | Prints latest N posts (`N = -1` → all)  
`DEGREES_OF_SEPARATION <u1> <u2>` | Shortest friend-path length or `-1` if no path
`SUGGEST_FRIENDS <user> <N>` | Suggests top N users based on mutual friends  (Friend of a friend)
`EXIT` | End program  

## Example Usage  

```
>> ADD_USER a
>> ADD_USER b
>> ADD_USER c

>> ADD_FRIEND a b
>> ADD_FRIEND b c

>> ADD_POST a This is post 1
>> ADD_POST b New post

>> OUTPUT_POSTS b 1
Mon Nov 4 18:10:21 2025
New post

>> LIST_FRIENDS b
a
c

>> DEGREES_OF_SEPARATION a a
2

>> SUGGEST_FRIENDS a 1
c(1)

>> EXIT
```

## Error Handling  
- Invalid commands produce descriptive messages. 
- Duplicate users or friend links checked. 
- non existent user names are used also checked.
- Validations for missing content or invalid numbers.

## Core Implementation Details  

### `User` Class  
- Stores username and friend set  
- Maintains AVL tree for posts  
- Interfaces for post operations

### `PostAVL`  
Balanced tree storing posts sorted by global increasing key (timestamp ID) with real time as a metadata.

Each node contains:
- avlKey — increasing timestamp index  
- time_t realTime — OS time  
- post string content  

### `Commands` Module  
Handles input parsing and routes actions to user/network functions. Handles the input operation

### Global Helpers  
- `GLOBAL_POST_TIME` to order posts  
- `convert_lower` to ensure case-insensitive usernames 

## Assumptions  
- Usernames converted to lowercase internally since they are to be considered case insensitive
- Commands written in uppercase as per assignment
- `N = -1` prints all available data  
- Content must be provided for posts.

## Improvements / Future Extensions  
- Persist data to disk  
- Support deleting users and posts  
- Add comments / likes / trending posts  for future ideas.
- use real time in avl trees for key comparsion.
---
