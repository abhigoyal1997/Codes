#include <iostream>

using namespace std;

class Node{
public:
	char val;
	Node* next;

	Node(){
		next= NULL;
	}
	Node(char s){
		val= s;
		next= NULL;
	}
	Node(char s, Node* n){
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

	char pop(){
		if(top!=NULL){
			Node* temp= top;
			top= top->next;
			return temp->val;
		}
		return '\0';
	}

	void add(char s){
		if(top==NULL){
			top= new Node(s);
			return;
		}
		Node* temp;
		temp= new Node(s);
		temp->next= top;
		top= temp;
		return;
	}
};

bool isPair(char x, char y){
	if(x=='[' && y==']') return 1;
	if(x=='{' && y=='}') return 1;
	if(x=='(' && y==')') return 1;
	return 0;
}

int main(){
	Stack x;
	string input; cin >> input;
	for(int i=0; input[i]!='\0'; i++){
		if(input[i]=='[' || input[i]=='(' || input[i]=='{') x.add(input[i]);
		else{
			char temp = x.pop();
			if(!isPair(temp, input[i])){
				cout << "INVALID!\n";
				return 0;
			}
		}
	}
	if(x.top!=NULL){
		cout << "INVALID!\n";
	}
	else cout << "VALID!\n";
}