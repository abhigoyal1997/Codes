#include"check.h"

int player=1;

int boxn(int x, int y){
	int n;
	n=(((x-50)/80)+1)+(8*((y-50)/80));
	if(n<=64 && n>=1)	return n;
	return 0;
}

void boxco(int n, int &x, int &y){
	x=90+80*((n-1)%8);	y=90+80*((n-1)/8);
	return;
}

int diskn(int n, disk d[]){
	int x=0, y=0;
	boxco(n,x,y);
	for(int i=0; i<24; i++)
		if(x==d[i].x && y==d[i].y)	return i;
	return 25;
}

void click(Circle c, disk d){
	c.setColor(COLOR("red"));
	c.setFill(1);
	return;
}