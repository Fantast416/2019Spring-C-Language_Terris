#include "tetris.h"

/**********************************************************
 *  全局变量组 
 **********************************************************/
double winwidth, winheight;		// 窗口尺寸
int selected_lable;
int MainMenuStatus = -1;
int nScore=0;					//分数 
int nSpeed=1;                   //速度等级 
int nSelectSpeed=1;				//选择速度等级 
int nSpeedUpScore;				//晋级速度分数 
int bottom;						//是否到达底部0/1 
int bottom2;
int nNext_block_index=-1;		//下一个方块类型 
int nCurrent_block_index=0 ;	//现在的方块类型编码 
double nOriginX=4;				//现在的x/y值 
double nOriginY=5;
int GameBoard[20][10];			//游戏板 
char GameBoardColor[20][10][15]; 
int KeyDown = 0;
int PauseNum;
int judge=0;
char SelectColor[100] = "ORANGE";
char HotKeyColor[100] = "RED";
char HotKeyFont[100] = "YELLOW";
int rankpage = 1;
int pixelnum = 0;
int titlenum = 0;
int animelenth = 0;
int addmoney;
int user_guest = 0;
struct score {
	int rank;
	char name[50];
	int score;
};								//排行榜数组 

struct score srank[20] = { 0 };		//排行榜全局变量 


//全局 
struct Save{
	char name[50]; //从属的用户 
	int Level;   //等级 
	int Score;   //分数 
    int GameBoard[20][10];  //游戏版数据			
    char GameBoardColor[20][10][15];  //游戏版数据
	int nNext_block_index;		//下一个方块类型 
    int nCurrent_block_index;
    int time[6];
};

struct Save ssave;

struct User{
	char name[50];
	char password[50];
	int money; 
	int save_exist;
	char Color[100]; 
};

struct User suser; 
int loginstatus = 0;
int registerstatus = 0;

// 用户主程序入口
// 仅初始化执行一次
void Main() 
{   
    PlaySound(TEXT("BGM-1.wav"),NULL,SND_FILENAME | SND_ASYNC|SND_LOOP);
	// 初始化窗口和图形系统
	SetWindowTitle("俄罗斯方块(Tetris)1.0.10");
	//SetWindowSize(10, 10); // 单位 - 英寸
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // 如果屏幕尺寸不够，则按比例缩小
    InitGraphics();
	//registerCharEvent(CharEventProcess); // 字符
	//registerKeyboardEvent(KeyboardEventProcess);// 键盘
	//registerMouseEvent(MouseEventProcess);      // 鼠标
	//registerTimerEvent(TimerEventProcess);      // 定时器
	// 开启定时器
	registerCharEvent(CharEventProcess2);
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess5);
	registerTimerEvent(PixelProcess);
	startTimer(0,500);
	display();
	// 打开控制台，方便输出变量信息，便于调试
	// InitConsole(); 

}








       



