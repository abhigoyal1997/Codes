#include <iostream>

using namespace std;

void sort(int* x, int n){
	for(int j=1; j!=n; j++){
		int key= x[j];		
		int i= j-1;
		while(i!=-1 && x[i]>key){
			x[i+1]= x[i];
			i--;
		}
		x[i+1]= key;
	}
}

int main(){
	int* x;
	int n; cin >> n;
	x= new int[n];
	for(int i=0; i!=n; i++) cin >> x[i];

	sort(x, n);
	for(int i=0; i!=n; i++) cout << x[i] << " ";
	cout << endl;
}