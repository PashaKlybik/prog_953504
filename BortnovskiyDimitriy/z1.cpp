﻿#include <stdio.h>

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
    char** d = new char* [k];
    for (int i = 0; i < k; i++)
        d[i] = new char[100];
    int i = 0,z=0,o=0;
    
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
    
    out(d, k);

    return 0;
}
