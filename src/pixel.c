#include "tetris.h"
extern double winwidth;
extern double winheight;
extern char SelectColor[100];


void drawWord(double x, double y, double size, int num){
	int pixel[8][26] = {
	{1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
	{1,0,1,1,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
	{1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
	{1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0},
	{1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,1},
	};
	int i, j;
	for(i = 0;i < 26;i++){
		for(j = 0;j < 8;j++){
			if(pixel[j][i]){
				switch(pixel[j][i])
				{
					case 1: SetPenColor("Red"); break;
				}
				drawRectangle(x+size*i,y-size*j+num*size,size,size,1);
			}
		}
	}
}

void drawQR(double x, double y, double size){
	int QR[34][34]=
{
{1,1,1,1,1,1,1,0,0,1,1,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,1},
{1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,1},
{1,0,1,1,1,0,1,0,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,0,1},
{1,0,1,1,1,0,1,0,1,0,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1},
{1,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,0,1},
{1,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,1,1,0,1,0,0,0,0,0,1},
{1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1},
{0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
{0,1,0,1,1,1,1,0,1,1,0,0,1,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,1,0,1,0},
{1,0,0,0,1,1,0,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,1},
{0,0,1,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1,0},
{0,0,0,1,1,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,1,1,0,0,1,0,0,1,0,0,1,0,0},
{1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0},
{1,1,1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0},
{1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,1,0,1,1},
{0,1,1,0,1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,0,1,1,1},
{0,1,1,1,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,1,1,1,1,0,1},
{0,1,1,1,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
{0,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,1,1,1,0,1,0,0},
{0,1,1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,0,0,1,0,1,0,1,0,1,1,1,0},
{1,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0},
{1,1,1,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,0,0,1,0,0,1,0},
{1,0,0,0,0,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,0,1},
{1,0,1,1,0,1,0,1,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1},
{1,1,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1},
{0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0},
{1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,0,1,0},
{1,0,0,0,0,0,1,0,1,1,0,0,1,0,0,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0},
{1,0,1,1,1,0,1,0,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,1},
{1,0,1,1,1,0,1,0,1,0,1,0,1,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,1,0,0,1,0},
{1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1},
{1,0,0,0,0,0,1,0,1,1,1,0,1,1,0,1,1,1,0,1,0,1,1,0,0,0,0,1,0,0,1,1,0},
{1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,0,1,0,0,1,0,1,0,1,1,0,0,1,0,1,0},
};
	int i, j;
	for(i = 0;i < 34;i++){
		for(j = 0;j < 34;j++){
			if(QR[j][i]){
				switch(QR[j][i])
				{
					case 1: SetPenColor("Black"); break;
				}
				drawRectangle(x+size*i,y-size*j,size,size,1);
			}
		}
	}
}

void drawTitle(double x, double y, double size, int num){
	int pixel[8][30] = {
	{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,1,0,0,1,0,0,1,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,1,1,0,1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
	};
	int i, j;
	for(i = 0;i < 30;i++){
		for(j = 0;j < 8;j++){
			if(pixel[j][i]){
				switch(pixel[j][i])
				{
					case 1: SetPenColor(SelectColor); break;
				}
				drawRectangle(x+size*((i+num)%30),y-size*j,size,size,1);
			}
		}
	}
}

void drawPixel(double x, double y, double size, int num){
	int pixel[78][10] = {
	{0,0,0,0,0,0,0,0,0,0},//num == 1
	{0,0,0,4,4,4,0,0,0,0},
	{0,0,4,4,4,4,4,4,0,0},
	{0,4,4,4,4,4,4,4,4,0},
	{0,4,4,5,5,5,4,4,4,0},//line 5
	{0,4,5,2,5,5,2,4,4,4},
	{4,5,5,5,5,5,5,5,5,4},
	{4,4,5,1,1,1,1,5,4,4},
	{0,4,5,5,1,1,1,5,4,0},
	{0,4,5,5,5,5,5,5,4,0},//line 10
	{0,4,4,4,5,5,4,4,4,0},
	{0,0,4,3,5,5,3,4,0,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,0,3,3,3,3,0,5,0},//line 15
	{0,5,0,3,3,3,3,0,5,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,3,3,3,3,3,3,3,3,0},
	{0,0,0,5,0,0,5,0,0,0},//line 20
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,6,3,6,6,3,6,6,0},
	{6,6,6,3,6,6,3,6,6,6},//line 25
	{0,6,6,6,6,6,6,6,6,6},
	
/*	{0,0,0,4,4,4,0,0,0,0},
	{0,0,4,4,4,4,4,4,0,0},
	{0,4,4,4,4,4,4,4,4,0},
	{0,4,4,5,5,5,4,4,4,0},
	{0,4,5,2,5,5,2,4,4,4},//line 5
	{0,5,5,5,5,5,5,5,5,4},
	{4,4,5,1,1,1,1,5,4,0},
	{4,4,5,5,1,1,1,5,0,0},
	{4,4,5,5,5,5,5,5,0,0},
	{4,4,4,4,5,5,4,4,0,0},//line 10
	{0,4,4,3,5,5,3,0,0,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,0,3,3,3,3,0,5,0},
	{0,5,0,3,3,3,3,0,5,0},//line 15
	{0,5,3,3,3,3,3,0,5,0},
	{3,5,3,3,3,3,3,3,5,0},
	{3,3,3,3,3,3,3,3,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},//line 20
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,6,6,3,6,6,3,6,0,0},
	{6,6,6,3,6,6,3,6,6,6},
	{0,6,6,6,6,6,6,6,6,0}//line 25*/ 
	{0,0,0,0,0,0,0,0,0,0},//num == 2
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,4,4,4,0,0,0,0},
	{0,0,4,4,4,4,4,4,0,0},
	{0,4,4,4,4,4,4,4,4,0},//line 5
	{0,4,4,5,5,5,4,4,4,0},
	{0,4,5,2,5,5,2,4,4,4},
	{0,5,5,5,5,5,5,5,5,4},
	{4,4,5,1,1,1,1,5,4,0},
	{4,4,5,5,1,1,1,5,0,0},//line 10
	{4,4,5,5,5,5,5,5,0,0},
	{4,4,4,4,5,5,4,4,0,0},
	{0,4,4,3,5,5,3,0,0,0},
	{0,5,3,3,3,3,3,3,5,0},
	{0,5,3,3,3,3,3,3,5,0},//line 15
	{0,5,0,3,3,3,3,0,5,0},
	{0,5,0,3,3,3,3,0,5,0},
	{0,5,3,3,3,3,3,0,5,0},
	{3,5,3,3,3,3,3,3,5,0},
	{3,3,3,3,3,3,3,3,0,0},//line 20
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,6,6,3,6,6,3,6,0,0},
	{6,6,6,3,6,6,3,6,6,6},//line 25
	{0,6,6,6,6,6,6,6,6,0},
	
	{0,0,0,4,4,4,0,0,0,0},//num == 3
	{0,0,4,4,4,4,4,4,0,0},
	{0,4,4,4,4,4,4,4,4,0},
	{0,4,4,5,5,5,4,4,4,0},
	{0,4,5,2,5,5,2,4,4,4},//line 5
	{4,5,5,5,5,5,5,5,5,4},
	{5,4,5,1,1,1,1,5,4,5},
	{5,4,5,5,1,1,1,5,4,5},
	{5,4,5,5,5,5,5,5,4,5},
	{5,4,4,4,5,5,4,4,4,5},//line 10
	{5,0,4,3,5,5,3,4,0,5},
	{0,5,3,3,3,3,3,3,5,0},
	{0,0,3,3,3,3,3,3,0,0},
	{0,0,0,3,3,3,3,0,0,0},
	{0,0,0,3,3,3,3,0,0,0},//line 15
	{0,0,3,3,3,3,3,3,0,0},
	{0,3,3,3,3,3,3,3,0,0},
	{0,3,3,3,3,3,3,3,3,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},//line 20
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,5,0,0,5,0,0,0},
	{0,0,0,3,0,0,3,0,0,0},
	{0,0,0,3,0,0,3,0,0,0},
	{0,6,6,6,6,6,6,6,6,0},//line 25
	{0,0,6,6,6,6,6,6,0,0}
} ;
	
	int i, j;
	for(i = 0;i < 10;i++){
		for(j = num * 26;j < (num+1) * 26;j++){
			if(pixel[j][i]){
				switch(pixel[j][i])
				{
					case 1: SetPenColor("White"); break;
					case 2: SetPenColor("Black"); break;
					case 3: SetPenColor(SelectColor); break;
					case 4: SetPenColor("Yellow"); break;
					case 5: SetPenColor("Flesh"); break;
					case 6: SetPenColor("Light Gray"); break;
				}
				drawRectangle(x+size*i,y-size*j+26*size*num,size,size,1);
			}
		}
	}
}

void drawHeart(double x, double y, double size, int num){
	int pixel[6][7] = {
	{0,1,1,0,1,1,0},
	{1,2,2,1,2,2,1},
	{1,2,2,2,2,2,1},
	{0,1,2,2,2,1,0},
	{0,0,1,2,1,0,0},
	{0,0,0,1,0,0,0},
	};
	int i, j;
	for(i = 0;i < 7;i++){
		for(j = 0;j < 6;j++){
			if(pixel[j][i]){
				switch(pixel[j][i])
				{
					case 1: SetPenColor("Red"); break;
					case 2: SetPenColor("Pink"); break;
				}
				drawRectangle(x+size*i,y-size*j+num*size,size,size,1);
			}
		}
	}
}
