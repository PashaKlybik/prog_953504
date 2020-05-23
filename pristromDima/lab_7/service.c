#include "service.h"

void print(char *text, int highlited)
{
    if (highlited == 1)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
    printf("%s", text);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
