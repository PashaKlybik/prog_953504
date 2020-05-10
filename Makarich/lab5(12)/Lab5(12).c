#include <stdio.h>
#include <string.h>

typedef struct item {
    int digit;
    struct item* next;
    struct item* prev;
} Item;

typedef struct mnumber {
    Item* head;
    Item* tail;
    int n;
} MNumber;

MNumber CreateMNumber();
void AddDigit(MNumber* number, int digit);
void PrintMNumber(MNumber number);
MNumber Sub(MNumber n1, MNumber n2);
MNumber Sum(MNumber n1);

void main(void)
{
    int n;
    scanf_s("%d", &n);

    MNumber a = CreateMNumber();
    MNumber b = CreateMNumber();

    for (int i = 1; i < n; i++)
    {
        b = Sum(b);
        a = Sub(a, b);
    }

    PrintMNumber(a);
}

MNumber CreateMNumber()
{
    MNumber number = { NULL, NULL, 0 };

    AddDigit(&number, 1);

    return number;
}

void AddDigit(MNumber* number, int digit)
{
    Item* p = (Item*)malloc(sizeof(Item));

    p->digit = digit;
    p->next = p->prev = NULL;

    if (number->head == NULL)
        number->head = number->tail = p;
    else
    {
        number->tail->next = p;
        p->prev = number->tail;
        number->tail = p;
    }

    number->n++;
}

MNumber Sub(MNumber n1, MNumber n2)
{
    MNumber fact = { NULL, NULL, 0 };

    Item* p1;
    Item* p2 = n2.head;
    Item* temp;

    int digit = 0, pos = 0, s1, s2, iter = 0;

    while (p2)
    {
        p1 = n1.head;
        temp = fact.head;

        for(int i = 0; i < iter; i++)
            if (temp)
                temp = temp->next;

        s2 = p2->digit;
        p2 = p2->next;

        while (p1)
        {
            s1 = p1->digit;
            p1 = p1->next;

            digit = (s1 * s2 + pos) % 10;
            pos = (s1 * s2 + pos) / 10;

            if (temp)
            {
                pos += (temp->digit + digit) / 10;
                temp->digit = (temp->digit + digit) % 10;
                temp = temp->next;
            }
            else
                AddDigit(&fact, digit);

            if (!p1 && pos)
            {
                AddDigit(&fact, pos);
                pos = 0;
            }
        }

        iter++;
    }

    return fact;
}

MNumber Sum(MNumber n1)
{
    MNumber sum = { NULL, NULL, 0 };

    Item* p1 = n1.head;

    int digit, pos = 0, s1, s2;

    while (p1)
    {
        if (p1 == n1.head)
        {
            digit = (p1->digit + 1 + pos) % 10;
            pos = (p1->digit + 1 + pos) / 10;

            AddDigit(&sum, digit);
        }
        else if (pos)
        {
            digit = (p1->digit + pos) % 10;
            pos = (p1->digit + pos) / 10;

            AddDigit(&sum, digit);
        }
        else
            AddDigit(&sum, p1->digit);

        p1 = p1->next;
    }

    if (pos)
        AddDigit(&sum, pos);

    return sum;
}

void PrintMNumber(MNumber number)
{
    Item* p = number.tail;
    printf("\nNumber: ");

    while (p) {
        printf("%d", p->digit);
        p = p->prev;
    }
}