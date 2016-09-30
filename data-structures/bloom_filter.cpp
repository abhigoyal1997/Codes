#include <stdio.h>
#include <vector>
#include <functional>
#include <unordered_map>
using namespace std;

class bloom_filter{
	vector<bool> data;
	int nhash;
	int size;

	struct myhash{  
		// hash for object x, i th hash function, m-sized bit array of filter
		std::size_t operator()(int const& x, int const& i, int const& m) const{  
		// note: this is important and represents the ith hash function
			std::size_t h = std::hash<int>{}(x+i);
			return h%m;                            // note: h should be between 0 and m-1 
		}
	};

	myhash xhash;
public:
	bloom_filter(){
		nhash = 0;
		size = 0;
	}
	bloom_filter(const int &n, const int &k){
		data.assign(n,0);
		nhash = k;
		size = n;
	}
	~bloom_filter(){
		nhash = 0;
		size = 0;
		data.clear();
	}

	void create(const int &n, const int &k){
		data.assign(n,0);
		nhash = k;
		size = n;
	}
	void insert(int x){
		for(int i=0; i!=nhash; i++){
			data[xhash(x,i,size)] = 1;
		}
	}
	void remove(int x){
		for(int i=0; i!=nhash; i++){
			data[xhash(x,i,size)] = 0;
		}
	}
	bool lookup(int x){
		for(int i=0; i!=nhash; i++){
			if(!data[xhash(x,i,size)]) return 0;
		}
		return 1;
	}
};

int main(){
	int t; scanf("%i",&t);
w:	while(t--){
		int n,k; scanf("%i%i",&n,&k);
		bloom_filter mybloom(n,k);
		unordered_map<int,bool> storedata;
		int ins=0, del=0;
		int falsepos=0, falseneg=0;
		char in;
		while(1){
			scanf("%c",&in);
			int num,nv,look;
			switch(in){
				case 'i':	scanf("%i",&nv);
						while(nv--){
							scanf("%i",&num);
							mybloom.insert(num);
							storedata[num]=1;
							ins++;
						}
						break;
				case 'd':	scanf("%i",&nv);
						while(nv--){
							scanf("%i",&num);
							mybloom.remove(num);
							storedata.erase(num);
							del++;
						}
						break;
				case 'l':	scanf("%i",&num);
						look = mybloom.lookup(num);
						printf("l %i %i\n", num,look);
						if(look==1 && storedata.find(num)==storedata.end()) falsepos++;
						else if(look==0 && storedata.find(num)!=storedata.end()) falseneg++;
						break;
				case 'r':	printf("r %i %i %i %i\n",falsepos,falseneg,ins,del);
						break;
				case 'e':	goto w;
			}
		}
	}
}