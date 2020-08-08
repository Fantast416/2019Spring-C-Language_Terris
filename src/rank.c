#include "tetris.h" 
struct score {
	int rank;
	char name[50];
	int score;
};								//排行榜数组 

extern struct score srank[20];

int readRank(void) {
	FILE *fp;

	if ((fp = fopen("..\\Tetris\\Save\\rank.txt", "r+")) == NULL) {
		return -1;/*提示打开文件失败*/
	}
	int i = 0;
	while (fscanf(fp, "%d%s%d", &srank[i].rank, &srank[i].name, &srank[i].score) != EOF) {
		i++;
	}
	if (fclose(fp)) {
		return -2;/*提示无法关闭文件*/
	}
	return 0;
}

int inputRank(char name[], int score) {
	struct score s[21], s0;
	FILE *fp;
	int j, i, e, d;
	s0.rank = 1;
	strcpy(s0.name, name);
	s0.score = score;


	if ((fp = fopen("..\\Tetris\\Save\\rank.txt", "a+")) == NULL) {
		return -1;/*提示打开文件失败*/
	}
	i = 0;
	while (fscanf(fp, "%d%s%d", &s[i].rank, &s[i].name, &s[i].score) != EOF) {
		i++;
	}
	if (fclose(fp)) {
		return -2;/*提示无法关闭文件*/
	}
	if (i == 20 && s0.score <= s[19].score) {
		return -4;/*提示排行榜已满*/
	}

	if ((fp = fopen("..\\Tetris\\Save\\rank.txt", "w+")) == NULL) {
		return -3;/*提示打开文件失败*/
	}
	if (!i) {
		fprintf(fp, "%d %s %d\n", s0.rank, s0.name, s0.score);
		if (fclose(fp)) {
			return -6;/*提示无法关闭文件*/
		}
		return 1;
	}

	if (i) {
		for (j = 0; j < i; j++) {
			if (s0.score >= s[j].score) {
				for (e = (i == 20) ? 19 : i; e > j; e--) {
					s[e].score = s[e - 1].score;
					strcpy(s[e].name, s[e - 1].name);
					s[e].rank = e + 1;
				}
				s[j] = s0;
				s[j].rank = j + 1;

				d = 0;
				while (s[d].rank > 0 && s[d].rank <= 20) {
					fprintf(fp, "%d %s %d\n", s[d].rank, s[d].name, s[d].score);
					d++;
				}
				if (fclose(fp)) {
					return -4;/*提示无法关闭文件*/
				}
				return d;
			}
		}
		s[i] = s0;
		s[i].rank = i + 1;

		d = 0;
		while (s[d].rank > 0) {
			fprintf(fp, "%d %s %d\n", s[d].rank, s[d].name, s[d].score);
			d++;
		}
		if (fclose(fp)) {
			return -5;/*提示无法关闭文件*/
		}
		return i + 1;
	}
}
