#include <stdio.h>

using namespace std;

const long long MOD = 1000000007;

long long** T;

long long** mat_pro(long long** m1, long long** m2){
	long long** p;
	p=new long long*[2];
	p[0]=new long long[2];
	p[1]=new long long[2];
	p[0][0]=(m1[0][0]%MOD)*(m2[0][0]%MOD)+(m1[0][1]%MOD)*(m2[1][0]%MOD);
	p[0][1]=(m1[0][0]%MOD)*(m2[0][1]%MOD)+(m1[0][1]%MOD)*(m2[1][1]%MOD);
	p[1][0]=(m1[1][0]%MOD)*(m2[0][0]%MOD)+(m1[1][1]%MOD)*(m2[1][0]%MOD);
	p[1][1]=(m1[1][0]%MOD)*(m2[0][1]%MOD)+(m1[1][1]%MOD)*(m2[1][1]%MOD);
	return p;
}

long long** mat_exp(long long n){
	if(n==1) return T;
	long long** m;
	m = mat_exp(n/2);
	m = mat_pro(m,m);
	if(n%2==0) return m;
	else return mat_pro(m, T);
}

int main(){
	T=new long long*[2];
	T[0]=new long long[2];
	T[1]=new long long[2];
	T[0][0]=1; T[0][1]=1; T[1][0]=1; T[1][1]=0;
	long long n;
	while(1){
		scanf("%lli",&n);
		if(n<0) break;
		if(n==0){
			printf("0\n"); continue;
		}
		if(n==1){
			printf("1\n"); continue;
		}
		printf("%lli\n",mat_exp(n-1)[0][0]);
	}
}