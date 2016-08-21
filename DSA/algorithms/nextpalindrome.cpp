#include<iostream>
#include<cstring>
using namespace std;

string rev(string s, long long a, long long b){
	if(b-a<1)  return s;
	swap(s[a], s[b]);
	return rev(s,a+1,b-1);
}

string nine(long long l){
	if(l==1)  return "1";
	return nine(l-1)+'0';
}

bool isnine(string s, long long l){
	if(l==0)  return 1;
	else if(s[l-1]!='9')  return 0;
	else return isnine(s,l-1);
}

int compare(string a, string b, long long l){
	if(l==0)  return 0;
	int an=a[l-1], bn=b[l-1];
	if(an>bn)  return 1;
	else if(an<bn)  return -1;
	else return compare(a,b,l-1);
}

int main(){
	long long n;
	cin >> n;
	for(long long i=0; i<n; i++){
		string s;
		cin >> s;
		int sn=s.length();
		string a=s.substr(0,sn/2), b=s.substr((sn+1)/2,sn/2);
		string br=rev(b,0,b.length()-1);
		int x=compare(a,br,a.length());
		
		if(sn%2==0){
			if(isnine(s, sn))  cout << nine(sn/2) << '0' << rev(nine(sn/2), 0, sn/2-1) << endl;
			else if(x>0) cout << a << rev(a,0,a.length()-1) << endl;
			else{
				if(a[a.length()-1]!='9'){
					a[a.length()-1]++;
					cout << a << rev(a,0,a.length()-1) << endl;
				}
				else if(a[a.length()-1]=='9' && !isnine(a, a.length())){
					int i;
					for(i=a.length()-1; i>=0 && a[i]=='9'; i--)  a[i]='0';
					a[i]++;
					cout << a << rev(a,0,a.length()-1) << endl;
				}
			}
		}

		else{
			char m=s[sn/2];
			if(isnine(s, sn))  cout << nine(sn/2) << "00" << rev(nine(sn/2), 0, sn/2-1) << endl;
			else if(x>0)  cout << a << m << rev(a,0,a.length()-1) << endl;
			else{
				if(m!='9'){
					m++;
					cout << a << m << rev(a,0,a.length()-1) << endl;
				}
				else if(m=='9' && !isnine(a, a.length())){
					m='0';
					int i;
					for(i=a.length()-1; i>=0 && a[i]=='9'; i--)  a[i]='0';
					a[i]++;
					cout << a << m << rev(a,0,a.length()-1) << endl;
				}
			}
		}
	}
	return 0;
}