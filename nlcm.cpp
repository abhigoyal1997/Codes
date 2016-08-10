#include <iostream>

using namespace std;

long long gcd(long long m, int n){
	if(m%n==0) return n;
	return gcd(n, m%n);
}

long long lcm(long long m, int n){
	return (m*n)/gcd(m,n);
}

int main(){
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		long long l=n;
		while(--n){
			l=lcm(l,n);
		}
		cout << l << endl;
	}
}