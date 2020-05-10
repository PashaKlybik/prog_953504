#include <stdio.h>

#define SIZE 50

int Length(char* str);
char* ReadFile();
int CheckText();
void Brackets(char* str);

char* tos, * top, arr[SIZE];

int main()
{
    tos = arr;
    top = arr;

    Brackets(ReadFile());

    system("pause");
    return 0;
}

void push(char symbol)
{
    *top = symbol;

    if (top == (tos + SIZE))
    {
        printf("Stack overflow");
        exit(1);
    }
}

char* ReadFile()
{
    static char str[80];
    FILE* fp = fopen("data.txt", "r");

    while ((fgets(str, 256, fp)) != NULL)

        fclose(fp);

    return str;
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

void Brackets(char* str)
{
    char* end;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (*(str + i) == '(' || *(str + i) == ')' || *(str + i) == '[' || *(str + i) == ']' || *(str + i) == '{' || *(str + i) == '}')
            push(*(str + i));
        if (*top - 1 == *tos || *top - 2 == *tos)
        {
            end = top;
            if (!CheckText())
            {
                printf("Check ypur brackets\n");
                for (int j = 0; arr[j] != '\0'; j++)
                    printf("%c ", arr[j]);
                exit(1);
            }
            top = end;
            tos = top + 1;
        }
        if (i == Length(str) - 1 && !CheckText())
        {
            printf("Check ypur brackets\n");
            for (int j = 0; arr[j] != '\0'; j++)
                printf("%c ", arr[j]);
            exit(1);
        }
       top++;
    }
    printf("Brackets are correct\n");
}

int CheckText()
{
    while (tos < top)
    {
        if (*tos == *top - 2 || *tos == *top - 1)
        {
            tos++;
            top--;
        }
        else
            return 0;
    }
    return 1;
}

