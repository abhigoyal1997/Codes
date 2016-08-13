#include <iostream>

using namespace std;

class Node{
public:
	string val;
	Node* next;

	Node(){
		next= NULL;
	}
	Node(const Node& n){
		val= n.val;
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

class Stack{
public:
	Node* top;

	Stack(){
		top= NULL;
	}
	~Stack(){
		delete top;
	}

	Node* pop(){
		if(top!=NULL){
			Node* out= top;
			top= top->next;
			return out;
		}
		return NULL;
	}
	void add(Node n){
		if(top==NULL){
			top= new Node(n);
			return;
		}
		Node* in;
		in= new Node(n);
		in->next= top;
		top= in;
	}
	bool isEmpty(){
		if(top==NULL) return 1;
		return 0;
	}
};

class Queue{
public:
	Stack push;
	Stack pop;

	bool isEmpty(){
		if(push.isEmpty() && pop.isEmpty()) return 1;
		return 0;
	}
	Node* dequeue(){
		if(this->isEmpty()) return NULL;
		if(pop.isEmpty()){
			while(!push.isEmpty()) pop.add(*push.pop());
		}
		return pop.pop();
	}
	void enqueue(Node n){
		push.add(n);
	}
};

int main(){
	Queue x;
	while(1){
		int n; cin >> n;
		if(n==-1) break;
		if(n==1){
			string s; cin >> s;
			Node inp(s);
			x.enqueue(inp);
		}
		else{
			if(x.isEmpty()) cout << "EMPTY QUEUE!\n";
			else cout << x.dequeue()->val << endl;
		}
	}
}