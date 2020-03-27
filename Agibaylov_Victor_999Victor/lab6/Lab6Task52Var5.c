#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct node
{
    char key;
    long count;
    struct node* left, * right;
} node;

void Insert(node** q, char x);
void Display(node* q);
int Count(node* q);

int main()
{
    node* root = NULL;
    char str[100];

    printf("Enter your string pls: ");

    gets_s(str);

    for (int i = 0; i < 100; i++)
    {
        if (str[i] != '\0' && !isdigit(str[i]))
        {
            Insert(&root, str[i]);
        }
        else if(isdigit(str[i]))
        {
            printf("Wrong string elements entered. It looks like you entered numbers instead of letters.\nThe program wel be shutted down.");
            return 0;
        }
        else
        {
            break;
        }
    }

    Display(root);

    printf("Number of leavs: %d", Count(root));
    
    return 0;
}

//добавляет значения
void Insert(node** q, char x)
{
    if (*q == NULL)
    {
        *q = (node*)malloc(sizeof(node));
        (*q)->key = x;
        (*q)->count = 1;
        (*q)->left = (*q)->right = NULL;
    }
    else
    {
        if ((*q)->key == x)
        {
            ((*q)->count)++;
        }
        else
        {
            if ((*q)->key > x)
            {
                Insert(&((*q)->left), x);
            }
            else
            {
                Insert(&((*q)->right), x);
            }
        }
    }
}

//вывод элементов дерева
void Display(node* q)
{
    if (q != NULL)
    {
        Display(q->left);
        printf("%c : %d\n", q->key, q->count);
        Display(q->right);
    }
}

//подсчет кол-ва листьев
int Count(node* q)
{
    if (q == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + Count(q->left) + Count(q->right);
    }
}