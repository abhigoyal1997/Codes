#include <iostream>

using namespace std;

void quickSort(int x[], int left, int right){
	cout << " " << left << " " << right << endl;
	if(left>=right) return;
	int pivot = x[right];

	int lo = left, hi = right-1;
	while(1){	
		while(lo<right && x[lo]<=pivot) lo++;
		while(hi>=0 && x[hi]>pivot) hi--;
		if(lo>=hi) break;
		int temp = x[lo];
		x[lo] = x[hi];
		x[hi] = temp;
		cout << lo << " " << hi << endl;
	}
	int temp = x[lo];
	x[lo] = x[right];
	x[right] = temp;

	quickSort(x, left, lo-1);
	quickSort(x, lo+1, right);
}

int main(){
	int n; cin >> n;
	int x[n];
	for(int i=0; i!=n; i++) cin >> x[i];
	quickSort(x, 0, n-1);

	for(int i=0; i!=n; i++) cout << x[i] << " ";
	cout << endl;
}