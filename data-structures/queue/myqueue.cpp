#include "myqueue.h"

using namespace std;

myqueue::myqueue(){
	head = NULL;
	tail = NULL;
	size = 0;
}

myqueue::~myqueue(){
	deleteNode(head);
}

void deleteNode(node* head){
	if(head == NULL) return;
	deleteNode(head->next);
	delete head;
}

bool myqueue::enqueue(int data){
	node* entry;
	entry = new node;
	entry->data = data;
	entry->next = NULL;

	if(head == NULL){
		head = entry;
	}
	else{
		tail->next = entry;
	}
	tail = entry;
	size++;
	return true;
}

int myqueue::dequeue(){
	if(head == NULL) return -1;

	node* element = head;
	head = head->next;
	size--;
	int data = element->data;
	delete element;
	return data;
}

void myqueue::print(){
	if(head == NULL) cout << "null";
	node* element = head;
	while(element != NULL){
		cout << element->data << " ";
		element = element->next;
	}
}

void enqueue(myqueue &queue){
	int n, data;
	cin >> n;

	while(n--){
		cin >> data;
		queue.enqueue(data);
	}
}

void dequeue(myqueue &queue){
	int n;
	cin >> n;

	while(n--){
		queue.dequeue();
	}
}

int main(){
	myqueue queue;

	char in;
	while(true){
		cin >> in;

		switch(in){
			case 'e':	enqueue(queue);
						break;
			case 'p':	queue.print();
						cout << endl;
						break;
			case 'd':	dequeue(queue);
						break;
			case 'q':	return 0;
		}
	}
}