/*В текстовом файле записаны целые числа. Построить бинарное
дерево поиска, в узлах которого хранятся числа из файла.
Разработать функцию, определяющую число узлов дерева на
каждом уровне.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

/* Структура, описывающая узел дерева */
typedef struct item
{
    int data;
    struct item *left;
    struct item *right;

} Item;

void AddNode(int data, Item **node)
{
    if (*node == NULL)
    {
        *node = (Item *)calloc(1, sizeof(Item));

        (*node)->data = data;

        (*node)->left = (*node)->right = NULL;
    }
    else
    {
        if (data < (*node)->data)
        {
            AddNode(data, &(*node)->left);
        }
        else if (data > (*node)->data)
        {
            AddNode(data, &(*node)->right);
        }
        else
        {
            puts("There is such element in the tree");
        }
    }
}

void PrintTree(Item *node, const char *dir, int level)
{
    if (node)
    {
        printf("Level: %d - %d (%s)\n", level, node->data, dir);
        PrintTree(node->left, "left", level+1);
        PrintTree(node->right, "right", level+1);
    }
}

void Number_of_nodes(Item *node, const char *dir, int level, int *n, int *count, int N)
{
    if (node)
    {
        if (level == N)
        {
            count[N] += 1;
            N++;
            *n = N;

        }
        Number_of_nodes(node->left, "left", level + 1, n, count, N);
        Number_of_nodes(node->right, "right", level + 1, n, count, N);
    }
}

int main()
{
    char *file_numbers = (char*)malloc(100);
    Item *root = NULL; /* корень дерева */

    printf("File contents:\n");

    FILE *file;
    file = fopen("№5.2 - 4.txt", "r");
    if (!file)
    {
        printf("Error");
    }
    else
    {
        while (fgets(file_numbers, 100, file) != NULL)
        {
            AddNode(atoi(file_numbers), &root); /* и добавляем в дерево */
            printf("%d ", atoi(file_numbers));
        }
    }
    fclose(file);

    printf("\n\nTree:\n\n");

    PrintTree(root, "root", 0);

    int *count = (int*)malloc(100);
    int n = 0;
    for (int i = 0; i < 30; i++)
    {
        count[i] = 0;
    }

    Number_of_nodes(root, "root", 0, &n, count, 0);

    for (int i = 0; i < n; i++)
    {
        printf("\n\nLevel: %d. Number_of_nodes: %d", i, count[i]);
    }
    return 0;
}

