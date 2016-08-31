#include "qUsingStack.h"

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

int Stack::bottom(){
	if(empty()) return -1;
	node* n = head;
	while(n->next != NULL) n = n->next;
	return n->data;
}

int Stack::getSize(){
	return size;
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
	if(head == NULL) return true;
	return false;
}

int Queue::front(){
	if(pop.empty()){
		while(!push.empty()) pop.push(push.pop());
	}
	return pop.top();
}

int Queue::back(){
	if(push.empty()){
		return pop.bottom();
	}
	return push.top();
}

int Queue::getSize(){
	return push.getSize() + pop.getSize();
}

int Queue::pop(){
	if(pop.empty()){
		while(!push.empty()) pop.push(push.pop());
	}
	return pop.pop();
}

void Queue::push(int data){
	push.push(data);
}

bool Queue::empty(){
	if(getSize == 0) return true;
	return false;
}