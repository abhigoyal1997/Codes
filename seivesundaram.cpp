#include <iostream>
#include <vector>

using namespace std;
const int N=1000000;

vector<bool> isprime(N,1);
vector<int> prime(1,2);

int main(){
	isprime[0]=0;
	for(int i=1; i<N; i++) for(int j=i; i+j+2*i*j<=N; j++) isprime[i+j+2*i*j]=0;
	for(int i=0; i<N; i++) if(isprime[i]) prime.push_back(2*i+1);
	int t; cin >> t;
	while(t--){
		int n; cin >> n;
		cout << prime[n-1] << endl;
	}
}