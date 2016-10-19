#include <stdio.h>
#include <set>
#include <stack>
#include <vector>
using namespace std;

class Graph{
	int size;
	set<int>* vertex;
	stack<int> order;
	int* scc;

	void dfsNode(int n, bool v[], int sccn){
		v[n] = 1;
		scc[n] = sccn;
		for(set<int>::iterator it = vertex[n].begin(); it!=vertex[n].end(); it++)
			if(!v[*it]) dfsNode(*it,v,sccn);
	}

	void finishOrder(int n, bool v[]){
		v[n] = 1;
		for(set<int>::iterator it = vertex[n].begin(); it!=vertex[n].end(); it++)
			if(!v[*it]) finishOrder(*it,v);
		order.push(n);
	}
public:
	Graph(){
		size = 0;
		vertex = NULL;
		scc = NULL;
	}
	Graph(int n){
		size = n;
		vertex = new set<int>[n];
		scc = new int[n];
	}
	~Graph(){
		delete[] vertex;
		delete[] scc;
	}
	
	void addEdge(int a, int b){
		vertex[a].insert(b);
	}

	Graph getTranspose(){
		Graph gt(size);
		for(int i=0; i!=size; i++)
			for(set<int>::iterator it = vertex[i].begin(); it!=vertex[i].end(); it++)
				gt.addEdge(*it,i);
		return gt;
	}

	void getSCC(){
		bool v[size];
		for(int i=0; i!=size; i++) v[i] = 0;
		for(int i=0; i!=size; i++)
			if(!v[i]) finishOrder(i,v);
		
		Graph gt = getTranspose();

		for(int i=0; i!=size; i++) v[i] = 0;
		
		int sccn=0;
		while(!order.empty()){
			int n = order.top();
			order.pop();
			if(!v[n]){
				gt.dfsNode(n,v,sccn);
				sccn++;
			}
		}
		for(int i=0; i!=size; i++) scc[i]=gt.scc[i];
	}

	bool isSC(int a,int b){
		return scc[a]==scc[b];
	}
};

int main(){
	int n,m; scanf("%i%i",&n,&m);
	Graph g(n);
	int a,b;
	for(int i=0; i!=m; i++){
		scanf("%i%i",&a,&b);
		g.addEdge(a-1,b-1);
	}

	g.getSCC();

	int q; scanf("%i",&q);
w:	while(q--){
		scanf("%i%i",&a,&b);
		printf("%d\n",g.isSC(a-1,b-1));
	}
}