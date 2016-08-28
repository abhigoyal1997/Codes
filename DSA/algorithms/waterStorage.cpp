#include <stdio.h>

using namespace std;

int main(){
	int t; scanf("%d",&t);
	while(t--){
		int n, w=0; scanf("%d",&n);
		int h[n];
		for(int i=0; i!=n; i++) scanf("%d",&h[i]);

		int l=0, r=n-1, m_l=h[l], m_r=h[r];
		while(l<r){
			if(m_l<m_r){
				l++;
				if(h[l]<m_l) w+=(m_l-h[l]);
				else m_l = h[l];
			}
			else{
				r--;
				if(h[r]<m_r) w+=(m_r-h[r]);
				else m_r = h[r];
			}
		}
		printf("%d\n",w);
	}
}