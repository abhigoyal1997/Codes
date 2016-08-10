#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
const long long N=86028122;

bitset<N> isprime;
vector<long long> prime(1,2);

int main(){
	isprime.flip();
	isprime[1]=0;
	long long p=2;
	while(1){
		long long i=2*p;
		while(i<N){
			isprime[i]=0; i+=p;
		}
		p++;
		while(p!=N && !isprime[p]){
			p++;
			if(p==N) break;
		}
		if(p==N) break;
		prime.push_back(p);
	}

	int t; cin >> t;
	while(t--){
		long long n; cin >> n;
		cout << prime[n-1] << endl;
	}
}