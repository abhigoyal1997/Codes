#include<iostream>

using namespace std;

int imax(int x[], int n){
	int j=0, k=0;
	for(int i=0; i<n; i++){
		if(x[i]<x[j]) j=i;
	}
	return j;
}

int main(){
	int an, bn;
	while(1){	
		cin >> an >> bn;
		if(an==0 && bn==0) break;
		int a[an], b[bn];
		bool s=0;
		for(int i=0; i<an; i++){
			cin >> a[i];
		}
		for(int i=0; i<bn; i++){
			cin >> b[i];
		}
		int c=b[imax(b,bn)];
		b[imax(b, bn)]=100000;
		for(int i=0; i<an; i++)
			if(a[i]<b[imax(b,bn)] || (a[i]==b[imax(b,bn)] && c!=a[i])){
				s=1; break;
			}
		
		if(s) cout << 'Y' << endl;
		else cout << 'N' << endl;
	}
}