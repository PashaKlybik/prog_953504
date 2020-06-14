//
//  main.c
//  lab5
//
//  Created by Tomashik Daniil on 5/18/20.
//  Copyright © 2020 Tomashik Daniil. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct item {
    int digit;
    struct item *next;
    struct item *prev;
} Item;
 
typedef struct mnumber {
    Item *head;
    Item *tail;
    int n;
} MNumber;
 
MNumber CreateMNumber(char *initStr);
void AddDigit(MNumber *number, int digit);
 
MNumber CreateMNumber(char initStr[])
{
    MNumber number = {NULL, NULL, 0};
    int n;
    for (n = strlen(initStr)-1; n >= 0; n--)
    AddDigit(&number, initStr[n]-'0');
    return number;
}
 
int gcd(int a, int b)
{
    return (a == 0) ? b : gcd(b % a, a);
}
 
int lcm(int a, int b)
{
    long long r = (long long)a * b;
    return (int)(r / gcd(a, b));
}
 
void AddDigit(MNumber *number, int digit)
{
    Item *p = (Item *)malloc(sizeof(Item));
    p->digit = digit;
    p->next = p->prev = NULL;
    if (number->head == NULL)
        number->head = number->tail = p;
    else {
        number->tail->next = p;
        p->prev = number->tail;
        number->tail = p;
    }
    number->n++;
}
 
void findLCM(MNumber a, MNumber b)
{
    Item *p1 = a.head, *p2 = b.head;
    int s1, s2;
 
    while (p1 || p2) {
        if (p1) { s1 = p1->digit; p1 = p1->next; }
        else s1 = 0;
        if (p2) { s2 = p2->digit; p2 = p2->next; }
        else s2 = 0;
        int l = lcm(s1, s2);
        printf("Least common multiple of %d & %d are: %d\n", s1, s2, l);
    }
}
 
int main(void)
{
    MNumber a = CreateMNumber("3680");
    MNumber b = CreateMNumber("238");
    findLCM(a, b);
    return 0;
}
