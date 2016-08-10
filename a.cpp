#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int N=100000;

vector<bool> isprime(N,1);
vector<int> prime(1,2);

long primeExp(long n, long p){
	int s=0, t=p;
	while(n/p!=0){
		s+=n/p;
		p*=t;
	}
	return s;
}

int main(){
	int k=2;
	while(1){
		int i=2*k;
		while(i<N){
			isprime[i]=0; i+=k;
		}
		k++;
		while(!isprime[k]){
			k++;
			if(k==N) break;
		}
		if(k==N) break;
		prime.push_back(k);
	}

	int t; cin >> t;
	while(t--){
		long n,m; cin >> n >> m;
		long long d=1;
		for(long i=0; prime[i]<=n; i++){
			d*=primeExp(n, prime[i])+1;
			d=d%m;
		}
		cout << d%m << endl;
	}
}