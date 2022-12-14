#include "SearchTree.h"

class Red_Black : public SearchTree
{
    private:
        void doublered(Node* node);
        void doubleblack(Node* node);
        
    public:
        Red_Black(){};
        void insert(int data);
        void remove(int data);
        void display();
        
};

void Red_Black::doubleblack(Node* node)
{
    if(node==root) return;
    auto nodex = node->parent;
    auto nodey = (nodex->left == node) ? nodex->right : nodex->left;
    
    if(nodey->isBlack())
    {
        if(nodey->left->isBlack() && nodey->right->isBlack())
        {

        }
        else
        {

        }
    }
    else
    {

    }
}

void Red_Black::display()
{
    if(!root)return;
    vector<Node*> nodes;
    this->inorder(root,0,0,nodes);
    char grid[height+1][3*size+1];
    for(int i=0;i<height+1;i++)  for(int j=0;j<3*size+1;j++)  grid[i][j] = ' ';
    for(auto nod:nodes)
    {
        int i = nod->depth;
        int j = 3*(nod->inorder_index);
        grid[i][j-2] = (nod->isBlack())?'B':'R';
        grid[i][j-1] = ((nod->data)/10)?((nod->data)/10)+'0':' ';
        grid[i][j] = (nod->data)%10+'0';
    }
    for(int i=0;i<height+1;i++) 
    { 
        for(int j=0;j<3*size+1;j++)  cout<<grid[i][j];
        cout<<'\n';
    }    
    cout<<'\n';
}

void Red_Black::doublered(Node* node)
{
    auto nodev = node->parent;
    auto nodeu = nodev->parent;
    auto nodew = (nodeu->left == nodev) ? nodeu->right : nodeu->left;
    auto parent = nodeu->parent;

    if(nodew->isBlack())
    {
        vector<Node*> subtrees;
        vector<Node*> nodes;
        nodes.push_back(node);
        nodes.push_back(nodev);
        nodes.push_back(nodeu);
        subtrees.push_back(node->left);
        subtrees.push_back(node->right);
        subtrees.push_back((node==nodev->left) ? nodev->right : nodev->left);
        subtrees.push_back(nodew);
        sort(nodes.begin(),nodes.end(),[](Node* a,Node* b){return a->data < b->data;});
        sort(subtrees.begin(),subtrees.end(),[](Node* a,Node* b){return a->data < b->data;});
        if(parent && parent->left == nodeu) parent->left = nodes[1];
        else if(parent) parent->right = nodes[1];
        else root = nodes[1];
        nodes[1]->parent = parent;
        nodes[1]->left = nodes[0];
        nodes[1]->right = nodes[2];
        nodes[0]->parent = nodes[1];
        nodes[2]->parent = nodes[1];
        nodes[0]->left = subtrees[0];
        nodes[0]->right = subtrees[1];
        nodes[2]->left = subtrees[2];
        nodes[2]->right = subtrees[3];
        subtrees[0]->parent = nodes[0];
        subtrees[1]->parent = nodes[0];
        subtrees[2]->parent = nodes[2];
        subtrees[3]->parent = nodes[2];
        nodes[1]->color = 1;
        nodes[0]->color = 0;
        nodes[2]->color = 0;        
    }
    else
    {
        if(nodeu!=root) nodeu->color = 0;
        nodew->color = 1;
        nodev->color = 1;
        if(parent && parent->isRed()) doublered(nodeu);
    }


}

void Red_Black::insert(int data)
{
    Node* insnode;
    if(root==nullptr) {insnode = new Node(data);root = insnode;}
    else 
    {
        insnode = find(data,root);
        if(!insnode->isExternal())return;
        insnode->data = data;
        insnode->color = 0;
    }
    insnode->left = new Node();
    insnode->right = new Node();
    insnode->left->parent = insnode;
    insnode->right->parent = insnode;

    size++;
    if(insnode->isRed() && insnode->parent->isRed()) doublered(insnode);    
}

void Red_Black::remove(int data)
{
    auto node = find(data,root);
    if(node==root && size==1){ *this = Red_Black();return;}
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
    bool flag_db{};
    if(temp->isRed() || rem->isRed()) temp->color =1;
    else flag_db = true;
    remaboveext(rem);
    if(flag_db) doubleblack(temp);
}

int main()
{
    vector<int> data = {4,7,12,15,3,5,14,18};
    Red_Black t;
    for(auto d:data){t.insert(d); t.display();}
}