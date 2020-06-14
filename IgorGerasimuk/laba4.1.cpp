#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>

using namespace std;

int main()
{
    char* str = (char*)malloc(128);
    puts(str);

    int outbkt = true;
    int nobkt = true;
    while (*str != '\0')
    {
        if (*str == '(') { printf("%c", *str++); outbkt = false; nobkt = false; }
        if (*str == ')') { printf("%c", *str++); outbkt = true; }
        if (outbkt)printf("%c", *str++);
        if (!outbkt)str++;
    }
    printf("\n");
    if (!outbkt)printf("Error: in input, no ')'\n");
    if (nobkt)printf("Error: no brekets was in input line");

    _getch();
    return 0;
}