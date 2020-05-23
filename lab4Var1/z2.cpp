//В текстовом файле находится произвольный текст.
//Найти и распечатать пары слов (анаграммы), при прочтении которых в 
//обратном направлении образуется другое слово пары, например: (ПОЛК КЛОП), (БАР РАБ). 
#include <stdio.h>
#include <stdlib.h>

int dli(char* s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

char* inv(char* a)
{
    int d = dli(a);
    char* s = (char*) calloc (d+1,sizeof(char));
    int i = d-1, y = 0;
    for (; i >= 0; i--)
    {
        s[y] = a[i];
        y++;
    }
    s[y] = '\0';
    return s;
}

bool est(char* a, char* b)
{
   
    int da = dli(a), db = dli(b);
    for (int i = 0; i < da; i++)
    { 
        int flag = 0;
        if (a[i] == b[0])
        {
            i++;
            for (int j = 1; j < db; i++, j++)
            {
                if (a[i] != b[j])
                {
                    flag = 1;
                    break;
                }
            }
            if (!flag) return true;
        }
    }
    return false;
}

int firstprob(char* s)
{
    int i = 0;
    while (s[i] != 32&&s[i]!='\0')
        i++;
    return i;
}

char* slovo(char* s, int k)
{
    char* a = (char*)calloc(k + 1, sizeof(char));
    int i;
    for (i = 0; i < k; i++)
        a[i] = s[i];
    a[i] = '\0';
    return a;
}

char* read(const char* filename)
{
    FILE* fp;
    char c;
    char *text= (char*)calloc(100, sizeof(char));
    if (fopen_s(&fp,filename,"r")!=0)
    {
        perror("Error occured while opening file");
        return NULL;
    }
   
    int i = 0;
    while ((c = getc(fp)) != EOF)
    {
        text[i] = c;
        i++;
    }
    text[i] = '\0';

    fclose(fp);
    return text;
}

int main()
{
    char* str;
    str=read("D:\\Учёба. Семестр 2\\Программирование\\4ЛР\\z2\\Text.txt");
    int l = dli(str);
    str[l] = '\0';
    char* p = str;
    p--;
    while (*p)
    {
        p++;
        int pr = firstprob(p);
        char* p1 = inv(slovo(p, pr));
        p += pr;
        if (est(p, p1))
        {
            printf("%s\t%s\n", inv(p1), p1);
        }
        free(p1);
    }
    free(str);

    return 0;
}

