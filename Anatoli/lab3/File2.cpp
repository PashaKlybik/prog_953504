#include<iostream>
#include <stdio.h>
#include<conio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int N;
	cout<<"Enter matrix size ";
	cin>>N;
	float tmp, xx[N+1], matrix[N][N+1];
	int N1 = N+1;
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N1; j++)
		{
			cout<<"matrix["<<i<<"]["<<j<<"] = ";
			cin>>matrix[i][j];
		}
/*Метод Гаусса*/
/*прямой ход*/
	for (int i = 0; i < N; i++)
	{
		tmp=matrix[i][i];
		for (int j = N;j >= i;j--)
		matrix[i][j] /= tmp;
		for (int j = i + 1;j < N;j++)
		{
			tmp=matrix[j][i];
			for (int k = N;k >= i;k--)
			matrix[j][k] -= (tmp * matrix[i][k]);
		}
	}
	if(matrix[N-1][N-1] == 0)
	{
		printf("Has no solution ");
		return 0;
	}
/*обратный ход*/
	xx[N - 1] = matrix[N - 1][N];
	for (int i = N - 2; i >= 0; i--)
	{
		xx[i] = matrix[i][N];
		for (int j = i + 1;j < N;j++) xx[i] -= matrix[i][j] * xx[j];
	}
/*вывод решения*/
	printf("\nMetod Gaussa:\n");
	for (int i = 0; i < N; i++)
	printf("x%d=%3.3f\n", i + 1, xx[i]);
	getch();
	return 0;
}
