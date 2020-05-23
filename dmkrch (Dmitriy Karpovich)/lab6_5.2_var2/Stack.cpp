#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Tree.h"
#include "Stack.h"


Stack* CreateStack()
{
    Stack* tmp = (Stack*)malloc(sizeof(Stack));
    tmp->size = 0;
    tmp->head = NULL;

    return tmp;
}


void PushTree(Stack* treeStack, Tree* tree)
{
    if (treeStack->head == NULL)
    {
        StackNode* nodeForAdd = (StackNode*)malloc(sizeof(StackNode));
        nodeForAdd->tree = tree;
        nodeForAdd->next = NULL;

        treeStack->head = nodeForAdd;

        ++treeStack->size;
    }

    else
    {
        StackNode* currListNode = (StackNode*)malloc(sizeof(StackNode));
        currListNode = treeStack->head; // устанавливаем значение временной переменной как корень списка

        while (true)
        {
            if (currListNode->next == NULL) // нашли последний узел в списке
            {
                StackNode* nodeForAdd = (StackNode*)malloc(sizeof(StackNode)); // создаем временную переменную ( узел стэка )

                nodeForAdd->tree = tree; // устанавливаем в новом узле ссылку на дерево
                nodeForAdd->next = NULL; // устанавливаем в новом узле ссылку на след. узел

                currListNode->next = nodeForAdd; // присваиваем предпоследнему узлу в поле next - добавленный новый узел

                ++treeStack->size;
                break; // выходим из цикла и функции
            }

            currListNode = currListNode->next; // присваиваем значению узла ссылку на следующий узел
        }
    }
}

void DeleteStack(Stack* stack)
{
    StackNode* item = stack->head;
    StackNode* next;

    while (item->next != NULL)
    {
        next = item->next;

        free(item);

        item = next;
    }

    free(item);
}