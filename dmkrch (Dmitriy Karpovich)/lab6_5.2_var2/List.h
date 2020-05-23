#pragma once

#ifndef SYMBOL
#define SYMBOL

/* Структура, описывающая узел двусвязного списка */
struct Node
{
    Node* next;
    Node* prev;
    int* arr;
    int arrSize;
    int treeNumber;
};


/* Структура, описывающая двусвязный список */
struct DoubleLinkedList
{
    int size;
    Node* head;
    Node* tail;
};


/* Функция создания экземпляра двусвязного списка */
DoubleLinkedList* CreateDblLinkedList();

/* Функция добавления узла в двусвязный список */
void PushNode(DoubleLinkedList* list, int* arr, int arrSize, int treeNumber);

/* Функция удаления списка */
void DeleteList(DoubleLinkedList* list);

#endif