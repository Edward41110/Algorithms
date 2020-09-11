#include <stdio.h>
#include <string.h>

int strStr(char * main, char * sub)
{
	int ret = -1;
	int M = strlen(sub);
	int N = strlen(main);
	int i, j;
	for (i = 0;i < N - M + 1;i++) {
		for (j = 0;j < M;j++) {
			if (main[i + j] != sub[j])
				break;
		}
		if (j == M) {
			ret = i;
			break;
		}
	}
	return ret;
}

int main()
{
	int ret = strStr("a", "a");
	printf("%d\n", ret);
	return 0; 
} 
