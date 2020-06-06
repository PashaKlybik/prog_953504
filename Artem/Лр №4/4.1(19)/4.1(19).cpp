//4.1 (19).Цепочка слов.Пусть слово – это последовательность от 1 до 8
//символов, не включающая пробелов.Вводится n слов s1, ..., sn.
//Можно ли их упорядочить так, чтобы получилась «цепочка», в
//которой первая буква каждого слова si совпадает с последней буквой
//предыдущего слова, а последняя буква последнего слова совпадает с
//первой буквой первого слова ? В цепочку должны входить все n слов
//без повторений.Если такое упорядочение возможно, то вывести
//цепочку слов.
#include <iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

char **Sort(char** words, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int length = strlen(words[i]) - 1;
			if (words[j][0] == words[i][length])
			{
				char* temp = words[i + 1];
				words[i + 1] = words[j];
				words[j] = temp;
				break;
			}
		}
	return words;
}

void Delete(char** words)
{
	for (int i = 0; i < 8; i++)
	{
		free(words[i]);
	}
	free(words);
}

int main()
{
	int n;
	cout << " Enter count of words: "; //5
	cin >> n;
	char** words;
	words = (char**)malloc((n + 1) * sizeof(char*));
	for (int i = 0; i < (n + 1); i++)
		words[i] = (char*)malloc(8 * sizeof(char));

	cout << " Enter words: ";
	for (int i = 0; i < n; i++)  //qwer asdfgh tqwera hvbxcm masdfq
	{
		cin >> words[i];
	}

	Sort(words, n);

	cout << " Words after sort: ";
	for (int i = 0; i < n; i++)
	{
		cout << endl << words[i];
	}

	Delete(words);
}