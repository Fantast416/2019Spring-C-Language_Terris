#include "tetris.h"
/*1.0.0�Լ�1.0.1�汾Ϊ���̳��ڳ��� 
/*1.0.2�汾�����������£�
 1������ѡ���ٶȵȼ�����
 2���޸����������޷�������bug
 3���޸���ͣ�����������bug
 */ 
 /*1.0.3�汾�����������£�
 1��������������
 2���޸���pauseʱ�����ƶ������bug 
 3����������Ϸ˵�� ����ѡ���У� 
 4�� �޸�һֱ��ס��ת�����ײ���������bug
 */  
 /*1.0.4�汾�����������£�
 1�����������а�ģ�飬�������ݱ�����exeĿ¼�µ�rank.exe��
 //�ѵ㣺rank��ض�д�ļ���������ƣ�1��readrank��ȡ�����ļ���������Ϣ��ȫ�ֱ���srank��ʹ�������ı����ļ�����ȡ���� 
 //2��inputrank������Ϸ����ʱ��õ�������Ϣ���ȶ�ȡ�ļ��е�������Ϣ����Ϊֻ��<=20����������һ�����ź����ģ�ʹ�����鴢����Ϣ���Ҳ��ò������򷨣��ٽ������ڵ���������fprintf���ļ��� 
 2����������ɫѡ���Ż���������ɫѡ��
 3����������Ϸ˵��������Ϸ�У� 
 /*1.0.5�汾�����������£�
 1�������˿�ʼ����Ķ���Ч��
 2���޸���ѡ�������ɫ��ʱ��ʾ������ 
 3���޸��˼��������޷�������bug
 /*1.0.6�汾�����������£�
 1�����ӵ�½����
 2�������û�ϵͳ�Լ�������Ľ�Ǯϵͳ 
 3���޸�ESC���水����λ��
 4�����ע����ַ����û������� 
 5��������� 
 /*1.0.7�汾�����������£�
 1���������
 2���޸����û����溯���Լ��û����º����Լ��浵���溯��������bug
 3����GameBoardColor�Ĵ��������ɵ�ַ���͸��ĵ��������ͣ����ǵ����ļ��Լ��ٴδ򿪳���ĵ�ַ�����������
 4�������˿�ݼ�����
 5�����а�ע�οͺ��û������� 
 6�������˵�¼����ķ��ذ����������˵�¼����  
 /*1.0.8�汾�����������£� 
 1������ٴδ���Ϸһ�������кܴ�����ܴ����� ��������ÿ���˳���Ϸ�Ѹ���Eventȡ���������������������棩 
 2�����һ�������xx��һ���µ����⣡��������VK_DOWN��ѭ������SpaceDown������ 
 3�������ȡ�浵���ؿ���Ϸ������ 
 4���ḻ����Ϸ�����Լ��������ɫ 
 5�������˴浵�ı���ʱ���¼�Լ���ʾ����
 6���޸���TimerEventProcess���߼��ṹ����if-else if�ṹ����switch�ṹ 
 7������˳�ֵ֮��ĸ����û����ݵ����� 
 /*1.0.9�汾�����������£�
 1�������˱�����棨����鲻��Ҫ��ʧ������ȡ�浵ʱ��Ҳ���᲻��ˢ�µ� 
 2������˴Ӵ浵��ʼ��Ϸ����ʾ��һ����������� 
 3���û��Զ�����ѡ�����ɫ���� 
 4������ɹ�����ʾ����ʱ���Լ�����ɹ���ʾ 
 5���û�ѡ����ɫ��Ҫ����200��ң����һ�ʵʱ��ʾ�û���Ϣ��ѡ����� 
 6�������˿�ݼ����ܣ�1������ݼ���ע�ڰ�����2������˰��¿�ݼ�����Ҫ�ƶ�������ˢ�µ�����3��������MainButton�Ķ���Ŀ¼��ESC���ع��� 
 /*1.0.10�汾�����������£�2019/6/14
 1���Ż���Ϸ�������飬Ĭ��BGM����Tetris/BGMĿ¼�µ�BGM.wav����������Ϸ�е���Ч 
 2���������û������Լ��浵�����Լ����а����ݵĴ洢λ�ã���Ϊ����exeʱ�������ȡ��Щ�ļ�
  
 6/14�չ����ƻ���
 2���Ż���Ϸ���� 
 1������ɾ��һЩ���õĺ���spacedown  
 6��������Ϸ���ұ߽�ķ�����ת���� 
 3����������˫��ģʽ��
 4���������Ӿ���������˫��ģʽ��
 5�����Ӷ���Ч���� 

/**********************************************************
 *  ȫ�ֱ����� 
 **********************************************************/
extern double winwidth, winheight;		// ���ڳߴ�
extern int selected_lable;
extern int MainMenuStatus;
extern int nScore;                     	//���� 
extern int nSpeed;                	//�ٶȵȼ� 
extern int nSelectSpeed;   			//ѡ���ٶȵȼ� 
extern int nSpeedUpScore;				//�����ٶ� 
extern int bottom;						//�Ƿ񵽴�ײ�0/1 
extern int bottom2;                    	//һ�����ʱ�Ƿ񵽴�ײ�0/1 
extern int nNext_block_index;			//��һ���������� 
extern int nCurrent_block_index;		//���ڵķ������ͱ��� 
extern double nOriginX;					//���ڵ�x/yֵ 
extern double nOriginY;
extern int GameBoard[20][10];					//��Ϸ�� 
extern char GameBoardColor[20][10][15];
extern int KeyDown; 
extern int PauseNum;                    //������ͣ�����еļ��� 
extern int judge;                    	//�����޸����������޷�������bug���������жϵı��� 
extern char SelectColor[100];
extern char HotKeyColor[100];
extern char HotKeyFont[100];
extern int rankpage; 
extern int pixelnum;
extern int titlenum;
extern int animelenth;
extern int addmoney;
extern int user_guest;
struct score {
	int rank;
	char name[50];
	int score;
};								//���а����� 

extern struct score srank[20];

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

extern struct Save ssave;

struct User{
	char name[50];
	char password[50];
	int money;
	int save_exist;
	char Color[100]; 
};

extern struct User suser;
extern int loginstatus;
extern int registerstatus;
/**********************************************************
 *  ��Ϸ���鴢������ 
 **********************************************************/
struct SHAPE
{
	int box[8];
	char color[15];
	/*ÿ����Ϸ�������ɫ*/
	int next;
	/*�¸���Ϸ����ı��*/
};

struct SHAPE shapes[MAX_BOX]=
{
	//��������    ��������    ��������    ��������  
	//��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
      
	{0,1,0,2,0,3,1,1,"CYAN",1},
	{0,2,0,3,1,3,2,3,"CYAN",2},
	{0,3,1,3,1,2,1,1,"CYAN",3},
	{0,1,1,1,2,1,2,2,"CYAN",0},

    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������

	{0,1,1,1,1,2,1,3,"MAGENTA",5},
	{0,2,0,3,1,2,2,2,"MAGENTA",6},
	{0,1,0,2,0,3,1,3,"MAGENTA",7},
	{0,3,1,3,2,3,2,2,"MAGENTA",4},

    //��������    ��������    
    //��������    ��������    
    //��������    ��������    
    //��������    ��������    

	{0,3,0,2,1,2,1,1,"YELLOW",9},
	{0,2,1,2,1,3,2,3,"YELLOW",8},

    //��������    ��������    
    //��������    ��������
    //��������    ��������    
    //��������    ��������

	{0,1,0,2,1,2,1,3,"BROWN",11},
	{0,3,1,3,1,2,2,2,"BROWN",10},
	
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������
    //��������    ��������    ��������    ��������

	{0,2,1,2,1,3,2,2,"GREEN",13},
	{0,1,0,2,0,3,1,2,"GREEN",14},
	{0,3,1,3,1,2,2,3,"GREEN",15},
	{0,2,1,1,1,2,1,3,"GREEN",12},

    //��������    ��������    
    //��������    ��������
    //��������    ��������    
    //��������    ��������

	{0,0,0,1,0,2,0,3,"RED",17},
	{0,1,1,1,2,1,3,1,"RED",16},

    //��������   
    //��������  
	//��������   
    //��������   

	{0,2,0,3,1,2,1,3,"BlUE",18},
};
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
 **********************************************************/
/**********************************************************
 *  ��Ϸ�����еļ��̴����� 
 **********************************************************/
void KeyBoardEventProcess(int key,int event)
{
	//char ScoreBuffer[100]={0},SpeedBuffer[100]={0};
	//char n[100]={"        score:  "};
	int i,j,k,EraseLineNum;
	char n[100]={"        score:  "};
	char ScoreBuffer[100]={0}; 
	uiGetKeyboard(key,event);
	switch(event){
		if(KeyDown == 0){
			case KEY_DOWN:
				KeyDown = 1;
				if(key == VK_SPACE){
				    while(1){
				    	if(bottom==1){
				    		Beep(GB_Frequency,GB_Duration); 
				    		break;
						}
				    	bottom=HandleDown(nCurrent_block_index,&nOriginX,&nOriginY);
				    	     //�����޸����䵽��ʱһֱ��ס���������δ��������������ڰ���һֱ����DOWN״̬�������޷�����Keyboardevent�����ж��� 
					}
					//tm��VK_DOWN�������ͣѭ��ֱ�����ײ������ˣ�����ô���е�û�ĸ�ʲô�������� �ǵð�SpaceDownɾ�ˣ�����drawGameBoardҲɾ�ˡ� 
					
					/*bottom2=SpaceDown(nCurrent_block_index,&nOriginX,&nOriginY);
                  	for(i=19;i>=0;i--)
        				for(j=0;j<10;j++){
            				if(GameBoard[i][(int)j]){
            					SetPenColor(GameBoardColor[i][(int)j]);
            					drawRectangle(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,1); 
							}
            				else {
	         					SetPenColor("WHITE");
             					drawRectangle(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,1);	
							} 
						}
    				for(i=19;i>=0;i--)
        				for(j=0;j<10;j++){
            				if(GameBoard[i][(int)j]){
              					SetPenColor("GRAY");
              					MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	         					DrawLine(0, BSIZE);
	         					DrawLine(BSIZE, 0);
	         					DrawLine(0, -BSIZE);
	         					DrawLine(-BSIZE, 0);
							}
						} */
				}
				else if(key == VK_LEFT){
					HandleLeft(nCurrent_block_index,&nOriginX,&nOriginY);
					//Beep(GB_Frequency,GB_Duration); 
				}
				else if(key == VK_RIGHT){
					HandleRight(nCurrent_block_index,&nOriginX,&nOriginY);
					//Beep(GB_Frequency,GB_Duration); 
				}
				else if(key == VK_UP){
					if(!IsConflict(shapes[nCurrent_block_index].next,nOriginX,nOriginY)&&judge==0)   //�����޸����䵽��ʱһֱ��ס��ת����������������� 
						HandleUp(&nCurrent_block_index,&nOriginX,&nOriginY);
						//Beep(GB_Frequency,GB_Duration); 
				}
				else if(key == VK_DOWN){
					if(bottom==1)
						break;     //�����޸����䵽��ʱһֱ��ס���������δ��������������ڰ���һֱ����DOWN״̬�������޷�����Keyboardevent�����ж��� 
				    bottom=HandleDown(nCurrent_block_index,&nOriginX,&nOriginY);
				    //Beep(GB_Frequency,GB_Duration); 
				}
				else if(key == VK_ESCAPE){
					cancelTimer(0); 
                    cancelTimer(1);
					cancelTimer(2);
					cancelTimer(3);
					cancelMouseEvent(); 
					registerMouseEvent(MouseEventProcess3);
					button(GenUIID(0),1,6.3,1,0.5,"������Ϸ!");
                    button(GenUIID(0),1,5.5,1,0.5,"ȷ���˳�?"); 
                    button(GenUIID(0),1,4.7,1,0.5,"������Ϸ!");
                    button(GenUIID(0),1,3.9,1,0.5,"���¿�ʼ!");
                    Beep(BN_Frequency,BN_Duration); 
				}
				else if(key == VK_CONTROL){
					if(suser.money>=(5+5*nSpeed)){
				  		nScore += (100 + (nSpeed-1) * 50);
				 		suser.money -= (5+5*nSpeed); 
				  		KillLine(20);
				  		itoa(nScore,ScoreBuffer,10);
            			drawRec(6.9, 3, statuswidth, statusheight-1.5, 0, "WHITE","WHITE");
						SetPenColor(SelectColor);
						textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5, strcat(n,ScoreBuffer), 0);
				  		DrawBlock(nCurrent_block_index,nOriginX,nOriginY);
				  		Beep(GS_Frequency,GS_Duration); 
					}
					else{
						Beep(GN_Frequency,GN_Duration); 
					}
				}
				break;
			case KEY_UP:
				KeyDown = 0;
				break;
		}
    }
    //drawGameBoard();//������ã���drawGameBoard����Ҳһ��ɾ�� 
}
/**********************************************************
 *  ��Ϸ������ļ������봦���� 
 **********************************************************/
 
void KeyboardEventProcess2(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display2(); // ˢ����ʾ
}
void KeyboardEventProcess3(int key, int event)   //�������ݼ� 
{
	uiGetKeyboard(key,event); // GUI��ȡ����
   switch (event) {
 	  case KEY_DOWN:
		    switch(key)
            {
                case VK_F1: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 1;
				display(); 
					break;
				}   /*��ʼ��Ϸ��ݼ�*/
                case VK_F2: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 2;
				display();
					break; 
				} /*ѡ���ݼ�*/
                case VK_F3: {
                	Beep(B_Frequency,B_Duration); 
                readRank();
                rankpage = 1;
				MainMenuStatus = 3;
				display();
					break; 
				} /*���а��ݼ�*/
                case VK_F4: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 4;
				display();
					break; 
				} /*��ֵ��ݼ�*/
                case  VK_F5: {
                	Beep(BN_Frequency,BN_Duration); 
			    exit(0);
				} /*�˳���ݼ�*/               
					break;
				case  VK_ESCAPE: {
					Beep(BN_Frequency,BN_Duration); 
					MainMenuStatus = 0;
					registerTimerEvent(PixelProcess);
					startTimer(0,500);
					display();
					break;
				}
}
}} 
void KeyboardEventProcess4(int key, int event)//Ϊɶ������4���������� 
{
	uiGetKeyboard(key,event);
	 switch (event) {
 	  case KEY_DOWN:
		    switch(key)
            {
                case VK_SPACE:/*��ͣ*/
                    wait();
    cancelKeyboardEvent();
	registerKeyboardEvent(KeyBoardEventProcess);
					break;
	
}
case KEY_UP: 
   break;}}
void KeyboardEventProcess5(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}
   
/**********************************************************
 *  ��Ϸ��������ַ����봦���� 
 **********************************************************/
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display2(); //ˢ����ʾ
}
void CharEventProcess2(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}
/**********************************************************
 *  ��Ϸ��ʼǰ����괦���� 
 **********************************************************/
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display();
}
/**********************************************************
 *  ��Ϸ���������괦���� 
 **********************************************************/
void MouseEventProcess2(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display2();

}
/**********************************************************
 *  ��Ϸ��ͣʱ����괦���� 
 **********************************************************/
void MouseEventProcess3(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display3();

}
void MouseEventProcessSelect(int x, int y, int button, int event)
{
	  uiGetMouse(x,y,button,event);
	 displayselect();
}


/**********************************************************
 *  ������ʾ�������� 
 *	display��������Ϸ��ʼǰ����ʾ�� 
 *	display2��������Ϸ���������ʾ�� 
 *	display3 ��������Ϸ��ͣʱ����ʾ�� 
 **********************************************************/
 /**********************************************************
 *  ��Ϸ��ʼǰ���洦���� 
 **********************************************************/
void display()
{   
	int k=3;
	int i,j=0;
	// ���� 
	DisplayClear();
	if(MainMenuStatus == -1){
		loginUI();
	}
	if(MainMenuStatus == 0){
		MainButton();
	}
	
	if(MainMenuStatus == 1){
		//cancelCharEvent();
		//cancelKeyboardEvent(); 
		cancelMouseEvent();
		StartGame(); 
  		for(i=0;i<20;i++)
    		for(j=0;j<10;j++){
    			SetPenColor("GRAY");
        		MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	    		DrawLine(0, BSIZE);
	    		DrawLine(BSIZE, 0);
	    		DrawLine(0, -BSIZE);
	    		DrawLine(-BSIZE, 0);
			}
		
 		registerTimerEvent(TimerEventProcess);
 		registerKeyboardEvent(KeyBoardEventProcess);
 		startTimer(1,500-nSelectSpeed*100);
 		startTimer(2,50);
   		startTimer(3,10);
    }
    if(MainMenuStatus == 2){
    	
		   cancelTimer(0);
		   cancelTimerEvent();
		   cancelMouseEvent();
		   displayselect();
    	   registerMouseEvent(MouseEventProcessSelect);
    	   
	} 
	if(MainMenuStatus == 3){
		DisplayClear();
		if(displayRank(rankpage)){
			if(rankpage<4&&button(GenUIID(0),winwidth/2-0.4,winheight/2-1.5,0.8,0.4,"��һҳ")){
				Beep(B_Frequency,B_Duration); 
				rankpage++; 
				display();
			} 
		}
		if(rankpage>1&&button(GenUIID(0),winwidth/2-1.5,winheight/2-1.5,0.8,0.4,"��һҳ")){
			Beep(B_Frequency,B_Duration); 
			rankpage--; 
			display();
			} 
		if(button(GenUIID(0),winwidth/2+0.7,winheight/2-1.5,0.8,0.4,"����(ESC)")){
			Beep(BN_Frequency,BN_Duration); 
			MainMenuStatus = 0;
			MainButton();
		} 
	} 
	if(MainMenuStatus == 4){
    	SetPenColor(HotKeyFont);
		/*static char b[10] = "";
		sprintf(b,"%d",GetFont());
		drawLabel(winwidth/2-1,winheight/2+0.9, b); */
		//�����ǹ�����һЩ��ֵ 
		cancelTimer(0);
		cancelTimerEvent();
		cancelMouseEvent();
		displaymoney();
		registerMouseEvent(MouseEventmoney);
	}
	if(MainMenuStatus == 5){
		SetPointSize(24);
		SetPenColor(SelectColor);
		drawLabel(winwidth/2-1.5,winheight/2+1.8,"��ѡ����Ϸ��ʼģʽ"); 
		SetPointSize(13);
		drawRec(winwidth/2 - 2,winheight/2 - 1.5,4,3,0.1,SelectColor,"White");
		if(button(GenUIID(0),winwidth/2-1.2,winheight/2+0.1,2.4,1,"����Ϸ")){
			Beep(B_Frequency,B_Duration); 
			MainMenuStatus = 1;
			MainButton();
		} 
		else if(suser.save_exist == 1&&button(GenUIID(0),winwidth/2-1.2,winheight/2-1.1,2.4,1,"�浵")){
			Beep(B_Frequency,B_Duration); 
			//cancelCharEvent();
			//cancelKeyboardEvent(); 
			//cancelMouseEvent();
			StartSaveGame(); 
  			for(i=0;i<20;i++)
    			for(j=0;j<10;j++){
    				SetPenColor("GRAY");
        			MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	    			DrawLine(0, BSIZE);
	    			DrawLine(BSIZE, 0);
	    			DrawLine(0, -BSIZE);
	    			DrawLine(-BSIZE, 0);
				}
		
 			registerTimerEvent(TimerEventProcess);
 			registerKeyboardEvent(KeyBoardEventProcess);
 			startTimer(1,500-nSelectSpeed*100);
 			startTimer(2,50);
   			startTimer(3,10);
		} 
		else if((suser.save_exist == 0||suser.save_exist == -1)&&button(GenUIID(0),winwidth/2-1.2,winheight/2-1.1,2.4,1,"δ�浵")){
			Beep(BN_Frequency,BN_Duration); 
		} 
		else if(button(GenUIID(0),winwidth/2-0.6,winheight/2-2.1,1.2,0.4,"����")){
			Beep(BN_Frequency,BN_Duration); 
			MainMenuStatus = 0;
			MainButton();
		} 
		else if(suser.save_exist == 1){
			char timedisplay[50] = "";
			readsave(suser.name);
			sprintf(timedisplay,"%d-%d-%d %d:%d:%d",ssave.time[0], ssave.time[1], ssave.time[2], ssave.time[3], ssave.time[4], ssave.time[5]);
			SetPenColor("White");
			drawLabel(winwidth/2-0.6,winheight/2-0.9,timedisplay);
		}
	}
}
void loginUI()
{
	winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
	double h = GetFontHeight() * 2;
	static char nametype[50] = "";
	static char passwordtype[50] = "";
	static char name[50] = "";
	static char password[50] = "";
	double w = TextStringWidth("Sampling")*4; // �ؼ����
	double x = winwidth / 2 - w / 2; //fH/8;
	double y = winheight / 2 + h * 4;
	
	drawPixel(x - 2.5,y - 0.8,0.1,pixelnum);
	drawTitle(x - 3,y + 0.4,0.08,titlenum);
	SetPointSize(40);
	drawLabel(3.5, 5.0, "����˹����(Tetris)1.0.10");
	SetPointSize(13);
	setButtonColors(SelectColor, "white", HotKeyColor, HotKeyFont, 1);
	drawRec(3.5, 2.5-h*2.5, 5.0, h * 9.5, 1, SelectColor, SelectColor);
	SetPenColor("White"); 
	setTextBoxColors("White", "White", HotKeyColor, HotKeyFont, 0);
	if(loginstatus == 0)
		drawLabel(3.8, 4.3, "�����������û����������¼��Ϸ");
	if(loginstatus == 1)
		drawLabel(3.8, 4.3, "���������������������");
	if(loginstatus == 2)
		drawLabel(3.8, 4.3, "��������û���������");
	if(registerstatus){
		if(registerstatus == 1)
			drawLabel(3.8, 4.3, "�������û���������ע����Ϸ");
		if(registerstatus == 2)
			drawLabel(3.8, 4.3, "��������û�����ע��");
		if(registerstatus == 3)
			drawLabel(3.8, 4.3, "�û��������벻��Ϊ��");
		drawLabel(3.8, 4.3 - h * 1.5, "�û���"); 
		drawLabel(3.8, 4.3 - h * 3, "����"); 
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 2, 2.0, h, nametype, sizeof(nametype)))
			sprintf(name,"%s", nametype);
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 3.5, 2.0, h, passwordtype, sizeof(passwordtype)))
			sprintf(password,"%s", passwordtype);
		if(button(GenUIID(0),3.8, 4.3 - h * 5, 0.5, h, "ע��")){
			if((registerstatus = (registeruser(name, password)))== 0){
				Beep(BN_Frequency,BN_Duration); 
				sprintf(nametype,"%s", "");
				sprintf(passwordtype,"%s", "");
				sprintf(name,"%s", "");
				sprintf(password,"%s", "");
				registerstatus = 2;
			}
			else if(registerstatus == 2 ||registerstatus == 3){
				Beep(BN_Frequency,BN_Duration); 
				registerstatus = 3;
			}
			else{
				Beep(B_Frequency,B_Duration); 
				user_guest = 1;
				MainMenuStatus = 0;
				sprintf(nametype,"%s", "");
				sprintf(passwordtype,"%s", "");
				sprintf(name,"%s", "");
				sprintf(password,"%s", "");
				cancelKeyboardEvent();
				cancelCharEvent();
				cancelMouseEvent();
			}
		} 
		if(button(GenUIID(0),3.8 + 1.0, 4.3 - h * 5, 1.0, h, "���ص�¼")){
			Beep(BN_Frequency,BN_Duration); 
			sprintf(nametype,"%s", "");
			sprintf(passwordtype,"%s", "");
			sprintf(name,"%s", "");
			sprintf(password,"%s", "");
			loginstatus = 0;
			registerstatus = 0;
		} 
	}
	if(registerstatus == 0){
		drawLabel(3.8, 4.3 - h * 1.5, "�û���"); 
		drawLabel(3.8, 4.3 - h * 3, "����"); 
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 2, 2.0, h, nametype, sizeof(nametype)))
				sprintf(name,"%s", nametype);
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 3.5, 2.0, h, passwordtype, sizeof(passwordtype)))
				sprintf(password,"%s", passwordtype);
		
		if(button(GenUIID(0),3.8, 4.3 - h * 5, 0.5, h, "��¼")){
			if((loginstatus = login(name, password)) == 1){
				Beep(B_Frequency,B_Duration); 
				
				if(!strcmp(suser.Color,"Orange")){
					strcpy(SelectColor,"ORANGE");
					strcpy(HotKeyColor,"RED");
    				strcpy(HotKeyFont,"YELLOW"); 
					SetCustomColor(0); 
				}
				else if(!strcmp(suser.Color,"Violet")){
					strcpy(SelectColor,"Violet"); 
					strcpy(HotKeyColor,"Violet7");
    				strcpy(HotKeyFont,"White");
    				SetCustomColor(1);
				}
				else if(!strcmp(suser.Color,"Black")){
					strcpy(SelectColor,"BLACK"); 
    				strcpy(HotKeyColor,"GRAY");
    				strcpy(HotKeyFont,"WHITE");
    				SetCustomColor(2);
				}
				user_guest = 1;
				MainMenuStatus = 0;
				sprintf(nametype,"%s", "");
				sprintf(passwordtype,"%s", "");
				sprintf(name,"%s", "");
				sprintf(password,"%s", "");
				cancelKeyboardEvent();
				cancelCharEvent();
				cancelMouseEvent();
			}
			if(loginstatus == 2){
				Beep(BN_Frequency,BN_Duration); 
				loginstatus = 1;
				sprintf(passwordtype,"%s", "");
			}
			if(loginstatus == 0){
				Beep(BN_Frequency,BN_Duration); 
				loginstatus = 2;
				sprintf(nametype,"%s", "");
				sprintf(passwordtype,"%s", "");
			}
		} 
		if(button(GenUIID(0),3.8 + 1.0, 4.3 - h * 5, 1.0, h, "ע�����û�")){
			Beep(B_Frequency,B_Duration); 
			sprintf(nametype,"%s", "");
			sprintf(passwordtype,"%s", "");
			sprintf(name,"%s", "");
			sprintf(password,"%s", "");
			loginstatus = 3;
			registerstatus = 1;
		} 
		if(button(GenUIID(0),3.8 + 2.5, 4.3 - h * 5, 1.0, h, "���ο͵�¼")){
			Beep(B_Frequency,B_Duration); 
			loginstatus = -1; 
			sprintf(suser.name,"%s","Guest");
			user_guest = 0;
			suser.money = 10;
			suser.save_exist = 0; 
			MainMenuStatus = 0;
			sprintf(nametype,"%s", "");
			sprintf(passwordtype,"%s", "");
			sprintf(name,"%s", "");
			sprintf(password,"%s", "");
			cancelKeyboardEvent();
			cancelCharEvent();
			cancelMouseEvent();
		} 
	} 
	if(button(GenUIID(0),3.8, 4.3 - h * 7.2, 1.6, 0.5, "�˳�")){
		Beep(BN_Frequency,BN_Duration); 
		exit(-1);
	} 
	
}
void displayUser()
{
	double h = GetFontHeight() * 2;
	static char displaymoney[50] = "";
	//double w = TextStringWidth("Sampling")*4; // �ؼ����
	double x = winwidth;
	double y = winheight;
	drawRec(x-1.5,y-h*2.4,1.5,h*2.4,0,"White","White");
	drawRec(x-1.5,y-h*2.4,1.5,h*2.4,0,SelectColor,SelectColor);
	SetPenColor("White"); 
	if(user_guest == 0){
		drawLabel(x-1.3,y-h, "�ο�"); 
		sprintf(displaymoney,"��ң�%d",suser.money);
		drawLabel(x-1.3,y-h*1.8, displaymoney); 
	}
	if(user_guest == 1){
		drawLabel(x-1.3,y-h, suser.name); 
		sprintf(displaymoney,"��ң�%d",suser.money);
		drawLabel(x-1.3,y-h*1.8, displaymoney); 
	}
	if(MainMenuStatus == 0){
		if(button(GenUIID(0),x - 1.5, y - h * 3.6, 1.0, h, "�˳���¼")){
			Beep(BN_Frequency,BN_Duration); 
			registerCharEvent(CharEventProcess2);
			registerKeyboardEvent(KeyboardEventProcess5);
			registerTimerEvent(PixelProcess);
			strcpy(SelectColor,"ORANGE");
			strcpy(HotKeyColor,"RED");
    		strcpy(HotKeyFont,"YELLOW"); 
			SetCustomColor(0); 
			MainMenuStatus = -1;
			loginstatus = 0;
			registerstatus = 0;
		} 
	}
}
/**********************************************************
 *  ��Ϸ��������洦���� 
 **********************************************************/
void MouseEventmoney(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event);
	  displaymoney();
	  
}
void displaymoney(){
	int i,j;
	DisplayClear();
	displayUser();
	addmoney=0; 
	if(button(GenUIID(0),1,5,2,1,"��ֵ10���")) { addmoney=10; Beep(B_Frequency,B_Duration); }
	if(button(GenUIID(0),3.5,5,2,1,"��ֵ20���")) {addmoney=20; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),6,5,2,1,"��ֵ50���")) {addmoney=50; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),1,3.5,2,1,"��ֵ100���")) {addmoney=100; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),3.5,3.5,2,1,"��ֵ200���")) {addmoney=200; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),6,3.5,2,1,"��ֵ500���")) {addmoney=500;Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),8,1,1,0.5,"����(ESC)")) {
		Beep(BN_Frequency,BN_Duration); 
		cancelMouseEvent();
		registerMouseEvent(MouseEventProcess); 
		MainMenuStatus=0;
		registerTimerEvent(PixelProcess);
		startTimer(0,500);
		display();
	} 
	if(addmoney!=0){
	Mainmoney(addmoney);
	registerTimerEvent(TimerMoney);
	cancelMouseEvent();
	startTimer(0,500);
	}
}
void TimerMoney(int timerID){
		static int a=0;
		static int time=0;
		switch(timerID){
	case 0:
		{ 
		SetPenColor("BLACK");
	    drawRectangle(4+(a%6)*0.3,0.6,0.2,0.2,1);
		a++;
		time++;
		if(a%6==0){
				SetPenColor("white");
	    drawRectangle(4,0.6,2,0.2,1);
	    Beep(GB_Frequency,GB_Duration);
		}
		if(time>=10){
			suser.money += addmoney;
			UpdateUserStatus(); 
			cancelTimer(0);
			cancelTimerEvent();
				a=0;
				time=0;
			registerMouseEvent(MouseEventmoney);
			SetPenColor("black");
			drawLabel(3,0.4,"��ֵ�ɹ����ƶ���������ֵ�򷵻أ�");
		}
		break;
		}

}}
void Mainmoney(int admy){
	int i,j;
	char addmoney[5]={0};
	char m[100]={"��ѡ����ǳ�ֵ"}; 
	char n[100]={"���,��ɨ���ά��֧�������ڵȴ���̨�������������ĵȴ�1min����"};
	 itoa(admy,addmoney,10);
	SetPenColor("Black");
	drawLabel(1,1,strcat(strcat(m,addmoney),n));
	drawQR(3.9,3.0,0.05);
/*	SetPenColor("BLACK");
	 for(i=0;i<=32;i++)
   for(j=0;j<=32;j++)  if(fangkuai[i][j]) drawRectangle(5.5-0.05*j,3-0.05*i,0.05,0.05,1);      
*/
}

void display2()
{
	
	//���²��ִ�����ҵ÷ֱ��� 
/**********************************************************
 *  1.0.4�汾��ʽ������������÷֡����򲢱���÷� 
 **********************************************************/
	double fH = GetFontHeight();
	double h = fH*2; // �ؼ��߶�
	static char result[50] = "";
	static char type[50] = "Your Name";
	static char name[50] = "Unname";
	static char status[50] = ""; 
	static int comfirmed = 0; 
	static int rankstatus = 0;
	displayUser();
	
	if(loginstatus == -1){
		if(!comfirmed){
			setTextBoxColors("White", "White", HotKeyColor, HotKeyFont, 0);
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			sprintf(result,"�������յ÷��ǣ�%d",nScore);
			SetPenColor("White"); 
			drawLabel(3.2, 2, result);
 		
			drawLabel(3.2, 2 - h, "������������Ӣ�ģ��Ա���÷�"); 
			if(textbox(GenUIID(0), 3.2, 2 - h*2.5, 1, h, type, sizeof(type)))
				sprintf(name,"%s", type);
			if(button(GenUIID(2),4.5,2 - h*2.5,0.5,h,"ȷ��")){
				Beep(B_Frequency,B_Duration); 
				rankstatus = inputRank(name, nScore);
    			if(rankstatus>0){
    				comfirmed = 1;
				} 
				if(rankstatus<0){
					comfirmed = 3;
					if(rankstatus == -4)
						comfirmed = 2; 	
				}
			}
		}
	
		if(comfirmed == 1){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "����ɹ�");
    		sprintf(status,"�ܹ���%d���ɼ�",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
		if(comfirmed == 2){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "ֻ�ܴ���20���ɼ�");
    		drawLabel(3.2, 2 - h, "�����ĳɼ�̫��");
		}
		if(comfirmed == 3){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "����ʧ��");
    		sprintf(status,"������룺%d",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
	}	
	if(loginstatus != -1){
		if(!comfirmed){
			setTextBoxColors("White", "White", HotKeyColor, HotKeyFont, 0);
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			sprintf(result,"�������յ÷��ǣ�%d",nScore);
			SetPenColor("White"); 
			drawLabel(3.2, 2, result);
			drawLabel(3.2, 2 - h*1.2, "�Ƿ񱣴汾���ɼ�");
 			sprintf(name,"%s*",suser.name); 
			if(button(GenUIID(2),3.8,2 - h*2.5,0.5,h,"����")){
				Beep(B_Frequency,B_Duration); 
				rankstatus = inputRank(name, nScore); 
    			if(rankstatus>0){
    				comfirmed = 1;
				} 
				if(rankstatus<0){
					comfirmed = 3;
					if(rankstatus == -4)
						comfirmed = 2; 
				}
			}
		}
	
		if(comfirmed == 1){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "����ɹ�");
    		sprintf(status,"�ܹ���%d���ɼ�",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
		if(comfirmed == 2){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "ֻ�ܴ���20���ɼ�");
    		drawLabel(3.2, 2 - h, "�����ĳɼ�̫��");
		}
		if(comfirmed == 3){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "����ʧ��");
    		sprintf(status,"������룺%d",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
	}	
	
    if(button(GenUIID(0),1,5,1,0.5,"������Ϸ")){
    	Beep(B_Frequency,B_Duration); 
    	cancelCharEvent();
		cancelMouseEvent(); 
		cancelKeyboardEvent(); 
		MainMenuStatus = 1;
		comfirmed = 0;
		rankstatus = 0; 
		display();
		
	} 
	else if(button(GenUIID(1),1,4,1,0.5,"����")){
		Beep(BN_Frequency,BN_Duration); 
		cancelCharEvent();
		cancelMouseEvent(); 
		cancelKeyboardEvent(); 
		MainMenuStatus = 0;
		startTimer(0,500);
		registerTimerEvent(PixelProcess);
		comfirmed = 0;
		rankstatus = 0; 
        display();
    }
    
}
/**********************************************************
 *  ��Ϸ��ͣʱ���洦���� 
 **********************************************************/ 
void display3()
{
	int i, j;
    if(button(GenUIID(0),1,6.3,1,0.5,"������Ϸ!")){
    	Beep(B_Frequency,B_Duration); 
		//MainMenuStatus = 0;
		//registerTimerEvent(PixelProcess);
		//startTimer(0,500);
		
		//��¼�浵����ʱ�� 
		time_t t;//��t����Ϊʱ����� 
		struct tm *p;//struct tm��һ���ṹ�壬����һ���ṹ��ָ�� 
		time(&t); 
		p=localtime(&t);//��õ��ص�ʱ�� 
		
		//EraseBlock(nCurrent_block_index,nOriginX,nOriginY);//!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		strcpy(ssave.name, suser.name);
		ssave.Level = nSpeed;
		ssave.Score = nScore;
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){
				ssave.GameBoard[i][j] = GameBoard[i][j];
				strcpy(ssave.GameBoardColor[i][j],GameBoardColor[i][j]);
			}
		}
		ssave.nNext_block_index = nNext_block_index;
		ssave.nCurrent_block_index = nCurrent_block_index;
		suser.save_exist = 1;
		ssave.time[0] = 1900+p->tm_year;
		ssave.time[1] = 1+p->tm_mon;
		ssave.time[2] = p->tm_mday;
		ssave.time[3] = p->tm_hour;
		ssave.time[4] = p->tm_min;
		ssave.time[5] = p->tm_sec;
		UpdateUserStatus();
		if(inputsave()){
			drawRec(2.9, 6.2, 2.7, 0.6, 0, SelectColor, SelectColor);
			SetPenColor("White"); 
			drawLabel(3.1, 6.44, "����ɹ�!");
			char timedisplay[50] = "";
			sprintf(timedisplay,"%d-%d-%d %d:%d:%d",ssave.time[0], ssave.time[1], ssave.time[2], ssave.time[3], ssave.time[4], ssave.time[5]);
			drawLabel(4.0,6.44,timedisplay);
			
		}
		drawRec(1,3.9,1.5,3,0,"white","white");
		
		//cancelKeyboardEvent();
		//display();
		//nOriginX=4;
		//nOriginY=5;
	} 
	else if(button(GenUIID(0),1,5.5,1,0.5,"ȷ���˳�?")){
		Beep(BN_Frequency,BN_Duration); 
		cancelCharEvent();
		cancelMouseEvent(); 
		cancelKeyboardEvent(); 
		MainMenuStatus = 0;
		registerTimerEvent(PixelProcess);
		startTimer(0,500);
		cancelKeyboardEvent();
		display();
		nOriginX=4;
		nOriginY=5;
	} 
	else if(button(GenUIID(0),1,4.7,1,0.5,"������Ϸ!")){
		Beep(B_Frequency,B_Duration); 
        cancelMouseEvent();
        startTimer(0,500);
		//registerTimerEvent(PixelProcess);
		drawRec(1,3.9,1.5,3,0,"white","white");
		drawRec(2.9, 6.2, 2.7, 0.6, 0, "White", "White");
		//DisplayClear();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//initboard(); 
		startTimer(1,500-(nSpeed-1)*100);
		startTimer(2,50);
		startTimer(3,1);
        }	
        
	else if(button(GenUIID(0),1,3.9,1,0.5,"���¿�ʼ!")){
		Beep(B_Frequency,B_Duration); 
        cancelMouseEvent();
        startTimer(0,500);
		//registerTimerEvent(PixelProcess);
		drawRec(0,3.9,1.5,3,0,"white","white");
		//DisplayClear();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    StartGame(); 
		nOriginX=4;
		nOriginY=5 ;
		startTimer(1,500-(nSpeed-1)*100);
		startTimer(2,50);
		startTimer(3,1);
        } 
    
}
/**********************************************************
 *  ��Ϸѡ���Ѷ�ʱ���洦���� 
 **********************************************************/ 
void displayselect(){
	char nOriginSpeedLevel[10]={0};
	char m[100]={"��ǰ�Ѷ�Ϊ��"}; 
	char n[100]={"��ǰ��ɫΪ��"};
	DisplayClear();
    SetPenColor("Black"); 
	drawLabel(3.2,2.6,"����200���");
	drawLabel(3.2,3.6,"����200���");
	drawLabel(3.2,4.6,"����200���");
	displayUser();
	setButtonColors(SelectColor, "white", HotKeyColor, HotKeyFont, 1);
    if(button(GenUIID(0),3,2,1.5,0.5,"BLACK")&&suser.money>=200){
    	Beep(B_Frequency,B_Duration); 
		strcpy(SelectColor,"BLACK"); 
    	strcpy(HotKeyColor,"GRAY");
    	strcpy(HotKeyFont,"WHITE");
    	SetCustomColor(2);
    	strcpy(suser.Color,"Black");
    	suser.money -= 200;
    	UpdateUserStatus();
    	displayUser();
	}
	if(button(GenUIID(0),3,3,1.5,0.5,"VIOLET")&&suser.money>=200){
		Beep(B_Frequency,B_Duration); 
		strcpy(SelectColor,"Violet"); 
		strcpy(HotKeyColor,"Violet7");
    	strcpy(HotKeyFont,"White");
    	SetCustomColor(1);
    	strcpy(suser.Color,"Violet");
    	suser.money -= 200;
    	UpdateUserStatus();
    	displayUser();
	} 	
	if(button(GenUIID(0),3,4,1.5,0.5,"ORANGE")&&suser.money>=200){
		Beep(B_Frequency,B_Duration); 
		strcpy(SelectColor,"ORANGE");
		strcpy(HotKeyColor,"RED");
    	strcpy(HotKeyFont,"YELLOW"); 
		SetCustomColor(0); 
    	strcpy(suser.Color,"Orange");
    	suser.money -= 200;
    	UpdateUserStatus();
    	displayUser();
	}  
	setTextBoxColors(SelectColor, "BLACK", HotKeyColor, HotKeyFont, 0);
	textbox(GenUIID(0), 3, 0.8, 2, statusheight-1.5,"", 0);
	textbox(GenUIID(0), 3, 0.8, 2, statusheight-1.5,strcat(n,SelectColor), 0);
	textbox(GenUIID(0),6, 6, statuswidth, statusheight-1.5, "�汾�ţ�1.0.10", 0);    
	SetPenColor("BLACK"); 
	drawLabel(4.8, 5.5,"������˹���鹲��4���Ѷȵȼ�,��Ϸ����˵�����£�" );
	drawLabel(4.8, 5,"1������һ�е�100�֣�ͬʱ�������л��ж���ӷ�\n");
	drawLabel(4.8, 4.5,"2�������Ѷȵȼ������ӣ�ÿ����һ�еõ��ķ������мӳ�\n");
	drawLabel(4.8, 4,"3����CTRL�����Ի���5+5*����������һ�еķ���"); 
	drawLabel(4.8, 3.5,"�����������£�");
	drawLabel(4.8, 3,"�����------���ƶ���˹����������ƶ�����ת");
	drawLabel(4.8, 2.5,"�ո��------һ������");
	drawLabel(4.8, 2," ESC��------�˳���Ϸ");    
	drawLabel(1,6, " ��ѡ����Ϸ�Ѷȣ�"); 
	drawLabel(3,5, " ��ѡ�������ɫ��"); 
	if(button(GenUIID(0),1,2,1.5,0.5,"level 4")){
		Beep(B_Frequency,B_Duration); 
		nSelectSpeed=4; 
	}   
	if(button(GenUIID(0),1,3,1.5,0.5,"level 3")){
		Beep(B_Frequency,B_Duration); 
		nSelectSpeed=3;
	} 
	if(button(GenUIID(0),1,4,1.5,0.5,"level 2")){
		Beep(B_Frequency,B_Duration); 
		nSelectSpeed=2;
	}  
	if(button(GenUIID(0),1,5,1.5,0.5,"level 1")){
		Beep(B_Frequency,B_Duration); 
		nSelectSpeed=1;
	}  
			itoa(nSelectSpeed,nOriginSpeedLevel,10);
		    textbox(GenUIID(0), 1, 0.8, statuswidth, statusheight-1.5,"", 0);
			textbox(GenUIID(0), 1, 0.8, statuswidth, statusheight-1.5,strcat(m,nOriginSpeedLevel), 0);
	
  

		if(button(GenUIID(0),8,1,1,0.5,"����(ESC)")){
			Beep(BN_Frequency,BN_Duration); 
			MainMenuStatus = 0;
			registerTimerEvent(PixelProcess);
			startTimer(0,500);
			display();
		} 
		
			    
}

/**********************************************************
 *  ��Ϸǰ������Լ������������� 
 **********************************************************/
 /**********************************************************
 *  ��Ϸǰ����
 **********************************************************/
void MainButton()
{  

	//SetFont("����"); 
	//SetPointSize(13); 
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess3);
	setButtonColors(SelectColor, "white", HotKeyColor, HotKeyFont, 1);

	//double fH = GetFontHeight() * 2;
	double h = GetFontHeight() * 3; // �ؼ��߶�
	double w = TextStringWidth("Sampling")*4; // �ؼ����
	double x = winwidth / 2 - w / 2; //fH/8;
	double y = winheight / 2 + h * 4;
	displayUser();
	if(button(GenUIID(0),x,y,w,h,"��ʼ��Ϸ(F1)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 5;
	} 
	if(button(GenUIID(1),x,y - h * 2,w,h,"ѡ��Ͱ���(F2)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 2;
	} 
	if(button(GenUIID(2),x,y - h * 4,w,h,"���а�(F3)")){
		Beep(B_Frequency,B_Duration); 
		readRank();
		rankpage = 1;
		MainMenuStatus = 3;
	} 
	if(button(GenUIID(3),x,y - h * 6,w,h,"��ֵ(F4)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 4;
	} 
	if(button(GenUIID(4),x,y - h * 8,w,h,"�˳�(F5)")){
		Beep(BN_Frequency,BN_Duration); 
		exit(-1);
	} 
	drawPixel(x - 2.5,y - 2,0.1,pixelnum);
	drawTitle(x - 3,y - 0.8,0.08,titlenum);
} 
void PixelProcess(int timerID)
{
	switch(timerID){
		case 0:{
			pixelnum = (pixelnum+1)%2;
			titlenum = (titlenum+1)%30;
			break;
		}
	}
	display();
}
void DrawSquare(double x, double y)
{
	drawRectangle(3+BSIZE*y,1+BSIZE*(19-x),BSIZE,BSIZE,1);
}
void drawRec(double x, double y, double width, double height, double thickness, char* outercolor, char* innercolor)
{

	SetPenColor(outercolor);
	drawRectangle(x, y, width, height, 1);
	SetPenColor(innercolor);
	drawRectangle(x + thickness, y + thickness, width - thickness * 2, height - thickness * 2, 1);
}
int displayRank(int page)
{
	struct score getRank;
	static char rankinfo[30] = "";
	static char rankscore[10] = ""; 
	static double h = 0.3;
	drawRec(winwidth/2-2,winheight/2-2,4,4,1,SelectColor,SelectColor);
    drawRec(winwidth/2-1.8,winheight/2-1.8,3.6,3.6,0.03,"WHITE",SelectColor);
    SetPenColor("White");
	drawLabel(winwidth/2-1,winheight/2+1.2, "���а񣨴�*Ϊע���û���"); 
    drawLabel(winwidth/2-1,winheight/2+0.9, "����   ����   ����"); 
    int d = 0, i;
    for(i = (page - 1) * 5; i < page * 5; i++){
    	if(srank[i].rank == 0){
    		drawLabel(winwidth/2-1,winheight/2 + 0.5 - h * d, "---   ---   ---"); 
    		return 0;
		}
		if(srank[i].rank){
			sprintf(rankinfo,"%-3d %s",srank[i].rank, srank[i].name);
			sprintf(rankscore,"%-6d",srank[i].score);
			drawLabel(winwidth/2-1,winheight/2 + 0.5 - h * d, rankinfo); 
			drawLabel(winwidth/2,winheight/2 + 0.5 - h * d, rankscore); 
		}
		d++;
	}
	return 1;
}
/**********************************************************
 *  ��Ϸ���̴������� 
 **********************************************************/
/**********************************************************
 *  ��Ϸ�����е�ʱ�䴦���� 
 **********************************************************/
void TimerEventProcess(int timerID)
{
  	int i,j;
   	switch(timerID){
	case 0:
		{
		pixelnum = (pixelnum+1)%2;
		drawGamePixel();
		break;
		}
	case 1:
	    {
	    displayUser();
    	bottom=HandleDown(nCurrent_block_index,&nOriginX,&nOriginY);
		break;
		}
    case 2:
   		{
  			if(nNext_block_index==-1)
        	{
            	nCurrent_block_index =RandomInteger(0,18);
            	nNext_block_index = RandomInteger(0,18);
            	/*������һ����ʾ��״*/
            	DrawBlock(nNext_block_index,7.15,4.25);
             	bottom=FALSE;
        	}
  			if(bottom==TRUE||bottom2==TRUE)
			{ 
            nCurrent_block_index = nNext_block_index;
            EraseBlock(nNext_block_index, 7.15,4.25); /* ����ԭ������ʾ��״ */
            nNext_block_index = RandomInteger(0,18);
            DrawBlock(nNext_block_index, 7.15,4.25); /*������һ����ʾ��״ */
            bottom=FALSE;
            bottom2=FALSE;
			nOriginX=4, nOriginY=5;
			DrawBlock(nCurrent_block_index,nOriginX,nOriginY);  
      		}/*������ڻ��Ƶ�ǰ��״*/
		}
	case 3:
	 	for(i=0;i<20;i++)
    		for(j=0;j<10;j++){
    	   		SetPenColor("GRAY");
              	MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	         	DrawLine(0, BSIZE);
	         	DrawLine(BSIZE, 0);
	         	DrawLine(0, -BSIZE);
	         	DrawLine(-BSIZE, 0);
			}
	}	
}
void drawGamePixel()
{
	double h = GetFontHeight() * 3; // �ؼ��߶�
	double w = TextStringWidth("Sampling")*4; // �ؼ����
	double dx = winwidth / 2 - w / 2; //fH/8;
	double dy = winheight / 2 + h * 4;

	drawRec(dx - 2.8,dy - 4.4,1,2.5,0,"White","White");
	drawPixel(dx - 2.8,dy - 2,0.1,animelenth?pixelnum+1:pixelnum);
	drawRec(dx - 2.6,dy - 5*0.1 - 1,7*0.1,7*0.1,0,"White","White");
	drawRec(dx - 3.3,dy - 0.92 + 1 - 7 * 0.08,26 * 0.08,9 * 0.08,0,"White","White");
	if(animelenth){
    	drawWord(dx - 3.3,dy - 0.92 + 1,0.08,pixelnum);
    	drawHeart(dx - 2.6,dy - 1,0.1,pixelnum);
    	animelenth--;
	}
}
/**********************************************************
 *  ��Ϸ��ͣ�Ĵ����� 
 **********************************************************/
void wait()
{
	int i,j;
	cancelKeyboardEvent();
	registerKeyboardEvent(KeyboardEventProcess4);
   	PauseNum++;
	if(PauseNum%2==1){
		cancelTimer(1);
		cancelTimer(2);
		cancelTimer(3);
		
		SetPenColor(SelectColor); 
		drawRec(2.5, 3, 3.5, 1, 1,SelectColor,SelectColor);
		setTextBoxColors(SelectColor, "WHITE", HotKeyColor, HotKeyFont, 0);
		textbox(GenUIID(0), 3.75, 3.25, 1, 0.5, "    PAUSE", 0);
	}
	else{
		drawRec(2.5, 3, 3.5, 1, 1,"WHITE","WHITE");
		drawRec(2.9, 0.9, boardwidth, boardheight, 0.1, SelectColor, "white");
		DrawBlock(nCurrent_block_index,nOriginX,nOriginY);
		
		for(i=0;i<20;i++)
            for(j=0;j<10;j++){
    	     	SetPenColor("GRAY");
              	MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	         	DrawLine(0, BSIZE);
	         	DrawLine(BSIZE, 0);
	         	DrawLine(0, -BSIZE);
	         	DrawLine(-BSIZE, 0);
			} 
	    for(i=19;i>=0;i--)
        	for(j=0;j<10;j++){
 				if(GameBoard[i][j]){
 				SetPenColor(GameBoardColor[i][j]);
				drawRectangle(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,1);
			} 
        }
		startTimer(1,500-nSpeed*100);
		startTimer(2,50);
		startTimer(3,1);
	}
}
/**********************************************************
 *  ��Ϸ���洦�� 
 **********************************************************/
void initboard() //��ʼ����Ϸ���� 
{   char speedlevel[10];
    char n[100]={"     speed:  level "};
    char s[100] = "";
	//int i,j;
  	/*for(i=0;i<20;i++)
    for(j=0;j<10;j++){
    	strcpy(GameBoardColor[i][j],ssave.GameBoardColor[i][j]);
	}*/
	char spend[50] = "";
	sprintf(spend,"level%d������%d��Ǯ",nSpeed,5+5*nSpeed);
	drawRec(2.9, 0.9, boardwidth, boardheight, 0.1, SelectColor, "white");
	drawRec(6.9, 3.9, statuswidth, statusheight, 0.1, SelectColor, "white");
	setTextBoxColors(SelectColor, SelectColor,SelectColor, SelectColor, 0);
	sprintf(s,"        score:  %d",nScore);
   	textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5,s, 0);
   	itoa(nSpeed,speedlevel,10);
	textbox(GenUIID(0), 6.9, 2.25, statuswidth, statusheight-1.5, strcat(n,speedlevel), 0);
	SetPointSize(15);
	drawLabel(6.9, 1.8, "�����ײ㣺ctrl��");
	drawLabel(6.9, 1.5, spend);
	drawLabel(6.9, 1.2, "һ�����䣺�ո��");
	drawLabel(6.9, 0.9, "���أ�    ESC��");
	SetPointSize(13);
}
void StartGame() //��Ϸ��ֵ��ʼ�� 
{
    int i,j;
	/*������Ϸ�����ÿ������ĳ�ʼֵ*/
    Randomize(); 
    
    for(i=0;i<20;i++)
        for(j=0;j<10;j++){
        	GameBoard[i][j] = 0;
        	strcpy(GameBoardColor[i][j],"WHITE");
		}
    DisplayClear();
nSpeed = nSelectSpeed;
	initboard();
    /*������Ϸ�����ĳ�ֵ*/
	
	/*��Ϸ��ʼ��û����һ����״��������*/
    nCurrent_block_index= RandomInteger(0,18);
    nNext_block_index = -1; 
 
    nScore = 0;
     drawRec(6.9, 3, statuswidth, statusheight-1.5, 0, "WHITE","WHITE");
		SetPenColor(SelectColor);
	textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5, "        score:  0", 0);
    nSpeedUpScore=800;
    PauseNum=0;
}
void StartSaveGame() //�Ӵ浵��ʼ����Ϸ��ֵ��ʼ�� 
{
	cancelCharEvent();
	cancelMouseEvent(); 
	cancelKeyboardEvent(); 
	cancelTimerEvent();
	readsave(suser.name);
    int i,j;
    Randomize();
	/*������Ϸ�����ÿ������ĳ�ʼֵ*/
    //Randomize(); 
    DisplayClear();
    /*������Ϸ�����ĳ�ֵ*/
	
	/*��Ϸ��ʼ��*/
	nOriginX=4, nOriginY=5;
    nCurrent_block_index= ssave.nCurrent_block_index;
    nNext_block_index = ssave.nNext_block_index;
    nSpeed = ssave.Level;
    nScore = ssave.Score;
    nSpeedUpScore = 0;
    switch(ssave.Level){
    	case 1:nSpeedUpScore+=800;
    	case 2:nSpeedUpScore+=2000;
    	case 3:nSpeedUpScore+=3000;
    	case 4:nSpeedUpScore+=4000;
    	case 5:nSpeedUpScore+=5000;
    	break;
	}
    PauseNum=0;
    initboard();
    for(i=0;i<20;i++)
        for(j=0;j<10;j++){
        	GameBoard[i][j] = ssave.GameBoard[i][j];
        	strcpy(GameBoardColor[i][j],ssave.GameBoardColor[i][j]);
		}
    drawGameBoard();
    DrawBlock(nNext_block_index, 7.15,4.25);
    registerTimerEvent(TimerEventProcess);
}
void drawGameBoard()
{
	int i, j;
	for(i=0;i<20;i++)
    	for(j=0;j<10;j++){
    		if(GameBoard[i][j])
    			drawRec(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,0,GameBoardColor[i][j],GameBoardColor[i][j]);
    	   	SetPenColor("GRAY");
            MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	        DrawLine(0, BSIZE);
	        DrawLine(BSIZE, 0);
	        DrawLine(0, -BSIZE);
	        DrawLine(-BSIZE, 0);
		}
}
void DrawBlock(int BlockIndex, double sx, double sy)   //����״���� 
{
    int i;
   
    for(i=0;i<7;i+=2){
        SetPenColor(shapes[BlockIndex].color); 
		drawRectangle(BSIZE*shapes[BlockIndex].box[i]+sx,BSIZE*shapes[BlockIndex].box[i+1]+sy,BSIZE,BSIZE,1);
		SetPenColor("GRAY");
  		DrawLine(0, BSIZE);
		DrawLine(BSIZE, 0);
		DrawLine(0, -BSIZE);
		DrawLine(-BSIZE, 0);
		strcpy(GameBoardColor[(int)(19-((sy-1)/BSIZE+shapes[BlockIndex].box[i+1]))][(int)(((sx-3)/BSIZE+shapes[BlockIndex].box[i]))],shapes[BlockIndex].color);	
	}

}     
void EraseBlock(int BlockIndex, double sx, double sy)   //�����״���� 
{
    int i;
    for(i=0;i<7;i+=2){
        SetPenColor("white"); 
		drawRectangle(BSIZE*shapes[BlockIndex].box[i]+sx,BSIZE*shapes[BlockIndex].box[i+1]+sy,BSIZE,BSIZE,1);
	 	SetPenColor("WHITE");
  		DrawLine(0, BSIZE);
		DrawLine(BSIZE, 0);
		DrawLine(0, -BSIZE);
		DrawLine(-BSIZE, 0);
		strcpy(GameBoardColor[(int)(19-((sy-1)/BSIZE+shapes[BlockIndex].box[i+1]))][(int)(((sx-3)/BSIZE+shapes[BlockIndex].box[i]))],"WHITE");
	}
}     
/**********************************************************
 *  ��Ϸ����
 **********************************************************/
 void HandleLeft(int BlockIndex,double *x, double *y) /*���������ʱ�Ĵ�����*/
{
    if(!IsConflict(BlockIndex,*x-BSIZE,*y)){
        EraseBlock(BlockIndex,*x,*y); /*����ԭ�ȵ���״*/
        *x=*x-BSIZE;
        DrawBlock(BlockIndex,*x,*y); /*���Ƶ�ǰ��״*/
    }
}
void HandleRight(int BlockIndex,double *x, double *y)/*�����ҷ����ʱ�Ĵ�����*/
{

    if(!IsConflict(BlockIndex,*x+BSIZE,*y)){
        EraseBlock(BlockIndex,*x,*y); /*����ԭ�ȵ���״*/
        *x=*x+BSIZE;
        DrawBlock(BlockIndex, *x, *y); /*���Ƶ�ǰ��״*/
    }
}
void HandleUp(int *BlockIndex,double *x, double *y) /*������ת��ʱ�Ĵ�����*/
{
    int NextBlockIndex, i;
    NextBlockIndex = shapes[*BlockIndex].next;  
		for(i=0;i<5;i++)
			if(!IsConflict(NextBlockIndex,*x,*y)){
        		EraseBlock(*BlockIndex, *x, *y); /*����ԭ�ȵ���״*/
        		*BlockIndex = shapes[*BlockIndex].next;
        		DrawBlock(*BlockIndex, *x, *y); /*���Ƶ�ǰ��״*/
			} 
}
int HandleDown(int BlockIndex,double *x, double *y)/*�����·��������������ʱ�Ĵ�����*/
{    
	char ScoreBuffer[100]={0},SpeedBuffer[100]={0};
	char n[100]={"        score:  "};
	char m[100]={"     speed:  level "};
	char spend[50] = "";
	
    int i,j;
    int Num=0;
    
    if(!IsConflict(BlockIndex,*x,*y-BSIZE)) /*��������*/
	{
        EraseBlock(BlockIndex,*x,*y); /*����ԭ�ȵ���״*/
        *y=*y-BSIZE;
        DrawBlock(BlockIndex, *x,*y); /*���Ƶ�ǰ��״*/
        judge=0;
		return FALSE;/*�������䷵��FALSE*/
    }
    else /*�޷���������*/
    {   judge=1;
		DrawBlock(BlockIndex,*x,*y);
		for (i=0;i<=7;i+=2){ 
			GameBoard[(int)(19-((*y-1)/BSIZE+shapes[BlockIndex].box[i+1]))][(int)(((*x-3)/BSIZE+shapes[BlockIndex].box[i]))]=1;
		} 
		for(i=20;i>=4;i=i-4){
          	Num=Num+KillLines(i); 
		}
		if(Num>0){
            animelenth = 6;
			switch(Num){ 
				case 0:
                	break;
                case 1:
                    nScore+=(100+(nSpeed-1)*50);
                    break;
                case 2:
                    nScore+=(300+(nSpeed-1)*50);
                    break;
                case 3:
                    nScore+=(500+(nSpeed-1)*50);
                    break;
                case 4:
                    nScore+=(800+(nSpeed-1)*50);
                    break;
            }
            itoa(nScore,ScoreBuffer,10);
            drawRec(6.9, 3, statuswidth, statusheight-1.5, 0, "WHITE","WHITE");
			SetPenColor(SelectColor);
			textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5, strcat(n,ScoreBuffer), 0);
			Beep(GS_Frequency,GS_Duration);
		}
  		if(nScore >= nSpeedUpScore)
    	{
        	if(nSpeed<=4){
			nSpeed++;
        	nSpeedUpScore+= nSpeed*1000;
        	itoa(nSpeed,SpeedBuffer,10);         
    		drawRec(6.9, 2.25, statuswidth, statusheight-1.5, 0, "White","White");
			SetPenColor(SelectColor);
			textbox(GenUIID(0), 6.9, 2.25, statuswidth, statusheight-1.5, strcat(m,SpeedBuffer), 0);
			drawRec(6.9,1.45,2.0,0.3,0,"White","White");
			sprintf(spend,"level%d������%d��Ǯ",nSpeed,5+5*nSpeed);
			SetPenColor(SelectColor);
			drawLabel(6.9, 1.5, spend);
			cancelTimer(1);
			startTimer(1,500-nSpeed*100);
			Beep(GS_Frequency,GS_Duration);
  			}
		}
		if(IsGameOver())
		{
        	cancelTimerEvent();
        	cancelKeyboardEvent();
        	SetPenColor(HotKeyFont); 
			drawRec(2.5, 3, 3.5, 1, 1,HotKeyColor,HotKeyColor);
			setTextBoxColors("WHITE", "BLACK", "BLACK", "WHITE", 0);
			textbox(GenUIID(0), 3.75, 3.25, 1, 0.5, "GAME OVER", 0);
			suser.money += (nScore/50);
			UpdateUserStatus();
			registerCharEvent(CharEventProcess);
			registerMouseEvent(MouseEventProcess2); 
			registerKeyboardEvent(KeyboardEventProcess2); 
			Beep(GN_Frequency,GN_Duration);
			
			button(GenUIID(0),1,5,1,0.5,"������Ϸ");
			button(GenUIID(1),1,4,1,0.5,"����");
		}
	return TRUE;   /*���䵽�׷���TRUE*/
 	}
}
int SpaceDown(int BlockIndex,double *x,double *y){
		char ScoreBuffer[100]={0},SpeedBuffer[100]={0};
	char n[100]={"        score:  "};
	char m[100]={"     speed:  level "};
	double j;
	int i;
	int Num=0;
	for(j=5;j>=0;j=j-BSIZE){
		if(IsConflict(BlockIndex,*x,j)){
			j=j+BSIZE;
		    EraseBlock(BlockIndex,*x,*y); 
	for (i=0;i<=7;i+=2)  GameBoard[(int)(19-((*y-1)/BSIZE+shapes[BlockIndex].box[i+1]))][(int)(((*x-3)/BSIZE+shapes[BlockIndex].box[i]))]=0;
			DrawBlock(BlockIndex,*x,j);
	for (i=0;i<=7;i+=2)  GameBoard[(int)(19-((j-1)/BSIZE+shapes[BlockIndex].box[i+1]))][(int)(((*x-3)/BSIZE+shapes[BlockIndex].box[i]))]=1;
		
		for(i=20;i>=4;i=i-4)  Num=Num+KillLines(i); 
		if(Num>0){
            switch(Num){ 
				case 0:
                	break;
                case 1:
                    nScore+=(100+(nSpeed-1)*50);
                    break;
                case 2:
                    nScore+=(300+(nSpeed-1)*50);
                    break;
                case 3:
                    nScore+=(500+(nSpeed-1)*50);
                    break;
                case 4:
                    nScore+=(800+(nSpeed-1)*50);
                    break;
            }
            itoa(nScore,ScoreBuffer,10);
            drawRec(6.9, 3, statuswidth, statusheight-1.5, 0, "WHITE","WHITE");
			SetPenColor("Orange");
			textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5, strcat(n,ScoreBuffer), 0);
		}
		
	  return 1;
		}
	}
	
}
/**********************************************************
 *  ��Ϸ�����е��ж� 
 **********************************************************/
int IsConflict(int BlockIndex,double sx, double sy) 
{
    int i;
    for (i=0;i<=7;i+=2)
    {
        if (shapes[BlockIndex].box[i]*BSIZE+sx<3 || shapes[BlockIndex].box[i]*BSIZE+sx>5.25)        //�жϺ����ұ߽��Ƿ��ͻ����ͻ�򷵻�1 
            return TRUE; 
        if (shapes[BlockIndex].box[i+1]*BSIZE+sy<1)    //�жϺ��±߽��Ƿ��ͻ����ͻ�򷵻�1 
            return TRUE; 
        if (GameBoard[(int)(19-(shapes[BlockIndex].box[i+1]+(sy-1)/BSIZE))][(int)(shapes[BlockIndex].box[i]+(sx-3)/BSIZE)])   //�жϸø������Ƿ����з��� gameboard����ԭʼ���ݾ�Ϊ0 
            return TRUE;
    }
    return FALSE;
}
int IsLineFull(int y)
{
    int i;
    for(i=0;i<10;i++)
        if(!GameBoard[y-1][i])
            return FALSE;
    return TRUE;
}
void KillLine(int y)
{
    int i,j;
    for(i=y-1;i>=1;i--)
        for(j=0;j<10;j++)
        {
            if(GameBoard[i][j]==GameBoard[i-1][j]){
                continue;
			}
            else if(GameBoard[i-1][j]==1)
            {
                GameBoard[i][j]=1 ;
            }
            else /*Gameboard[i][j-1]==EMPTY*/
            {
                GameBoard[i][j] = 0;
            }
        }
 	for(i=y-1;i>=1;i--)
        for(j=0;j<10;j++)
        {
			if(GameBoardColor[i][j]==GameBoardColor[i-1][j]){
                continue;
			}
        	else /*Gameboard[i][j-1]==EMPTY*/
            {
                strcpy(GameBoardColor[i][j],GameBoardColor[i-1][j]);
            }
		}
	for(i=y-1;i>=0;i--)
        for(j=0;j<10;j++){
            if(GameBoard[i][j])
			{
            	SetPenColor(GameBoardColor[i][j]);
            	drawRectangle(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,1); 
			}
            else 
			{
	         	SetPenColor("WHITE");
             	drawRectangle(3+BSIZE*j,1+BSIZE*(19-i),BSIZE,BSIZE,1);	
			} 
		}
    for(i=y-1;i>=0;i--)
        for(j=0;j<10;j++){
            if(GameBoard[i][j])
			{
              	SetPenColor("GRAY");
              	MovePen(3+BSIZE*j,1+BSIZE*(19-i));
	         	DrawLine(0, BSIZE);
	         	DrawLine(BSIZE, 0);
	         	DrawLine(0, -BSIZE);
	         	DrawLine(-BSIZE, 0);
			}
		}
}
int KillLines(int y)
{
    int i, j, LinesKilled=0;
    for(i=0;i<4;i++)
    {
        while(IsLineFull(y))
        {
            KillLine(y);
            LinesKilled++;
            i++;
        }
        y--;
        if(y<1)
            break;
    }
    return LinesKilled;
} 
int IsGameOver()
{
    int i;
    for(i=0;i<10;i++)
        if(GameBoard[0][i]){ 
         	return TRUE;
        } 
    return FALSE;
}
