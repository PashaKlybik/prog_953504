#pragma once



/* Структура, описывающая узел бинарного дерева */
struct TreeNode
{
    int key;

    TreeNode* left;
    TreeNode* right;
};

/* Структура, описывающая бинарное дерево поиска */
struct Tree
{
    TreeNode* root;

    int pos;
    int size;
};


/* Функция создания экземпляра бинарного поискового дерева */
Tree* CreateTree();

/* Функция добавления узла дерева в дерево */
void PushTreeNode(TreeNode* root, int key);

/* Функция удаления дерева */
void DeleteTree(TreeNode* leaf);