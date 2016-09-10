#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class BigNum{
public:
	vector<short> val;
 	BigNum(){}
 	~BigNum(){
 		val.clear();
 	}
 	BigNum(const BigNum& num){
 		for(size_t i=0; i!=num.val.size(); i++){
 			val.push_back(num.val[i]);
 		}
 	}
 	BigNum(string num){
 		for(size_t i=0; i!=num.length(); i++){
 			val.push_back(num[num.length()-i-1]-'0');
 		}
 	}

 	void operator=(const BigNum& num){
 		val.clear();
 		for(size_t i=0; i!=num.val.size(); i++){
 			val.push_back(num.val[i]);
 		}
 	}
 	bool operator<=(BigNum num){
 		if(num.val.size()<val.size()) return false;
 		if(num.val.size()>val.size()) return true;

 		size_t i=val.size();
 		while(i--){
 			if(num.val[i]<val[i]) return false;
 			if(num.val[i]>val[i]) return true;
 		}
 		return true;
 	}
 	BigNum operator+(BigNum num){
 		BigNum res;
 		short sum=0,car=0;
 		vector<short>::iterator i=val.begin();
 		vector<short>::iterator j=(num.val).begin();
 		while(true){
 			if(i==val.end() && j==num.val.end()){
 				if(car==0) return res;
 				res.val.push_back(car);
 				return res;
 			}
 			if(i==val.end()){
 				while(j!=num.val.end()){
 					sum=*j+car;
 					res.val.push_back(sum%10);
 					car=sum/10;
 					j++;
 				}
 			}
 			else if(j==num.val.end()){
 				while(i!=val.end()){
 					sum=*i+car;
 					res.val.push_back(sum%10);
 					car=sum/10;
 					i++;
 				}
 			}
 			else{
 				sum=*j+*i+car;
				res.val.push_back(sum%10);
				car=sum/10;
				i++; j++;
 			}
 		}
 	}
 	BigNum operator-(BigNum num){
 		BigNum res;
 		short diff=0,car=0;
 		vector<short>::iterator i=val.begin();
 		vector<short>::iterator j=(num.val).begin();
 		while(true){
 			if(i==val.end() && j==num.val.end()){
 				if(car==0) break;;
 				res.val[res.val.size()-1]-=car;
 				break;
 			}
 			if(j==num.val.end()){
 				while(i!=val.end()){
 					diff=*i-car;
 					if(diff<0){
 						diff+=10;
 						car=1;
 					}
 					else car=0;
 					res.val.push_back(diff);
 					i++;
 				}
 			}
 			else{
 				diff=*i-*j-car;
				if(diff<0){
					diff+=10;
					car=1;
				}
				else car=0;
				res.val.push_back(diff);
				i++; j++;
 			}
 		}
 		if(res.val.back()==0){
 			res.val.pop_back();
 		}
 		return res;
 	}
 	BigNum operator*(int num){
 		BigNum res;
 		short pro=1,car=0;
 		vector<short>::iterator i=val.begin();
 		while(true){
 			if(i==val.end()){
 				while(car!=0){
 					res.val.push_back(car%10);
 					car/=10;
 				}
 				return res;
 			}
			pro=num*(*i)+car;
			res.val.push_back(pro%10);
			car=pro/10;
			i++;
 		}
 	}
 	int operator/(BigNum num){
 		int q=0;
 		BigNum d(num);
 		BigNum n(*this);

 		while(d<=n){
 			q++;
 			d=d+num;
 		}
 		return q;
 	}

 	void print(){
 		for(size_t i=val.size()-1; i!=-1; i--) printf("%hi",val[i]);
 	}
};

int main(){
	string x,y;
	cin >> x >> y;

	BigNum a(x);
	BigNum b(y);

	bool q = a<=b;
	cout << q << endl;

	(a+b).print(); printf("\n");

	a=b;
	a.print(); printf("\n");
}