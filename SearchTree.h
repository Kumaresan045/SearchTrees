#include "Node.h"

class SearchTree
{
    protected:
        Node* root{nullptr};
        Node* find(int data,Node* Root);
        int size{};
        int height{};
        int inorder(Node* node,int cnt,int depth,vector<Node*>& nodes);
        void remaboveext(Node* node);
    
    public:
        SearchTree(){};
        bool search(int data);

        virtual void insert(int data)=0;
        virtual void remove(int data) =0;

        Node* getRoot(){return root;}

        virtual void display();
              
};

// BST
// AVL
// Splay
// Red Black

// (2,4) Trees
