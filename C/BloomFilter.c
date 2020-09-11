#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int hashTimes = 3;
static int hashArgs[3][5] = 
{	{5, 8, 4, 7, 3},
	{4, 7, 3, 6, 3},
	{5, 6, 4, 5, 3} };

typedef struct _BloomFilter {
	int intSize;
	int* map;
}BF;

void initBF(BF* bf, int length) {
	bf->intSize = (length + 31) / 32;
	bf->map = (int*)calloc(bf->intSize, sizeof(int));
}

void freeBF(BF* bf) {
	free(bf->map);
}

int myHash(int key, int* args) {
	int HashKey = key;
	HashKey ^= (HashKey >> args[0]) ^ (HashKey >> args[1]);
	HashKey ^= (HashKey << args[2]) ^ (HashKey << args[3]);
	return HashKey >> args[4];
}

void mark(BF* bf, int hashCode) {
	hashCode %= 32 * bf->intSize;
	int intIndex = hashCode / 32;
	int bitIndex = hashCode % 32;
	bf->map[intIndex] |= 1 << bitIndex;
}

bool check(BF* bf, int hashCode) {
	hashCode %= 32 * bf->intSize;
	int intIndex = hashCode / 32;
	int bitIndex = hashCode % 32;
	return (bf->map[intIndex] & 1 << bitIndex) == 0;
}

void put(BF* bf, int key) {
	int i;
	for (i = 0;i < hashTimes;i++) {
		int hashCode = myHash(key, hashArgs[i]);
		mark(bf, hashCode);
	}
}

bool isExist(BF* bf, int key) {
	int i;
	for (i = 0;i < hashTimes;i++) {
		int hashCode = myHash(key, hashArgs[i]);
		if (check(bf, hashCode)) return 0;
	}
	return 1;
}

void save(BF* bf) {
	FILE* fp = fopen("save.txt", "w");
	if (fp) {
		int i;
		fprintf(fp, "%d ", bf->intSize);
		for (i = 0;i < bf->intSize;i++)
			fprintf(fp, "%d ", bf->map[i]);
	}
	fclose(fp);
}

BF* load() {
	BF* bf = (BF*)malloc(sizeof(BF));
	FILE* fp = fopen("save.txt", "r");
	if (fp) {
		int i;
		fscanf(fp, "%d", &bf->intSize);
		bf->map = (int*)calloc(bf->intSize, sizeof(int));
		for(i = 0;i < bf->intSize;i++) {
			fscanf(fp, "%d", &bf->map[i]);
		}
	} else {
		printf("can not open the file\n");
		free(bf);
		bf = NULL;
	}
	return bf;
}

int main()
{
	
	return 0;
}
