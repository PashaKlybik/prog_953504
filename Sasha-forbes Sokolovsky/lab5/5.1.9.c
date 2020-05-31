#include <stdio.h>
#include <stdbool.h>
#include "foo.h"

int main()
{
    char str[200] = "";
    fgets(str, 200, stdin);

    for (int i = 0; i < len(str) / 2; i++)
    {
        if(check(str[i]))
            Push(str[i]);
    }

    int x = len(str) / 2;
    if (len(str) % 2 != 0)
        x++;
    for (int i = x; i < len(str); i++) {
        if(check(str[i]))
            if (str[i] != Pop()) {
                printf_s("%s is not palindrom", str);
                return 0;
            }
    }
    printf_s("%s is palindrom", str);
    return 0;
}