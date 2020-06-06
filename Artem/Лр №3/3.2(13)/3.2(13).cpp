//3.2 (13).Дан целочисленный массив a(n, m).Упорядочить по неубыванию
//элементы на главной диагонали и диагоналях, параллельных ей.
//Перестановка элементов допускается только в пределах
//соответствующей диагонали.
#include <iostream>

using namespace std;

int** input_arrr(int n, int m, int** arr)
{
	cout << " Введите массив: \n";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			cout << " Введите [" << i << "][" << j << "] элемент массива: ";
			cin >> arr[i][j];
		}
	return arr;
}

void output_arrr(int n, int m, int** arr)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << " " << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

void main_diagonal(int n, int m, int** arr)
{
	cout << " Главная диагональ: \n";
	for (int i = 0; i < n && i < m; i++)
	{
		cout << " " << arr[i][i] << "\t";
	}
	cout << endl;
}

int** sort(int n, int m, int** arr)
{
	int a, b, c;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i && j < m - 1; j++)
		{
			a = j;
			for (c = j + 1; c < n - i && c < m; c++)
				if (arr[i + c][c] < arr[i + a][a])
					a = c;
			b = arr[i + j][j];
			arr[i + j][j] = arr[i + a][a];
			arr[i + a][a] = b;
		}
	}
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 0; j < n - 1 && j + i < m - 1; j++)
		{
			a = j;
			for (c = j + 1; c < n && c + i < m; c++)
				if (arr[a][i + a] > arr[c][i + c])
					a = c;
			b = arr[j][j + i];
			arr[j][j + i] = arr[a][a + i];
			arr[a][a + i] = b;
		}

	}
	return arr;
}

void Delete(int** arr, int n)
{
	for (int i = 0; i < n; i++)  
		free(arr[i]);  
	free(arr);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int n, m;
	cout << " Введите количество строк: ";
	cin >> n;
	cout << " Введите количество столбцов: ";
	cin >> m;

	int** arr = (int**)malloc(sizeof(int*) * n);

	for (int i = 0; i < n; i++)
		arr[i] = (int*)malloc(sizeof(int) * m);

	input_arrr(n, m, arr);
	cout << " Ваш массив: \n";
	output_arrr(n, m, arr);
	main_diagonal(n, m, arr);
	sort(n, m, arr);
	cout << " Отсортированный массив: \n";
	output_arrr(n, m, arr);
	Delete(arr, n);
}