/*
	Symbolic polynomial differentiation
*/

#include <iostream>
#include <string>

using namespace std;

int end(string s, int l){
	if(s[l]!='('){
		while(s[l]!=',') l++;
		return l;
	}
	int n = 1;
	while(n!=0){
		l++;
		if(s[l]=='(') n++;
		else if(s[l]==')') n--;
	}
	return l+1;
}

class Exp{
  public:
	Exp *left;
	Exp *right;
	char op;
	Exp(){
		left = NULL;
		right = NULL;
	}
	Exp(const Exp &exp){
		left = exp.left;
		right = exp.right;
		op = exp.op;
	}

	virtual void print(){
		cout << "(";
		left->print();
		cout << op;
		right->print();
		cout << ")";
	}

	virtual Exp *diff(){
		return NULL;
	}
	virtual int getInt(){
		return 0;
	}
};

Exp *construct(string inp);

class IntExp: public Exp{
  public:	
	int val;
	IntExp(){
		val = 0;
		left = NULL;
		right  = NULL;
	}
	IntExp(const IntExp &x){
		val = x.val;
		left = NULL;
		right  = NULL;
	}
	IntExp(string inp){
		int l = inp.length(), i=0;
		val = 0;
		while(i!=l){
			val = val*10 + inp[i] - '0';
			i++;
		}
		left = NULL;
		right  = NULL;
	}
	Exp *diff(){
		return construct("0");
	}
	void print(){
		cout << val;
	}
	int getInt(){
		return val;
	}
};

class VarExp: public Exp{
  public:	
	char var;
	VarExp(){
		var = '\0';
		left = NULL;
		right  = NULL;
	}
	VarExp(const VarExp &x){
		var = x.var;
		left = NULL;
		right  = NULL;
	}
	VarExp(string inp){
		var = inp[0];
		left = NULL;
		right  = NULL;
	}
	Exp *diff(){
		if(var!='x') return construct("0");
		return construct("1");
	}
	void print(){
		cout << var;
	}
	int getInt(){
		return 0;
	}
};

class AddExp: public Exp{
  public:	
	AddExp(string l, string r){
		op = '+';
		left = construct(l);
		right = construct(r);
	}
	AddExp(Exp *l, Exp *r){
  		op = '+';
  		left = l;
		right = r;
  	}
  	Exp *diff(){
		return new AddExp(left->diff(), right->diff());
	}
	int getInt(){
		return 0;
	}
};

class SubExp: public Exp{
  public:	
	SubExp(string l, string r){
		op = '-';
		left = construct(l);
		right = construct(r);
	}
	SubExp(Exp *l, Exp *r){
  		op = '-';
  		left = l;
		right = r;
  	}
	Exp *diff(){
		return new SubExp(left->diff(), right->diff());
	}
	int getInt(){
		return 0;
	}
};

class ProductExp: public Exp{
  public:
  	ProductExp(string l, string r){
  		op = '*';
  		left = construct(l);
		right = construct(r);
  	}
  	ProductExp(Exp *l, Exp *r){
  		op = '*';
  		left = l;
		right = r;
  	}
  	Exp *diff(){
		Exp *l = new ProductExp(right, left->diff());
		Exp *r = new ProductExp(left, right->diff());
		return new AddExp(l, r);
  	}
  	int getInt(){
		return 0;
	}
};

class DivExp: public Exp{
  public:
  	DivExp(string l, string r){
  		op = '/';
  		left = construct(l);
  		right = construct(r);
  	}
  	DivExp(Exp *l, Exp *r){
  		op = '/';
  		left = l;
		right = r;
  	}
  	Exp *diff(){
  		Exp *ll = new ProductExp(right, left->diff());
  		Exp *lr = new ProductExp(left, right->diff());
  		Exp *l = new SubExp(ll, lr);
  		Exp *r = new ProductExp(right, right);
  		return new DivExp(l, r);
  	}
  	int getInt(){
		return 0;
	}
};

class ExpExp: public Exp{
  public:
  	ExpExp(string l, string r){
  		op = '^';
  		left = construct(l);
  		right = construct(r);
  	}
  	ExpExp(Exp *l, Exp *r){
  		op = '^';
  		left = l;
		right = r;
  	}
  	Exp *diff(){
  		char t1 = right->getInt()+'0', t2 = t1-1;
  		string n,m;
  		n += t1;
  		m += t2;
  		Exp *lr = new ExpExp(left, construct(m));
  		Exp *l = new ProductExp(construct(n), lr);
  		Exp *r = left->diff();
  		return new ProductExp(l, r);
  	}
  	int getInt(){
		return 0;
	}
};

Exp *construct(string inp){
	Exp *ex;
	if(inp[0]=='('){
		int i = 2;
		string l, r;
		int lx = end(inp, 2);
		while(i!=lx){
			l = l + inp[i];
			i++;
		}
		i++;
		int lInp = inp.length();
		while(i!=lInp-1){
			r = r + inp[i];
			i++;
		}
		switch(inp[1]){
			case '+':	if(l=="0") ex = construct(r);
						else if(r=="0") ex = construct(l);
						else ex = new AddExp(l, r);
						break;

			case '-':	if(l=="0") ex = construct(r);
						else if(r=="0") ex = construct(l);
						else ex = new SubExp(l, r);
						break;

			case '*':	if(l=="0" || r=="0") return construct("0");
						else ex = new ProductExp(l, r);
						break;

			case '/':	if(r=="0"){
							cout << "INVALID INPUT\n";
							return NULL;
						}
						else if(l=="0") return construct("0");
						else ex = new DivExp(l, r);
						break;

			case '^':	if(l=="0") ex = construct("0");
						else if(l=="1" || r=="0") ex = construct("1");
						else ex = new ExpExp(l, r);
		}
	}
	else if(inp[0]>='0' && inp[0]<='9') ex = new IntExp(inp);
	else ex = new VarExp(inp);
	return ex;
}

int main(){
	string inp;
	cin >> inp;

	Exp *ex = construct(inp);

	cout << "\nEntered expression is: "; ex->print(); cout << endl;

	cout << "\nDerivative of the expression is: "; (ex->diff())->print(); cout << endl << endl;
}