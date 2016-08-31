#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	long t; cin >> t;
	while(t--){
		vector<short> n;
		string input; cin >> input;
		bool allNine=1;

		for(int i=0; i!=input.length(); i++){
			n.push_back(input[i]-'0');
			allNine = allNine && (n[i]==9);
		}

		if(allNine){
			cout << 1;
			for(size_t i=1; i!=n.size(); i++) cout << 0;
			cout << 1 << endl;
			continue;
		}

		if(n.size()%2==0){
			int i = n.size()/2-1, j = i+1;
			while(i!=-1){
				if(n[i]==n[j]){
					i--; j++;
				}
				else break;
			}

			if(i==-1 || n[i]<n[j]){
				i = n.size()/2-1; j = i+1;
				n[i]++;
				int car=n[i]/10; n[i]=n[i]%10; n[j]=n[i];
				while(i!=0){
					i--; j++;
					n[i]+=car; car=n[i]/10; n[i]=n[i]%10; n[j]=n[i];
				}
			}
			else while(i!=-1){
					n[j]=n[i];
					i--; j++;
			}
		}
		else{
			int i = (n.size()-1)/2-1, j = i+2;
			while(i!=-1){
				if(n[i]==n[j]){
					i--; j++;
				}
				else break;
			}

			if(i==-1 || n[i]<n[j]){
				i = (n.size()-1)/2-1; j = i+2;
				n[i+1]++;
				int car=n[i+1]/10; n[i+1]=n[i+1]%10;
				while(i!=-1){
					n[i]+=car; car=n[i]/10; n[i]=n[i]%10; n[j]=n[i];
					i--; j++;
				}
			}
			else while(i!=-1){
					n[j]=n[i];
					i--; j++;
			}
		}

		for(size_t i=0; i!=n.size(); i++) cout << n[i];
		cout << endl;
	}
}