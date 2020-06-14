#include <stdio.h>
#include <stdlib.h>
struct Node {
 int key; //  данные (ключ)
struct Node *left, *right;
 };
typedef struct Node *PNode; // указатель на вершину

PNode MakeTree (int data[], int from, int n)
{
PNode Tree;
int n1, n2;
if ( n == 0 ) return NULL; // ограничение рекурсии
Tree =  (struct Node*)malloc(1 * sizeof(struct Node));// выделить пам€ть под вершину
Tree->key = data[from]; // записать данные (ключ)
n1 = n / 2; // размеры поддеревьев
n2 = n - n1 - 1;
Tree->left = MakeTree(data, from+1, n1);
Tree->right = MakeTree(data, from+1+n1, n2);
return Tree;
}

void PrintLKP(PNode Tree)
{
if ( ! Tree ) return; // пустое дерево Ц окончание рекурсии
PrintLKP(Tree->left); // обход левого поддерева
printf("%d ", Tree->key); // вывод информации о корне
PrintLKP(Tree->right); // обход правого поддерева
}
PNode AddtoTree (PNode Tree, int data)
{
if ( ! Tree ) {
 Tree = (struct Node*)malloc( sizeof(struct Node));
 Tree->key = data;
 Tree->left = NULL;
 Tree->right = NULL;
 return Tree;
 }
if ( data < Tree->key )
 Tree->left=AddtoTree ( Tree->left, data );
else if(data > Tree->key) Tree->right=AddtoTree( Tree->right, data );
     return Tree;
}
PNode TreeeMake(PNode node, PNode result) {
	if (node == NULL)return result;
		//Sort2((node)->left, &(*result));
		result = AddtoTree( result,node->key);
		 result=TreeeMake(node->left, result);
		 result=TreeeMake(node->right, result);
		 return result;
}
void Tree_clear(PNode Tree) {

	if (!Tree)
		return;
	Tree_clear(Tree->left);
	Tree_clear(Tree->right);
	free(Tree);
}



int main()
{
    int data[] = { 21, 8, 9, 11, 15, 19, 20, 21, 7 };
    PNode Tree; // указатель на корень дерева
    int n = sizeof(data) / sizeof(int) /*- 1*/; // размер массива
    Tree = MakeTree (data, 0, n); // использовать n элементов, начина€ с номера 0
    PrintLKP( Tree);
PNode tree = NULL;
 tree=TreeeMake(Tree, tree);
 PrintLKP( tree);

    return 0;
}
