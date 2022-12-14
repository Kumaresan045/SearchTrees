#include<bits/stdc++.h>
using namespace std;

class Node
{
    public:
        int data{};
        Node *left{nullptr};
        Node *right{nullptr};
        Node* parent{nullptr};
        int color{1};
        int height{};

        int inorder_index{};
        int depth{};
       

    
        Node(int data, int color): data{data}, color{color}{};
        Node(int data): data{data}{};
        Node(){};

        bool isExternal(){return left == nullptr && right == nullptr;}
        bool isAboveExternal(){return left->isExternal() || right->isExternal();}
        bool isleftChild(){return parent->left == this;}
        bool isrightChild(){return parent->right == this;}
        bool isRoot(){return parent == nullptr;}
        bool isRed(){return color == 0;}
        bool isBlack(){return color == 1;}
};