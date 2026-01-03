#ifndef POSTAVL_HPP
#define POSTAVL_HPP

#include <ctime>
#include <string>
using namespace std;

// consists structures and class for Post AVL tree used in each User.

struct Post {
    long long avlKey; // unique global increasing key (for AVL ordering)
    time_t realTime;  // real world timestamp (metadata only, for display)
    string content;
    Post(long long key, time_t t, const string &c);
};

struct Node {
    Post postdata;
    Node* left;
    Node* right;
    int height;
    Node(const Post &p);
};

class PostAVL {
private:
    Node* root;
    int height(Node*);
    int updateHeight(Node*);
    int balanceFactor(Node*);
    Node* rightRotate(Node*);
    Node* leftRotate(Node*);
    Node* inserttotree(Node*, const Post&);
    void reverseInOrder(Node*, int &);
    void freeTree(Node*);

public:
    PostAVL();
    ~PostAVL();
    void insert(const Post&);
    void printLatest(int N);
};

#endif
