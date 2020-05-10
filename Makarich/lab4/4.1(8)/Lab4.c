#include <stdio.h>
#include <string.h>

char* TextRev(char* str)
{
    static char newText1[80];
    for (int i = Length(str) - 1, j = 0; i >= 0; i--, j++)
    {
        newText1[j] = str[i];
    }

    newText1[Length(str)] = '\0';
    return newText1;
}

int Length(char* str)
{
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

int main()
{
    char text[80];
    gets(text);

    puts(TextRev(text));

    system("pause");
    return 0;
}
//С клавиатуры вводится многострочный текст.
//Распечатать, начиная с последнего, «перевернутые» слова из текста.