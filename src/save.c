#include "tetris.h" 
struct baocun{
	int Level;   //�ȼ� 
	int Score;   //���� 
    int GameBoard[20][10];  //��Ϸ������			
    char *GameBoardColor[20][10];  //��Ϸ������
	int nNext_block_index;		//��һ���������� 
    int nCurrent_block_index;
};


