//ͷ�ļ����� 
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#pragma comment(lib, "winmm.lib")
//����ͷ�ļ����� 
#include "imgui.h"

//Ԥ����ָ�� 
#define B_Frequency 450
#define B_Duration 75
#define BN_Frequency 225
#define BN_Duration 75
#define GB_Frequency 1500
#define GB_Duration 75
#define GN_Frequency 500
#define GN_Duration 75
#define GS_Frequency 1800
#define GS_Duration 75
#define blocksize 0.25
#define boardwidth 2.7
#define boardheight 5.2 
#define statuswidth 1.5
#define statusheight 2.0
#define MAX_BOX 19 
#define BSIZE 0.25 
#define FILLED 1
#define EMPTY 0 
#define TRUE 1
#define FALSE 0

#ifndef tetris_functions
#define tetris_functions 

/**********************************************************
 *  �û����봦������ 
 *	�������봦������
 *	KeyBoardEventProcess��������Ϸ�����еļ������룩
 *	KeyBoardEventProcess2��������Ϸ������ļ������룩
 *  �ַ����봦������
 *	CharEventProcess��������Ϸ��������������������ַ����룩 
 *	������봦������
 *	MouseEventProcess��������Ϸ��ʼǰ��������룩 
 *	MouseEventProcess2��������Ϸ�������������룩 
 *	MouseEventProcess3��������Ϸ��ͣʱ��������룩 
 *  MouseEventProcessSelect(������Ϸѡ���Ѷ�ʱ��������룩 
 **********************************************************/
void KeyBoardEventProcess(int key,int event);
void KeyboardEventProcess2(int key, int event);
void KeyboardEventProcess3(int key, int event);
void KeyboardEventProcess4(int key, int event);
void KeyboardEventProcess5(int key, int event);
void CharEventProcess(char ch);
void CharEventProcess2(char ch);
void MouseEventProcess(int x, int y, int button, int event);
void MouseEventProcess2(int x, int y, int button, int event);
void MouseEventProcess3(int x, int y, int button, int event);
void MouseEventProcessSelect(int x, int y, int button, int event); 

/**********************************************************
 *  ������ʾ�������� 
 *	display��������Ϸ��ʼǰ����ʾ�� 
 *	display2��������Ϸ���������ʾ�� 
 *	display3 ��������Ϸ��ͣʱ����ʾ�� 
 *  displayselect(����ѡ���Ѷ�ʱ����ʾ) 
 **********************************************************/
void display();
void display2();
void display3();
void displayselect();

/**********************************************************
 *  ��Ϸǰ������Լ������������� 
 **********************************************************/
void MainButton();//��Ϸ��ʼǰ���� 
void loginUI();//��Ϸ��½���� 
void displayUser();
void PixelProcess(int timerID);
int readRank(void);//��ȡ��������а����ݣ���ȡ��ȫ�ֽṹ����srank�� 
int inputRank(char name[], int score); //�ȶ�ȡ���а񣬲������ֺͳɼ������ź�������а��� 
int displayRank(int page);//��ʾ��pageҳ���а� 
void DrawSquare(double x, double y);
void drawRec(double x, double y, double width, double height, double thickness, char* outercolor, char* innercolor);
 
/**********************************************************
 *  ��Ϸ���̴������� 
 **********************************************************/
void TimerEventProcess(int timerID);
void TimerMoney(int timerID);
void wait(); 
//��Ϸ���洦��
void initboard();
void StartGame();
void StartSaveGame();
void drawGameBoard();
void drawWord(double x, double y, double size, int num);
void drawGamePixel();
void DrawBlock(int BlockIndex, double sx, double sy); 
void EraseBlock(int BlockIndex, double sx, double sy); 
//��Ϸ���� 
void HandleLeft(int BlockIndex,double *x, double *y);
void HandleRight(int BlockIndex,double *x, double *y);
void HandleUp(int *BlockIndex,double *x, double *y);
int HandleDown(int BlockIndex,double *x, double *y);
int SpaceDown(int BlockIndex,double *x,double *y);
//��Ϸ�����е��жϺ��� 
int IsConflict(int BlockIndex,double sx, double sy);
int IsLineFull(int y);
void KillLine(int y);
int KillLines(int y);
int IsGameOver();
void MouseEventmoney(int x, int y, int button, int event);
void displaymoney();
void Mainmoney(int addmoney);

/*struct score {
	int rank;
	char name[50];
	int score;
};			
extern struct score srank[20];*/

#endif
