/*Разнобуквица. С клавиатуры вводится многострочный текст. Распечатать самое длинное слово, в котором все буквы разные.*/
//hhhhhhh fgh qwerty defdd zxcvbn

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Max_word (char *new_text)
{
    int count_of_symbols = 0, end = 0, begin = 0, max = 0;

    for (int i = 0; i < strlen(new_text); i++)
    {
        if ((new_text[i] >= 'A' && new_text[i] <= 'Z') || (new_text[i] >= 'a' && new_text[i] <= 'z'))
        {
            count_of_symbols++;
        }
        if (max < count_of_symbols)
        {
            max = count_of_symbols;
            end = i;
            begin = end - count_of_symbols + 1;
        }

        if ((i + 1) == strlen(new_text) || (new_text[i + 1] == ' ' || new_text[i + 1] == '.' || new_text[i + 1] == '!' || new_text[i + 1] == '?'))
        {
            count_of_symbols = 0;
        }
    }

    for (int i = begin; i <= end; i++)
    {
        printf("%c", new_text[i]);
    }
    printf("%c", ' ');
}

void checking_letters (int begin, int end, char *text, char *new_text)
{
    int control = 0, check = 0, count_of_symbols = 0, i = 0, j = 0, n = 0;
    for (int i = begin; i < end; i++)
    {
        control += end - i;

        for (int j = i + 1; j <= end; j++)
        {
            if (text[i] != text[j])
            {
               check += 1;
            }
            else
            {
                check += 0;
            }
        }

        count_of_symbols++;
    }

    if (check == control)
    {
        for (i = begin, j = n; i <= end; i++, j++, n++)
        {
           new_text[j] = text[i];
        }

        new_text[j++] = ' ';
        n += 2;
    }
}

int  main ()
{
    char *text = (char*)malloc(100);

    char *new_text = (char*)malloc(100);

    printf("String: ");

    gets(text);

    int count_of_symbols = 0, end = 0, begin = 0;

    for (int i = 0; i != strlen(text); i++)
    {
        count_of_symbols++;
        end = i;
        begin = end - count_of_symbols + 1;

        if ((text[i + 1] == strlen(text)) || (text[i + 1] == ' ' || text[i + 1] == '.' || text[i + 1] == '!' || text[i + 1] == '?'))
        {
            checking_letters (begin, end, text, new_text);
            count_of_symbols = 0;
            i += 1;
        }
    }

    Max_word (new_text);

    return 0;
}
