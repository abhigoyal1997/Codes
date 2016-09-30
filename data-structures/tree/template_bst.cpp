#include "template_bst.h"

template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>::~BST(){
	if(root!=NULL) delete root;
}

template <class T>
void BST<T>::insert(T data){
	insertNode(&root, data);
}

template <class T>
void BST<T>::insertNode(BSTNode** node, T data){
	if(*node == NULL){
            *node = new BSTNode;
            (*node)->data = data;
        }
        else if((*node)->data > data){
            insertNode(&(*node)->left, data);
        }
        else if((*node)->data < data){
            insertNode(&(*node)->right, data);
        }
}

template <class T>
void BST<T>::print() const{
	printTree(root);
	cout << endl;
}

template <class T>
void BST<T>::printTree(BSTNode* node) const{
	if(node == NULL){
		return;
	}

	printTree(node->left);
	cout << node->data << " ";
	printTree(node->right);
}

template <class T>
bool BST<T>::search(T data) const{
	return searchNode(root, data);
}

template <class T>
bool BST<T>::searchNode(BSTNode* node, T data) const{
	if(node == NULL) return false;
	if(node->data == data) return true;
	if(node->data > data) return searchNode(node->left, data);
	if(node->data < data) return searchNode(node->right, data);
}

template <class T>
typename BST<T>::BSTNode* BST<T>::getParent(T data, bool* isRoot){
	if(root->data == data){
		*isRoot = true;
		return NULL;
	}
	BSTNode* parent = NULL;
	BSTNode* node = root;
	while(node->data != data){
		parent = node;
		if(node->data < data) node = node->right;
		else node = node->left;

		if(node == NULL) return NULL;
	}
	return parent;
}

template <class T>
void BST<T>::remove(T data){
	if(root == NULL) return;
	bool isRoot = false;
	BSTNode* parent = getParent(data, &isRoot);
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
	else if(parent->left->data == data) node = parent->left;
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
		T temp = leastBig->data;
		remove(temp);
		node->data = temp;
	}
	if(isRoot) delete parent;
}

template <class T>
void BST<T>::printroot() const{
	if(root == NULL) return;
	cout << root->data << " ";
	if(root->left != NULL) cout << root->left->data << " ";
	if(root->right != NULL) cout << root->right->data << endl;
}

template <class T>
void BST<T>::rebalance(T data){
	rebalanceNode(root, data);
}

template <class T>
bool BST<T>::rebalanceNode(BSTNode* node, T data){
	if(node == NULL) return false;
	if(node->data == data){
		root = node;
	}
	else if(node->data > data){
		if(rebalanceNode(node->left, data)){
			node->left = NULL;
			getMax(root)->right = node;
		}
		else return false;
	}
	else{
		if(rebalanceNode(node->right, data)){
			node->right = NULL;
			getMin(root)->left = node;
		}
		else return false;
	}
	return true;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::getMin(BSTNode* node){
	if(node == NULL) return NULL;
	BSTNode* min = node;
	while(min->left != NULL) min = min->left;
	return min;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::getMax(BSTNode* node){
	if(node == NULL) return NULL;
	BSTNode* max = node;
	while(max->right != NULL) max = max->right;
	return max;
}
template <class T>
void BST<T>::deleteNode(BSTNode* node){
	if(node == NULL) return;
	deleteNode(node->left);
	deleteNode(node->right);
	delete node;
}

template class BST<int>;
template class BST<float>;
template class BST<double>;
template class BST<char>;