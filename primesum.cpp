#include <iostream>
#include <vector>

using namespace std;
const int N=10000;

vector<bool> isprime(N,1);
vector<int> prime(1,2);

int main(){
	int p=2;
	while(1){
		int i=2*p;
		while(i<N){
			isprime[i]=0; i+=p;
		}
		p++;
		while(!isprime[p]){
			p++;
			if(p==N) break;
		}
		if(p==N) break;
		prime.push_back(p);
	}

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		long sum=0;
		for(size_t i=0; i!=prime.size(); i++){
			if(prime[i]>n) break;
			sum+=prime[i];
		}
		cout << sum << endl;
	}
}