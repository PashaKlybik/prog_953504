#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

int n, m;

int IsSimilar(int *arr1, int *arr2);
int IsGreater(int *arr1, int *arr2);
void ReadArray(int **arr);
void WriteArray(int **arr);
void Sort(int **arr);
void DeleteSimilar(int **arr);

int main()
{
	int **arr;

	printf("Enter number of rows:\n = ");
	scanf("%d", &n);
	printf("Enter number of cols:\n = ");
	scanf("%d", &m);
	arr = (int **)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		arr[i] = (int *)malloc(m * sizeof(int));
	}
	ReadArray(arr);
	DeleteSimilar(arr);
	Sort(arr);
	WriteArray(arr);

	for (int i = 0; i < n; i++)
	{
		free(arr[i]);
	}
	free(arr);

	return 0;
}

void ReadArray(int **arr)
{
	char *temp;
	temp = (char *)malloc(m * sizeof(char));
	for (int i = 0; i < n; i++)
	{
		printf("Enter line %d: ", i + 1);
		scanf("%s", temp);
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = temp[j] - 48;
		}
	}
	printf("\n");
}

void WriteArray(int **arr)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int IsSimilar(int *arr1, int *arr2)
{
	for (int i = 0; i < m; i++)
	{
		if (arr1[i] != arr2[i])
		{
			return 0;
		}
	}
	return 1;
}

int IsGreater(int *arr1, int *arr2)
{
	for (int i = 0; i < m; i++)
	{
		if (arr1[i] > arr2[i])
		{
			return 1;
		}
		else if (arr1[i] < arr2[i])
		{
			return 0;
		}
	}
	return 0;
}

void Sort(int **arr)
{
	int *temp;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (IsGreater(arr[j-1], arr[j]))
			{
				temp = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void DeleteSimilar(int **arr)
{
	int *temp;

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (IsSimilar(arr[i], arr[j]))
			{
				temp = arr[n-1];
				arr[n-1] = arr[j];
				arr[j] = temp;
				j--;
				n--;
			}
		}
	}
}
