#include "CImg.h"
#include <iostream>
#include <conio.h>

cimg_library::CImg <unsigned char> clear(cimg_library::CImg <unsigned char> bg) {
	unsigned char white[] = {254,254,254};
	
	
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 64; j++) {
			
			bg.draw_point(i, j,white);
		}
	}
	return bg;
}
cimg_library::CImg <unsigned char> draw(char** object, int x,int y, cimg_library::CImg <unsigned char> bg) {
	const unsigned char zero[] = { 255,255,255 };
	const unsigned char one[] = { 0,0,0 };
	int j;
	bool value;
	int posy = y;
	int posx = x;
	//std::cout <<"arraylenght: " << sizeof(object) << "\n";
	for (int i = 0; i < sizeof(object); i++) {
		
		if (object[i][0] == 0) {
			value = 0;
		}
		else {
			value = 1;
		}
		j = 1;
		posy = y;
		while (j < sizeof(object)) {
			if (value == 0) {
				posy = posy + object[i][j];
			}
			else {
				for (int k = 0; k < object[i][j]; k++) {
					bg.draw_point(posx ,posy,one);
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
		
		posx = posx+ 1;
		
	}
	//bg.display();
	return bg;
}
cimg_library::CImg <unsigned char> drawall(char*** objectarray,short** cords, cimg_library::CImg <unsigned char> bg){
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
short addobjectarray(char*** objectarray,char** toadd,short curentpos) {
	objectarray[curentpos] = toadd;
	return (curentpos + 1);
}
void changecords(short** cords, short pos,short x,short y) {
	cords[pos][0] = x;
	cords[pos][1] = y;
}
short** getcords() {
	short** cords = (short**)malloc(64 * sizeof(short*));
	for (int i = 0; i < 64; i++) {
		cords[i] = (short*)malloc(2 * sizeof(short));
	}
	for (int i = 0; i < 64; i++) {
		cords[i][0] = -32768;
		cords[i][0] = -32768;
	}
	return cords;
}
char*** getobjectarray() {
	char*** objectarray =(char***)malloc(64* sizeof(char**));
	for (int i = 0; i < 64; i++) {
		objectarray[i] = nullptr;
	}
	
	return objectarray;
}
void movecords(short** cords,int x, int y) {
	short cordslenght = 0;
	while((cords[cordslenght][0] != -32768) && (cordslenght < 64)) {
		cordslenght++;
	}
	for (int i = 0; i < cordslenght; i++) {
		cords[i][0] = cords[i][0] + x;
		cords[i][1] = cords[i][1] + y;
	}
}
int main() {
	cimg_library::CImg <unsigned char> bg(128,64,1,3,0 );
	
	short curentpos = 0;
	char** box = (char**)malloc(sizeof(char*)* 8);
	for (int i = 0; i < 8; i++) {
		box[i] = (char*)malloc(sizeof(char) * 2);
		box[i][0] = 1;
		box[i][1] = 8;
	}

	char*** objectarray =	getobjectarray();
	curentpos = addobjectarray(objectarray, box, curentpos);
	curentpos = addobjectarray(objectarray, box, curentpos);
	short** cords = getcords();
	changecords(cords,0,16,16);
	changecords(cords, 1, 24, 24);
	
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
		bg = drawall(objectarray, cords, bg);
		dsp.display(bg);
	}
	 

	return 0;
}