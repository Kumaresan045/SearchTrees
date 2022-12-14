#include "SearchTree.h"

Node* SearchTree::find(int data,Node* Root)
{
    if(Root->isExternal() || data == Root->data) return Root;
    if(data < Root->data) return find(data,Root->left);
    return find(data,Root->right);
}

bool SearchTree::search(int data)
{
    Node* temp = find(data,root);
    if(temp->isExternal()) return false;
    return true;
}

void SearchTree::display()
{
    if(!root)return;
    vector<Node*> nodes;
    this->inorder(root,0,0,nodes);
    char grid[height+1][2*size+1];
    for(int i=0;i<height+1;i++)  for(int j=0;j<2*size+1;j++)  grid[i][j] = ' ';
    for(auto nod:nodes)
    {
        int i = nod->depth;
        int j = 2*(nod->inorder_index);
        grid[i][j-1] = ((nod->data)/10)?((nod->data)/10)+'0':' ';
        grid[i][j] = (nod->data)%10+'0';
    }
    for(int i=0;i<height+1;i++) 
    { 
        for(int j=0;j<2*size+1;j++)  cout<<grid[i][j];
        cout<<'\n';
    }    
    cout<<'\n';
}

int SearchTree::inorder(Node* node,int cnt,int depth,vector<Node*>& nodes)
{
    if(node->isExternal()) return cnt;
    cnt = inorder(node->left,cnt,depth+1,nodes);
    cnt++;
    node->inorder_index = cnt;
    node->depth = depth;
    if(node->depth> height) height = node->depth;
    nodes.push_back(node);
    cnt = inorder(node->right,cnt,depth+1,nodes);
    return cnt;
}

void SearchTree::remaboveext(Node* node)
{
    auto parent = node->parent;
    auto child = (node->left->isExternal())?node->right:node->left;
    if(parent && parent->left == node) parent->left = child;
    else if(parent) parent->right = child;
    else root = child;
    child->parent = parent;

    if(node->right != child) delete node->right;
    if(node->left != child) delete node->left;
    delete node;

    size--;
    
}