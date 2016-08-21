#include <iostream>
#include <map>

using namespace std;

char win[1000001];
long k, l, m;

int main(){
	cin >> k >> l >> m;
	if(k>l){
		int t = l;
		l = k; k = t;
	}
	win[0] = 'B';
	win[k] = 'A';
	win[l] = 'A';
	while(m--){
		long n; cin >> n;
		for(long i=1; i!=n+1; i++){
			if(win[i]!='\0') continue;
			if(i-k<0 && win[i-1]=='A') win[i] = 'B';
			else if(i-l<0 && win[i-1]=='A' && win[i-k]=='A1') win[i] = 'B';
			else if(win[i-1]=='A' && win[i-l]=='A' && win[i-k]=='A') win[i] = 'B';
			else win[i] = 'A';
		}
		cout << win[n];
	}
}