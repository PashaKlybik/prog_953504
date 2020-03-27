#include<iostream>
#include<conio.h>
#include<stdio.h>

using namespace std;

void regist (char text[5][100], int i);

int main()
{
	FILE *fp;
	char text[5][100], text2[100];
	if( (fp = fopen("C:\\143\\file.txt","r")) == NULL)
	{
		printf("Error");
		getch();
		return 0;
	}
	int i = 0;
	while( fgets(text2, 100, fp) != NULL)
	{
		strcpy(text[i], text2);
		i++;
	}
	fclose(fp);
	for(int n = 0; n < i; n++)
		for(int m = 0; m < 100; m++)
		{
			if((text[n][m] == ' ') && (text[n][m+1] == ' '))
			{
				for(int k = m + 1; k < 100; k++)
					text[n][k] = text[n][k+1];
				m--;
			}
		}
	regist(text , i);
	for(int n = 0; n < i; n++)
	{
		cout<<text[n];
	}
	getch();
	return 0;
}
void regist (char text[5][100], int i)
{
    for(int n = 0; n < i; n++)
		for(int m = 0; m < 100; m++)
		{
			if((text[n][m] == '.') && (text[n][m+1] >= 97 && text[n][m+1] <= 122))
				text[n][m+1] = toupper(text[n][m+1]);
		}
}
