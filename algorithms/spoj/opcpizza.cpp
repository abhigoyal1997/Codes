#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
	int t; scanf("%i",&t);
	while(t--){
		int n,m; scanf("%i%i",&n,&m);
		int in[n];
		for(int i=0; i!=n; i++) scanf("%i",&in[i]);
		sort(in,in+n);
		int pair=0;
		int i=0, j=n-1;
		while(j-i>0){
			int s=in[i]+in[j];
			if(s>m) j--;
			else if(s<m) i++;
			else{
				i++;
				j--;
				pair++;
			}
		}
		printf("%i\n",pair);
	}
}