#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int key;
    int height;
    Node* left;
    Node* right;
};

Node* newNode(int key){
    Node* node = new Node();
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
}

int height(Node* node){
    if(node==NULL)
        return 0;
    return node->height;
}

Node* leftRotate(Node* y){
    Node* x=y->right;
    Node* T=x->left;

    y->right=T;
    x->left=y;

    y->height=max(height(y->left), height(y->right))+1;
    x->height=max(height(x->left), height(x->right))+1;

    return x;
}

Node* rightRotate(Node* x){
    Node* y=x->left;
    Node* T=y->right;

    y->right=x;
    x->left=T;

    y->height=max(height(y->left), height(y->right))+1;
    x->height=max(height(x->left), height(x->right))+1;

    return y;
}

int getBalance(Node* node){
    return height(node->left)-height(node->right);
}

Node* insertNode(Node* root, int key){
    //inserts node and returns pointer to new node
    if(root==NULL){
        return newNode(key);
    }

    if(key<root->key){
        root->left=insertNode(root->left, key);
    }else if(key>root->key){
        root->right=insertNode(root->right, key);
    }else return root;

    int balance=getBalance(root);

    //LL
    if(balance>1 && getBalance(root->left)>=0)
        return rightRotate(root);
    
    //LR
    if(balance>1 && getBalance(root->left)<0){
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    //RL
    if(balance<-1 && getBalance(root->right)>=0){
        root->right=rightRotate(root->right);
        return leftRotate(root);
    }

    //RR
    if(balance<-1 && getBalance(root->right)<0){
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node* root){
    if(root==NULL)
        return;
    
    preOrder(root->left);
    cout<<root->key<<" ";
    preOrder(root->right);
}

Node* minValueNode(Node* root){
    int minVal=INT_MAX;
    Node* node=NULL;
    while(root!=NULL){
        if(root->key<minVal){
            node=root;
            minVal=root->key;
        }
        root=root->left;
    }
    return node;
}

Node* deleteNode(Node* root, int key){

    if(root==NULL)
        return root;

    if(key<root->key){
        root->left=deleteNode(root->left, key);
    }else if(key>root->key){
        root->right=deleteNode(root->right, key);
    }else{
        Node* temp=root;
        if(root->left==NULL){
            root=root->right;
            free(temp);
        }else if(root->right==NULL){
            root=root->left;
            free(temp);
        }else{
            temp=minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right, temp->key);
        }
    }

    if(root==NULL)
        return NULL;

    int balance=getBalance(root);

    //LL
    if(balance>1 && getBalance(root->left)>=0){
        root=rightRotate(root);
    }

    //LR
    if(balance>1 && getBalance(root->right)<0){
        root->left=leftRotate(root->left);
        root=rightRotate(root);
    }

    //RL
    if(balance<-1 && getBalance(root->right)>=0){
        root->right=rightRotate(root->right);
        root=leftRotate(root);
    }

    //RR
    if(balance<-1 && getBalance(root->right)<0){
        root=leftRotate(root);
    }

    return root;

}

int main(){

    Node* root= new Node();

    vector<int> arr={19, -5, 10, 0, 67, 11, -1, -51, 2, 7};
    for(int i=0; i<arr.size(); i++){
        root=insertNode(root, arr[i]);
    }
    preOrder(root);
    root=deleteNode(root, -5);
    root=deleteNode(root, 10);
    cout<<endl;
    preOrder(root);
}