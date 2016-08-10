#include <iostream>
#include <cmath>

using namespace std;

int gcd(int m, int n){
	if(m%n==0) return n;
	return gcd(n, m%n);
}

int main(){
	int n, m; cin >> n >> m;
	int g=gcd(m,n);

	int sq=sqrt(g);

	int d=1;
	int temp=0;
	while(sq%2==0){
		temp++; sq/=2;
	}
	d*=temp+1;

	for(int i=3; i<sq; i+=2){
		
	}
}