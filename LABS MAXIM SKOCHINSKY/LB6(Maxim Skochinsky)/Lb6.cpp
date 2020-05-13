
// Задание 5.2(24) Cкочинский М.В.(гр. №953504)

/*Построить бинарное дерево поиска из букв строки, вводимой
пользователем. Разработать функцию, которая для заданной буквы
определяет число узлов в правом и левом поддеревьях. 
*/

#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <conio.h>

using namespace std;


typedef struct ROOT//Структура "Дерево"
{
    char symbol;// в переменной будет хранится уникальный символ из строки.
    long count;// кол-во таких символов.
    struct ROOT* left, * right;// указатель на правого и левого потомка.
} ROOT;

void Insert(ROOT** root, char x)// добавление символа из строки в дерево
{
    if (*root == NULL)// если дерево пустое, то
    {
        *root = (ROOT*)malloc(sizeof(ROOT));// выделяем память под корень
        (*root)->symbol = x; // в корень кладём наш символ 
        (*root)->count = 1;// пока что такой символ единственный
        (*root)->left = (*root)->right = NULL;// правый и левый потомки пока что не существуют, есть только корень.
    }
    else // иначе
    {
        if ((*root)->symbol == x) //  если символ из данного узла равен проверяемому символу x, то 
            ((*root)->count)++; // увеличиваем счетчик в данном узле на единицу
        else// иначе
            if ((*root)->symbol > x) // если наш проверяемый символ находится в алфавите до символа из узла, то 
                Insert(&((*root)->left), x);// идем по левой части дерева(рекурсия)
            else Insert(&((*root)->right), x);// иначе, идем по правой части.
    }
}

void Display(ROOT* root) // показать все буквы, хранящиеся в дереве, и их кол-во.
{
    if (root != NULL)
    {
        Display(root->left);
        printf("%c : %d\n", root->symbol, root->count);
        Display(root->right);
    }
}

long Count(ROOT* q)// высчитать кол-во узлов в правом и левом поддеревьях для определенного символа
{
    return q == NULL ? 0 : 1 + Count(q->left) + Count(q->right);
}

ROOT* Search(ROOT* root, char x) // поиск символа в дереве
{
    if (root == NULL)// дерево пустое - возращаем указатель на пустоту.
        return NULL;
    else// иначе 
        if (root->symbol == x) // если в данном узле содержится наш символ
            return root;// возращаем указатель на него.
        else// иначе 
            if (root->symbol > x) // если нужный символ "меньше", то осуществляем поиск в левом потомке.
                return Search(root->left, x);
            else// иначе 
                return Search(root->right, x); // поиск в правом потомке.
}






int main()
{
    setlocale(LC_ALL, "Russian");
    ROOT* root = NULL, * q;
    char str[20];
    char c;
    printf("Введите строку:");
    scanf_s("%s", str, 20);
    printf("Введите символ для поиска: ");
    scanf_s(" %c", &c);
    char* pstr;// ps - указатель на строку, с - символ, для которого мы будем считать кол-во узлов.
    for (pstr = str; *pstr; ++pstr) // пробегаемся по строке, начиная с первого символа. 
        Insert(&root, *pstr);// вставляем данный символ в дерево.
    Display(root);// показываем всё, что содержится в дереве
    if (q = Search(root, c))// ищем указатель на узел, в котором хранится символ c. 
    {
        printf("left: %d\n", Count(q->left));// выписывем число узлов в левом поддереве для узла q.
        printf("right: %d\n", Count(q->right));// выписывем число узлов в правом поддереве для узла q.
    }

    return 0;
}