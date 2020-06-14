#include <stdio.h>
#include <stdlib.h>
struct Node {
 int key; //  ������ (����)
struct Node *left, *right;
 };
typedef struct Node *PNode; // ��������� �� �������

PNode MakeTree (int data[], int from, int n)
{
PNode Tree;
int n1, n2;
if ( n == 0 ) return NULL; // ����������� ��������
Tree =  (struct Node*)malloc(1 * sizeof(struct Node));// �������� ������ ��� �������
Tree->key = data[from]; // �������� ������ (����)
n1 = n / 2; // ������� �����������
n2 = n - n1 - 1;
Tree->left = MakeTree(data, from+1, n1);
Tree->right = MakeTree(data, from+1+n1, n2);
return Tree;
}

void PrintLKP(PNode Tree)
{
if ( ! Tree ) return; // ������ ������ � ��������� ��������
PrintLKP(Tree->left); // ����� ������ ���������
printf("%d ", Tree->key); // ����� ���������� � �����
PrintLKP(Tree->right); // ����� ������� ���������
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
    PNode Tree; // ��������� �� ������ ������
    int n = sizeof(data) / sizeof(int) /*- 1*/; // ������ �������
    Tree = MakeTree (data, 0, n); // ������������ n ���������, ������� � ������ 0
    PrintLKP( Tree);
PNode tree = NULL;
 tree=TreeeMake(Tree, tree);
 PrintLKP( tree);

    return 0;
}
