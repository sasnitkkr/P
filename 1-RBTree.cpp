#include<bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    Node* p;
    Node* left;
    Node* right;
    char color;
    Node(int data){
        key=data;
        p=NULL;
        left=NULL;
        right=NULL;
        color='R';
    }
};

struct Tree{
    Node* root;
    Node* nil;
    Tree(){
        nil=NULL;
        root=NULL;
    }
};

void leftRotate(Tree* T, Node* x){
    Node* y=x->right;

    x->right=y->left;
    if(y->left!=T->nil){
        y->left->p=x;
    }
    
    y->p=x->p;
    if(x->p==T->nil){
        T->root=y;
    }else if(x==x->p->left){
        x->p->left=y;
    }else{
        x->p->right=y;
    }

    y->left=x;
    x->p=y;
}

void rightRotate(Tree* T, Node* x){
    Node* y=x->left;

    x->left=y->right;
    if(y->right!=T->nil)
        y->right->p=x;

    y->p=x->p;
    if(x->p=T->nil){
        T->root=y;
    }else if(x==x->p->left){
        x->p->left=y;
    }else{
        x->p->right=y;
    }

    y->right=x;
    x->p=y;
}

void RBInsertFixup(Tree* T, Node* z){
    while(z->p!=T->nil && z->p->color=='R'){
        if(z->p == z->p->p->left){
            Node* y=z->p->p->right;
            if(y->color=='R'){
                z->p->color='B';
                y->color='B';
                z->p->p->color='R';
                z=z->p->p;
            }else{
                if(z==z->p->right){
                    z=z->p;
                    leftRotate(T, z);
                }
                z->p->color='B';
                z->p->p->color='R';
                rightRotate(T, z->p->p);
            }
        }else{
            Node* y=z->p->p->left;
            if(y->color=='R'){
                z->p->color='B';
                y->color='B';
                z->p->p->color='R';
                z=z->p->p;
            }else{
                if(z==z->p->left){
                z=z->p;
                rightRotate(T, z);
                }
                z->p->color='B';
                z->p->p->color='R';
                leftRotate(T, z->p->p);
            }
        }
    }
    T->root->color='B';
}

void RBInsert(Tree* T, Node* z){
    Node* y=T->nil;
    Node* x=T->root;
    while(x!=T->nil){
        y=x;
        if(z->key<x->key){
            x=x->left;
        }else{
            x=x->right;
        }
    }
    z->p=y;
    if(y==T->nil){
        T->root=z;
    }else if(z->key<y->key){
        y->left=z;
    }else{
        y->right=z;
    }
    z->left=T->nil;
    z->right=T->nil;
    z->color='R';
    RBInsertFixup(T, z);
}

void inorder(Tree* T, Node* root){
    if(root==T->nil){
        return;
    }
    inorder(T, root->left);
    cout<<root->key<<"-"<<root->color<<" ";
    inorder(T, root->right);
}

void preorder(Tree* T, Node* root){
    if(root==T->nil){
        return;
    }
    cout<<root->key<<"-"<<root->color<<" ";
    preorder(T, root->left);
    preorder(T, root->right);
}

void RBTransplant(Tree* T, Node* u, Node* v){
    if(u->p==T->nil){
        T->root=v;
    }else if(u==u->p->left){
        u->p->left=v;
    }else{
        u->p->right=v;
    }
    v->p=u->p;
}

Node* TreeMinimum(Tree* T, Node* root){
    if(root==T->nil || root->left==T->nil)
        return root;
    return TreeMinimum(T, root->left);
}

void RBDeleteFixup(Tree* T, Node* x){
    while(x!=T->root && x->color=='B'){
        if(x==x->p->left){
            Node* w=x->p->right;
            if(w->color=='R'){
                w->color='B';
                x->p->color='R';
                leftRotate(T, x->p);
                w=x->right;
            }
            if(w->left->color=='B' && w->right->color=='B'){
                w->color='R';
                x=x->p;
            }else{
                if(w->right->color=='B'){
                    w->left->color='B';
                    w->color='R';
                    rightRotate(T, w);
                    w=x->p->right;
                }
                w->color=x->p->color;
                x->p->color='B';
                w->right->color='B';
                leftRotate(T, x->p);
                x=T->root;
            }
        }else{
            Node* w=x->p->left;
            if(w->color=='R'){
                w->color='B';
                x->p->color='R';
                rightRotate(T, x->p);
                w=x->left;
            }
            if(w->right->color=='B' && w->left->color=='B'){
                w->color='R';
                x=x->p;
            }else{
                if(w->left->color=='B'){
                    w->right->color='B';
                    w->color='R';
                    leftRotate(T, w);
                    w=x->p->left;
                }
                w->color=x->p->color;
                x->p->color='B';
                w->left->color='B';
                rightRotate(T, x->p);
                x=T->root;
            }
        }
    }
    x->color='B';
}

void RBDelete(Tree* T, Node* z){
    if(z==T->nil)
        return;
    Node* y=z;
    Node* x;
    char y_original_color=y->color;
    if(z->left==T->nil){
        x=z->right;
        RBTransplant(T, z, z->right);
    }else if(z->right==T->nil){
        x=z->left;
        RBTransplant(T, z, z->left);
    }else{
        y=TreeMinimum(T, z->right);
        y_original_color=y->color;
        x=y->right;
        if(y->p==z){
            x->p=y;
        }else{
            RBTransplant(T, y, y->right);
            y->right=z->right;
            y->right->p=y;
        }
        RBTransplant(T, z, y);
        y->left=z->left;
        y->left->p=y;
        y->color=z->color;
    }
    if(y_original_color=='B')
        RBDeleteFixup(T, x);
}

Node* findNode(Tree* T, Node* root, int key){
    if(root==T->nil || root->key==key)
        return root;
    if(key <= root->key){
        return findNode(T, root->left, key);
    }else{
        return findNode(T, root->right, key);
    }
}


int main(){
    Tree* T = new Tree();
    RBInsert(T, new Node(5));
    RBInsert(T, new Node(1));
    RBInsert(T, new Node(14));
    RBInsert(T, new Node(6));
    RBInsert(T, new Node(-6));
    RBInsert(T, new Node(62));
    cout<<"***Illustration***"<<endl;
    cout<<"Inorder Traversal"<<endl;
    inorder(T, T->root);
    cout<<endl;
    cout<<"Preorder Traversal"<<endl;
    preorder(T, T->root);
    // Node* x=findNode(T, T->root, 5);
    // if(x!=T->nil)
    //     RBDelete(T, x);
    // cout<<"***Illustration***"<<endl;
    // cout<<"Inorder Traversal"<<endl;
    // inorder(T, T->root);
    // cout<<endl;
    // cout<<"Preorder Traversal"<<endl;
}