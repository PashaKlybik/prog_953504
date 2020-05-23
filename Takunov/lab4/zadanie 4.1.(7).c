//Для двух строк символов найти самую длинную общую подстроку.
//Пробелы и знаки препинания игнорировать, строчные и прописные
//буквы считать неразличимыми.Например, строки: “Дай вилку!Бок
//севрюжий кончается” и “Чемпионский кубок достался не нам”
//содержат общую подстроку “кубок”.

#include <Windows.h>
#include<stdio.h>
#include<string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void EditString(char* A)
{
	for (int i = 0; i < strlen(A); i++)
	{
		if (A[i] >= 'A' && A[i] <= 'Z')
			A[i] = A[i] + 32;
		if (A[i] == '!' || A[i] == '?' || A[i] == '.' || A[i] == ',' || A[i] == ':' || A[i] == ';' || A[i] == '-' || A[i] == ' ')
		{
			for (int j = i; j < strlen(A); j++)
			{
				A[j] = A[j + 1];
			}
			i--;
		}
	}
}

void FinalString(char* buffer, int begin, int end, char* source)
{
	for (int i = begin, k = 0; i < end; i++, k++)
	{
		buffer[k] = source[i];
		buffer[k + 1] = '\0';
	}
	printf("the final string: %s\n", buffer);
}

void FoundSubstring(char* A, char* B)
{
	char buffer_string[20];
	int indexbegin = 0, indexend = 0,length_max = 0;
	int j = 0;
	int resolution = 0;
	for (int i = 0; i < strlen(A); i++)
	{
		for (j = 0; j < strlen(B); j++)
		{
			if (A[i] == B[j])//&& resolution == 0)
			{
				int repetition = 1;
				while (A[i + repetition] == B[j + repetition] && A[i + repetition]!='\0'&&B[j + repetition]!='\0')
				{
					repetition++;
				}
				if (repetition>length_max)
				{					
					indexbegin = i;
					indexend = i + repetition;
					length_max = repetition;
					i += repetition;
				}
			}
			//{
			//	indexbeginbuff = j;
			//	resolution = 1;
			//	length++;
			//}
			//else 
			//	if (resolution==1)
			//{
			//	if (A[i + j] == B[j])
			//	{
			//		length++;
			//	}
			//	else
			//	{
			//		if (length > length_max)
			//		{
			//			length_max = length;
			//			indexend = j;
			//			indexbegin = indexbeginbuff;
			//			length = 0;
			//			resolution = 0;
			//			//i = i + j;
			//		}
			//		break;
			//	}
			//}
		}
	}
	FinalString(buffer_string, indexbegin, indexend, A);
}
int main()
{
	for (;;)
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		char string_1[100];
		puts("input first string: ");
		gets(string_1);
		char string_2[100];
		puts("input second string: ");
		gets(string_2);
		EditString(string_1);
		EditString(string_2);
		FoundSubstring(string_1, string_2);
	}
}
