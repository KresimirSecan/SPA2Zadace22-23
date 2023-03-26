#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
	int key;
	Node *left, *right, *parent;
};

class BST
{
	Node *root;
	
	Node* insert(int key, Node *node)
	{
		if (node == NULL) 
		{
			node = new Node;
			node->key = key;
			node->left = node->right = node->parent = NULL;
		} else if (key > node->key) 
		{
			node->right = insert(key, node->right);
			node->right->parent = node;
		} else 
		{
			node->left = insert(key, node->left);
			node->left->parent = node;
		}
		return node;
			
	}

	void inorder(Node *node)
	{
		if (node == NULL)
			return;
		inorder(node->left);
		cout << node->key << ' ';
		inorder(node->right);
	}

	Node* search(int key, Node *node)
	{
		if (node == NULL || key == node->key)
			return node;
		if (key > node->key)
			return search(key, node->right);
		return search(key, node->left);
	}

	Node* find_min(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->left == NULL)
			return node;
		return find_min(node->left);
	}

	Node* find_max(Node *node)
	{
		if (node == NULL)
			return NULL;
		if (node->right == NULL)
			return node;
		return find_min(node->right);
	}

	Node* successor(Node *node)
	{
		if (node->right != NULL)
			return find_min(node->right);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->right) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

	Node* predecessor(Node *node)
	{
		if (node->left != NULL)
			return find_max(node->left);

		Node *parent = node->parent;
		while (parent != NULL && node == parent->left) {
			node = parent;
			parent = node->parent;
		}

		return parent;
	}

public:
	BST() : root(NULL) {}
	
	BST(Node* root) : root(root) {};
    Node* getroot(){
        return root;
    }
    void setroot(Node* a){
        root = a;
    }
	void print()
	{
		inorder(root);
	}

	void insert(int key)
	{
		root = insert(key, root);
	}

	bool search(int key)
	{
		return search(key, root);
	}

	int find_min()
	{
		Node *node = find_min(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int find_max()
	{
		Node *node = find_max(root);
		if (node != NULL)
			return node->key;
		return -1;
	}

	int successor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = successor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}

	int predecessor(int key)
	{
		Node *node = search(key, root);
		if (node == NULL)
			return -1;
		node = predecessor(node);
		if (node == NULL)
			return -1;
		return node->key;
	}
};


//zadatak 1 
bool nodesEqual(Node *node1, Node *node2){
    if(node1 == nullptr && node2 == nullptr){
        return true;
    }
    if(node1 == nullptr || node2 == nullptr){
        return false;
    }
    return nodesEqual(node1->left, node2->left) && nodesEqual(node1->right, node2->right);
}

  


bool structurallyEqual(BST T1, BST T2){
    return(nodesEqual(T1.getroot(),T2.getroot()));
}
//zadatak 2
void nthPower(Node *node, int n){
    for (int  i = 1 ; i<n ; i++){
        node->key *= node->key;
    }
}
void reqpoz(Node* node, int n){
    if (node==nullptr){
        return;
    }
    nthPower(node,n);
    reqpoz(node->right,n);
    reqpoz(node->left,n);
}
BST nthPowerBST(BST T, int n){
    reqpoz (T.getroot(),n);
    return T;
}


//zadatak 3
void Noded(Node *node1, Node *node2){
    if (node1==nullptr|| node2 ==nullptr){
        return ;
    }
    node1->key = node1->key+node2->key;
    Noded(node1->left,node2->left);
    Noded(node1->right,node2->right);
}

//bonus
void inordervec(Node* root, vector<Node*>& arr) {
    if (root == nullptr) return;
    inordervec(root->left, arr);
    arr.push_back(root);
    inordervec(root->right, arr);
}

Node* buildBST(Node** arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    Node* root =  arr[mid];
    root->left = buildBST(arr, start, mid-1);
    root->right = buildBST(arr, mid+1, end);
    return root;
}


BST* mergearr(Node* root1, Node* root2) {
    vector<Node*> arr;
    inordervec(root1, arr);
    inordervec(root2, arr);
    sort(arr.begin(), arr.end(),[](Node* a, Node* b) { return a->key < b->key ; });

	vector<Node*> uniqueArr;
	uniqueArr.push_back(arr[0]);

	for (int i = 1; i < arr.size(); i++) {
   		 if (arr[i]->key != arr[i-1]->key) {
        	uniqueArr.push_back(arr[i]);
   		 }
	}
	arr = uniqueArr;
    Node* root = buildBST(&arr[0], 0, arr.size()-1);
    return new BST(root);
}

//3 zad main part
BST BSTadd(BST T1, BST T2){
	if (structurallyEqual(T1,T2)){
		Noded(T1.getroot(),T2.getroot());
	}else{
		return *mergearr(T1.getroot(),T2.getroot());
	}
    return (T1);
}


int main(){
    
	BST tree1;
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);
    tree1.insert(1);
    tree1.insert(4);
    tree1.insert(9);
	BST tree2;
    tree2.insert(10);
    tree2.insert(5);
    tree2.insert(14);
    tree2.insert(2);
    tree2.insert(8);
    tree2.insert(16);
	BST tree3;
	tree3.insert(8);
	tree3.insert(3);

	//1zad
	cout<<structurallyEqual(tree1,tree2)<<endl;
	cout<<structurallyEqual(tree3,tree2)<<endl;
	cout<<endl;

    //2 zad
    tree1.print();
    tree1 = nthPowerBST(tree1,2);
    cout<<endl;
    tree1.print(); 
	cout<<endl;
	cout<<endl;

    //3 zad
    tree1.print();
	cout<<endl;
    tree2.print();
    cout<<endl;
    BST tree4 = BSTadd(tree1,tree2);
	cout<<"--------------------"<<endl;
	tree4.print();
	cout<<endl<<endl;
	tree2.print();
	cout<<endl;
    tree3.print();
    cout<<endl;
    tree4 = BSTadd(tree2,tree3);
	cout<<"--------------------"<<endl;
	tree4.print();

    return 0;
}

