#include "bst.h"

BST::BST(){
	root = NULL;
}

BST::~BST(){
	deleteNode(root);
}

void BST::insert(int n){
	insertNode(root, n);
}

void BST::insertNode(BSTNode*& node, int n){
    if(node == NULL){
        node = new BSTNode;
        node->data = n;
        node->size = 1;
    }
    else if(node->data > n){
        insertNode(node->left, n);
        node->size++;
    }
    else if(node->data < n){
        insertNode(node->right, n);
        node->size++;
    }
}

void BST::print() const{
	if(root == NULL) return;
	printTree(root);
	cout << endl;
}

void BST::printTree(BSTNode* node) const{
	if(node == NULL){
		return;
	}

	printTree(node->left);
	cout << node->data << " ";
	printTree(node->right);
}

bool BST::search(int n) const{
	return searchNode(root, n);
}

bool BST::searchNode(BSTNode* node, int n) const{
	if(node == NULL) return false;
	if(node->data == n) return true;
	if(node->data > n) return searchNode(node->left, n);
	if(node->data < n) return searchNode(node->right, n);
}

BST::BSTNode* BST::getParent(int n, bool* isRoot){
	if(root->data == n){
		*isRoot = true;
		return NULL;
	}
	BSTNode* parent = NULL;
	BSTNode* node = root;
	while(node->data != n){
		parent = node;
		if(node->data < n) node = node->right;
		else node = node->left;

		if(node == NULL) return NULL;
	}
	return parent;
}

void BST::remove(int n){
	if(root == NULL) return;
	bool isRoot = false;
	BSTNode* parent = getParent(n, &isRoot);
	if(isRoot){
		parent = new BSTNode;
		parent->right = root;
	}
	if(parent == NULL) return;

	BSTNode* node;
	bool left = true;
	if(parent->left == NULL){
		node = parent->right;
		left = false;
	}
	else if(parent->right == NULL) node = parent->left;
	else if(parent->left->data == n) node = parent->left;
	else{
		node = parent->right;
		left = false;
	}

	if(node->right == NULL){
		if(isRoot){
			root = node->left;
		}
		if(left) parent->left = node->left;
		else parent->right = node->left;
		delete node;
	}
	else if(node->left == NULL){
		if(isRoot){
			root = node->right;
		}
		if(left) parent->left = node->right;
		else parent->right = node->right;
		delete node;
	}
	else{
		BSTNode* leastBig = node->right;
		while(leastBig->left != NULL) leastBig = leastBig->left;
		int temp = leastBig->data;
		remove(temp);
		node->data = temp;
	}
	if(isRoot) delete parent;
}

void BST::printroot() const{
	if(root == NULL) return;
	cout << root->data << " ";
	if(root->left != NULL) cout << root->left->data << " ";
	if(root->right != NULL) cout << root->right->data;
	cout << endl;
}

void BST::rebalance(int n){
	rebalanceNode(root, n);
}

bool BST::rebalanceNode(BSTNode* node, int n){
	if(node == NULL) return false;
	if(node->data == n){
		root = node;
	}
	else if(node->data > n){
		if(rebalanceNode(node->left, n)){
			node->left = NULL;
			getMax(root)->right = node;
		}
		else return false;
	}
	else{
		if(rebalanceNode(node->right, n)){
			node->right = NULL;
			getMin(root)->left = node;
		}
		else return false;
	}
	return true;
}

BST::BSTNode* BST::getMin(BSTNode* node){
	if(node == NULL) return NULL;
	BSTNode* min = node;
	while(min->left != NULL) min = min->left;
	return min;
}

BST::BSTNode* BST::getMax(BSTNode* node){
	if(node == NULL) return NULL;
	BSTNode* max = node;
	while(max->right != NULL) max = max->right;
	return max;
}

void BST::deleteNode(BSTNode* node){
	if(node == NULL) return;
	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
}