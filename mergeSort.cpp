#include <iostream>

using namespace std;

void sort(int x[], int l, int h){
	if(l==h) return;

	int m=(l+h)/2;
	sort(x, l, m);
	sort(x, m+1, h);

	int n=h-l+1;
	int temp[n];
	for(int i=0; i!=n; i++) temp[i] = x[l+i];

	int i=0, j=(n-1)/2+1, k=l;
	for(k=l; k!=h+1 & i!=(n-1)/2+1 & j!=n; k++){
		if(temp[i]<=temp[j]){
			x[k]=temp[i]; i++;
		}
		else{
			x[k]=temp[j]; j++;
		}
	}

	while(i!=(n-1)/2+1){
		x[k]=temp[i]; i++; k++;
	}
	while(j!=n){
		x[k]=temp[j]; j++; k++;
	}
	return;
}

int main(){
	int n; cin >> n;
	int x[n];
	
	for(int i=0; i!=n; i++) cin >> x[i];

	sort(x, 0, n-1);

	for(int i=0; i!=n; i++) cout << x[i] << " ";
	cout << endl;
}