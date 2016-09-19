#include <simplecpp>

class disk{
	int x,y;
	bool player;
	Circle *king;
	Circle *shape;
public:
	disk(){};
	disk(int x, int y, bool player){
		this->x = x;
		this->y = y;
		this->player = player;
		this->king = NULL;
		this->shape = new Circle(x,y,30);
		if(!player) this->shape->setColor(COLOR("orange"));
		else this->shape->setColor(COLOR("black"));
		this->shape->setFill(1);
	}
	~disk(){
		delete shape;
		if(king!=NULL)delete king;
	};
	
	bool getPlayer(){
		return player;
	}
	bool isKing(){
		return !(king==NULL);
	}
	void setState(bool red){
		if(red) this->shape->setColor(COLOR("red"));
		else if(!player) this->shape->setColor(COLOR("orange"));
		else this->shape->setColor(COLOR("black"));
	}
	void moveTo(int x, int y){
		shape->moveTo(90+80*x, 90+80*y);
		this->x = 90+80*x;
		this->y = 90+80*y;
		if(this->isKing()){
			king->moveTo(90+80*x, 90+80*y);
		}
		if((player && y==0) || (!player && y==7)){
			if(this->isKing()) return;
			king = new Circle(this->x, this->y, 10);
			king->setColor(COLOR("green"));
			king->setFill(1);
		} 
	}
};


// int boxn(int x,int y);
// int diskn(int n, disk d[]);
// void click(Circle c, disk d);
