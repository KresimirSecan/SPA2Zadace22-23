#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	int key;
    int height;
    int size; //zad1
	Node *left, *right, *parent;
};

class AVL
{
private:
    
    Node *root; 

	int height(Node *node)
	{
		if (node == nullptr)
			return 0;
		
        return node->height;
	}

    //zad1
    int size(Node *node)
    {
        if (node == nullptr)
            return 0;
        return node->size;
    }

    Node* rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *temp = x->right;
 
        x->right = y;
        y->left = temp;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        //zad1
        y->size = size(y->left) + size(y->right) + 1; 
        x->size = size(x->left) + size(x->right) + 1;

        if(temp != nullptr)
            temp->parent = y;

        x->parent = y->parent;
        y->parent = x;

        return x;
    }

    Node* leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        //zad1
        x->size = size(x->left) + size(x->right) + 1; 
        y->size = size(y->left) + size(y->right) + 1;

        if(temp != nullptr)
            temp->parent = x;

        y->parent = x->parent;
        x->parent = y;

        return y;
    }

    int balanceOfNode(Node *node)
    {
        if(node == nullptr)
            return 0;
        
        return height(node->left) - height(node->right);
    }

    Node* insert(Node *node, int key)
    {
        if(node == nullptr)
            node = new Node {key, 0,1, nullptr, nullptr, nullptr};
        else if(key < node->key)
        {
            node->left = insert(node->left, key);
            node->left->parent = node;
        }
        else if(key > node->key)
        {
            node->right = insert(node->right, key);
            node->right->parent = node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right); //zad1

        int balance = balanceOfNode(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        
        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    
        return node;
    }

    void inorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        inorder(node->left);
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << ", S: " << node->size << "] ";
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if(node == nullptr)
            return;
        
        cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << ", S: " << node->size << "] ";
        preorder(node->left);
        preorder(node->right);
    }

    //ZAD3
    Node* OS_SELECT(Node *x, int i){ 
        int r=size(x->left)+1;
        if (i ==r) 
            return x;
        else if(i<r)
            return OS_SELECT(x->left, i);
        else   
            return OS_SELECT(x->right, i - r );
    }

    
public:
    AVL() : root(nullptr) {}

	void insert(int key)
	{
        root = insert(root, key);
	}

    void printInorder()
    {
        inorder(root);
    }

    void printPreorder()
    {
        preorder(root);
    }

    //ZAD3
    void OS_SELECT(int i){
        Node* node = OS_SELECT(root, i);
        if(node == nullptr)
            cout << "node error" << endl;
        else
            cout << "[K: " << node->key << ", H: " << node->height << ", B: " << balanceOfNode(node) << ", S: " << node->size << "] ";

    }
    
    //ZAD4
    int OS_RANK(AVL T,Node* x ) {
        int r = size(x->left)+1 +1;
        Node* y  =x;
        while (y!=T.root){
            if(y==y->parent->right)
                r=r+size(y->parent->left)+1;
            y=y->parent;
        }
        return r;
    }
    Node* TREE_SEARCH(Node *node,int key){
		if (node == NULL || key == node->key)
			return node;
		if (key > node->key)
			return TREE_SEARCH(node->right,key);
		return TREE_SEARCH(node->left,key);
	}

    int OS_KEY_RANK(AVL T, int k){
        Node* x= TREE_SEARCH(T.root,k);
        if (x==nullptr){return -1;}
        else {return OS_RANK(T,x);}
    }

    
    //ZAD5
    void ithSuccessor(AVL T,int key, int i){ 
        int r = OS_KEY_RANK(T,key);
        OS_SELECT(i-1+r);
    }
    


};

int main(){
    AVL t1 ;
    t1.insert(29);
    t1.insert(6);
    t1.insert(56);
    t1.insert(3);
    t1.insert (7);
    t1.insert(37);
    t1.insert(61);
    t1.insert(4);
    t1.insert(22);
    t1.insert(48);
    t1.insert(59);
    t1.insert(69);

    //ZAD3
    t1.OS_SELECT(8); 
    cout<<endl;

    //ZAD4  
    cout<<t1.OS_KEY_RANK(t1,48)<<endl; 

    //ZAD5
    t1.ithSuccessor(t1,56,3); 


    return 0;


}