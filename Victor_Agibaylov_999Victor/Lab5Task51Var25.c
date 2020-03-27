/*5.1 (25).Разработать функцию, которая инвертирует заданный стек, т.е.
первый элемент становится последним, второй – предпоследним и
т.д*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//макс размер стека
//реализовано через массив элементов
int const stackSize = 100;

void push(struct stack* stk, float f);
void init(struct stack* stk);
int getcount(struct stack* stk);
void inverce(struct stack* stk, int size);

struct stack
{
    float elem[stackSize];
    int top;
};

int main()
{
    struct stack* stk;
    int i, n;
    float elem;

    stk = (struct stack*)malloc(sizeof(struct stack));

    init(stk);

    do
    {
        printf("Enter quantity of elements in stack: ");
        scanf_s("%d", &n);

        if (n <= 100 && n > 0)
        {
            break;
        }
        else
        {
            printf("Wrong value!\n");
        }
    } while (true);

    for (i = 0; i < n; i++)
    {
        do
        {
            printf("Enter element number %d:", i);
            scanf_s("%f", &elem);

            if (elem > -2147483647 && elem < 2147483648)
            {
                break;
            }
        } while (true);

        push(stk, elem);
    }

    printf("It is %d elements in stack\n\n", getcount(stk));

    int j = stk->top;

    printf("Before inverce: \n");
    {
        do
        {
            j--;
            printf("%f\n", stk->elem[j]);
        } while (j > 0);
    }

    inverce(stk, n);

    printf("After inverce: \n");
    {
        j = stk->top;

        do
        {
            j--;
            printf("%f\n", stk->elem[j]);
        } while (j > 0);
    }

    return 0;
}

void inverce(struct stack* stk, int size)
{
    struct stack* dummyStk;

    dummyStk = (struct stack*)malloc(sizeof(struct stack));

    init(dummyStk);

    for (int i = size - 1, j = 0; i >= 0, j < size; i--, j++)
    {
        if ((stk->top) > 0)
        {
            stk->top--;
            dummyStk->elem[j] = stk->elem[i];
            dummyStk->top++;
        }
    }

    for (int i = size - 1; i >= 0; i--)
    {
        if ((dummyStk->top) > 0)
        {
            dummyStk->top--;
            stk->elem[i] = dummyStk->elem[i];
            stk->top++;
        }
    }
}

//инициализация стека
void init(struct stack* stk)
{
    stk->top = 0;
}

//добавление элемента в стек
void push(struct stack* stk, float f)
{
    if (stk->top < stackSize) {
        stk->elem[stk->top] = f;
        stk->top++;
    }
    else
    {
        printf("Stack is full, quantity of elements is: %d !\n", stk->top);
    }
}

//возвращает количество элементов в стеке
int getcount(struct stack* stk)
{
    return stk->top;
}