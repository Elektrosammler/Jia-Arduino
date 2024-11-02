#include "CImg.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cmath>
unsigned char*** getobjectarray() {
	unsigned char*** objectarray = (unsigned char***)malloc(64 * sizeof(unsigned char**));
	for (int i = 0; i < 64; i++) {
		objectarray[i] = nullptr;
	}
	return objectarray;
}
unsigned char**  gethuman1() {
	unsigned char** human = (unsigned char**)malloc(sizeof(unsigned char*) * 9);
	human[0] = (unsigned char*)malloc(sizeof(unsigned char) * 6);
	human[0][0] = 0; human[0][1] = 5; human[0][2] = 6; human[0][3] = 3; human[0][4] = 5; human[0][5] = 255;
	human[1] = (unsigned char*)malloc(sizeof(unsigned char) * 9);
	human[1][0] = 1; human[1][1] = 5; human[1][2] = 6; human[1][3] = 1; human[1][4] = 1; human[1][5] = 1; human[1][6] = 4; human[1][7] = 2; human[1][8] = 255;
	human[2] = (unsigned char*)malloc(sizeof(unsigned char) * 12);
	human[2][0] = 0; human[2][1] = 4; human[2][2] = 1; human[2][3] = 1; human[2][4] = 4; human[2][5] = 1; human[2][6] = 2; human[2][7] = 3; human[2][8] = 1; human[2][9] = 1; human[2][10] = 2; human[2][11] = 255;
	human[3] = (unsigned char*)malloc(sizeof(unsigned char) * 11);
	human[3][0] = 1; human[3][1] = 5; human[3][2] = 5; human[3][3] = 1; human[3][4] = 1; human[3][5] = 1; human[3][6] = 1; human[3][7] = 1; human[3][8] = 2; human[3][9] = 3; human[3][10] = 255;
	human[4] = (unsigned char*)malloc(sizeof(unsigned char) * 8);
	human[4][0] = 0; human[4][1] = 5; human[4][2] = 5; human[4][3] = 3; human[4][4] = 4; human[4][5] = 1; human[4][6] = 2; human[4][7] = 255;
	human[5] = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	human[5][0] = 0; human[5][1] = 18; human[5][2] = 2; human[5][3] = 255;
	human[6] = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	human[6][0] = 0; human[6][1] = 18; human[6][2] = 2; human[6][3] = 255;
	human[7] = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	human[7][0] = 0; human[7][1] = 18; human[7][2] = 2; human[7][3] = 255;
	human[8] = nullptr;
	return human;
}
unsigned char**  getground() {
	unsigned char** ground = (unsigned char**)malloc(129 * sizeof(unsigned char*));
	for (int i = 0; i < 128; i++) {
		ground[i] = (unsigned char*)malloc(3 * sizeof(unsigned char));
		ground[i][0] = 1;
		ground[i][1] = 8;
		ground[i][2] = 255;
	}
	ground[128] = nullptr;
	return ground;
}
unsigned char**  getbox(unsigned char widht, unsigned char hight) {
	unsigned char** box = (unsigned char**)malloc(sizeof(unsigned char*)*(widht+1));
	for (int i = 0; i < widht; i++) {
		box[i] = (unsigned char*)malloc(sizeof(unsigned char*) * 3);
		box[i][0] = 1;
		box[i][1] = hight;
		box[i][2] = 255;
	}
	box[widht] = nullptr;
	return box;
}
unsigned char**  getcords()      {
	unsigned char** cords = (unsigned char**)malloc(64 * sizeof(unsigned char*));
	for (int i = 0; i < 64; i++) {
		cords[i] = (unsigned char*)malloc(2 * sizeof(unsigned char));
	}
	for (int i = 0; i < 64; i++) {
		cords[i][0] = 255;
		cords[i][0] = 255;//-32768;
	}
	return cords;
} 
unsigned char**  gethitboxes() {
	unsigned char** hitbox = (unsigned char**)malloc(64 * sizeof(unsigned char*));
	for (int i = 0; i < 64; i++) {
		hitbox[i] = (unsigned char*)malloc(4 * sizeof(unsigned char));
		hitbox[i][0] = 255;
		hitbox[i][1] = 255;
		hitbox[i][2] = 255;
		hitbox[i][3] = 255;
	}
	
	return hitbox;
}
unsigned char*   getobjectprops() {
	unsigned char* objectprops = (unsigned char*)malloc(64 * sizeof(unsigned char));
	for (int i = 0; i < 64; i++) {
		objectprops[i] = 255;
	}
	return objectprops;
}
cimg_library::CImg <unsigned char> clear(cimg_library::CImg <unsigned char> bg) {
	unsigned char white[] = { 254,254,254 };
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 64; j++) {

			bg.draw_point(i, j, white);
		}
	}
	return bg;
}
cimg_library::CImg <unsigned char> draw(unsigned char** object, int x, int y, cimg_library::CImg <unsigned char> bg) {
	const unsigned char zero[] = { 255,255,255 };
	const unsigned char one[] = { 0,0,0 };
	int j;
	bool value;
	int posy = y;
	int posx = x;
	int inti;
	for (int i = 0; object[i] != nullptr; i++) {
		if (object[i][0] == 0) {
			value = 0;
		}
		else {
			value = 1;
		}
		j = 1;
		posy = y;

		while (object[i][j] != 255) {
			inti = object[i][j];
			if (value == 0) {
				posy = posy + inti;

			}
			else {
				for (int k = 0; k < inti; k++) {
					bg.draw_point(127 - posx, 63 - posy, one);
					posy++;
				}
			}
			if (value == 1) {
				value = 0;
			}
			else {
				value = 1;
			}
			j++;
		}
		posx = posx + 1;
	}
	return bg;
}
cimg_library::CImg <unsigned char> drawall(unsigned char*** objectarray, unsigned char** cords, cimg_library::CImg <unsigned char> bg) {
	bg = clear(bg);
	short objectarraylenght = 0;
	while (objectarray[objectarraylenght] != nullptr) {
		objectarraylenght++;
	}
	for (int i = 0; i < objectarraylenght; i++) {
		bg = draw(objectarray[i], cords[i][0], cords[i][1], bg);
	}
	//bg.display();
	return bg;
}
void addobjectarray(unsigned char*** objectarray, unsigned char** toadd, short curentpos) {
	objectarray[curentpos] = toadd;
}
void addcords(unsigned char** cords, short curentpos, unsigned char x, unsigned char y) {
	cords[curentpos][0] = x;
	cords[curentpos][1] = y;
}
void addhitboxes(unsigned char** hitboxes, short curentpos, unsigned char pwidht, unsigned char widht, unsigned char phight, unsigned char hight) {
	hitboxes[curentpos][0] = pwidht;
	hitboxes[curentpos][1] = widht;
	hitboxes[curentpos][2] = phight;
	hitboxes[curentpos][3] = hight;
}
void addall(short curentpos, unsigned char*** objectarray, unsigned char** toadd, unsigned char** cords, unsigned char x, unsigned char y, unsigned char** hitboxes, unsigned char pwidht, unsigned char widht , unsigned char phight, unsigned char hight, unsigned char* objectprops, unsigned char props) {
	addobjectarray(objectarray, toadd, curentpos);
	addcords(cords, curentpos, x, y);
	addhitboxes(hitboxes, curentpos,pwidht, widht,phight, hight);
	objectprops[curentpos] = props;
}
void movecords(unsigned char** cords, int x, int y, short von, short bis) {
	short cordslenght = 0;
	while ((cords[cordslenght][0] != 255) && (cordslenght < 64)&& (cordslenght < bis)) {
		cordslenght++;
	}
	for (int i = von; i < cordslenght; i++) {
		cords[i][0] = cords[i][0] - x;
		cords[i][1] = cords[i][1] + y;
	}
}
bool checkmove(unsigned char** cords, unsigned char** hitboxes,unsigned char pos, int x, int y) {
	int lenght = 1;
	unsigned char check = 0;
	bool colision = 0;
	while (cords[lenght][0] != 255) {
		lenght++;
	}
	for (int i = 1; (i < lenght) && (check != 2); i++) {
		check = 0;
		for (int j = hitboxes[pos][0]; (j < hitboxes[pos][1] + hitboxes[pos][0]) && (colision == 0); j++) {
			if ((cords[pos][0] - x + j >= cords[i][0]) && (cords[pos][0] - x + j <= cords[i][0] + (hitboxes[i][1] - 1))) {
				colision = 1;
			}
		}
		if (colision == 1) {
			check++;
			colision = 0;
		}
		for (int j = hitboxes[pos][2]; (j < hitboxes[pos][3]+ hitboxes[pos][2]) && (colision == 0); j++) {
			if ((cords[pos][1] + y + j >= cords[i][1]) && (cords[pos][1] + y + j <= cords[i][1] + (hitboxes[i][3] - 1))) {
				colision = 1;
			}
		}
		if (colision == 1) {
			check++;
			colision = 0;
		}
	}
	if (check != 2) {
		return 0;
	}
	return 1;
}
void moveplayer(unsigned char** cords,char* velocity, unsigned char** hitboxes, int x, int y) {
	bool check = 0;
	velocity[1]++;
	//printf("velocity[0]: %d\nvelocity[1]:%d\n", velocity[0], velocity[1]);
	if (velocity[0] - velocity[1] > 0) {
		if (checkmove(cords, hitboxes, 0, 0, 1) == 0) {
			movecords(cords, 0, 1, 0, 1);
		}
	}
	else {
		if (checkmove(cords, hitboxes, 0, 0, -1) == 1) {
			velocity[0] = 0;
			velocity[1] = 0;
		}
		else {
			movecords(cords, 0,-1,0,1);
		}
	}
	if (checkmove(cords,hitboxes,0,x,y) == 0) {
		movecords(cords, x, y, 0, 1);
	}
}
void fliphuman(unsigned char** human, unsigned char**hitboxes,unsigned char** cords, bool direction){
	unsigned char lenght = 0;
	while (human[lenght] != nullptr) {
		lenght++;
	}
	for (int i = 0; i < lenght/2; i++) {
		human[lenght] = human[i];
		human[i] = human[lenght-i-1];
		human[lenght - i-1] = human[lenght];
	}
	human[lenght] = nullptr;
	if (direction == 1) {
		hitboxes[0][0] = 0;
		cords[0][0] = cords[0][0] + 2;
	}
	else {
		hitboxes[0][0] = 3;
		cords[0][0] = cords[0][0] - 2;
	}
}
void freemost(unsigned char pos, unsigned char*** objectarray, unsigned char** cords, unsigned char** hitboxes) {
	free(hitboxes[pos]);
	free(cords[pos]);
	for (int i = 0; objectarray[i] != nullptr; i++) {
		free(objectarray[pos][i]);
	}
	free(objectarray[pos]);
}
void freeall(unsigned char*** objectarray, unsigned char** cords, unsigned char** hitboxes, unsigned char* objectpops) {
	unsigned char lenght = 0;
	while (objectpops[lenght] != 255) {
		lenght++;
	}
	for (int i = 0; i < lenght; i++) {
		freemost(i, objectarray, cords, hitboxes);
	}
	free(objectarray);
	free(cords);
	free(hitboxes);
	free(objectpops);

}
void rremove(unsigned char pos, unsigned char*** objectarray, unsigned char** cords, unsigned char** hitboxes, unsigned char* objectpops) {
	unsigned char lenght = 0;
	unsigned char* ptrtmp;
	while (objectarray[lenght] != nullptr) {
		lenght++;
	}
	for (int i = 0; objectarray[i] != nullptr; i++) {
		free(objectarray[pos][i]);
	}
	objectarray[pos] = objectarray[lenght - 1];
	objectarray[lenght - 1] = nullptr;
	ptrtmp = cords[pos];
	cords[pos] = cords[lenght - 1];
	cords[lenght - 1] = ptrtmp;
	cords[lenght - 1][0] = 255;
	cords[lenght - 1][1] = 255;
	ptrtmp = hitboxes[pos];
	hitboxes[pos] = hitboxes[lenght - 1];
	hitboxes[lenght - 1] = ptrtmp;
	hitboxes[lenght - 1][0] = 255;
	hitboxes[lenght - 1][1] = 255;
	hitboxes[lenght - 1][2] = 255;
	hitboxes[lenght - 1][3] = 255;
	objectpops[pos] = objectpops[lenght - 1];
	objectpops[lenght - 1] = 255;
}
int main() {
	cimg_library::CImg <unsigned char> bg(128, 64, 1, 3, 0);
	bool direction = 0;
	unsigned char*** objectarray = getobjectarray();
	unsigned char**  cords = getcords();
	unsigned char**  hitboxes = gethitboxes();
	unsigned char*   objectprops = getobjectprops();
	char velocity[] = {0,0};
	char x = 0;
	char y = 0;
	addall(0,objectarray, gethuman1(),cords,16,16,hitboxes,0,5,0,20, objectprops,0);
	addall(1, objectarray, getbox(8,8), cords, 48, 48, hitboxes, 0, 8, 0, 8, objectprops, 1);
	addall(2,objectarray,getground(),cords,0,0,hitboxes,0,128,0,8,objectprops,2);
	addall(3,objectarray,getbox(10,4),cords,100,12,hitboxes,0,10,0,4,objectprops,1);
	bg = drawall(objectarray, cords, bg);
	cimg_library::CImgDisplay dsp(128 * 8, 64 * 8, "1", 0);
	dsp.display(bg);
	while (!dsp.is_closed()) {
		x = 0;
		y = 0;
		char storechar = 'b';
		storechar = _getch();
		if (storechar == 'a') {
			if (direction == 1) {
				fliphuman(objectarray[0],hitboxes,cords,direction);
				direction = 0;
			}
			x = -1;
		}
		else if (storechar == 'd') {
			if (direction == 0) {
				fliphuman(objectarray[0],hitboxes ,cords, direction);
				direction = 1;
			}
			x = 1;
		}
		/*else if (storechar == 'w') {
			y = 1;
		}
		else if (storechar == 's') {
			y = -1;
		}*/
		else if (storechar == ' ') {
			if (checkmove(cords,hitboxes,0,0,-1) == 1) {
				velocity[0] = 10;
				velocity[1] = 0;
			}
		}
		else if (storechar == 'r') {
			rremove(1,objectarray,cords,hitboxes,objectprops);
		}
		else if (storechar == 'e') {
			freeall(objectarray,cords,hitboxes,objectprops);
			return 0;
		}
		moveplayer(cords, velocity, hitboxes, x, y);
		
		bg = drawall(objectarray, cords, bg);
		dsp.display(bg);
	}
	return 0;
}
