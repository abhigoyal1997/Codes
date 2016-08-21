#include "prodcon.h"

using namespace std;

myqueue::myqueue(){
	head = NULL;
	tail = NULL;
	size = 0;
	maxSize = 0;
}

myqueue::~myqueue(){
	deleteNode(head);
}

void deleteNode(node* head){
	if(head == NULL) return;
	deleteNode(head->next);
	delete head;
}

void myqueue::setMaxSize(int m){
	maxSize = m;
}

void myqueue::increaseMaxSize(int m){
	maxSize += m;
}

bool myqueue::enqueue(int data){
	if(size == maxSize) return false;

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
			case 'i':	int m; cin >> m;
						queue.setMaxSize(m);
						break;
			case 'g':	int k; cin >> k;
						queue.increaseMaxSize(k);
						break;
			case 'p':	enqueue(queue);
						break;
			case 'd':	queue.print();
						cout << endl;
						break;
			case 'c':	dequeue(queue);
						break;
			case 'q':	return 0;
		}
	}
}