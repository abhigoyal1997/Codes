#include"check.h"

main_program{
	initCanvas("Checkers", 900, 700);
	Rectangle sq(90, 90, 80, 80);
	sq.setColor(COLOR("blue"));
	
	bool color=1;
	for(int j=0; j<8; j++){
		for(int i=0; i<8; i++){
			sq.imprint();
			sq.moveTo(90+80*i, 90+80*j);
			color=!color;
			if(i==0)	color=!color;
			sq.setFill(color);
		}
	}
	
	disk d[24];

	Circle c[24];
	for(int j=0; j<6; j++){
		for(int i=0; i<4; i++){
			if(i+j*4<12){
				c[i+j*4].reset(90+160*i+(j*80)%160, 90+80*j, 30);
				c[i+j*4].setColor(COLOR("orange"));
				c[i+j*4].setFill(1);
				d[i+j*4].p=1;
			}
			else{
				c[i+j*4].reset(90+160*i+((j-2)*80)%160, 80*5+90+80*(j-3), 30);
				c[i+j*4].setColor(COLOR("black"));
				c[i+j*4].setFill(1);
				d[i+j*4].p=2;
			}
		}
	}

	for(int i=0; i<24; i++){
		d[i].x=c[i].getX();
		d[i].y=c[i].getY();
	}

	int g=getClick();
	int x=g/65536, y=g%65536;
	int s=boxn(x,y);
	int dn=diskn(s, d);
	click(c[dn],d[dn]);

	getClick();
}