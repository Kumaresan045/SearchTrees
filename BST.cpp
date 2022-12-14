#include "SearchTree.h"

class BST : public SearchTree
{
    public:
        BST(){};
        void insert(int data);
        void remove(int data);
};

void BST::insert(int data)
{
    Node* insnode;
    if(root==nullptr) {insnode = new Node(data);root = insnode;}
    else 
    {
        insnode = find(data,root);
        if(!insnode->isExternal())return;
        insnode->data = data;
    }
    insnode->left = new Node();
    insnode->right = new Node();
    insnode->left->parent = insnode;
    insnode->right->parent = insnode;

    size++;
   
}

void BST::remove(int data)
{
    auto node = find(data,root);
    if(node==root && size==1){ *this = BST();return;}
    if(node->isExternal()) return;
    if(node->isAboveExternal()){remaboveext(node);return;}
    auto succ = node->right;
    while(!succ->left->isExternal()) succ = succ->left;
    node->data = succ->data;
    remaboveext(succ);

}
