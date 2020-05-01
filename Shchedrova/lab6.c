#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode
{
    char *word;
    int count;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct List
{
    char *word;
    int count;
    struct List *next;
};

struct TreeNode *WriteToTree(struct TreeNode *node);
int CheckLetter(char let);
struct TreeNode *AddTree(struct TreeNode *node, char *word);
void WriteInList(struct TreeNode *node, struct List **list);
struct List *AddList(struct List *list, char *word, int count);
void PrintList(struct List *list);
void FreeMemoryTree(struct TreeNode **node);
void FreeMemoryList(struct List **item);

int main()
{
    struct TreeNode *root = NULL;
    struct List *list = NULL;
    root = WriteToTree(root);

    WriteInList(root, &list);
    PrintList(list);
    FreeMemoryTree(&root);
    FreeMemoryList(&list);

    return 0;
}

struct TreeNode *WriteToTree(struct TreeNode *node)
{
    FILE *fileName;
    fileName = fopen("text.TXT", "rb");

    if (!fileName)
    {
        printf("Error: opening file.");
        exit(1);
    }

    while(!feof(fileName)) {

        char letter, word[30] = {'\0'};
        int i = 0;

        while(!feof(fileName)) {

            fread(&letter, sizeof(char), 1, fileName);

            if(!CheckLetter(letter = letter | ' '))
                break;

            word[i++] = letter;
        }

        if(word[0] != '\0')
            node = AddTree(node, word);
    }

    fclose(fileName);
    return node;
}

int CheckLetter(char let)
{
    int bits = ~0UL / 255;
    return (((let - bits * 123) & ~(let)) & (((let) & bits * 127) + bits * 31) & (bits * 128));
}

struct TreeNode *AddTree(struct TreeNode *node, char *word)
{
    int ratio;

    if(!node) {

        node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->word  = strdup(word);
        node->count = 1;
        node->left  = node->right = NULL;
    }

    else if((ratio = strcmp(word, node->word)) == 0)
        node->count++;

    else if(ratio < 0)
        node->left = AddTree(node->left, word);

    else
        node->right = AddTree(node->right, word);

    return node;
}

void WriteInList(struct TreeNode *node, struct List **list)
{
    if(!node)
        return;

    WriteInList(node->left, &(*list));

    (*list) = AddList((*list), node->word, node->count);

    WriteInList(node->right, &(*list));

}

struct List *AddList(struct List *list, char *word, int count)
{
    struct List *item = (struct List*)malloc(sizeof(struct List));

    item->word  = strdup(word);
    item->count = count;
    item->next = NULL;

    if(!list) {

        list = item;
        return list;
    }

    struct List *place = (struct List*)malloc(sizeof(struct List));
    place->next = list;

    while(place->next) {

        if(place->next->count <= item->count) {

            item->next = place->next;
            place->next = item;
            return list;
        }
        place = place->next;
    }
    place->next = item;
    return list;
}

void PrintList(struct List *list)
{
    struct List *place; place = list;

    while(place) {

        printf("%d - %s\n", place->count, place->word);
        place = place->next;
    }
}

void FreeMemoryTree(struct TreeNode **node)
{
    if(*node) {

        FreeMemoryTree(&((*node)->left));
        FreeMemoryTree(&((*node)->right));
        free(*node);
    }
}

void FreeMemoryList(struct List **item)
{
    struct List *temp;

    while(*item) {

        temp = *item;
        *item = (*item)->next;
        free(temp);
    }
}


