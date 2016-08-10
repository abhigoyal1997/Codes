#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int t; cin >> t;
	while(t--){
		int n,m;
		cin >> n >> m;
		int note[n];
		for(int i=0; i!=n; i++){
			cin >> note[i];
		}

		int p=pow(2, n);
		bool b=0;

		while(p--){
			int sum=0;
			int temp=p;

			for(int i=0; i!=n; i++){
				if(temp%2==1) sum += note[i];
				temp/=2;
			}

			if(sum==m){
				b=1; break;
			}
		}

		if(b) cout << "YES\n";
		else cout << "NO\n";
	}
}