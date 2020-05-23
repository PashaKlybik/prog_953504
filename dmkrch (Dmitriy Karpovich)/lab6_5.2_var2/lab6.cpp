#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "List.h"  // Заголовочный файл двусвязного списка
#include "Tree.h"  // Заголовочный файл дерева
#include "Stack.h" // Заголовочный файл стэка



/* Функция формирования деревьев на основе информации, хранящейся в двусвязном списке. Получает List - список и
   treeStack - для хранения полученных деревьев */
void AddTreeFromList(DoubleLinkedList* List, Stack* treeStack)
{
    Node* currListNode = (Node*)malloc(sizeof(Node)); // создаем временную переменную чтобы делать обход по узлам двусвязного списка
    currListNode = List->head; // устанавливаем значение в "голову" списка

    for (int i = 0; i < List->size; ++i)
    {

        Tree* tree = CreateTree(); // создаем дерево

        tree->pos = currListNode->treeNumber; // устанавливаем поле pos дерева

        for (int k = 0; k < currListNode->arrSize; ++k) // цикл добавления узлов дерева на основе массива целых чисел
        {

            if(tree->root != NULL)
                PushTreeNode(tree->root, currListNode->arr[k]);
            else
            {
                TreeNode* newNode = new TreeNode();
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->key = currListNode->arr[k];

                tree->root = newNode;
            }
        }


        // экземпляр класса Tree - tree полностью сформирован и теперь может быть добавлен в стэк
        PushTree(treeStack, tree);


        // теперь надо установить указатель в временной переменной на след адрес, чтобы заново считать данные и сделать новое дерево
        currListNode = currListNode->next;
    }
}


void ShowHighestKeyOfTrees(Stack* treeStack)
{
    StackNode* currNode = treeStack->head; // создаем временную переменную обозначающую текущий узел стэка

    while(currNode != NULL)
    {
        TreeNode* root = currNode->tree->root; // создаем узел дерева текущего узла стэка для поиска

        while (root->right != NULL)  // по окончанию цикла в root лежит узел, значение которого максимально
            root = root->right;
        
        printf("Max key of tree #%d = %d\n", currNode->tree->pos, root->key);

        currNode = currNode->next; // устанавливаем значение текущего узла стэка на следущий узел
    }
}

int main()
{
    DoubleLinkedList* List = CreateDblLinkedList();

    int arr[3] = { 1,2,3 };
    int arr1[4] = { 3,7,4,8 };
    int arr2[5] = { 2,9,7,3,6 };

    PushNode(List, arr, 3, 34);
    PushNode(List, arr1, 4, 75);
    PushNode(List, arr2, 5, 22);
    // На данный момент сформирован двусвязный список List с тремя узлами, которые позже мы сможем преобразовать в деревья


    // Теперь создаем стэк(контейнер) для хранения деревьев
    Stack* treeStack = CreateStack();

    //Добавляем в стэк деревья на основе информации, лежащей в узлах двусвязного списка
    AddTreeFromList(List, treeStack);


    // Теперь в переменной treeStack сформированы деревья и можно вызвать 
    // функцию моего варианта для отображения наибольшего числа в каждом дереве
    ShowHighestKeyOfTrees(treeStack);

    DeleteList(List);
    DeleteStack(treeStack);
}