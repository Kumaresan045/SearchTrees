#include "SearchTree.h"

class Splay: public SearchTree
{
    private:
        void splay(Node* node);
        void splay3(Node* node);
        void splay2(Node* node);
    public:
        Splay(){};
        bool search(int data);
        void insert(int data);
        void remove(int data);
};

void Splay::splay2(Node* node)
{
    auto nodey = node->parent;
    Node *nodew,*t0,*t1;
    if(nodey->left == node)
    {
        nodew=node->left;
        t0 = node->right;
        t1 = nodey->right;

        root=node;
        node->parent=nullptr;
        node->left=nodew;
        nodew->parent=node;
        node->right=nodey;
        nodey->parent=node;
    }
    else
    {
        nodew=node->right;
        t0 = nodey->left;
        t1 = node->left;

        root=node;
        node->parent=nullptr;
        node->right=nodew;
        nodew->parent=node;
        node->left=nodey;
        nodey->parent=node;
    }
    nodey->left=t0;
    t0->parent=nodey;
    nodey->right=t1;
    t1->parent=nodey;
}

void Splay::splay3(Node* node)
{
    if((node->parent->left == node)^(node->parent->parent->left == node->parent))
    {
        vector<Node*> nodes {node,node->parent,node->parent->parent};
        sort(nodes.begin(),nodes.end(),[](Node* a,Node* b){return a->data<b->data;});
        auto nodea = nodes[0];
        auto nodeb = nodes[1];
        auto nodec = nodes[2];
        auto t1 = nodeb->left;
        auto t2 = nodeb->right;
        auto gp = node->parent->parent->parent;
        if(gp) (gp->left == nodec)?gp->left = nodeb:gp->right = nodeb;
        else root = nodeb;
        nodeb->parent = gp;
        nodeb->left = nodea;
        nodea->parent = nodeb;
        nodeb->right = nodec;
        nodec->parent = nodeb;
        nodea->right = t1;
        t1->parent = nodea;
        nodec->left = t2;
        t2->parent = nodec;
    }
    else
    {
        if(node->parent->left == node)
        {
            auto nodez = node->parent->parent;
            auto nodey = node->parent;
            auto t0 = node->left;
            auto t1 = node->right;
            auto t2 = nodey->right;
            auto t3 = nodez->right;
            auto gp = nodez->parent;
            if(gp) (gp->left == nodez)?(gp->left = node):(gp->right = node);
            else root = node;
            node->parent = gp;
            node->left = t0;
            t0->parent = node;
            node->right = nodey;
            nodey->parent = node;
            nodey->left = t1;
            t1->parent = nodey;
            nodey->right = nodez;
            nodez->parent = nodey;
            nodez->left = t2;
            t2->parent = nodez;
            nodez->right = t3;
            t3->parent = nodez;
        }
        else
        {
            auto nodez = node->parent->parent;
            auto nodey = node->parent;
            auto t0 = nodez->left;
            auto t1 = nodey->left;
            auto t2 = node->left;
            auto t3 = node->right;
            auto gp = nodez->parent;
            if(gp) (gp->left == nodez)?(gp->left = node):(gp->right = node);
            else root = node;
            node->parent = gp;
            node->left = nodey;
            nodey->parent = node;
            node->right = t3;
            t3->parent = node;
            nodey->left = nodez;
            nodez->parent = nodey;
            nodey->right = t2;
            t2->parent = nodey;
            nodez->left = t0;
            t0->parent = nodez;
            nodez->right = t1;
            t1->parent = nodez;
        }
    }

}

void Splay::splay(Node* node)
{
    while(node->parent)
    {
        if(node->parent->parent) splay3(node);
        else splay2(node);
    }
}

bool Splay::search(int data)
{
    auto node = find(data,root);
    if(node->isExternal()){splay(node->parent);return false;}
    splay(node);
    return true;
}

void Splay::insert(int data)
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
    splay(insnode);

    size++;
}

void Splay::remove(int data)
{
    auto node = find(data,root);
    if(node==root && size==1){ *this = Splay();return;}
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
    splay(temp);

    size--;
}
