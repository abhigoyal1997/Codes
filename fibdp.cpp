#include <iostream>
#include <map>

using namespace std;

map<int, int> fib;
int i=0;

int fibonacci(int n){
	i++;
	if(fib[n]!=0 || n==0) return fib[n];

	fib[n] = fibonacci(n-1) + fibonacci(n-2);
	return fib[n];
}

int main(){
	int n;
	do{
		i=0;
		fib[0]=0; fib[1]=1;
		cin >> n;
		cout << fibonacci(n) << endl;
		cout << i << endl;
	}while(n!=-1);
}