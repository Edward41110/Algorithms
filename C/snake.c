#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define LENGTH 16

typedef struct _pos {
	int x;
	int y;
}pos;

int board[LENGTH][LENGTH];
pos food, head, tail;
// dir: 1上 2下 3左 4右 
int dir = 1;

int isFullLine(int n) {
	int i;
	for (i = 0;i < LENGTH;i++)
		if (!board[n][i]) return 0;
	return 1;
}

void getRandomPos(pos* p) {
	int i, cnt = 0;
	int line = rand() % LENGTH;
	int position[LENGTH];
	if (isFullLine(line))
		line = rand() % LENGTH;
	for (i = 0;i < LENGTH;i++)
		if (!board[line][i])
			position[cnt++] = i;
	p->x = line;
	p->y = (int)(rand() % cnt);
}

void init() {
	int i, j;
	for (i = 0;i < LENGTH;i++) {
		for (j = 0;j < LENGTH;j++) {
			board[i][j] = 0;
		}
	}
	getRandomPos(&food);
	getRandomPos(&head);
	tail = head;
	board[food.x][food.y] = 1;
	board[head.x][head.y] = 2;
}

void update() {
	int i, j;
	for (i = 0;i < LENGTH;i++)
		for (j = 0;j < LENGTH;j++)
			if (board[i][j] > 1)
				board[i][j]++;
}

void findTail(pos* p) {
	int i, max = 0;
	int arr[4];
	arr[0] = p->x > 0 ? board[p->x - 1][p->y] : 0;			// 上 
	arr[1] = p->x < LENGTH - 1 ? board[p->x + 1][p->y] : 0;// 下 
	arr[2] = p->y > 0 ? board[p->x][p->y - 1] : 0;			// 左 
	arr[3] = p->y < LENGTH - 1 ? board[p->x][p->y + 1] : 0;// 右
	for (i = 1;i < 4;i++) {
		if (arr[i] > arr[max]) {
			max = i;
		}
	}
	if (max == 0) p->x--;
	else if (max == 1) p->x++;
	else if (max == 2) p->y--;
	else if (max == 3) p->y++;
}

void show() {
	system("cls");
	int i, j;
	for (i = 0;i < LENGTH;i++) {
		for (j = 0;j < LENGTH;j++)
			if (board[i][j] == 1) printf("*");
			else if (board[i][j]) printf("%d", board[i][j] % 10);
			else printf(" ");
		printf("\n");
	}
}

int move() {
	int eat = 0;
	if (dir == 1) {
		if (head.x <= 0 || board[head.x - 1][head.y] > 1) return 0;
		else head.x--;
	}
	else if (dir == 2) {
		if (head.x >= LENGTH - 1 || board[head.x + 1][head.y] > 1) return 0;
		else head.x++;
	}
	else if (dir == 3) {
		if (head.y <= 0 || board[head.x][head.y - 1] > 1) return 0;
		else head.y--;
	}
	else if (dir == 4) {
		if (head.y >= LENGTH - 1 || board[head.x][head.y + 1] > 1) return 0;
		else head.y++;
	}

	update();
	board[head.x][head.y] = 2;
	if (head.x == food.x && head.y == food.y) {
		eat = 1;
		getRandomPos(&food);
		board[food.x][food.y] = 1;
	}
	else {
		board[tail.x][tail.y] = 0;
		findTail(&tail);
	}
	show();
	return 1;
}

int main() {
	srand(time(NULL));
	init();
	show();
	time_t t;
	while (move()) {
		time(&t);
		while (difftime(time(NULL), t) < 1) {
			if (_kbhit()) {
				int key = _getch();
				switch (key) {
				case 'w': if (dir != 2) dir = 1; break;
				case 's': if (dir != 1) dir = 2; break;
				case 'a': if (dir != 3) dir = 3; break;
				case 'd': if (dir != 4) dir = 4; break;
				}
			}
		}
	}
	return 0;
}

