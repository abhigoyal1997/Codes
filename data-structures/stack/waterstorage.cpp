#include "mystack.h"
#include <cmath>
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

void findNextBig(int n, int in[], int nextBig[]){
	Stack stack;
	for(int i=0; i!=n; i++){
		updateStack(i, in, nextBig, stack);
	}
	clearStack(stack, nextBig);
}

int main(){
	int n; cin >> n;
	int in[n];
	int nextBig[n];

	for(int i=0; i!=n; i++){
		cin >> in[i];
		cout << in[i] << " ";
	}cout << endl;

	findNextBig(n, in, nextBig);

	int l=0, r=0, water=0;
	while(l<n-1){
		r = nextBig[l];
		if(r == -1) break;
		
		int h = min(in[l],in[r]);

		for(int i=l+1; i<r; i++) water += h - in[i];
		l = r;
	}

	int in1[n], nextBig1[n];;

	for(int i=0; i!=n; i++){
		in1[n-1-i] = in[i];
	}

	findNextBig(n, in1, nextBig1);

	l=0, r=0;
	while(l<n-1){
		r = nextBig1[l];
		if(r == -1) break;
		
		if(in1[l] == in1[r]){
			// if(nextBig[r] == -1) break;
			l=r;
			continue;
		}
		int h = min(in1[l],in1[r]);

		for(int i=l+1; i<r; i++) water += h - in1[i];
		l = r;
	}
	cout << water << endl;
}