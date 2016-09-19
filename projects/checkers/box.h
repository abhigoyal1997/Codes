#include <simplecpp>
#include "disk.h"

class box{
	int x,y;
	bool blue;
	disk *piece;
public:
	box(){};
	box(int x,int y,bool b){
		this->x = x;
		this->y = y;
		blue = b;
		piece = NULL;
	}
	~box(){
		delete piece;
	};

	int getX(){
		return x;
	}
	int getY(){
		return y;
	}
	disk* getDisk(){
		return piece;
	}
	void setDisk(disk *d){
		this->piece = d;
	}
	bool getColor(){
		return blue;
	}
};