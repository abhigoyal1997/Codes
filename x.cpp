#include <iostream>

using namespace std;

int** T;

int** mat_pro(int** m1, int** m2){
	int** p;
	p=new int*[2];
	p[0]=new int[2];
	p[1]=new int[2];
	p[0][0]=m1[0][0]*m2[0][0]+m1[0][1]*m2[1][0];
	p[0][1]=m1[0][0]*m2[0][1]+m1[0][1]*m2[1][1];
	p[1][0]=m1[1][0]*m2[0][0]+m1[1][1]*m2[1][0];
	p[1][1]=m1[1][0]*m2[0][1]+m1[1][1]*m2[1][1];
	return p;
}

int** mat_exp(int n){
	if(n==1) return T;
	int** m;
	m = mat_exp(n/2);
	m = mat_pro(m,m);
	if(n%2==0) return m;
	else return mat_pro(m, T);
}

int main(){
	T=new int*[2];
	T[0]=new int[2];
	T[1]=new int[2];
	T[0][0]=1; T[0][1]=1; T[1][0]=1; T[1][1]=0;
	int n;
	while(1){
		cin >> n;
		if(n<0) break;
		if(n==0){
			cout << "0" << endl; continue;
		}
		if(n==1){
			cout << "1" << endl; continue;
		}
		cout << mat_exp(n-1)[0][0] << endl;
	}
}