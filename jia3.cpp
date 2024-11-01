#include "CImg.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
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
		hitbox[i] = (unsigned char*)malloc(2 * sizeof(unsigned char));
	}
	for (int i = 0; i < 64; i++) {
		hitbox[i][0] = 255;
		hitbox[i][0] = 255;
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
	//std::cout << "\n1st lenght " << sizeof(object);
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
			//std::cout << "\nobject[i][j]: " << inti;
			if (value == 0) {
				posy = posy + inti;

			}
			else {
				for (int k = 0; k < inti; k++) {
					bg.draw_point(128 - posx, 64 - posy, one);
					posy++;

					//std::cout <<"\ny: " << y << "\nposy: " << posy << "\nk: " << k << "\ninti: " << inti;
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
		//std::cout << "\nlenght of "<<i <<": " << j<<"\n";

		posx = posx + 1;

	}
	//bg.display();
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
void addhitboxes(unsigned char** hitboxes, short curentpos, unsigned char widht, unsigned char hight) {
	hitboxes[curentpos][0] = widht;
	hitboxes[curentpos][1] = hight;
}
void addall(short curentpos, unsigned char*** objectarray, unsigned char** toadd, unsigned char** cords, unsigned char x, unsigned char y, unsigned char** hitboxes, unsigned char widht, unsigned char hight, unsigned char* objectprops, unsigned char props) {
	addobjectarray(objectarray, toadd, curentpos);
	addcords(cords, curentpos, x, y);
	addhitboxes(hitboxes, curentpos, widht, hight);
	objectprops[curentpos] = props;
}
void movecords(unsigned char** cords, int x, int y, short von, short bis) {
	short cordslenght = 0;
	while ((cords[cordslenght][0] != 255) && (cordslenght < 64)&& (cordslenght < bis)) {
		cordslenght++;
	}
	for (int i = von; i < cordslenght; i++) {
		cords[i][0] = cords[i][0] - x;
		cords[i][1] = cords[i][1] - y;
	}
}
void moveplayer(unsigned char** cords, unsigned char** hitboxes, int x, int y) {
	int lenght = 1;
	unsigned char check = 0;
	bool colision = 0;
	while (cords[lenght][0] != 255) {
		lenght++;
	}

	for (int i = 1; i < lenght; i++) {
		for (int j = 0; (j < hitboxes[0][0]) && (colision == 0);j++) {
			if ((cords[0][0] -x+ j >= cords[i][0]) && (cords[0][0] -x + j <= cords[i][0] + (hitboxes[i][0]-1))) {
				colision = 1;
			}
		}
	}
	if (colision == 1) {
		check++;
	}

	colision = 0;
	for (int i = 1; i < lenght; i++) {
		for (int j = 0; (j < hitboxes[0][1]) && (colision == 0); j++) {
			if ((cords[0][1] -y + j >= cords[i][1]) && (cords[0][1] -y + j <= cords[i][1] + (hitboxes[i][1]-1))) {
				colision = 1;
				//printf("\ny: %d\ncords[0][1]: %d\ncords[i][1]: %d\nj: %d\nhitboxes[i][1]: %d", y, cords[0][1], cords[i][1], j, hitboxes[i][1]);
				//printf("\nx: %d\ncords[0][0]: %d\ncords[i][0]: %d\nj: %d\n hitboxes[i][0]: %d", x, cords[0][0], cords[i][0], j, hitboxes[i][0]);
			}
		}
	}
	if (colision == 1) {
		check++;
	}

	if (check < 2) {
		movecords(cords,x,y,0,1);
	}
}
int main() {
	cimg_library::CImg <unsigned char> bg(128, 64, 1, 3, 0);

	unsigned char** box = (unsigned char**)malloc(sizeof(unsigned char*) * 9);
	for (int i = 0; i < 8; i++) {
		box[i] = (unsigned char*)malloc(sizeof(unsigned char) * 3);
		box[i][0] = 1;
		box[i][1] = 8;
		box[i][2] = 255;
	}
	box[8] = nullptr;

	unsigned char*** objectarray = getobjectarray();
	unsigned char**  cords = getcords();
	unsigned char**  hitboxes = gethitboxes();
	unsigned char*   objectprops = getobjectprops();
	addall(0,objectarray, gethuman1(),cords,16,16,hitboxes,5,20, objectprops,0);
	addall(1, objectarray, box, cords, 48, 48, hitboxes, 8, 8, objectprops,1);
	bg = drawall(objectarray, cords, bg);
	
	cimg_library::CImgDisplay dsp(128 * 8, 64 * 8, "1", 0);
	dsp.display(bg);
	while (!dsp.is_closed()) {
		char storechar = 'b';
		storechar = _getch();
		if (storechar == 'a') {
			moveplayer(cords, hitboxes, -1, 0);
		}
		else if (storechar == 'd') {
			moveplayer(cords, hitboxes, 1, 0);
		}
		else if (storechar == 'w') {
			moveplayer(cords, hitboxes, 0, -1);
		}
		else if (storechar == 's') {
			moveplayer(cords, hitboxes, 0, 1);
		}
		else if (storechar == 'e') {
			return 0;
		}
		bg = drawall(objectarray, cords, bg);
		dsp.display(bg);
	}


	return 0;
}
