//4.2 (19).В файле задан произвольный текст.Напечатать в алфавитном
//порядке все слова, которые входят в этот текст по одному разу.
#include <iostream>
#include <cstdio>

using namespace std;

//ищем количество слов
int WordAmount(char* str, int wordCount)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
			wordCount++;
	}
	return wordCount;
}

//заполняем двумерный массив словами из одномерного массива str
char** ArrayFilling(char* str, int n, char** words, int position)
{
	for (int i = 0; i < (n + 1); i++)
		words[i] = (char*)malloc(128 * sizeof(char));
	int j = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' || '\0')
		{
			words[position][j] = str[i];
			words[position][j + 1] = '\0';
		}
		j++;
		if (str[i] == ' ')
		{
			position++;
			j = 0;
		}

	}
	return words;
}

//сортируем двумерный массив слов с помощью таблицы аски
char** Sort(char** words, char* temp, int wordCount)
{
	for (int i = 0; i < wordCount; i++) {
		for (int j = 0; j < wordCount - 1; j++) {
			if ((int)(words[j][0]) > (int)(words[j + 1][0]))
			{
				temp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = temp;
			}
		}
	}
	return words;
}

void Output(char** words, int wordCount)
{
	for (int i = 0; i < wordCount; i++)
	{
		for (int j = 0; words[i][j] != '\0'; j++)
		{
			cout << words[i][j];
		}
		cout << endl;
	}
}

void Delete(char** words, char* temp, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(words[i]);
	}
	free(words);
	free(temp);
}

int main()
{
	FILE* file;
	char str[500];
	int n = 100;
	int position = 0;
	char* temp = (char*)malloc(n * sizeof(char));
	char** words = (char**)malloc((n) * sizeof(char*));

	fopen_s(&file, "text.txt", "r");
	if (!file)
	{
		cout << " Error: file not found!";
		exit(0);
	} 
	fgets(str, sizeof(str), file);

	int wordCount = WordAmount(str, 1);
	ArrayFilling(str, n, words, position);
	cout << " Words in file: \n";
	Output(words, wordCount);
	cout << endl;
	Sort(words, temp, wordCount);
	cout << " Words in alphabetical order: \n";
	Output(words, wordCount);
	Delete(words, temp, n);
}