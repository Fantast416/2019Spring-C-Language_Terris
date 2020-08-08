#include "tetris.h"

/**********************************************************
 *  ȫ�ֱ����� 
 **********************************************************/
double winwidth, winheight;		// ���ڳߴ�
int selected_lable;
int MainMenuStatus = -1;
int nScore=0;					//���� 
int nSpeed=1;                   //�ٶȵȼ� 
int nSelectSpeed=1;				//ѡ���ٶȵȼ� 
int nSpeedUpScore;				//�����ٶȷ��� 
int bottom;						//�Ƿ񵽴�ײ�0/1 
int bottom2;
int nNext_block_index=-1;		//��һ���������� 
int nCurrent_block_index=0 ;	//���ڵķ������ͱ��� 
double nOriginX=4;				//���ڵ�x/yֵ 
double nOriginY=5;
int GameBoard[20][10];			//��Ϸ�� 
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
};								//���а����� 

struct score srank[20] = { 0 };		//���а�ȫ�ֱ��� 


//ȫ�� 
struct Save{
	char name[50]; //�������û� 
	int Level;   //�ȼ� 
	int Score;   //���� 
    int GameBoard[20][10];  //��Ϸ������			
    char GameBoardColor[20][10][15];  //��Ϸ������
	int nNext_block_index;		//��һ���������� 
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

// �û����������
// ����ʼ��ִ��һ��
void Main() 
{   
    PlaySound(TEXT("BGM-1.wav"),NULL,SND_FILENAME | SND_ASYNC|SND_LOOP);
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("����˹����(Tetris)1.0.10");
	//SetWindowSize(10, 10); // ��λ - Ӣ��
	//SetWindowSize(15, 10);
	//SetWindowSize(10, 20);  // �����Ļ�ߴ粻�����򰴱�����С
    InitGraphics();
	//registerCharEvent(CharEventProcess); // �ַ�
	//registerKeyboardEvent(KeyboardEventProcess);// ����
	//registerMouseEvent(MouseEventProcess);      // ���
	//registerTimerEvent(TimerEventProcess);      // ��ʱ��
	// ������ʱ��
	registerCharEvent(CharEventProcess2);
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess5);
	registerTimerEvent(PixelProcess);
	startTimer(0,500);
	display();
	// �򿪿���̨���������������Ϣ�����ڵ���
	// InitConsole(); 

}








       



