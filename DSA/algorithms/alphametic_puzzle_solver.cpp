#include <iostream>
#include <map>
#include <string>
using namespace std;

map<char, int> f;// map from character to integer(a digit from 0 to 9)
string s;// string to traverse the characters
bool asg[10];// to keep account of which digits have been already mapped
int count=0, xl;

void dasg(int n){
	asg[f[s[n]]]=0;
	f[s[n]]=-1;
}

void carry(int n, int &car, int &dig){
	int temp;
	if(s[n-1]=='#') temp = (f[s[n-2]]+car);
	else if(s[n-2]=='#') temp = (f[s[n-1]]+car);
	else temp = (f[s[n-1]]+f[s[n-2]]+car);
	car=temp/10;
	dig=temp%10;
}

bool check(int n, int g, int car){// to check if the digit assigned to a character of the result string if valid
	int dig;
	carry(n, car, dig);
	if((car==1 && n==s.length()-1) || (car==0 && n==s.length()-2)) return 0;
	if(g==dig) return 1;
	return 0;
}

void print(){// to print the map of charaters
	count++;
	map<char, int>::iterator i=f.begin();
	if(i->first=='#') i++;
	for(i; i!=f.end(); i++){
		cout << i->first << " = " << i->second << endl;
	}
	cout << endl;
}

bool solve(int n, int car){// to solve for the map
	bool solexists=0;// keeps track if atleast one solution exists
	if(n==0) car=0;// to initialize the car variable with carry
	if(f[s[n]]!=-1 || s[n]=='#'){// if s[n] is already assigned a digit
		int t=3*xl-3;
		if(n%3==2){// if s[n] is a character of the result string(this is the case in which an additional check for the validity is required)
			if(n>=t && s.length()==t+3 && f[s[n]]==0) return 0;
			if(!check(n, f[s[n]], car)) return 0;
			if(n>=s.length()-2){// if condition is true then n is at it's maximum and since the check returned true, current map is a valid solution
				print();
				return 1;
			}
			int dig;
			carry(n, car, dig);
		}
		if(n>=t && f[s[n]]==0) return 0;
		if(solve(n+1, car)) return 1;// reccursive call to the solve function to solve for the remaining problem and if solution exists return 1
		return 0;// since solve returned false, solution doesn't current map can't form a valid solution
	}
	// s[n] is not already assigned a digit
	if(n%3==2){// if s[n] is a character of the result string
		int dig;
		carry(n, car, dig);
		if((car==1 && n==s.length()-1) || (car==0 && n==s.length()-2) || (asg[dig])) return 0;
		f[s[n]]=dig;
		asg[f[s[n]]]=1;
		if(n>=s.length()-2){// if condition is true then n is at it's maximum and since the check returned true, current map is a valid solution
			print();
			dasg(n);
			return 1;
		}
		
		if(solve(n+1, car)){// reccursive call to the solve function to solve for the remaining problem and if solution exists return 1
			dasg(n);
			return 1;
		}
		dasg(n);
		return 0;// none of above conditions come out to be true means the current map can't form a valid solution
	}
	// s[n] is not already assigned and also is not a character of the result string
	int i=0, t=s.length()-4;
	if(n>=t) i=1;// ensures the validity in case s[n] is is first character of x or y string(coz first character of x or y can't be assigned to 0)
	for(i; i<10; i++){
		while(asg[i]){
			i++;
			if(i==10) return solexists;
		}
		f[s[n]]=i;
		asg[i]=1;
		if(solve(n+1, car)) solexists=1;
		dasg(n);
	}
	return solexists;// return 1 if atleast 1 solution exists
}

int main(){
	string x, y, r;
	cin >> x >> y >> r;
	int i=1, yl=y.length(), rl=r.length(); xl=x.length();

	if(yl>xl){
		string ts=x; x=y; y=ts;
		int tl=xl; xl=yl; yl=tl;
	}
	if(xl>yl){ 
		if(rl!=xl && rl!=xl+1) goto end;
		for(int i=0; i!=(xl-yl); i++) y = "#" + y;
	}

	while(i!=xl+1){// to initialize the string s
		s=s+x[xl-i]+y[xl-i]+r[rl-i];
		f[x[xl-i]]=f[y[xl-i]]=f[r[rl-i]]=-1;
		i++;
	}
	if(rl==xl+1) s=s+r[0];
	for(int i=0; i!=10; i++) asg[i]=0;// to initialize the asg array

	if((s.length()-1)==3*xl){// if no. of characters in result string is no. of char in other strings +1 then the first char of result is always assigned to 1
		f[s[s.length()-1]]=1;
		asg[1]=1;
	}

	solve(0, 0);
  end:	cout << "No. of solutions = " << count << endl;
}