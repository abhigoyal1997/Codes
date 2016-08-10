#include<iostream>

using namespace std;

long int hanoi(int n){
	if(n==1) return 2;
	return 3*hanoi(n-1)+2;
}

int main(){
	int t;
	cin >> t;
	int n;
	for(int i=0; i<t; i++){
		cin >> n;
		cout << hanoi(n);
	}
}
