//
//  main.c
//  lab6.0
//
//  Created by Tomashik Daniil on 6/2/20.
//  Copyright © 2020 Tomashik Daniil. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// N5.2 variant 10
//Пользователь вводит слова с клавиатуры (ввод прекращается, когда будет введено слово “end”).
//Построить бинарное дерево поиска, каждый узел которого содержит слово,
//и вывести по алфавиту те слова, которые являются палиндромами ( т . е . читаются справа налево и слева направо одинаково).

//Выводится дерево , палиндромы  выделяются зелёным цветом,а остальные - красным.

typedef   struct TreeNode
{
    char* word;
    bool polindrom;
    struct TreeNode* tLeft;
    struct TreeNode* tRight;
}treeNode;
treeNode* Insert( char* value, bool polindrom, treeNode* root)
{
    if (root == NULL)
    {
        root = (treeNode*)malloc(sizeof(treeNode));
        root->word = _strdup(value);
        root->polindrom = polindrom;
        root->tLeft = NULL;
        root->tRight = NULL;
    }
    else
    {
        
        if(strcmp(value, root->word)<0)
        //if (value[0] <= root->word[0])
        {
            root->tLeft = Insert(value, polindrom, root->tLeft);
        }
        else
        {
            root->tRight = Insert(value, polindrom, root->tRight);
        }
    }
    return root;
}
int Counter(char* value)
{
    int counter = 0, i = 0;
    while (value[i] != 0)
    {
        counter++;
        i++;
    }
    return counter;
}
bool CheckPolindrom(char* value)
{
    int len = Counter(value);

    for (int i = 0; i < len / 2; ++i)
    {
        if (value[i] != value[len - i - 1])
        {
            return 0;
        }
    }
    return 1;
}

void Show(treeNode* tree, const int level = 0; )
{
    if (tree->tLeft)
        Show(tree->tLeft, level + 1);
    for (int i = 0; i < level; i++)
        printf("\t");
    if (tree->polindrom)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    }
    else
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
    }
    printf("%s", tree->word);
        printf("\n");
    if (tree->tRight)
        Show(tree->tRight, level + 1);
}


int main()
{
    struct treeNode* tree = NULL;
    bool pol = 0;
    int temp = 0;
    char word[30];
    char close[5] = "end";
    while (true)
    {
        system("cls");
        gets(word);

        if (Counter(word) == 3)
        {
            temp = 0;
            for (int i = 0; i < 4; i++)
            {
                if (word[i] == close[i])
                    temp++;
                if (temp == 3)
                {
                    system("cls");
                    Show(tree);
                    return 0;
                }
            }
        }
        pol = CheckPolindrom(word);
        tree = Insert(word, pol, tree);
    }
}
