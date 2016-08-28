#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;
const int N=1000000;

vector<bool> isprime(N,1);
vector<int> prime(1,2);

map<int,int> pfactor(int n){
	map<int,int> p;
	for(int i=0; prime[i]<=n; i++) while(n%prime[i]==0){
		p[prime[i]]++; n/=prime[i];
	}
	return p;
}

int ndiv(map<int,int> p){
	int d=1;
	for(map<int,int>::iterator i=p.begin(); i!=p.end(); i++) d*=((i->second)+1);
	return d;
}

int main(){
	system("clear");
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

	while(1){
		int n; 
		cout << "Enter a positive integer: ";
		cin >> n;
		if(n<=0){
			cout << "Please enter a positive integer only." << endl;
			continue;
		}
		map<int,int> p=pfactor(n);
		cout << "Prime Factorisation: ";
		for(map<int,int>::iterator i=p.begin(); i!=p.end();i++){
			int j=i->second;
			while(j--) cout << i->first << " ";
		}
		cout << endl;
		cout << "Total no. of factors on n are: " << ndiv(p) << endl;
		cout << "Do u want to continue?(enter y if yes)\n";
		char ch; cin >> ch;
		if(ch!='y' && ch!='Y') break;
	}
}
