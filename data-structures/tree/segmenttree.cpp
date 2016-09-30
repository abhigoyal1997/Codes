#include <stdio.h>
using namespace std;

class segmenttree{
	struct node{
		node* left;
		node* right;
		int minVal, l, r;
	};

	int size;
	int* x;
	node* root;

	int min(int a, int b){
		if(a<b) return a;
		return b;
	}
	void buildNode(node* &root,int l, int r){
		root=new node;
		root->l=l;
		root->r=r;
		if(l==r) root->minVal=x[l];
		else{
			int m=(l+r)/2;
			buildNode(root->left,l,m);
			buildNode(root->right,m+1,r);
			root->minVal=min(root->left->minVal, root->right->minVal);
		}
	}
	int getMin(node* root, int l, int r){
		if(l>r) return 0;
		if(l==r) return x[l];
		if(root->l==l && root->r==r) return root->minVal;
		int rm=(root->l+root->r)/2;
		if(l<=rm && r<=rm) return getMin(root->left,l,r);
		if(l>rm && r>rm) return getMin(root->right,l,r);
		return min(getMin(root->left,l,rm),getMin(root->right,rm+1,r));
	}
	void updateNode(node* root, int i){
		if(root==NULL) return;
		if(i==root->l && i==root->r){
			root->minVal=x[i];
			return;
		}
		int rm=(root->l+root->r)/2;
		if(i<=rm) updateNode(root->left,i);
		else if(i>rm) updateNode(root->right,i);
		root->minVal=min(root->left->minVal, root->right->minVal);
	}
	void removeNode(node* &root){
		if(root==NULL) return;
		removeNode(root->left);
		removeNode(root->right);
		delete root;
	}

public:
	segmenttree(){
		size=0;
		x=NULL;
		root=NULL;
	}
	segmenttree(int* arr, int n){
		size=n;
		x=new int[size];
		for(int i=0; i!=n; i++) x[i]=arr[i];
		buildNode(this->root,0,n-1);
	}
	~segmenttree(){
		removeNode(this->root);
	}

	int query(int l, int r){
		return getMin(this->root,l,r);
	}
	void update(int i, int v){
		x[i]=v;
		updateNode(this->root,i);
	}
};

int main(){
	int n,q; scanf("%i%i",&n,&q);
	int arr[n];
	for(int i=0; i!=n; i++) scanf("%i",arr+i);

	segmenttree tree(arr,n);

	int query;
	while(q--){
		scanf("%i",&query);
		if(query==1){
			int l,r; scanf("%i%i",&l,&r);
			printf("%i\n",tree.query(l,r));
		}
		else if(query==2){
			int i,v; scanf("%i%i",&i,&v);
			arr[i]=v;
			tree.update(i,v);
		}
	}
}