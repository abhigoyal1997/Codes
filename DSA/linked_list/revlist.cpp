#include <iostream>

using namespace std;

struct node{
    int data;
    node* next;
};

void print(node* head){
	if(head == NULL) cout << "null";
	node* element = head;
	while(element != NULL){
		cout << element->data << " ";
		element = element->next;
	}
	cout << endl;
}

node* reverseBatch(node* &i, node* &bi, int m){
	if(i->next == NULL) return NULL;
	bi = i;
	node* t1 = i;
	node* t2 = t1->next;
	node* t3 = t2->next;

	while(m != 1){
		t2->next = t1;
		t1 = t2;
		t2 = t3;
		if(t2 == NULL){
			break;
		}
		t3 = t2->next;
		m--;
	}
	i->next = NULL;
	i = t1;
	return t2;
}

void reverse(node* &head, int m){
	if(m <= 1) return;
	if(head == NULL) return;
	if(head->next == NULL) return;

	node* i = head;
	node* oi = i;
	node* bi = NULL;
	node* ni = reverseBatch(i, bi, m);
	head = i;
	oi->next = ni;
	i = ni;
	while(i != NULL){
		ni = reverseBatch(i, bi, m);
		oi->next = i;
		oi = bi;
		i = ni;
	}
}

void insert(node* &head, int data){
	node* element;
	if(head == NULL){
		head = new node;
		element = head;
	}
	else{
		element = head;
		while(element->next != NULL) element = element->next;
		element->next = new node;
		element = element->next;
	}
	element->data = data;
	element->next = NULL;
}

int main(){
	node* head;

	char in;
	while(true){
		cin >> in;

		switch(in){
			case 'i':	int n; cin >> n;
						while(n--){
							int data; cin >> data;
							insert(head, data);
						}
						break;
			case 'p':	print(head);
						break;
			case 'r':	int m; cin >> m;
						reverse(head, m);
						break;
			case 'q':	return 0;
		}
	}
}