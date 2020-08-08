//头文件包含 
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
//本地头文件包含 
#include "imgui.h"

//预处理指令 
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
 *  用户输入处理函数组 
 *	键盘输入处理函数：
 *	KeyBoardEventProcess（处理游戏进行中的键盘输入）
 *	KeyBoardEventProcess2（处理游戏结束后的键盘输入）
 *  字符输入处理函数：
 *	CharEventProcess（处理游戏结束后输入玩家姓名的字符输入） 
 *	鼠标输入处理函数：
 *	MouseEventProcess（处理游戏开始前的鼠标输入） 
 *	MouseEventProcess2（处理游戏结束后的鼠标输入） 
 *	MouseEventProcess3（处理游戏暂停时的鼠标输入） 
 *  MouseEventProcessSelect(处理游戏选择难度时的鼠标输入） 
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
 *  界面显示处理函数组 
 *	display（处理游戏开始前的显示） 
 *	display2（处理游戏结束后的显示） 
 *	display3 （处理游戏暂停时的显示） 
 *  displayselect(处理选择难度时的显示) 
 **********************************************************/
void display();
void display2();
void display3();
void displayselect();

/**********************************************************
 *  游戏前后界面以及其他处理函数组 
 **********************************************************/
void MainButton();//游戏开始前界面 
void loginUI();//游戏登陆界面 
void displayUser();
void PixelProcess(int timerID);
int readRank(void);//读取保存的排行榜数据，读取到全局结构数组srank中 
int inputRank(char name[], int score); //先读取排行榜，并将名字和成绩插入排好序的排行榜中 
int displayRank(int page);//显示第page页排行榜 
void DrawSquare(double x, double y);
void drawRec(double x, double y, double width, double height, double thickness, char* outercolor, char* innercolor);
 
/**********************************************************
 *  游戏进程处理函数组 
 **********************************************************/
void TimerEventProcess(int timerID);
void TimerMoney(int timerID);
void wait(); 
//游戏界面处理
void initboard();
void StartGame();
void StartSaveGame();
void drawGameBoard();
void drawWord(double x, double y, double size, int num);
void drawGamePixel();
void DrawBlock(int BlockIndex, double sx, double sy); 
void EraseBlock(int BlockIndex, double sx, double sy); 
//游戏操作 
void HandleLeft(int BlockIndex,double *x, double *y);
void HandleRight(int BlockIndex,double *x, double *y);
void HandleUp(int *BlockIndex,double *x, double *y);
int HandleDown(int BlockIndex,double *x, double *y);
int SpaceDown(int BlockIndex,double *x,double *y);
//游戏进程中的判断函数 
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
