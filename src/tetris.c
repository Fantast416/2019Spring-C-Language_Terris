#include "tetris.h"
/*1.0.0以及1.0.1版本为工程初期程序 
/*1.0.2版本更新内容如下：
 1、新增选择速度等级功能
 2、修复加速下落无法消除的bug
 3、修复暂停后会加速下落的bug
 */ 
 /*1.0.3版本更新内容如下：
 1、新增换肤功能
 2、修改了pause时可以移动方块的bug 
 3、增加了游戏说明 （在选项中） 
 4、 修复一直按住旋转键到底部误消除的bug
 */  
 /*1.0.4版本更新内容如下：
 1、增加了排行榜模块，排名数据保存在exe目录下的rank.exe中
 //难点：rank相关读写文件函数的设计，1）readrank读取排名文件的排名信息到全局变量srank，使用正常的遍历文件并读取操作 
 //2）inputrank插入游戏结束时获得的排名信息，先读取文件中的排名信息，因为只有<=20个排名，且一定是排好名的，使用数组储存信息并且采用插入排序法，再将数组内的排名数据fprintf到文件中 
 2、增加了颜色选择，优化了主体颜色选择
 3、增加了游戏说明（在游戏中） 
 /*1.0.5版本更新内容如下：
 1、增加了开始界面的动画效果
 2、修复了选项更改颜色及时显示的问题 
 3、修复了加速下落无法消掉的bug
 /*1.0.6版本更新内容如下：
 1、增加登陆界面
 2、增加用户系统以及相关联的金钱系统 
 3、修改ESC界面按键的位置
 4、解决注册空字符串用户的问题 
 5、保存界面 
 /*1.0.7版本更新内容如下：
 1、添加音乐
 2、修复了用户保存函数以及用户更新函数以及存档保存函数的若干bug
 3、将GameBoardColor的储存类型由地址类型更改到数组类型，考虑到跨文件以及再次打开程序的地址随机分配问题
 4、增加了快捷键功能
 5、排行榜备注游客和用户的区别 
 6、增加了登录界面的返回按键，美化了登录界面  
 /*1.0.8版本更新内容如下： 
 1、解决再次打开游戏一键下落有很大问题很大问题 ！！！（每次退出游戏把各种Event取消掉，否则会调出结束画面） 
 2、解决一键下落和xx键一起按下的问题！！！（用VK_DOWN的循环代替SpaceDown函数） 
 3、解决读取存档后重开游戏的问题 
 4、丰富了游戏界面以及方块的颜色 
 5、增加了存档的保存时间记录以及显示功能
 6、修改了TimerEventProcess的逻辑结构，用if-else if结构代替switch结构 
 7、解决了充值之后的更新用户数据的问题 
 /*1.0.9版本更新内容如下：
 1、美化了保存界面（活动方块不需要消失），读取存档时间也不会不能刷新掉 
 2、解决了从存档开始游戏不显示下一个方块的问题 
 3、用户自动保存选择的颜色方案 
 4、保存成功将显示保存时间以及保存成功提示 
 5、用户选择颜色需要花费200金币，并且会实时显示用户信息在选择界面 
 6、完善了快捷键功能，1）将快捷键标注在按键上2）解决了按下快捷键后需要移动鼠标才能刷新的问题3）增加了MainButton的二级目录的ESC返回功能 
 /*1.0.10版本更新内容如下：2019/6/14
 1、优化游戏音乐体验，默认BGM是在Tetris/BGM目录下的BGM.wav，增加了游戏中的音效 
 2、更改了用户数据以及存档数据以及排行榜数据的存储位置，作为独立exe时更方便读取这些文件
  
 6/14日工作计划：
 2、优化游戏音乐 
 1、考虑删除一些无用的函数spacedown  
 6、考虑游戏左右边界的方块旋转问题 
 3、考虑增加双人模式？
 4、考虑增加局域网联机双人模式？
 5、增加动画效果？ 

/**********************************************************
 *  全局变量组 
 **********************************************************/
extern double winwidth, winheight;		// 窗口尺寸
extern int selected_lable;
extern int MainMenuStatus;
extern int nScore;                     	//分数 
extern int nSpeed;                	//速度等级 
extern int nSelectSpeed;   			//选择速度等级 
extern int nSpeedUpScore;				//晋级速度 
extern int bottom;						//是否到达底部0/1 
extern int bottom2;                    	//一键落地时是否到达底部0/1 
extern int nNext_block_index;			//下一个方块类型 
extern int nCurrent_block_index;		//现在的方块类型编码 
extern double nOriginX;					//现在的x/y值 
extern double nOriginY;
extern int GameBoard[20][10];					//游戏板 
extern char GameBoardColor[20][10][15];
extern int KeyDown; 
extern int PauseNum;                    //用于暂停函数中的计数 
extern int judge;                    	//用于修复加速下落无法消除的bug，来进行判断的变量 
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
};								//排行榜数组 

extern struct score srank[20];

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
 *  游戏方块储存数组 
 **********************************************************/
struct SHAPE
{
	int box[8];
	char color[15];
	/*每个游戏方块的颜色*/
	int next;
	/*下个游戏方块的编号*/
};

struct SHAPE shapes[MAX_BOX]=
{
	//■□□□    ■■■□    ■■□□    □□□□  
	//■□□□    ■□□□    □■□□    □□■□
    //■■□□    □□□□    □■□□    ■■■□
    //□□□□    □□□□    □□□□    □□□□
      
	{0,1,0,2,0,3,1,1,"CYAN",1},
	{0,2,0,3,1,3,2,3,"CYAN",2},
	{0,3,1,3,1,2,1,1,"CYAN",3},
	{0,1,1,1,2,1,2,2,"CYAN",0},

    //□■□□    ■□□□    ■■□□    ■■■□
    //□■□□    ■■■□    ■□□□    □□■□
    //■■□□    □□□□    ■□□□    □□□□
    //□□□□    □□□□    □□□□    □□□□

	{0,1,1,1,1,2,1,3,"MAGENTA",5},
	{0,2,0,3,1,2,2,2,"MAGENTA",6},
	{0,1,0,2,0,3,1,3,"MAGENTA",7},
	{0,3,1,3,2,3,2,2,"MAGENTA",4},

    //■□□□    □■■□    
    //■■□□    ■■□□    
    //□■□□    □□□□    
    //□□□□    □□□□    

	{0,3,0,2,1,2,1,1,"YELLOW",9},
	{0,2,1,2,1,3,2,3,"YELLOW",8},

    //□■□□    ■■□□    
    //■■□□    □■■□
    //■□□□    □□□□    
    //□□□□    □□□□

	{0,1,0,2,1,2,1,3,"BROWN",11},
	{0,3,1,3,1,2,2,2,"BROWN",10},
	
    //□■□□    ■□□□    ■■■□    □■□□
    //■■■□    ■■□□    □■□□    ■■□□
    //□□□□    ■□□□    □□□□    □■□□
    //□□□□    □□□□    □□□□    □□□□

	{0,2,1,2,1,3,2,2,"GREEN",13},
	{0,1,0,2,0,3,1,2,"GREEN",14},
	{0,3,1,3,1,2,2,3,"GREEN",15},
	{0,2,1,1,1,2,1,3,"GREEN",12},

    //■□□□    ■■■■    
    //■□□□    □□□□
    //■□□□    □□□□    
    //■□□□    □□□□

	{0,0,0,1,0,2,0,3,"RED",17},
	{0,1,1,1,2,1,3,1,"RED",16},

    //■■□□   
    //■■□□  
	//□□□□   
    //□□□□   

	{0,2,0,3,1,2,1,3,"BlUE",18},
};
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
 **********************************************************/
/**********************************************************
 *  游戏过程中的键盘处理函数 
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
				    	     //用于修复下落到底时一直按住下落键会有未消除的情况（由于按键一直处于DOWN状态，导致无法跳出Keyboardevent进行判定） 
					}
					//tm让VK_DOWN的情况不停循环直到触底不就行了，整这么多有的没的干什么！！！！ 记得把SpaceDown删了，还有drawGameBoard也删了。 
					
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
					if(!IsConflict(shapes[nCurrent_block_index].next,nOriginX,nOriginY)&&judge==0)   //用于修复下落到底时一直按住旋转键会有误消除的情况 
						HandleUp(&nCurrent_block_index,&nOriginX,&nOriginY);
						//Beep(GB_Frequency,GB_Duration); 
				}
				else if(key == VK_DOWN){
					if(bottom==1)
						break;     //用于修复下落到底时一直按住下落键会有未消除的情况（由于按键一直处于DOWN状态，导致无法跳出Keyboardevent进行判定） 
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
					button(GenUIID(0),1,6.3,1,0.5,"保存游戏!");
                    button(GenUIID(0),1,5.5,1,0.5,"确定退出?"); 
                    button(GenUIID(0),1,4.7,1,0.5,"继续游戏!");
                    button(GenUIID(0),1,3.9,1,0.5,"重新开始!");
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
    //drawGameBoard();//如果不用，把drawGameBoard函数也一并删除 
}
/**********************************************************
 *  游戏结束后的键盘输入处理函数 
 **********************************************************/
 
void KeyboardEventProcess2(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display2(); // 刷新显示
}
void KeyboardEventProcess3(int key, int event)   //主界面快捷键 
{
	uiGetKeyboard(key,event); // GUI获取键盘
   switch (event) {
 	  case KEY_DOWN:
		    switch(key)
            {
                case VK_F1: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 1;
				display(); 
					break;
				}   /*开始游戏快捷键*/
                case VK_F2: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 2;
				display();
					break; 
				} /*选项快捷键*/
                case VK_F3: {
                	Beep(B_Frequency,B_Duration); 
                readRank();
                rankpage = 1;
				MainMenuStatus = 3;
				display();
					break; 
				} /*排行榜快捷键*/
                case VK_F4: {
                	Beep(B_Frequency,B_Duration); 
				MainMenuStatus = 4;
				display();
					break; 
				} /*充值快捷键*/
                case  VK_F5: {
                	Beep(BN_Frequency,BN_Duration); 
			    exit(0);
				} /*退出快捷键*/               
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
void KeyboardEventProcess4(int key, int event)//为啥这里是4？？？？？ 
{
	uiGetKeyboard(key,event);
	 switch (event) {
 	  case KEY_DOWN:
		    switch(key)
            {
                case VK_SPACE:/*暂停*/
                    wait();
    cancelKeyboardEvent();
	registerKeyboardEvent(KeyBoardEventProcess);
					break;
	
}
case KEY_UP: 
   break;}}
void KeyboardEventProcess5(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}
   
/**********************************************************
 *  游戏结束后的字符输入处理函数 
 **********************************************************/
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display2(); //刷新显示
}
void CharEventProcess2(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}
/**********************************************************
 *  游戏开始前的鼠标处理函数 
 **********************************************************/
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display();
}
/**********************************************************
 *  游戏结束后的鼠标处理函数 
 **********************************************************/
void MouseEventProcess2(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display2();

}
/**********************************************************
 *  游戏暂停时的鼠标处理函数 
 **********************************************************/
void MouseEventProcess3(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display3();

}
void MouseEventProcessSelect(int x, int y, int button, int event)
{
	  uiGetMouse(x,y,button,event);
	 displayselect();
}


/**********************************************************
 *  界面显示处理函数组 
 *	display（处理游戏开始前的显示） 
 *	display2（处理游戏结束后的显示） 
 *	display3 （处理游戏暂停时的显示） 
 **********************************************************/
 /**********************************************************
 *  游戏开始前界面处理函数 
 **********************************************************/
void display()
{   
	int k=3;
	int i,j=0;
	// 清屏 
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
			if(rankpage<4&&button(GenUIID(0),winwidth/2-0.4,winheight/2-1.5,0.8,0.4,"下一页")){
				Beep(B_Frequency,B_Duration); 
				rankpage++; 
				display();
			} 
		}
		if(rankpage>1&&button(GenUIID(0),winwidth/2-1.5,winheight/2-1.5,0.8,0.4,"上一页")){
			Beep(B_Frequency,B_Duration); 
			rankpage--; 
			display();
			} 
		if(button(GenUIID(0),winwidth/2+0.7,winheight/2-1.5,0.8,0.4,"返回(ESC)")){
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
		//以上是供监视一些数值 
		cancelTimer(0);
		cancelTimerEvent();
		cancelMouseEvent();
		displaymoney();
		registerMouseEvent(MouseEventmoney);
	}
	if(MainMenuStatus == 5){
		SetPointSize(24);
		SetPenColor(SelectColor);
		drawLabel(winwidth/2-1.5,winheight/2+1.8,"请选择游戏开始模式"); 
		SetPointSize(13);
		drawRec(winwidth/2 - 2,winheight/2 - 1.5,4,3,0.1,SelectColor,"White");
		if(button(GenUIID(0),winwidth/2-1.2,winheight/2+0.1,2.4,1,"新游戏")){
			Beep(B_Frequency,B_Duration); 
			MainMenuStatus = 1;
			MainButton();
		} 
		else if(suser.save_exist == 1&&button(GenUIID(0),winwidth/2-1.2,winheight/2-1.1,2.4,1,"存档")){
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
		else if((suser.save_exist == 0||suser.save_exist == -1)&&button(GenUIID(0),winwidth/2-1.2,winheight/2-1.1,2.4,1,"未存档")){
			Beep(BN_Frequency,BN_Duration); 
		} 
		else if(button(GenUIID(0),winwidth/2-0.6,winheight/2-2.1,1.2,0.4,"返回")){
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
	double w = TextStringWidth("Sampling")*4; // 控件宽度
	double x = winwidth / 2 - w / 2; //fH/8;
	double y = winheight / 2 + h * 4;
	
	drawPixel(x - 2.5,y - 0.8,0.1,pixelnum);
	drawTitle(x - 3,y + 0.4,0.08,titlenum);
	SetPointSize(40);
	drawLabel(3.5, 5.0, "俄罗斯方块(Tetris)1.0.10");
	SetPointSize(13);
	setButtonColors(SelectColor, "white", HotKeyColor, HotKeyFont, 1);
	drawRec(3.5, 2.5-h*2.5, 5.0, h * 9.5, 1, SelectColor, SelectColor);
	SetPenColor("White"); 
	setTextBoxColors("White", "White", HotKeyColor, HotKeyFont, 0);
	if(loginstatus == 0)
		drawLabel(3.8, 4.3, "请输入您的用户名和密码登录游戏");
	if(loginstatus == 1)
		drawLabel(3.8, 4.3, "您输入的密码有误，请重试");
	if(loginstatus == 2)
		drawLabel(3.8, 4.3, "您输入的用户名不存在");
	if(registerstatus){
		if(registerstatus == 1)
			drawLabel(3.8, 4.3, "请输入用户名和密码注册游戏");
		if(registerstatus == 2)
			drawLabel(3.8, 4.3, "您输入的用户名已注册");
		if(registerstatus == 3)
			drawLabel(3.8, 4.3, "用户名或密码不能为空");
		drawLabel(3.8, 4.3 - h * 1.5, "用户名"); 
		drawLabel(3.8, 4.3 - h * 3, "密码"); 
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 2, 2.0, h, nametype, sizeof(nametype)))
			sprintf(name,"%s", nametype);
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 3.5, 2.0, h, passwordtype, sizeof(passwordtype)))
			sprintf(password,"%s", passwordtype);
		if(button(GenUIID(0),3.8, 4.3 - h * 5, 0.5, h, "注册")){
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
		if(button(GenUIID(0),3.8 + 1.0, 4.3 - h * 5, 1.0, h, "返回登录")){
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
		drawLabel(3.8, 4.3 - h * 1.5, "用户名"); 
		drawLabel(3.8, 4.3 - h * 3, "密码"); 
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 2, 2.0, h, nametype, sizeof(nametype)))
				sprintf(name,"%s", nametype);
		if(textbox(GenUIID(0), 4.5, 4.3 - h * 3.5, 2.0, h, passwordtype, sizeof(passwordtype)))
				sprintf(password,"%s", passwordtype);
		
		if(button(GenUIID(0),3.8, 4.3 - h * 5, 0.5, h, "登录")){
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
		if(button(GenUIID(0),3.8 + 1.0, 4.3 - h * 5, 1.0, h, "注册新用户")){
			Beep(B_Frequency,B_Duration); 
			sprintf(nametype,"%s", "");
			sprintf(passwordtype,"%s", "");
			sprintf(name,"%s", "");
			sprintf(password,"%s", "");
			loginstatus = 3;
			registerstatus = 1;
		} 
		if(button(GenUIID(0),3.8 + 2.5, 4.3 - h * 5, 1.0, h, "以游客登录")){
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
	if(button(GenUIID(0),3.8, 4.3 - h * 7.2, 1.6, 0.5, "退出")){
		Beep(BN_Frequency,BN_Duration); 
		exit(-1);
	} 
	
}
void displayUser()
{
	double h = GetFontHeight() * 2;
	static char displaymoney[50] = "";
	//double w = TextStringWidth("Sampling")*4; // 控件宽度
	double x = winwidth;
	double y = winheight;
	drawRec(x-1.5,y-h*2.4,1.5,h*2.4,0,"White","White");
	drawRec(x-1.5,y-h*2.4,1.5,h*2.4,0,SelectColor,SelectColor);
	SetPenColor("White"); 
	if(user_guest == 0){
		drawLabel(x-1.3,y-h, "游客"); 
		sprintf(displaymoney,"金币：%d",suser.money);
		drawLabel(x-1.3,y-h*1.8, displaymoney); 
	}
	if(user_guest == 1){
		drawLabel(x-1.3,y-h, suser.name); 
		sprintf(displaymoney,"金币：%d",suser.money);
		drawLabel(x-1.3,y-h*1.8, displaymoney); 
	}
	if(MainMenuStatus == 0){
		if(button(GenUIID(0),x - 1.5, y - h * 3.6, 1.0, h, "退出登录")){
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
 *  游戏结束后界面处理函数 
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
	if(button(GenUIID(0),1,5,2,1,"充值10金币")) { addmoney=10; Beep(B_Frequency,B_Duration); }
	if(button(GenUIID(0),3.5,5,2,1,"充值20金币")) {addmoney=20; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),6,5,2,1,"充值50金币")) {addmoney=50; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),1,3.5,2,1,"充值100金币")) {addmoney=100; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),3.5,3.5,2,1,"充值200金币")) {addmoney=200; Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),6,3.5,2,1,"充值500金币")) {addmoney=500;Beep(B_Frequency,B_Duration); } 
	if(button(GenUIID(0),8,1,1,0.5,"返回(ESC)")) {
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
			drawLabel(3,0.4,"充值成功！移动鼠标继续充值或返回！");
		}
		break;
		}

}}
void Mainmoney(int admy){
	int i,j;
	char addmoney[5]={0};
	char m[100]={"您选择的是充值"}; 
	char n[100]={"金币,请扫描二维码支付，正在等待后台程序反馈，请耐心等待1min左右"};
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
	
	//以下部分处理玩家得分保存 
/**********************************************************
 *  1.0.4版本正式可以做到输入得分、排序并保存得分 
 **********************************************************/
	double fH = GetFontHeight();
	double h = fH*2; // 控件高度
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
			sprintf(result,"您的最终得分是：%d",nScore);
			SetPenColor("White"); 
			drawLabel(3.2, 2, result);
 		
			drawLabel(3.2, 2 - h, "请输入姓名（英文）以保存得分"); 
			if(textbox(GenUIID(0), 3.2, 2 - h*2.5, 1, h, type, sizeof(type)))
				sprintf(name,"%s", type);
			if(button(GenUIID(2),4.5,2 - h*2.5,0.5,h,"确认")){
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
    		drawLabel(3.2, 2, "保存成功");
    		sprintf(status,"总共有%d条成绩",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
		if(comfirmed == 2){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "只能储存20条成绩");
    		drawLabel(3.2, 2 - h, "而您的成绩太低");
		}
		if(comfirmed == 3){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "保存失败");
    		sprintf(status,"错误代码：%d",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
	}	
	if(loginstatus != -1){
		if(!comfirmed){
			setTextBoxColors("White", "White", HotKeyColor, HotKeyFont, 0);
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			sprintf(result,"您的最终得分是：%d",nScore);
			SetPenColor("White"); 
			drawLabel(3.2, 2, result);
			drawLabel(3.2, 2 - h*1.2, "是否保存本条成绩");
 			sprintf(name,"%s*",suser.name); 
			if(button(GenUIID(2),3.8,2 - h*2.5,0.5,h,"保存")){
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
    		drawLabel(3.2, 2, "保存成功");
    		sprintf(status,"总共有%d条成绩",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
		if(comfirmed == 2){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "只能储存20条成绩");
    		drawLabel(3.2, 2 - h, "而您的成绩太低");
		}
		if(comfirmed == 3){
			drawRec(2.5, 0.8, 3.5, h*5, 1,SelectColor,SelectColor);
			SetPenColor("White"); 
    		drawLabel(3.2, 2, "保存失败");
    		sprintf(status,"错误代码：%d",rankstatus);
    		drawLabel(3.2, 2 - h, status);
		}
	}	
	
    if(button(GenUIID(0),1,5,1,0.5,"重新游戏")){
    	Beep(B_Frequency,B_Duration); 
    	cancelCharEvent();
		cancelMouseEvent(); 
		cancelKeyboardEvent(); 
		MainMenuStatus = 1;
		comfirmed = 0;
		rankstatus = 0; 
		display();
		
	} 
	else if(button(GenUIID(1),1,4,1,0.5,"返回")){
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
 *  游戏暂停时界面处理函数 
 **********************************************************/ 
void display3()
{
	int i, j;
    if(button(GenUIID(0),1,6.3,1,0.5,"保存游戏!")){
    	Beep(B_Frequency,B_Duration); 
		//MainMenuStatus = 0;
		//registerTimerEvent(PixelProcess);
		//startTimer(0,500);
		
		//记录存档保存时间 
		time_t t;//将t声明为时间变量 
		struct tm *p;//struct tm是一个结构体，声明一个结构体指针 
		time(&t); 
		p=localtime(&t);//获得当地的时间 
		
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
			drawLabel(3.1, 6.44, "保存成功!");
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
	else if(button(GenUIID(0),1,5.5,1,0.5,"确定退出?")){
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
	else if(button(GenUIID(0),1,4.7,1,0.5,"继续游戏!")){
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
        
	else if(button(GenUIID(0),1,3.9,1,0.5,"重新开始!")){
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
 *  游戏选择难度时界面处理函数 
 **********************************************************/ 
void displayselect(){
	char nOriginSpeedLevel[10]={0};
	char m[100]={"当前难度为："}; 
	char n[100]={"当前颜色为："};
	DisplayClear();
    SetPenColor("Black"); 
	drawLabel(3.2,2.6,"花费200金币");
	drawLabel(3.2,3.6,"花费200金币");
	drawLabel(3.2,4.6,"花费200金币");
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
	textbox(GenUIID(0),6, 6, statuswidth, statusheight-1.5, "版本号：1.0.10", 0);    
	SetPenColor("BLACK"); 
	drawLabel(4.8, 5.5,"本俄罗斯方块共分4个难度等级,游戏功能说明如下：" );
	drawLabel(4.8, 5,"1、消除一行得100分，同时消除多行会有额外加分\n");
	drawLabel(4.8, 4.5,"2、随着难度等级的增加，每消除一行得到的分数会有加成\n");
	drawLabel(4.8, 4,"3、按CTRL键可以花费5+5*金币消除最低一行的方块"); 
	drawLabel(4.8, 3.5,"按键设置如下：");
	drawLabel(4.8, 3,"方向键------控制俄罗斯方块的左右移动及旋转");
	drawLabel(4.8, 2.5,"空格键------一键下落");
	drawLabel(4.8, 2," ESC键------退出游戏");    
	drawLabel(1,6, " 请选择游戏难度："); 
	drawLabel(3,5, " 请选择界面颜色："); 
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
	
  

		if(button(GenUIID(0),8,1,1,0.5,"返回(ESC)")){
			Beep(BN_Frequency,BN_Duration); 
			MainMenuStatus = 0;
			registerTimerEvent(PixelProcess);
			startTimer(0,500);
			display();
		} 
		
			    
}

/**********************************************************
 *  游戏前后界面以及其他处理函数组 
 **********************************************************/
 /**********************************************************
 *  游戏前界面
 **********************************************************/
void MainButton()
{  

	//SetFont("黑体"); 
	//SetPointSize(13); 
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess3);
	setButtonColors(SelectColor, "white", HotKeyColor, HotKeyFont, 1);

	//double fH = GetFontHeight() * 2;
	double h = GetFontHeight() * 3; // 控件高度
	double w = TextStringWidth("Sampling")*4; // 控件宽度
	double x = winwidth / 2 - w / 2; //fH/8;
	double y = winheight / 2 + h * 4;
	displayUser();
	if(button(GenUIID(0),x,y,w,h,"开始游戏(F1)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 5;
	} 
	if(button(GenUIID(1),x,y - h * 2,w,h,"选项和帮助(F2)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 2;
	} 
	if(button(GenUIID(2),x,y - h * 4,w,h,"排行榜(F3)")){
		Beep(B_Frequency,B_Duration); 
		readRank();
		rankpage = 1;
		MainMenuStatus = 3;
	} 
	if(button(GenUIID(3),x,y - h * 6,w,h,"充值(F4)")){
		Beep(B_Frequency,B_Duration); 
		MainMenuStatus = 4;
	} 
	if(button(GenUIID(4),x,y - h * 8,w,h,"退出(F5)")){
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
	drawLabel(winwidth/2-1,winheight/2+1.2, "排行榜（带*为注册用户）"); 
    drawLabel(winwidth/2-1,winheight/2+0.9, "排名   名字   分数"); 
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
 *  游戏进程处理函数组 
 **********************************************************/
/**********************************************************
 *  游戏进程中的时间处理函数 
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
            	/*绘制下一个提示形状*/
            	DrawBlock(nNext_block_index,7.15,4.25);
             	bottom=FALSE;
        	}
  			if(bottom==TRUE||bottom2==TRUE)
			{ 
            nCurrent_block_index = nNext_block_index;
            EraseBlock(nNext_block_index, 7.15,4.25); /* 消除原来的提示形状 */
            nNext_block_index = RandomInteger(0,18);
            DrawBlock(nNext_block_index, 7.15,4.25); /*绘制下一个提示形状 */
            bottom=FALSE;
            bottom2=FALSE;
			nOriginX=4, nOriginY=5;
			DrawBlock(nCurrent_block_index,nOriginX,nOriginY);  
      		}/*在面板内绘制当前形状*/
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
	double h = GetFontHeight() * 3; // 控件高度
	double w = TextStringWidth("Sampling")*4; // 控件宽度
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
 *  游戏暂停的处理函数 
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
 *  游戏界面处理 
 **********************************************************/
void initboard() //初始化游戏界面 
{   char speedlevel[10];
    char n[100]={"     speed:  level "};
    char s[100] = "";
	//int i,j;
  	/*for(i=0;i<20;i++)
    for(j=0;j<10;j++){
    	strcpy(GameBoardColor[i][j],ssave.GameBoardColor[i][j]);
	}*/
	char spend[50] = "";
	sprintf(spend,"level%d将花费%d金钱",nSpeed,5+5*nSpeed);
	drawRec(2.9, 0.9, boardwidth, boardheight, 0.1, SelectColor, "white");
	drawRec(6.9, 3.9, statuswidth, statusheight, 0.1, SelectColor, "white");
	setTextBoxColors(SelectColor, SelectColor,SelectColor, SelectColor, 0);
	sprintf(s,"        score:  %d",nScore);
   	textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5,s, 0);
   	itoa(nSpeed,speedlevel,10);
	textbox(GenUIID(0), 6.9, 2.25, statuswidth, statusheight-1.5, strcat(n,speedlevel), 0);
	SetPointSize(15);
	drawLabel(6.9, 1.8, "消除底层：ctrl键");
	drawLabel(6.9, 1.5, spend);
	drawLabel(6.9, 1.2, "一键下落：空格键");
	drawLabel(6.9, 0.9, "返回：    ESC键");
	SetPointSize(13);
}
void StartGame() //游戏数值初始化 
{
    int i,j;
	/*设置游戏面板中每个方块的初始值*/
    Randomize(); 
    
    for(i=0;i<20;i++)
        for(j=0;j<10;j++){
        	GameBoard[i][j] = 0;
        	strcpy(GameBoardColor[i][j],"WHITE");
		}
    DisplayClear();
nSpeed = nSelectSpeed;
	initboard();
    /*设置游戏变量的初值*/
	
	/*游戏初始，没有下一个形状的索引号*/
    nCurrent_block_index= RandomInteger(0,18);
    nNext_block_index = -1; 
 
    nScore = 0;
     drawRec(6.9, 3, statuswidth, statusheight-1.5, 0, "WHITE","WHITE");
		SetPenColor(SelectColor);
	textbox(GenUIID(0), 6.9, 3, statuswidth, statusheight-1.5, "        score:  0", 0);
    nSpeedUpScore=800;
    PauseNum=0;
}
void StartSaveGame() //从存档开始的游戏数值初始化 
{
	cancelCharEvent();
	cancelMouseEvent(); 
	cancelKeyboardEvent(); 
	cancelTimerEvent();
	readsave(suser.name);
    int i,j;
    Randomize();
	/*设置游戏面板中每个方块的初始值*/
    //Randomize(); 
    DisplayClear();
    /*设置游戏变量的初值*/
	
	/*游戏初始，*/
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
void DrawBlock(int BlockIndex, double sx, double sy)   //画形状函数 
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
void EraseBlock(int BlockIndex, double sx, double sy)   //清除形状函数 
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
 *  游戏操作
 **********************************************************/
 void HandleLeft(int BlockIndex,double *x, double *y) /*按下左方向键时的处理函数*/
{
    if(!IsConflict(BlockIndex,*x-BSIZE,*y)){
        EraseBlock(BlockIndex,*x,*y); /*擦除原先的形状*/
        *x=*x-BSIZE;
        DrawBlock(BlockIndex,*x,*y); /*绘制当前形状*/
    }
}
void HandleRight(int BlockIndex,double *x, double *y)/*按下右方向键时的处理函数*/
{

    if(!IsConflict(BlockIndex,*x+BSIZE,*y)){
        EraseBlock(BlockIndex,*x,*y); /*擦除原先的形状*/
        *x=*x+BSIZE;
        DrawBlock(BlockIndex, *x, *y); /*绘制当前形状*/
    }
}
void HandleUp(int *BlockIndex,double *x, double *y) /*按下旋转键时的处理函数*/
{
    int NextBlockIndex, i;
    NextBlockIndex = shapes[*BlockIndex].next;  
		for(i=0;i<5;i++)
			if(!IsConflict(NextBlockIndex,*x,*y)){
        		EraseBlock(*BlockIndex, *x, *y); /*擦除原先的形状*/
        		*BlockIndex = shapes[*BlockIndex].next;
        		DrawBlock(*BlockIndex, *x, *y); /*绘制当前形状*/
			} 
}
int HandleDown(int BlockIndex,double *x, double *y)/*按下下方向键或自由下落时的处理函数*/
{    
	char ScoreBuffer[100]={0},SpeedBuffer[100]={0};
	char n[100]={"        score:  "};
	char m[100]={"     speed:  level "};
	char spend[50] = "";
	
    int i,j;
    int Num=0;
    
    if(!IsConflict(BlockIndex,*x,*y-BSIZE)) /*仍在下落*/
	{
        EraseBlock(BlockIndex,*x,*y); /*擦除原先的形状*/
        *y=*y-BSIZE;
        DrawBlock(BlockIndex, *x,*y); /*绘制当前形状*/
        judge=0;
		return FALSE;/*仍在下落返回FALSE*/
    }
    else /*无法再下落了*/
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
			sprintf(spend,"level%d将花费%d金钱",nSpeed,5+5*nSpeed);
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
			
			button(GenUIID(0),1,5,1,0.5,"重新游戏");
			button(GenUIID(1),1,4,1,0.5,"返回");
		}
	return TRUE;   /*下落到底返回TRUE*/
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
 *  游戏进程中的判断 
 **********************************************************/
int IsConflict(int BlockIndex,double sx, double sy) 
{
    int i;
    for (i=0;i<=7;i+=2)
    {
        if (shapes[BlockIndex].box[i]*BSIZE+sx<3 || shapes[BlockIndex].box[i]*BSIZE+sx>5.25)        //判断和左右边界是否冲突，冲突则返回1 
            return TRUE; 
        if (shapes[BlockIndex].box[i+1]*BSIZE+sy<1)    //判断和下边界是否冲突，冲突则返回1 
            return TRUE; 
        if (GameBoard[(int)(19-(shapes[BlockIndex].box[i+1]+(sy-1)/BSIZE))][(int)(shapes[BlockIndex].box[i]+(sx-3)/BSIZE)])   //判断该格子上是否本来有方块 gameboard数组原始数据均为0 
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
