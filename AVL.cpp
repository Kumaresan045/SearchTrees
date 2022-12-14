#include "SearchTree.h"

class AVL : public SearchTree
{
    private:
        Node* restructure(Node* node);
        Node* restore(Node* node,int mode);
        void recheck(Node* node,int mode);
        void setheight(Node* node);
    public:
        AVL(){};
        void insert(int data);
        void remove(int data);
        
};
 
void AVL::recheck(Node* temp,int mode)
{
    while(temp) 
    {
        if(abs(temp->left->height - temp->right->height)>1) temp=restore(temp,mode);
        else setheight(temp);
        temp = temp->parent;
    }
}

void AVL::setheight(Node* node) {node->height = max(node->left->height,node->right->height)+1;}

void AVL::remove(int data)
{
    auto node = find(data,root);
    if(node==root && size==1){ *this = AVL();return;}
    if(node->isExternal()) return;
    Node* rem;
    if(node->isAboveExternal())rem=node;
    else
    {
        rem = node->right;
        while(!rem->left->isExternal()) rem = rem->left;
        node->data = rem->data;
    }
    auto temp = rem->parent;
    remaboveext(rem);
    recheck(temp,1);
}



void AVL::insert(int data)
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
    auto temp = insnode;
    setheight(temp);
    recheck(temp->parent,0);
}

Node* AVL::restore(Node* node,int mode)
{
    auto child = (node->left->height > node->right->height)?node->left:node->right;
    Node* grandchild;
    if(mode==0 || child->left->height != child->right->height) grandchild = (child->left->height > child->right->height)?child->left:child->right;
    else  grandchild = (node->left == child)?child->left:child->right;
    return restructure(grandchild);
}

Node* AVL::restructure(Node* nodex)
{
    auto nodey = nodex->parent;
    auto nodez = nodey->parent;
    auto parent = nodez->parent;
    int side;
    if(parent) side = parent->left == nodez;
    vector<Node*> nodes{nodex,nodey,nodez};
    sort(nodes.begin(),nodes.end(),[](Node* a,Node* b){return a->data < b->data;});
    auto nodea = nodes[0];
    auto nodeb = nodes[1];
    auto nodec = nodes[2];
    Node *t1,*t2;
    if(nodea == nodex && nodeb == nodey) t1=nodea->right;
    else t1=nodeb->left;
    if(nodea == nodez && nodeb == nodey) t2=nodec->left;
    else t2=nodeb->right;

    if(parent && side) parent->left = nodeb;
    else if(parent) parent->right = nodeb;
    nodeb->parent = parent;
    nodeb->left = nodea;
    nodea->parent = nodeb;
    nodeb->right = nodec;
    nodec->parent = nodeb;
    nodea->right = t1;
    t1->parent = nodea;
    nodec->left = t2;
    t2->parent = nodec;
    setheight(nodea);
    setheight(nodec);
    setheight(nodeb);
    if(!parent)root=nodeb;
    return nodeb;
}
