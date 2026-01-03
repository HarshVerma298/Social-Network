#include "PostAVL.hpp"
#include <algorithm>
#include <iostream>
using namespace std;


Post::Post(long long key, time_t t, const string &c)
    : avlKey(key), realTime(t), content(c) {}

Node::Node(const Post &p) : postdata(p), left(nullptr), right(nullptr), height(0) {}

PostAVL::PostAVL() {
    root=nullptr;
}
PostAVL::~PostAVL() {
    freeTree(root);
}

int PostAVL::height(Node* n) {
    return (n == nullptr) ? -1 : n->height;
}
int PostAVL::balanceFactor(Node* n) {
    if (n == nullptr) return 0;
    return height(n->left)-height(n->right);
}

int PostAVL::updateHeight(Node* n) {
    if (n == nullptr) return -1;
    return 1 + max(height(n->left), height(n->right));
}

Node* PostAVL::leftRotate(Node* x) {
    Node* y=x->right;
    Node* z=y->left;
    y->left=x;
    x->right=z;
    x->height=1+max(height(x->left),height(x->right));
    y->height=1+max(height(y->left),height(y->right));
    return y;
}

Node* PostAVL::rightRotate(Node* y) {
    Node* x=y->left;
    Node* z=x->right;
    x->right=y;
    y->left=z;
    y->height=1+max(height(y->left),height(y->right));
    x->height=1+max(height(x->left),height(x->right));
    return x;
}

Node* PostAVL::inserttotree(Node* node, const Post &p) {
    if (node == nullptr)
        return new Node(p);
    if (p.avlKey < node->postdata.avlKey){
        node->left=inserttotree(node->left, p);
    }
    else if (p.avlKey>node->postdata.avlKey){
        node->right=inserttotree(node->right, p);
    }
    else
        return node; 

    node->height=updateHeight(node);
    int bf = balanceFactor(node);

    // Left child of Left child heavy. Not possible in this context but for completeness
    if (bf>1 && p.avlKey<node->left->postdata.avlKey){
        return rightRotate(node);
    }
    // Right child of Right child heavy
    if (bf<-1 && p.avlKey>node->right->postdata.avlKey){
        return leftRotate(node);
    }
    // Left child of Right child heavy. Not possible in this context but for completeness
    if (bf>1 && p.avlKey>node->left->postdata.avlKey) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right child of Left child heavy. Not possible in this context but for completeness
    if (bf<-1 && p.avlKey<node->right->postdata.avlKey) {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
} 

// print newest posts first
void PostAVL::reverseInOrder(Node* node, int &N) {
    if (!node) return;

    // If N == -1 print all posts (just normal reverse inorder traversal)
    if (N==-1) {
        reverseInOrder(node->right, N);
        cout<<ctime(&node->postdata.realTime);
        cout<<node->postdata.content <<endl;
        cout<<endl;
        reverseInOrder(node->left, N);
        return;
    }
    // N>0 print up to N posts
    if (N>0) {
        reverseInOrder(node->right, N);
        if (N>0) {
            cout<<ctime(&node->postdata.realTime);
            cout<<node->postdata.content <<endl;
            cout<<endl;
            N--;
        }
        reverseInOrder(node->left, N);
    }
}

void PostAVL::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

void PostAVL::insert(const Post &p) {
    root=inserttotree(root, p);
}
void PostAVL::printLatest(int N) {
    reverseInOrder(root, N);
}