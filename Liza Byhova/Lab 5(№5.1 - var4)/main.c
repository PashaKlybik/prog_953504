//123456789123456789

#include <stdio.h>
#include <stdlib.h>

struct ListItem
{
    int data;
    struct ListItem *next;
    struct ListItem *prev;
};

struct List
{
    int count;
    struct ListItem *begin;
    struct ListItem *end;
};

struct List ConvertToOct(struct List *dec);
char NextNumber(struct ListItem *item);
struct ListItem *Empty(struct List *dec);
void Initialize(struct List *list);
int HasBetween(char ch);
void Add(struct List *list, char data);
void AddToEnd(struct List *list, char data);
void Display(struct List *list);
void Clear(struct List *list);

int main(void)
{
    struct List dec, oct;
    char chr;

    Initialize(&dec);

    printf("Enter the number in decimal notation:\n");

    while((chr = getchar()) != '\n') {

        if(!HasBetween(chr)) {

            printf("Error.");
            exit(1);
        }
        Add(&dec, chr - 48);
    }

    oct = ConvertToOct(&dec);

    printf("Number in octal number system:\n");
    Display(&oct);

    Clear(&dec);
    Clear(&oct);
    return 0;
}

struct List ConvertToOct(struct List *dec)
{
    struct List oct;
    struct ListItem *item = dec->begin;
    int _size = 0;

    Initialize(&oct);

    while(item) {

        AddToEnd(&oct, NextNumber(item));
        item = Empty(dec);
        _size++;
    }
    return oct;
}

char NextNumber(struct ListItem *item)
{
    int temp = 0;

    while(item) {

        temp = (temp << 3) + (temp << 1) + item->data;
        item->data = temp >> 3;
        temp = temp % 8;
        item = item->next;
    }
    return temp;
}

struct ListItem *Empty(struct List *dec)
{
    struct ListItem *item = dec->begin;

	while(item) {

		if (item->data != 0)
			return item;

        item = item->next;
	}
	return NULL;
}

void Initialize(struct List *list)
{
    list->begin = NULL;
    list->end = NULL;
}

int HasBetween(char ch)
{
    int bits = ~0UL / 255;
    return (((ch - bits * 58) & ~(ch)) & (((ch) & bits * 127) + bits * 80) & (bits * 128));
}

void Add(struct List *list, char data)
{
    struct ListItem *item = (struct ListItem*)malloc(sizeof(struct ListItem));

    item->next = NULL;
    item->prev = list->end;
    item->data = data;

    if(!list->begin)
        list->begin = item;

    else
        list->end->next = item;

    list->end = item;
}

void AddToEnd(struct List *list, char data)
{
    struct ListItem *item = (struct ListItem*)malloc(sizeof(struct ListItem));

    item->next = list->begin;
    item->prev = NULL;
    item->data = data;

    if(!list->end)
        list->end = item;

    else
        list->begin->prev = item;

    list->begin = item;
}

void Display(struct List *list)
{
    struct ListItem *item = list->begin;

    while(item) {

        printf("%d", item->data);
        item = item->next;
    }
    printf("\n");
}

void Clear(struct List *list)
{
    struct ListItem *item = list->begin, *temp;

    while(item) {

        temp = item;
        item = item->next;
        free(temp);
    }
}
