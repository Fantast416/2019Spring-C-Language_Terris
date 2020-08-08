#include "tetris.h"
/**********************************************************
 *  用户数据以及用户存档处理函数组 
 *	void Trim(char *src);							给定一个C-String的变量(非字面值常量)，去除首尾两端Blank的字符
 *  void SetCustomColor(int num);					设定游戏方块的颜色
 *  int login(char name[], char password[]);		处理用户的登录函数
 *  int registeruser(char name[], char password[]);	处理用户的注册函数
 *  void UpdateUserStatus();						更新用户数据函数
 *  int readsave(char name[]);						读取用户的存档函数
 *  int inputsave();								将前的用户的游戏状态存入存档文件
 **********************************************************/
struct SHAPE
{
	int box[8];
	char color[15];
	int next;
};

extern struct SHAPE shapes[MAX_BOX];

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

void Trim(char *src);

void SetCustomColor(int num)
{
	char PreSetColor[3][7][15] = {
	{"CYAN","MAGENTA","YELLOW","BROWN","GREEN","RED","BlUE"},
	{"Violet1","Violet2","Violet3","Violet4","Violet5","Violet6","Violet7",},
	{"Black1","Black2","Black3","Black4","Black5","Black6","Black7",}
	};
	int i;
	for(i = 0;i < 19;i++){
		switch(i){
			case 0:
			case 1:
			case 2:
			case 3: strcpy(shapes[i].color,PreSetColor[num][0]);break;
			case 4:
			case 5:
			case 6:
			case 7: strcpy(shapes[i].color,PreSetColor[num][1]);break;
			case 8:
			case 9: strcpy(shapes[i].color,PreSetColor[num][2]);break;
			case 10:
			case 11: strcpy(shapes[i].color,PreSetColor[num][3]);break;
			case 12:
			case 13:
			case 14:
			case 15: strcpy(shapes[i].color,PreSetColor[num][4]);break;
			case 16:
			case 17: strcpy(shapes[i].color,PreSetColor[num][5]);break;
			case 18: strcpy(shapes[i].color,PreSetColor[num][6]);break;
		}
	}
} 

int login(char name[], char password[])
{
	FILE *fp;
	struct User user;

	if ((fp = fopen("..\\Tetris\\Save\\user.txt", "r+")) == NULL) {
		return -1;/*提示打开文件失败*/
	}
	while (fscanf(fp, "%s%s%d%d%s /n", &user.name, &user.password, &user.money, &user.save_exist, &user.Color) != EOF) {
		if(!strcmp(name, user.name)){
			if(!strcmp(password, user.password)){
				suser = user;
				return 1;//登录成功 
			}
			else{
				return 2;//密码提示错误 
			}
		}
	}
	if (fclose(fp)) {
		return -2;/*提示无法关闭文件*/
	}
	return 0;//用户不存在 
}

int registeruser(char name[], char password[])
{
	FILE *fp;
	int status = 0; 
	Trim(name);
	Trim(password); 
	if(!strcmp(name,"")){
		return 2;//用户名不能为空 
	}
	if(!strcmp(password,"")){
		return 3;//密码不能为空 
	}
	if((status = login(name, password)) == 1||(status = login(name, password))== 2){
		return 0;//用户名已经注册 
	}
	if(!status){
		if((fp = fopen("..\\Tetris\\Save\\user.txt", "a+")) == NULL){
			return -1;//提示打开文件失败 
		}
		fprintf(fp, "%s %s %d %d %s\n", name, password, 10, 0, "Orange");
		if(fclose(fp)){
			return -2;//提示关闭文件失败
		}
		strcpy(suser.name, name);
		strcpy(suser.password, password);
		suser.money = 10;
		suser.save_exist = 0;
		strcpy(suser.Color,"Orange");
		return 1;//注册成功 
	}
	return status;//其他情况，debug使用 
} 

void UpdateUserStatus() {
	struct list {
		struct User user;
		struct list *next;
	};
	struct User user;
	FILE *fp;
	if ((fp = fopen("..\\Tetris\\Save\\user.txt", "r+")) == NULL) {
		return -1;//提示打开文件失败
	}
	struct list *head, *p, *s;
	int i, j;
	fscanf(fp, "%s %s %d %d %s /n ", &user.name, &user.password, &user.money, &user.save_exist, &user.Color);

	head = (struct list*)malloc(sizeof(struct list));
	p = head;
	if (!strcmp(suser.name,user.name)) {
		p->user = suser;
	}
	else {
		p->user = user;
	}
	p->next = NULL;
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d %d %s /n ", &user.name, &user.password, &user.money, &user.save_exist, &user.Color);
		s = (struct list*)malloc(sizeof(struct list));
		if (!strcmp(suser.name, user.name)) {
			s->user = suser;
		}
		else {
			s->user = user;
		}
		p->next = s;
		p = s;
	}
	p->next = NULL;

	if (fclose(fp)) {
		return -2;//提示关闭文件失败 
	}

	if ((fp = fopen("..\\Tetris\\Save\\user.txt", "w+")) == NULL) {
		return -3;//提示打开文件失败 
	}
	p = head;
	while (p->next != NULL) {
		fprintf(fp, "%s %s %d %d %s \n", p->user.name, p->user.password, p->user.money, p->user.save_exist, p->user.Color);
		p = p->next;
	}
	fprintf(fp, "%s %s %d %d %s \n", p->user.name, p->user.password, p->user.money, p->user.save_exist, p->user.Color);
	if (fclose(fp)) {
		return -4;//提示关闭文件失败 
	}
}

int readsave(char name[])
{
	struct Save save;
	FILE *fp;
	int i, j;
	if ((fp = fopen("..\\Tetris\\Save\\save.txt", "r")) == NULL) {
		return -1;//打开文件失败 
	}
	while (!feof(fp)) {
		fscanf(fp, "%s%d%d", &save.name, &save.Level, &save.Score);
		for (i = 0; i < 20; i++) {
			for (j = 0; j < 10; j++) {
				fscanf(fp, "%d", &save.GameBoard[i][j]);
			}
		}
		for (i = 0; i < 20; i++) {
			for (j = 0; j < 10; j++) {
				fscanf(fp, "%s", &save.GameBoardColor[i][j]);
			}
		}
		fscanf(fp, "%d%d", &save.nNext_block_index, &save.nCurrent_block_index);
		for(i = 0;i < 6;i++){
			fscanf(fp, "%d", &save.time[i]);
		}
		fscanf(fp, "\n");
		if (!strcmp(name, save.name)) {
			ssave = save;
			return 1;//读取到了存档 
		}
	}
	return 0;//不存在相应存档 	
}

/*int inputsave(){
	int exist = 0;
	FILE *fp;
	int i, j;
	if((fp = fopen("save.txt", "w+")) == NULL){
		return -3;//提示打开文件失败 
	}
	if(exist == 0){
		fprintf(fp, "%s %d %d\n", ssave.name, ssave.Level, ssave.Score);
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){
				fprintf(fp, "%d ", ssave.GameBoard[i][j]);
			}
		}
		fprintf(fp, "\n");
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){				
				fprintf(fp, "%s ", ssave.GameBoardColor[i][j]);
			}
		}
		fprintf(fp, "\n%d %d\n", ssave.nNext_block_index, ssave.nCurrent_block_index);
		
		if(fclose(fp)){
			return -4;//提示关闭文件失败 
		}
		return 1;//存入一个存档 
	}
}*/

int inputsave()
{
	static int exist = 1;
	static int input = 0;
	struct list{
		struct Save save;
		struct list *next;
	};
	struct Save save;
	FILE *fp;
	if((fp = fopen("..\\Tetris\\Save\\save.txt", "r+")) == NULL){
		return -1;//提示打开文件失败
	}
	struct list *head, *p, *s;
	int i, j;
	fscanf(fp, "\n");
	if(!feof(fp)){
		fscanf(fp, "%s%d%d", &save.name,  &save.Level, &save.Score);
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){
				fscanf(fp, "%d", &save.GameBoard[i][j]);
			}
		}
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){				
				fscanf(fp, "%s", &save.GameBoardColor[i][j]);
			}
		}
		fscanf(fp, "%d%d", &save.nNext_block_index, &save.nCurrent_block_index);
		for(i = 0;i < 6;i++){
			fscanf(fp, "%d", &save.time[i]);
		}
		fscanf(fp, "\n");
		
		head = (struct list*)malloc(sizeof(struct list));
		p = head;
		if(!strcmp(save.name,ssave.name)){
			p->save = ssave;
			input = 1;
		}
		else{
			p->save = save;
		}
		p->next = NULL;
		//fscanf(fp, "%s%d%d", &save.name,  &save.Level, &save.Score);
		while(!feof(fp)){
			fscanf(fp, "%s%d%d", &save.name,  &save.Level, &save.Score);
			for(i = 0;i < 20;i++){
				for(j = 0;j < 10;j++){
					fscanf(fp, "%d", &save.GameBoard[i][j]);
				}
			}
			for(i = 0;i < 20;i++){
				for(j = 0;j < 10;j++){				
					fscanf(fp, "%s", &save.GameBoardColor[i][j]);
				}
			}
			fscanf(fp, "%d%d", &save.nNext_block_index, &save.nCurrent_block_index);
			for(i = 0;i < 6;i++){
				fscanf(fp, "%d", &save.time[i]);
			}
			fscanf(fp, "\n");
		
			s = (struct list*)malloc(sizeof(struct list));
			if(!strcmp(save.name,ssave.name)){
				s->save = ssave;
				input = 1;
			}
			else{
				s->save = save;
			}
			p->next = s;
			p = s;
		}
		if(input == 0){
			s = (struct list*)malloc(sizeof(struct list));
			s->save = ssave;
			p->next = s;
			p = s;
		}
		p->next = NULL;
	}
	else{
		exist = 0;
	}
	
	
	if(fclose(fp)){
		return -2;//提示关闭文件失败 
	}
	
	if((fp = fopen("..\\Tetris\\Save\\save.txt", "w+")) == NULL){
		return -3;//提示打开文件失败 
	}
	if(exist == 0){
		fprintf(fp, "%s %d %d\n", ssave.name, ssave.Level, ssave.Score);
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){
				fprintf(fp, "%d ", ssave.GameBoard[i][j]);
			}
		}
		fprintf(fp, "\n");
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){				
				fprintf(fp, "%s ", ssave.GameBoardColor[i][j]);
			}
		}
		fprintf(fp, "\n%d %d\n", ssave.nNext_block_index, ssave.nCurrent_block_index);
		for(i = 0;i < 6;i++){
			fprintf(fp, "%d ", ssave.time[i]);
		}
		fprintf(fp, "\n");

		if(fclose(fp)){
			return -4;//提示关闭文件失败 
		}
		return 1;//存入一个存档 
	}
	p = head;
	while(p->next != NULL){
		fprintf(fp, "%s %d %d\n", p->save.name, p->save.Level, p->save.Score);
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){
				fprintf(fp, "%d ", p->save.GameBoard[i][j]);
			}
		}
		fprintf(fp, "\n");
		for(i = 0;i < 20;i++){
			for(j = 0;j < 10;j++){				
				fprintf(fp, "%s ", p->save.GameBoardColor[i][j]);
			}
		}
		fprintf(fp, "\n%d %d\n", p->save.nNext_block_index, p->save.nCurrent_block_index);
		for(i = 0;i < 6;i++){
			fprintf(fp, "%d ", p->save.time[i]);
		}
		fprintf(fp, "\n");
		p = p->next;
	}
	fprintf(fp, "%s %d %d\n", p->save.name, p->save.Level, p->save.Score);
	for(i = 0;i < 20;i++){
		for(j = 0;j < 10;j++){
			fprintf(fp, "%d ", p->save.GameBoard[i][j]);
		}
	}
	fprintf(fp, "\n");
	for(i = 0;i < 20;i++){
		for(j = 0;j < 10;j++){				
			fprintf(fp, "%s ", p->save.GameBoardColor[i][j]);
		}
	}
	fprintf(fp, "\n%d %d\n", p->save.nNext_block_index, p->save.nCurrent_block_index);
	for(i = 0;i < 6;i++){
			fprintf(fp, "%d ", p->save.time[i]);
		}
		fprintf(fp, "\n");
	if(fclose(fp)){
		return -4;//提示关闭文件失败 
	}
	return 1; 
}

/*****************************************************************************
  **  函数名称: Trim
  **  功能描述: 给定一个C-String的变量(非字面值常量)，去除首尾两端Blank的字符                                            
  **  当前版本:                                                                                                    
  **  作    者: JohnnyHu                                                                                    
  **  修    改：                                                                                                             
  **  输入参数: char *src   --->  带有'\0'的C-String
  **  输出参数: char *src       --->  格式化后(去除首尾两端Blank的字符)
  **  返回结果：无
  **  使用条件：非字母值常量的C-String变量
  ****************************************************************************/
void Trim(char *src)
{
    char *begin = src;
    char *end   = src;

    while ( *end++ ) {
        ; // Statement is null  
    }

    if ( begin == end ) return; 

    while ( *begin == ' ' || *begin == '\t' )          
        ++begin;
    while ( (*end) == '\0' || *end == ' ' || *end == '\t') 
        --end;

    if ( begin > end ) {
        *src = '\0';  return; 
    } 
    //printf("begin=%1.1s; end=%1.1s\n", begin, end);
    while ( begin != end ) {
        *src++ = *begin++;
    }

    *src++ = *end;
    *src = '\0';

    return;
}


/*if(user.save_exist){
			fscanf(fp, "%d%d", &user.save.Level, &user.save.Score);
			for(i = 0;i < 20;i++){
				for(j = 0;j < 10;j++){
					fscanf(fp, "%d", &user.save.GameBoard[i][j]);
				}
			}
			for(i = 0;i < 20;i++){
				for(j = 0;j < 10;j++){
					fscanf(fp, "%s", &user.save.GameBoardColor[i][j]);
				}
			}
			fscanf(fp, "%d%d", &user.save.nNext_block_index, &user.save.nCurrent_block_index);
		}*/ 
