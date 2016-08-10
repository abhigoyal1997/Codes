#include<simplecpp>

int clickbox(long c){
	int x=c/65536, y=c%65536, n;
	n=(((x-50)/80)+1)+(8*((y-50)/80));
	if(n<=64 && n>=1)	return n;
	return 0;
}

void boxco(int n, int &x, int &y){
	x=90+80*((n-1)%8);	y=90+80*((n-1)/8);
	return;
}

int isfilled(int n, Circle c1[], Circle c2[]){
	int x=0, y=0;
	boxco(n, x, y);
	for(int i=0; i<12; i++){
		if(c1[i].getX()==x && c1[i].getY()==y)	return i;
		else if(c2[i].getX()==x && c2[i].getY()==y)	return 12+i;
	}
	return 25;
}

void move(int d, Circle &c){
	int x=0, y=0;
	boxco(d, x, y);
	c.moveTo(x, y);
	return;
}

bool cutvalid(int player, int s, int d, Circle c1[], Circle c2[]){
	if(player==1 && d!=s+14 && d!=s+18) return 0;
	if(player==2 && d!=s-14 && d!=s-18) return 0;
	if(isfilled(d, c1, c2)!=25) return 0;
	int c=(s+d)/2;
	int cbox=isfilled(c, c1, c2);
	int playerc=(cbox)/12+1;
	if(player*playerc==2)		return 1;
	else return 0;
}

bool cutpossible(int player, int s, Circle c1[], Circle c2[]){
	if(player==1){
		if(cutvalid(player, s, s+14, c1, c2)) return 1;
		if(cutvalid(player, s, s+18, c1, c2)) return 1;
	}
	if(player==2){
		if(cutvalid(player, s, s-14, c1, c2)) return 1;
		if(cutvalid(player, s, s-18, c1, c2)) return 1;
	}
	return 0;
}

void cutmove(int player, int s, Circle c1[], Circle c2[]){
	int d=clickbox(getClick());
	int dbox=isfilled(d, c1, c2);
	int sbox=isfilled(s, c1, c2);
	int cbox=isfilled((s+d)/2, c1, c2);
	if(dbox!=25) cutmove(player, s, c1, c2);
	if(cutvalid(player, s, d, c1, c2) && player==1){
		move(d, c1[sbox]);
		c2[cbox-12].moveTo(2000, 2000);
		if(cutpossible(player, d, c1, c2))	cutmove(player, d, c1, c1);
	}
	if(cutvalid(player, s, d, c1, c2) && player==2){
		move(d, c2[sbox-12]);
		c1[cbox].moveTo(2000, 2000);
		if(cutpossible(player, d, c1, c2))	cutmove(player, d, c1, c1);
	}
	return;
}

main_program{
	initCanvas("checkers", 700, 700);
	Rectangle box(90, 90, 80, 80);
	box.setColor(COLOR("blue"));
	
	bool color=1;
	for(int j=0; j<8; j++){
		for(int i=0; i<8; i++){
			box.imprint();
			box.moveTo(90+80*i, 90+80*j);
			color=!color;
			if(i==0)	color=!color;
			box.setFill(color);
		}
	}

	Circle c1[12];

	for(int j=0; j<3; j++){
		for(int i=0; i<4; i++){
			c1[i+j*4].reset(90+160*i+(j*80)%160, 90+80*j, 30);
			c1[i+j*4].setColor(COLOR("orange"));
			c1[i+j*4].setFill(1);
		}
	}

	Circle c2[12];
	
	for(int j=0; j<3; j++){
		for(int i=0; i<4; i++){
			c2[i+j*4].reset(90+160*i+((j+1)*80)%160, 80*5+90+80*j, 30);
			c2[i+j*4].setColor(COLOR("black"));
			c2[i+j*4].setFill(1);
		}
	}

	int player=1;
	while(true){
		cout << player << endl;
		int s=clickbox(getClick());
		int sbox=isfilled(s, c1, c2);
		if(sbox==25) continue;
		
		if(player==1 && sbox<12)	c1[sbox].setColor(COLOR("red"));
		if(player==2 && sbox>=12)	c2[sbox-12].setColor(COLOR("red"));
		if(cutpossible(player, s, c1, c2)){
			cutmove(player, s, c1, c2);
			player=player%2+1;
			continue;
		}
		
		int d=clickbox(getClick());	
		int dbox=isfilled(d, c1, c2);
		if(dbox!=25) continue;
		if(sbox<12 && (d==s+7 || d==s+9) && player==1) move(d, c1[sbox]);
		else if(sbox>=12 && (d==s-7 || d==s-9) && player==2)	move(d, c2[sbox-12]);
		else continue;
		if(player==1 && sbox<12)	c1[sbox].setColor(COLOR("orange"));
		if(player==2 && sbox>=12)	c2[sbox-12].setColor(COLOR("black"));
		player=player%2+1;
		
	}
	getClick();
}