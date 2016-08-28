#include <iostream>
#include <vector>
#include <map>

using namespace std;
const int N=20000;

vector<bool> isprime(N,1);
vector<int> prime(1,2);
map<int, int> p;

void pfactor(int n){
	for(int i=0; prime[i]<=n; i++) while(n%prime[i]==0){
		p[prime[i]]++; n/=prime[i];
	}
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

	int n; cin >> n;
	for(int i=2; i!=n+1; i++) pfactor(i);

	for(map<int,int>::iterator i=p.begin(); i!=p.end();i++){
			if(i!=p.begin()) cout << " * ";
			cout << i->first << "^" << i->second;
	}
}