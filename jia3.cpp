#include "CImg.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>

unsigned char** gethuman1() {
	unsigned char** human = (unsigned char**)malloc(sizeof(unsigned char*) * 15);

	human[0] = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	human[0][0] = 0; human[0][1] = 18; human[0][2] = 1; human[0][3] = 255;
	human[1]  = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[1][0] = 0; human[1][1] = 8; human[1][2] = 2; human[1][3] = 8; human[1][4] = 1; human[1][5] = 255;
	human[2]  = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[2][0] = 0; human[2][1] = 8; human[2][2] = 2; human[2][3] = 8; human[2][4] = 1; human[2][5] = 255;
	human[3]  = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[3][0] = 0; human[3][1] = 8; human[3][2] = 2; human[3][3] = 4; human[3][4] = 6; human[3][5] = 255;
	human[4]  = (unsigned char*)malloc(sizeof(unsigned char) *7);
	human[4][0] = 1; human[4][1] = 10; human[4][2] = 3; human[4][3] = 1; human[4][4] = 4; human[4][5] = 2; human[4][6] = 255;
	human[5]  = (unsigned char*)malloc(sizeof(unsigned char) *9);
	human[5][0] = 1; human[5][1] = 11; human[5][2] = 1; human[5][3] = 1; human[5][4] = 3; human[5][5] = 1; human[5][6] = 1; human[5][7] = 2; human[5][8] = 255;
	human[6]  = (unsigned char*)malloc(sizeof(unsigned char) *8);
	human[6][0] = 0; human[6][1] = 4; human[6][2] = 8; human[6][3] = 1; human[6][4] = 1; human[6][5] = 4; human[6][6] = 2; human[6][7] = 255;
	human[7]  = (unsigned char*)malloc(sizeof(unsigned char) *8);
	human[7][0] = 0; human[7][1] = 4; human[7][2] = 8; human[7][3] = 1; human[7][4] = 1; human[7][5] = 4; human[7][6] = 2; human[7][7] = 255;
	human[8]  = (unsigned char*)malloc(sizeof(unsigned char) *9);
	human[8][0] = 1; human[8][1] = 11; human[8][2] = 1; human[8][3] = 1; human[8][4] = 3; human[8][5] = 1; human[8][6] = 1; human[8][7] = 2; human[8][8] = 255;
	human[9]  = (unsigned char*)malloc(sizeof(unsigned char) *7);
	human[9][0] = 1; human[9][1] = 10; human[9][2] = 3; human[9][3] = 1; human[9][4] = 4; human[9][5] = 2; human[9][6] = 255;
	human[10] = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[10][0] = 0; human[10][1] = 8; human[10][2] = 2; human[10][3] = 4; human[10][4] = 6; human[10][5] = 255;
	human[11] = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[11][0] = 0; human[11][1] = 8; human[11][2] = 2; human[11][3] = 8; human[11][4] = 1; human[11][5] = 255;
	human[12] = (unsigned char*)malloc(sizeof(unsigned char) *6);
	human[12][0] = 0; human[12][1] = 8; human[12][2] = 2; human[12][3] = 8; human[12][4] = 1; human[12][5] = 255;
	human[13] = (unsigned char*)malloc(sizeof(unsigned char) *4);
	human[13][0] = 0; human[13][1] = 18; human[13][2] = 1; human[13][3] = 255;
	human[14] = nullptr;
	/*for (int i = 0; i < 14; i++) {
		for (int j = 0; human[i][j] != 255;j++) {
			printf("human[%d][%d]: %d\n",i,j,human[i][j]);
		}
	}*/
	return human;
}
cimg_library::CImg <unsigned char> clear(cimg_library::CImg <unsigned char> bg) {
	unsigned char white[] = {254,254,254};
	
	
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 64; j++) {
			
			bg.draw_point(i, j,white);
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
				for (int k = 0; k <  inti; k++) {
					bg.draw_point(128 -posx ,64 -posy,one);
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
		
		posx = posx+ 1;
		
	}
	//bg.display();
	return bg;
}
cimg_library::CImg <unsigned char> drawall(unsigned char*** objectarray, unsigned char** cords, cimg_library::CImg <unsigned char> bg){
	bg = clear(bg);
	short objectarraylenght = 0;
	while (objectarray[objectarraylenght] != nullptr) {
		objectarraylenght++;
	}
	for (int i = 0; i <objectarraylenght; i++) {
		bg = draw(objectarray[i],cords[i][0],cords[i][1],bg);
	}
	//bg.display();
	return bg;
}
short addobjectarray(unsigned char*** objectarray, unsigned char** toadd,short curentpos) {
	objectarray[curentpos] = toadd;
	return (curentpos + 1);
}
void changecords(unsigned char** cords, short pos, unsigned char x, unsigned char y) {
	cords[pos][0] = x;
	cords[pos][1] = y;
}
unsigned char** getcords() {
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
unsigned char*** getobjectarray() {
	unsigned char*** objectarray =(unsigned char***)malloc(64* sizeof(unsigned char**));
	for (int i = 0; i < 64; i++) {
		objectarray[i] = nullptr;
	}
	
	return objectarray;
}
void movecords(unsigned char** cords,int x, int y) {
	short cordslenght = 0;
	while((cords[cordslenght][0] != 255) && (cordslenght < 64)) {
		cordslenght++;
	}
	for (int i = 0; i < cordslenght; i++) {
		cords[i][0] = cords[i][0] - x;
		cords[i][1] = cords[i][1] - y;
	}
}
short add(char*** objectarray,char** toadd,short curentpos,short** cords,short x,short y) {
	return 0;
}
int main() {
	cimg_library::CImg <unsigned char> bg(128, 64, 1, 3, 0);

	short curentpos = 0;
	unsigned char** box = (unsigned char**)malloc(sizeof(unsigned char*) * 9);
	for (int i = 0; i < 8; i++) {
		box[i] = (unsigned char*)malloc(sizeof(unsigned char) * 3);
		box[i][0] = 1;
		box[i][1] = 8;
		box[i][2] = 255;
	}
	box[8] = nullptr;

	unsigned char*** objectarray =	getobjectarray();
	unsigned char** cords = getcords();
	curentpos = addobjectarray(objectarray, gethuman1(), curentpos);
	curentpos = addobjectarray(objectarray, box, curentpos);
	
	changecords(cords,0,16,16);
	changecords(cords, 1, 48, 48);
	//return  0;
	
	//bg.display();
	
	//(bg = draw(box,16,16,bg);
	//bg = draw(box, 63,63, bg);
	bg = drawall(objectarray, cords, bg);
	//bg.display();
	
	cimg_library::CImgDisplay dsp(128*8,64*8,"1",0);
	dsp.display(bg);
	while (!dsp.is_closed()) {
		char storechar = 'b';
		storechar = _getch();
		if(storechar == 'a'){
			movecords(cords, -1, 0);
		}
		else if (storechar == 'd') {
			movecords(cords, 1, 0);
		}
		else if (storechar == 'w') {
			movecords(cords, 0, -1);
		}
		else if (storechar == 's') {
			movecords(cords,0, 1);
		}
		else if (storechar == 'e') {
			return 0;
		}
		bg = drawall(objectarray, cords, bg);
		dsp.display(bg);
	}
	 

	return 0;
}
