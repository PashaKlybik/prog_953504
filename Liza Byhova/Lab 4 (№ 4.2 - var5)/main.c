/*Один из способов идентификации автора литературного
произведения – подсчет частоты вхождения отдельных слов. В
заданном текстовом файле найти 20 наиболее часто встречающихся
слов с указанием частоты использования каждого из них.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max_size 1100
#define symbols " .,/<>!?:;^%$#@()+-=*1234567890"

void RepeatWords(char *text)
{
    int words_counter = 0;
    char *pointer_to_word[max_size];
    char *words[20];
    pointer_to_word[0] = strtok(text, symbols);

    while (pointer_to_word[words_counter] != NULL)
    {
        words_counter++;
        pointer_to_word [words_counter] =  strtok(NULL, symbols);
    }

    bool first_iter = true, go = false, check = false, first = true, check_f = true;
    int max_number1 = 0, max_number2 = 0, max_word = 0, flag = 0;
    int index1 = 0, index2 = 0, u = 0, n = 0, f = 0, q = 0;

    int frequency[20];

    while (n < 20)
    {
        for (int i = 0; i < (words_counter - 1); i++)
        {
            if (!first)
            {
                for (int y = 0; y < u; y++)
                {
                    if (strcmp(pointer_to_word[i], words[y]) == 0)
                    {
                        check = true;
                        break;
                    }
                    else
                    {
                        check = false;
                    }
                }
            }
            if (!check)
            {
                flag++; // инкремент итераций
                for (int j = i + 1; j < words_counter; j++)
                {
                    if (strcmp(pointer_to_word [i], pointer_to_word [j] ) == 0)
                    {
                        if (first_iter)
                        {
                            max_number1++;
                            first_iter = false;
                            index1 = i;
                        }
                        else
                        {
                            max_number2++;
                            index2 = i;
                        }
                    }
                }
                if (flag == 2 || go)
                {
                    if (max_number1 >= max_number2)
                    {
                        max_word = index1;
                    }
                    else
                    {
                        max_word = index2;
                        max_number1 = max_number2;
                    }
                    flag = 0;
                    go = true;
                }
                if (check_f)
                {
                    f = max_number2 + 2;
                    check_f = false;
                }
                max_number2 = 0;
            }
        }
        if (first)
        {
            words[u] = pointer_to_word[max_word];
            u++;
            first = false;
        }
        else
        {
            words[u] = pointer_to_word[max_word];
            u++;
        }
        frequency[n] = f;
        n++;
        first_iter = check_f = true;
        go = false;
    }
    for (int i = 0; i < u; i++)
    {
        printf("\n%s - %d", words[i], frequency[i]);
    }
}

int main(int argc, char **argv)
{
    char *file_text = (char*)malloc(max_size);
    char* text = (char*)malloc(max_size);
    text[0] = ' ';

    FILE *file;
    file = fopen("№4.2 - 5.txt", "r");
    if (!file)
    {
        printf("Error");
    }
    else
    {
        printf("File content:\n");
        while (fgets(file_text, max_size, file) != NULL)
        {
            strcat(text, file_text);
        }
    }
    printf("%s\n", text);

    printf("\n20 most common words:\n");
    RepeatWords(text);

    return 0;
}
