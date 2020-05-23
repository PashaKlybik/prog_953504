//С клавиатуры вводится многострочный текст.
//Отсортировать по длине и вывести на печать все слова текста.

#include <stdio.h>
#include <stdlib.h>

int dli(char* s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int prob(char* s)
{
    int i = 0, k = 0;
    while (s[i] != '\0')
    {
        if (s[i] == 32) k++;
        i++;
    }
    return k;
}

void out (char** d, int size) 
{
    int l = 0;
    for (int i = 1; i < 101; i++)
    {
        int l = 0;
        while (l < size)
        {
            if (dli(d[l]) == i)
            {
                printf("%s\n",d[l]);
            }
            l++;
        }
    }
 }

int main()
{
    char s[100];
    gets_s(s);
    int k = prob(s) + 1;
    char** d = (char**) calloc (k, sizeof(char*));
    for (int i = 0; i < k; i++)
        d[i] = (char*)calloc(100, sizeof(char));
    int i = 0,z=0,o=0;
    
    //создаём массив строк
    while (s[i] != '\0')
    {
        if (s[i] == 32)
        {
            d[z][o] = '\0';
            z++;
            o = 0;
            i++;
            continue;
        }
        else
        {
            d[z][o] = s[i];
            o++;
            i++;
        }
                 
    }
    d[z][o] = '\0';
    
    out(d, k);//выводим их по возрастанию длины

    for (int i = 0; i < k; i++)
        free(d[i]);
    free(d);

    return 0;
}
