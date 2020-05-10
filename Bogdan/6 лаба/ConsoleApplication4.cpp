#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cmath>

/*
 * Нужно реализовать дерево и спускать значения по поддеревьям основываясь на таком принципе
 * если число 101010, то идя справа берём по крайней справа цифре, т.е. сначала 0, потом 1, 0 1, 0, 1
 * Где 1 значит переход вправо, 0 - влево
 */

struct tnode
{
    std::string field;           // поле данных
    struct tnode* left;  // левый потомок
    struct tnode* right; // правый потомок
};

void treeprint(tnode* tree) {
    if (tree != NULL) { //Пока не встретится пустой узел
        treeprint(tree->left); //Рекурсивная функция для левого поддерева
        if (tree->field != "NULL")
            printf("%s ", tree->field.c_str()); //Отображаем корень дерева
        treeprint(tree->right); //Рекурсивная функция для правого поддерева
    }
}

void addnode(std::string x, tnode* &tree, std::string x_full, int count) {
    if (tree == NULL) // Если дерева нет, то формируем корень
    {
        tree = new tnode; // память под узел
        tree->field = "NULL";
        tree->left = NULL;
        tree->right = NULL; // ветви инициализируем пустотой
    }

    if (x == "1" || x == "0")
    {
    	if(x=="1")
    	{
            tnode *tree_new = new tnode;
            tree_new->right = tree_new->left = NULL;
            tree->right = tree_new;
            x_full.resize(6);
            tree_new->field = x_full;
    	}
        else
        {
            tnode* tree_new = new tnode;
            tree_new->right = tree_new->left = NULL;
            tree->left = tree_new;
            x_full.resize(6);
            tree_new->field = x_full;
        } // заполняем ячейку, если убедились, что спустились вниз
    	return;
    }
    if (x[count] == '0')   // условие добавление левого потомка
    {
        std::string buffer = x;
        buffer.resize(count);
        addnode(buffer, tree->left, x_full, count - 1);
    }
    else    // условие добавление правого потомка
    {
        std::string buffer = x;
        buffer.resize(count);
        addnode(buffer, tree->right, x_full, count - 1);
    }
}

void freemem(tnode* tree)
{
    if (tree != nullptr)
    {
        freemem(tree->left);
        freemem(tree->right);
        delete tree;
    }
}

int main()
{
    tnode* root = nullptr;
    int n = 0, m = 0;
    printf("Enter n: ");
    scanf_s("%d", &n);              //Ввод данных
    printf("Enter m: ");
    scanf_s("%d", &m);

    FILE* fp;
    fopen_s(&fp, "Text.txt", "r");              //Чтение файла

    char ch = 0;
    int i = 0;
    auto numbers = new std::string[n];

    do {
        ch = getc(fp);
        if (ch == ' ')
        {
            numbers[i] += '\0';         //Если пробел встречаем, меняем номер слова
            i++;
        }
        else
            numbers[i] += ch;               //Лепис справа новый символ встречающийся, если не пробел втречается
    } while (ch != EOF);

    for (int i = 0; i < n; i++)
    {
        printf("%s\n", numbers[i].c_str());         //Вывод в консоль чисел для самопроверки
    }

    for (int i = 0; i < n; i++)
    {
        addnode(numbers[i], root, numbers[i], m - 1);           //Вот тут уже спускаем числа вниз по одному
    }

    treeprint(root);            //Вывод дерева

    fclose(fp);

    getchar();
    return 0;
}