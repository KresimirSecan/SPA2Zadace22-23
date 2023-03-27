#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node{
    int key;
    int h;
    Node *left, *right, *parent;
};

int height(Node *node){
    if (node == NULL)
        return -1;
    return node->h;
}

Node* rightRotate(Node *y){
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent != NULL) {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    y->h = max(height(y->left), height(y->right)) + 1;
    x->h = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node *x){
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent != NULL) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    x->h = max(height(x->left), height(x->right)) + 1;
    y->h = max(height(y->left), height(y->right)) + 1;
    return y;
}

int balanceOfNode(Node *node){
    if (node == NULL)
        return 0;
    return  height(node->left) - height(node->right);
}

Node* insert(Node *node, int key){

    if (node == NULL){
    node = new Node();
    node->key = key;
    node->h = 0;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    }

    else if (key < node->key){
    node->left = insert(node->left, key);
    node->left->parent = node;
    }

    else if (key > node->key){
    node->right = insert(node->right, key);
    node->right->parent = node;
    }
    
    node->h = max(height(node->left), height(node->right)) + 1;
    int balance = balanceOfNode(node);

    if (balance > 1 && key < node->left->key)
    return rightRotate(node);

    if (balance < -1 && key > node->right->key)
    return leftRotate(node);

    if (balance > 1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key){
    node->right = rightRotate(node->right);
    return leftRotate(node);
    }

    return node;
}


void inorder(Node *node){
    if (node == NULL)
		return;
	inorder(node->left);
	cout << node->key << ' ';
	inorder(node->right);
}

int main(){
    Node *root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++)
    root = insert(root, keys[i]);
    inorder(root);
    return 0;
}