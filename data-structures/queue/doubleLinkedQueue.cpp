#include <stdio.h>
using namespace std;

class queue{
	struct node{
		int val;
		node* next[2];
	};
	node* head;
	node* tail;
	bool dir;
	void deleteNode(node* head){
		if(head == NULL) return;
		deleteNode(head->next[dir]);
		delete head;
	}
public:
	queue(){
		head=NULL;
		tail=NULL;
		dir=0;
	}
	~queue(){
		deleteNode(head);
	}
	
	void back();
	void front();
	void reverse();
	void push_back(int);
	void toFront(int);
};

void queue::back(){
	if(head==NULL){
		printf("No job for Ada?\n");
		return;
	}
	printf("%i\n",tail->val);
	if(head->next[dir] == NULL){
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	tail = tail->next[!dir];
	delete tail->next[dir];
	tail->next[dir] = NULL;
}

void queue::front(){
	if(head==NULL){
		printf("No job for Ada?\n");
		return;
	}
	printf("%i\n",head->val);
	if(head->next[dir] == NULL){
		delete head;
		head = NULL;
		tail = NULL;
		return;
	}
	head = head->next[dir];
	delete head->next[!dir];
	head->next[!dir] = NULL;
}

void queue::reverse(){
	node* temp = head;
	head = tail;
	tail = temp;
	dir = !dir;
}

void queue::push_back(int n){
	node* entry;
	entry = new node;
	entry->val = n;
	if(head == NULL){
		head = entry;
		tail = entry;
		return;
	}
	tail->next[dir] = entry;
	entry->next[dir] = NULL;
	entry->next[!dir] = tail;
	tail = entry;
}

void queue::toFront(int n){
	node* entry;
	entry = new node;
	entry->val = n;
	if(head == NULL){
		head = entry;
		tail = entry;
		return;
	}
	head->next[!dir] = entry;
	entry->next[dir] = head;
	entry->next[!dir] = NULL;
	head = entry;
}

int main(){
	queue q;
	int t; scanf("%i",&t);
	while(t--){
		char in[10]; scanf("%s",in);
		if(in[0]=='b') q.back();
		else if(in[0]=='f') q.front();
		else if(in[0]=='r') q.reverse();
		else if(in[0]=='p'){
			int	n; scanf("%i",&n);
			q.push_back(n);
		}
		else if(in[0]=='t'){
			int	n; scanf("%i",&n);
			q.toFront(n);
		}
	}
}