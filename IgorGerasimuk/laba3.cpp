#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#define NN 6

int main()
{
	float a[NN][NN];
	bool key = true;
	int i, j, n, k = 0;
	printf("Vvedite razmernost\n");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			//std::cout << "\n[" << i << "][" << j << "]=";
			printf("a[%d][%d]=", i, j);
			scanf_s("%f", &a[i][j]);
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%4.0f\t", a[i][j]);
		printf("\n");
	}

	for (i = 0; i < n; ++i)
		for (k = i + 1; k < n; k++)
		{
			double multi = a[k][i] / a[i][i];
			for (j = 0; j < n; j++)
			{
				double i2j = a[k][j];

				double mulxmj = (multi * a[i][j]);
				a[k][j] = i2j - mulxmj;
			}
		}
	printf("\n");
	printf("\n");
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf("%4.0f\t", a[i][j]);
		printf("\n\n");
	}
	printf("\n");

	int rang = 0;
	key = true;

	for (i = 0; i < n; ++i)
	{
		key = false;
		for (j = 0; j < n; ++j)
			if (a[i][j] != 0.0)
				key = true;

		if (key)
			rang++;
	}

	printf("rang = %d", rang);
	printf("\n");
	getchar();
	getchar();
}