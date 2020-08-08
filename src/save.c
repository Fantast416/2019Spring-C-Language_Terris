#include "tetris.h" 
struct baocun{
	int Level;   //等级 
	int Score;   //分数 
    int GameBoard[20][10];  //游戏版数据			
    char *GameBoardColor[20][10];  //游戏版数据
	int nNext_block_index;		//下一个方块类型 
    int nCurrent_block_index;
};


