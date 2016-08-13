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
			Node* temp= top;
			top= top->next;
			return temp;
		}
		return NULL;
	}

	void add(Node* s){
		if(top==NULL){
			top= s;
			return;
		}
		Node* temp;
		temp= s;
		temp->next= top;
		top= temp;
		return;
	}
	bool empty(){
		if(top==NULL) return 1;
		return 0;
	}
};

class Queue{
public:
	Stack push;
	Stack pop;

	void enqueue(Node* s){
		push.add(s);
	}
	Node* dequeue(){
		if(!pop.empty()) return pop.pop();
		while(!push.empty()){
			pop.add(push.pop());
		}
		if(!pop.empty()) return pop.pop();
		return NULL;
	}
	bool empty(){
		if(pop.empty() && push.empty()) return true;
		return false;
	}
};

int main(){
	Queue x;
	while(true){
		int n; cin >> n;
		if(n==-1) break;
		if(n==1){
			string input; cin >> input;
			Node* inp;
			inp= new Node(input);
			x.enqueue(inp);
		}
		else{
			Node* out;
			out= x.dequeue();
			if(out==NULL) cout << "EMPTY QUEUE!\n";
			else cout << out->val << endl;
		}
	}
}