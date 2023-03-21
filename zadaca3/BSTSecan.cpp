#include <iostream>
using namespace std;

struct Node{
    int key;
    Node *left, *right, *parent;
};

class BST{
    Node *root;
    
    Node* insert(int key, Node* node){
        if(node == nullptr) {
            node = new Node;
            node->key = key;
            node->left = nullptr;
            node->right = nullptr;
            node->parent = nullptr;
        }
        else if(key < node->key) {
            node->left = insert(key, node->left);
            node->left->parent = node;
        }
        else if(key > node->key) {
            node->right = insert(key, node->right);
            node->right->parent = node;
        }
        
        return node;
    }

    void inorder(Node *node){
        if(node != nullptr){
            inorder(node->left);
            cout<<(node->key)<<" ";
            inorder(node->right);
        }
    }

    Node* search(int key, Node *node){
        if (node==nullptr || key==node->key){
            return node;
        }
        if( key<node->key)
            return(search(key,node->left));
        else
            return(search(key,node->right));
    }

    Node* find_min(Node *node){
        while(node->left!=nullptr){
            node=node->left;
        }
        return node;
    }

    Node* find_max(Node *node){
        while(node->right!=nullptr){
            node=node->right;
        }
        return node;
    }

    Node* successor(Node *node){
        if(node->right != nullptr){
            return(find_min(node->right));
        }
        Node* y = node->parent;
        while(y!=nullptr && node==y->right){
            node=y;
            y=y->parent;
        }
        return y;
    }

    Node* predecessor(Node *node){
        if(node->left != nullptr){
            return(find_max(node->left));
        }
        Node* y = node->parent;
        while(y!=nullptr && node==y->left){
            node=y;
            y=y->parent;
        }
        return y;
    }

    void transplant (Node* u , Node* v){
        if(u->parent==nullptr){
            root = v;
        }else if(u==u->parent->left){
            u->parent->left = v;
        }else{
             u->parent->right = v;
             if (v!= nullptr){
                v->parent = u->parent;
             }
        }
    }

    Node* BSTdelete(int key, Node *node){
        if(node==nullptr) {
            return node;
        }
        
        if(key < node->key) {
            node->left = BSTdelete(key, node->left);
        }
        else if(key > node->key) {
            node->right = BSTdelete(key, node->right);
        }
        else {
            if(node->left == nullptr) {
                Node *temp = node->right;
                if (temp != nullptr) temp->parent = node->parent;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                if (temp != nullptr) temp->parent = node->parent;
                delete node;
                return temp;
            }
            Node *temp = find_min(node->right);
            node->key = temp->key;
            node->right = BSTdelete(temp->key, node->right);
        }
        return node;
        }

public:

    BST() : root(nullptr) {}

    void print(){
        inorder(root);
        cout << endl;
    }

    void insert(int key){
        root = insert(key, root);
    }

    bool search(int key){
        return search(key, root) != nullptr;
    }

   int find_min(){
    Node *node = find_min(root);
    if (node != nullptr) return node->key;
    else return -1;
    }

    int find_max(){
        Node *node = find_max(root);
        if (node != nullptr) return node->key;
        else return -1; 
    }

    int successor(int key){
        Node *node = search(key, root);
        if (node == nullptr) return -1; 
        node = successor(node);
        if (node != nullptr) return node->key;
        else return -1; 
    }

    int predecessor(int key){
        Node *node = search(key, root);
        if (node == nullptr) return -1; 
        node = predecessor(node);
        if (node != nullptr) return node->key;
        else return -1; 
    }

    void BSTdelete(int key){
        root = BSTdelete(key, root);
    }

};

int main(){
    BST tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(8);
    tree.insert(9);
    tree.insert(1);
    tree.insert(11);
    tree.insert(15);
    tree.insert(3);
    tree.print();
    cout << tree.find_min() << endl; 
    cout << tree.find_max() << endl; 
    cout << tree.successor(8) << endl; 
    cout << tree.predecessor(10) << endl; 
    tree.BSTdelete(10);
    tree.print(); 
    return 0;
}

