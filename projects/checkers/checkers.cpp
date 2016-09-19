#include "box.h"

box *b[64];
disk *d[24];

box* getBox(int x, int y){
	int n;
	n=((x-50)/80)+(8*((y-50)/80));
	if(n<=63 && n>=0)	return b[n];
	return NULL;
}

int moveType(int sx, int sy, int dx, int dy, bool player, bool king){
	if(!king){
		if((dx==sx+1 && dx<=7) || (dx==sx-1 && dx>=0)){
			if(player && dy==sy-1 && dy>=0) return 1;
			if(!player && dy==sy+1 && dy<=8) return 1;
		}
		if((dx==sx+2 && dx<=7) || (dx==sx-2 && dx>=0)){
			box *middle;
			middle = b[(sx+dx)/2+8*(sy+dy)/2];
			cout << (sx+dx)/2 << " " << (sy+dy)/2 << " ";
			cout << middle->getX() << " " << middle->getY() << endl;
			if(middle->getDisk() == NULL) return 0;
			if(player && dy==sy-2 && dy>=0)	if(middle->getDisk()->getPlayer()!=player) return 2;
			if(!player && dy==sy+2 && dy<=8) if(middle->getDisk()->getPlayer()!=player) return 2;
		}
		return 0;
	}
	if((dx==sx+1 && dx<=7) || (dx==sx-1 && dx>=0)){
		if((dy==sy-1 && dy>=0) || (dy==sy+1 && dy<=8)) return 1;
	}
	if((dx==sx+2 && dx<=7) || (dx==sx-2 && dx>=0)){
		box *middle;
		middle = b[(sx+dx)/2+8*(sy+dy)/2];
		if((dy==sy-2 && dy>=0) || (dy==sy+2 && dy<=8))	if(middle->getDisk()->getPlayer()!=player) return 2;
	}
	return 0;
}

bool move(box *boxclick, box *boxdest, bool player){
	disk *diskclick = boxclick->getDisk();
	int sx=boxclick->getX(),sy=boxclick->getY(),dx=boxdest->getX(),dy=boxdest->getY();
	int movet = moveType(sx,sy,dx,dy,player,diskclick->isKing());
	if(movet==0) return false;
	diskclick->moveTo(dx,dy);
	boxclick->setDisk(NULL);
	boxdest->setDisk(diskclick);
	if(movet == 2){
		box *middle;
		middle = b[(sx+dx)/2+8*(sy+dy)/2];
		delete middle->getDisk();
		middle->setDisk(NULL);
	}
	diskclick->setState(0);
	return true;
}

int main(){
	initCanvas("Checkers", 900, 700);
	Rectangle sq(90, 90, 80, 80);
	sq.setColor(COLOR("blue"));

	bool color=1;
	for(int j=0; j<8; j++){
		for(int i=0; i<8; i++){
			sq.imprint();
			sq.moveTo(90+80*i, 90+80*j);
			color=!color;
			if(i==0) color=!color;
			sq.setFill(color);
			b[j*8+i] = new box(i,j,1);
		}
	}
	
	for(int j=0; j<6; j++){
		for(int i=0; i<4; i++){
			if(i+j*4<12){
				box *place = getBox(90+160*i+(j*80)%160, 90+80*j);
				d[j*4+i] = new disk(90+160*i+(j*80)%160, 90+80*j, 0);
				place->setDisk(d[j*4+i]);
			}
			else{
				box *place = getBox(90+160*i+((j-2)*80)%160, 80*5+90+80*(j-3));
				d[j*4+i] = new disk(90+160*i+((j-2)*80)%160, 80*5+90+80*(j-3), 1);
				place->setDisk(d[j*4+i]);
			}
		}
	}

	bool player=0;
	while(true){
		int click=getClick();
		int xclick=click/65536, yclick=click%65536;
		box *boxclick;
		boxclick = getBox(xclick,yclick);
		if(boxclick == NULL) continue;

		disk *diskclick = boxclick->getDisk();
		if(diskclick == NULL) continue;
		if(diskclick->getPlayer()!=player) continue;

		diskclick->setState(1);

	cD:	click=getClick();
		xclick=click/65536, yclick=click%65536;
		box *boxdest;
		boxdest = getBox(xclick,yclick);
		if(boxdest == NULL) goto cD;
		if(boxdest == boxclick){
			diskclick->setState(0);
			continue;
		}
		if(boxdest->getDisk()!=NULL) goto cD;

		if(move(boxclick, boxdest, player)) player = !player;
		else goto cD;
	}

	getClick();
}