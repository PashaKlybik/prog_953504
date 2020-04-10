#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <conio.h>

using namespace std;

typedef struct tree
{
    int key;
    struct tree* left;
    struct tree* right;
} node;

node* Create(node* root, int key)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}
void Add(node** Node, int x) 
{
    if ((*Node == NULL))  //Если дерева не существует
    {
        (*Node) = new node; //Выделяем для него память
        (*Node)->left = (*Node)->right = NULL; //И очищаем пути дальнейшего роста
        (*Node)->key = x; //Записываем информацию в узел на выделенное место
    }
    else //Если дерево уже есть
    {            //Сравниваем корень дерева с вводимым элементом
        if (x < (*Node)->key) Add(&(*Node)->left, x); //Если он меньше, пытаемся записать в левое поддерево
        else Add(&(*Node)->right, x); //Если больше, пытаемся в правое   
    }
}
node* search(node* root, int key)
{
    // Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
    if ((root == NULL) || (root->key = key))
        return root;
    // Поиск нужного узла
    if (key < root->key)
        return search(root->left, key);
    else return search(root->right, key);
}
void SortBubble(int mass[] , int k)
{
    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < k - 1; i++)
        {
            if (mass[i] > mass[i + 1])
            {
                flag = 1;
                int tmp = mass[i];
                mass[i] = mass[i + 1];
                mass[i + 1] = tmp;
            }
        }
    }
}
void Show(node* Node)
{
    if (Node == NULL)   
        return;    //Если дерева нет, выходим

    cout << Node->key << endl; //Посетили узел
    Show(Node->left); //Обошли левое поддерево   
    Show(Node->right); //Обошли правое поддерево 
}
//Functions get and lvl show number of nodes on each level
int get(node* node, int n, int c)
{
    if (n == c)  return 1;
    return ((node->left) ? get(node->left, n, c + 1) : 0) + ((node->right) ? get(node->right, n, c + 1) : 0);
}
void lvl(node* node) {
    int t = 0, l = 0;
    while ((l = get(node, t++, 0)) != 0) {
        printf("lvl(%d) = %d\n", t, l);
    }
}
int main()
{
    int s = 0, k = 0;
    FILE* f;
    f = fopen("C:\\Users\\AnatoliHP\\Documents\\Embarcadero\\Studio\\Projects\\953504\\Прогр-е 1сем\\лр6(4)\\123.txt","r");
    while ((fscanf(f, "%d", &s) != EOF))
    {
        if (!f) break;   
        k += 1;
    }
    int* c = (int*)malloc(k * sizeof(int));  
    rewind(f);    //перематываем файл для повторного чтения
    for (int i = 0; i < k; i++)
    {
        fscanf(f, "%d", &c[i]);
    }
    fclose(f);
    int flag = 1;
    //sort numbers from the file
    SortBubble(c, k);
    printf("\n");
    node* tree = (node*)malloc(sizeof(node));
    //root of the tree will be the central member of the array
    tree = Create(tree, c[k / 2]);
    for (int i = 0; i < k / 2; i++)
    {
         Add(&tree ,c[i]);
    }
    for (int i = k/2+1; i < k; i++)
    {
         Add(&tree , c[i]);
    }
    printf("\n");
    Show(tree);
    printf("\n");
    lvl(tree);
    return 0;
}
