#include "mystack.h"
using namespace std;

void updateStack(int i, int in[], int* nextBig, Stack &stack){
	if(stack.empty()){
		stack.push(i);
		return;
	}
	while(in[stack.top()] <= in[i]){
		nextBig[stack.pop()] = i;
		if(stack.empty()) break;
	}
	stack.push(i);
}

void clearStack(Stack &stack, int* nextBig){
	while(!stack.empty()){
		nextBig[stack.pop()] = -1;
	}
}

int main(){
	int n; cin >> n;
	int in[n];
	int nextBig[n];

	Stack stack;

	for(int i=0; i!=n; i++){
		cin >> in[i];
		cout << in[i] << " ";
		updateStack(i, in, nextBig, stack);
	}cout << endl;

	clearStack(stack, nextBig);

	for(int i=0; i!=n; i++){
		if(nextBig[i] == -1) cout << -1 << " ";
		else cout << in[nextBig[i]] << " ";
	}cout << endl;

	for(int i=0; i!=n; i++){
		cout << nextBig[i] << " ";
	}cout << endl;
}