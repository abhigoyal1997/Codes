#include <iostream>

using namespace std;

class Node{
public:
	string val;
	Node* next;

	Node(){
		next= NULL;
	}
	Node(string s){
		val= s;
		next= NULL;
	}
	Node(string s, Node* n){
		val= s;
		next= n;
	}
	~Node(){
		delete next;
	}
};

class Queue{
public:
	Node* first;
	Node* last;

	Queue(){
		first= last= NULL;
	}
	~Queue(){
		delete first;
		delete last;
	}

	void dequeue(){
		if(first!=NULL){
			Node* temp= first;
			first= first->next;
			return temp;
		}
		return NULL;
	}
	void enqueue(Node* s){
		if(first==NULL){
			first= last= s;
			return;
		}
		last->next= s;
		last= last->next;
		return;
	}
};