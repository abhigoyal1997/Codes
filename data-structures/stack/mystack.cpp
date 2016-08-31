#include "mystack.h"

Stack::Stack(){
	head = NULL;
	size = 0;
}

Stack::~Stack(){
	deleteNode(head);
}

void Stack::deleteNode(node* n){
	if(n != NULL){
		deleteNode(n->next);
		delete n;
	}
}

int Stack::top(){
	if(empty()) return -1;
	return head->data;
}

int Stack::pop(){
	if(empty()) return -1;
	int data = head->data;
	node* temp = head;
	head = head->next;
	size--;
	delete temp;
	return data;
}

void Stack::push(int data){
	node* newHead;
	newHead = new node;

	newHead->data = data;
	newHead->next = head;
	head = newHead;
	size++;
}

bool Stack::empty(){
	if(head == NULL) return 1;
	return 0;
}
