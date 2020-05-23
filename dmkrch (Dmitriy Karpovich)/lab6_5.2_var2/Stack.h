#pragma once



/* Структура, описывающая узел стэка, хранящего деревья */
struct StackNode
{
    Tree* tree;
    StackNode* next;
};

/* Структура, описывающая узел стэка, хранящего деревья */
struct Stack
{
    StackNode* head;

    int size;
};


/* Функция создания экземпляра стэка */
Stack* CreateStack();

/* Функция добавления дерева "tree" в стэк "treeStack" */
void PushTree(Stack* treeStack, Tree* tree);

/* Функция удаления стэка */
void DeleteStack(Stack* stack);