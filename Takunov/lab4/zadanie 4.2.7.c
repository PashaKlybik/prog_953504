#include <stdio.h>
#include <string.h>
#include <Windows.h>
//#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996).

int arr_max(const int arr[], const int N)
{
	int m = arr[0];
	for (int i = 1; i < N; i++)
		if (m < arr[i]) m = arr[i];
	return m;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE* fp;
	fp = fopen("my.txt", "r");
	if (fp == NULL)
	{
		printf("Не удалось открыть файл");
		//getchar();
		return 0;
	}
	char string[256];
	fgets(string, 256, fp);
	printf("%s", string);
	//scanf("%s", &string);
	int N = 0, len;
	if (string[0] != ' ') N++;
	for (int i = 0; string[i]; i++)
		if (string[i] == ' ' && string[i + 1] != ' ')
			N++;
	int* gis = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		gis[i] = 0;
	int k = 0, c = 0;
	if (string[0] != ' ')
	{
		while (!(strchr(".,! ", string[k]) || string[k] == '\0'))
		{
			gis[c]++;
			k++;
		}
		c++;
	}
	while (k < strlen(string))
	{
		if (string[k] == ' ' && string[k + 1] != ' ')
		{
			k++;
			while (!(strchr(".,! ", string[k]) || string[k] == '\0'))
			{
				gis[c]++;
				k++;
			}
			c++;
		}
		else
			k++;
	}
	int max = arr_max(gis, N);
	for (int i = max; i > 0; i--)
	{
		printf("\n");
		for (int j = 0; j < N; j++)
		{
			if (gis[j] >= i)
			{
				printf("|");
			}
			else
				printf(" ");
			printf(" ");
		}
	}
	//}
	printf("\n\n");
	system("pause");
	return 0;
}