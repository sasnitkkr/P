#include <bits/stdc++.h>
using namespace std;
 
struct Node {
    int key;
    Node* p;
    Node* child;
    Node* left;
    Node* right;
    int degree;
    bool mark;
    Node(int data){
        key=data;
        p=NULL;
        child=NULL;
        left=NULL;
        right=NULL;
        degree=0;
        mark=false;
    }
};

struct FibHeap{
    Node* min;
    int n;
    FibHeap(){
        min=NULL;
        n=0;
    }
};

// Creating min pointer as "H->min"
// struct Node* H->min = NULL;
 
// Declare an integer for number of nodes in the heap
// int H->n = 0;
 
// Function to insert a Node in heap
void FibHeapInsert(FibHeap* H, Node* x)
{
    
    if(H->min == NULL){
        x->left = x;
        x->right = x;
        H->min=x;
    }else{
        H->min->left->right = x;
        x->right = H->min;
        x->left = H->min->left;
        H->min->left = x;
        if (x->key < H->min->key)
            H->min = x;
    }
    H->n=H->n+1;
}
 
// Function to display the heap
void display(FibHeap* H)
{
    Node* ptr = H->min;
    if (ptr == NULL)
        cout << "The Heap is Empty" << endl;
 
    else {
        cout << "The root nodes of Heap are: " << endl;
        do {
            cout << ptr->key;
            ptr = ptr->right;
            if (ptr != H->min) {
                cout << "-->";
            }
        } while (ptr != H->min && ptr->right != NULL);
        cout << endl
             << "The heap has " << H->n << " nodes" << endl;
    }
}
// Function to find min Node in the heap
void FibHeapFindMin(FibHeap* H)
{
    cout << "min of heap is: " << H->min->key << endl;
}

void Fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
    (ptr2->left)->right = ptr2->right;
    (ptr2->right)->left = ptr2->left;
    if (ptr1->right == ptr1)
        H->Min = ptr1;
    ptr2->left = ptr2;
    ptr2->right = ptr2;
    ptr2->parent = ptr1;
    if (ptr1->child == NULL)
        ptr1->child = ptr2;
    ptr2->right = ptr1->child;
    ptr2->left = (ptr1->child)->left;
    ((ptr1->child)->left)->right = ptr2;
    (ptr1->child)->left = ptr2;
    if (ptr2->key < (ptr1->child)->key)
        ptr1->child = ptr2;
    ptr1->degree++;
}
// Consolidating the heap
void Consolidate()
{
    int temp1;
    float temp2 = (log(no_of_nodes)) / (log(2));
    int temp3 = temp2;
    struct node* arr[temp3+1];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    node* ptr1 = H->Min;
    node* ptr2;
    node* ptr3;
    node* ptr4 = ptr1;
    do {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL) {
            ptr2 = arr[temp1];
            if (ptr1->key > ptr2->key) {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == H->Min)
                H->Min = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                H->Min = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != H->Min);
    H->Min = NULL;
    for (int j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (H->Min != NULL) {
                (H->Min->left)->right = arr[j];
                arr[j]->right = H->Min;
                arr[j]->left = H->Min->left;
                H->Min->left = arr[j];
                if (arr[j]->key < H->Min->key)
                    H->Min = arr[j];
            }
            else {
                H->Min = arr[j];
            }
            if (H->Min == NULL)
                H->Min = arr[j];
            else if (arr[j]->key < H->Min->key)
                H->Min = arr[j];
        }
    }
}
 
// Function to extract minimum node in the heap
void FibHeapExtractMin(H)
{
    z=H->min;
    if(z!=NULL){
        node* temp = H->Min;
        node* pntr;
        pntr = temp;
        node* x = NULL;
        if (temp->child != NULL) {
 
            x = temp->child;
            do {
                pntr = x->right;
                (H->Min->left)->right = x;
                x->right = H->Min;
                x->left = H->Min->left;
                H->Min->left = x;
                if (x->key < H->Min->key)
                    H->Min = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        H->Min = temp->right;
        if (temp == temp->right && temp->child == NULL)
            H->Min = NULL;
        else {
            H->Min = temp->right;
            Consolidate();
        }
        no_of_nodes--;
    }
}
 
// Cutting a node in the heap to be placed in the root list
void Cut(struct node* found, struct node* temp)
{
    if (found == found->right)
        temp->child = NULL;
 
    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;
 
    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (H->Min->left)->right = found;
    found->right = H->Min;
    found->left = H->Min->left;
    H->Min->left = found;
    found->parent = NULL;
    found->mark = 'B';
}
 
// Recursive cascade cutting function
void Cascase_cut(struct node* temp)
{
    node* ptr5 = temp->parent;
    if (ptr5 != NULL) {
        if (temp->mark == 'W') {
            temp->mark = 'B';
        }
        else {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}
 
// Function to decrease the value of a node in the heap
void Decrease_key(struct node* found, int val)
{
    if (H->Min == NULL)
        cout << "The Heap is Empty" << endl;
 
    if (found == NULL)
        cout << "Node not found in the Heap" << endl;
 
    found->key = val;
 
    struct node* temp = found->parent;
    if (temp != NULL && found->key < temp->key) {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < H->Min->key)
        H->Min = found;
}
 
// Function to find the given node
void Find(struct node* H->Min, int old_val, int val)
{
    struct node* found = NULL;
    node* temp5 = H->Min;
    temp5->c = 'Y';
    node* found_ptr = NULL;
    if (temp5->key == old_val) {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == NULL) {
        if (temp5->child != NULL)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}
 
// Deleting a node from the heap
void Deletion(int val)
{
    if (H->Min == NULL)
        cout << "The heap is empty" << endl;
    else {
 
        // Decreasing the value of the node to 0
        Find(H->Min, val, 0);
 
        // Calling Extract_min function to
        // delete minimum value node, which is 0
        Extract_min();
        cout << "Key Deleted" << endl;
    }
}
 
 
 
// Driver code
int main()
{
    FibHeap* H = new FibHeap();
    FibHeapInsert(H, new Node(4));
    FibHeapInsert(H, new Node(3));
    FibHeapInsert(H, new Node(7));
    FibHeapInsert(H, new Node(5));
    FibHeapInsert(H, new Node(2));
    FibHeapInsert(H, new Node(1));
    FibHeapInsert(H, new Node(10));
 
    display(H);
 
    FibHeapFindMin(H);
 
    return 0;
}