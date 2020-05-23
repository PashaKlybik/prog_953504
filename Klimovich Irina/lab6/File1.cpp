// ---------------------------------------------------------------------------

#pragma hdrstop
#include <stdio.h>
#include <stdlib.h>
#include <alloc.h>
#include <conio.h>
#include <tchar.h>
#include <string.h>
// ---------------------------------------------------------------------------
/*5.2(9)¬ текстовом файле содержатс€ n целых чисел в двоичной системе
счислени€ (m бит каждое). ѕостроить бинарное дерево, в котором
числам соответствуют листь€ дерева, а путь по дереву определ€етс€
двоичным представлением числа (С1Т Ц переход к правому потомку,
С0Т Ц переход к левому потомку).*/
#pragma argsused

/* —труктура, описывающа€ узел дерева */
typedef struct item {
	int data; // поле данных
	struct item *left; //левый потомок
	struct item *right; //правый потомок
}Item;

void AddNode(char* data, int count, Item **node, int number);
void PrintTree(Item *node);
void DeleteTree(Item *node);

int _tmain(int argc, _TCHAR* argv[]) {
	char buffer[128];
	int m = 0, n = 0;
	Item *root = NULL; /* корень дерева */
	FILE *fp = fopen("G:\\Ira\\Progr\\LR6\\Binnum.txt", "r");
	if (!fp) {
		puts("ERROR");
		getch();
		return 1;
		}
	/* —читываем значени€ из файла построчно */
	while (fgets(buffer, 128, fp) != NULL) {
		++n;
		printf("%s", buffer); // вывод содержимого файла
	}
	rewind (fp); // возвращение в начало файла
	fgets(buffer, 128, fp);
	while (buffer[m]!=NULL) {
		++m;
	}
	--m;
	printf("\n%d numbers %d bits each\n", n, m);// выводит количество чисел и бит в числе
	rewind (fp); // возвращение в начало файла
    while (fgets(buffer, 128, fp) != NULL) {
		AddNode(buffer, m-1, &root, atoi(buffer));
	}
	PrintTree(root);
	DeleteTree(root);
	fclose(fp);
	getch();
	return 0;
}
void DeleteTree(Item *node) {
	if(node!=NULL) {
		DeleteTree(node->left);
		DeleteTree(node->right);
		free(node);
	}
}

/* ƒобавить число в дерево */
void AddNode(char* data, int count, Item **node, int number) {
	if (*node == NULL) {      // если узла нет
		*node = (Item*)malloc(sizeof(Item));  // выдел€ем пам€ть под новый узел
		(*node)->data = NULL;
		(*node)->left = (*node)->right = NULL;
	}
	if (count == 0) {  // если перебрали всве цифры числа кроме последнего
		Item *newnode = (Item*)malloc(sizeof(Item));
		newnode->right = newnode->left = NULL;
		newnode->data = number;
		if (data[count]=='1') {        //  заполн€ем узел числом
			(*node)->right = newnode;
		}
		else (*node)->left = newnode;
		return;
	}
	if (data[count] == '1') {
		--count;                      // добавл€ем правый потомок
		AddNode(data, count, &(*node)->right, number);
	}
	else if (data[count] == '0') {
		--count;                      // добавл€ем левый потомок
		AddNode(data, count, &(*node)->left, number);
	}
}

// ¬ывод дерева
void PrintTree(Item *node) {
	if (node != NULL) { // если узел не пустой
		PrintTree(node->left); //рекурсивна€ функци€ дл€ левого поддерева
		if (node->data != NULL) { // если есть данные в этом узле
			printf("%d ", node->data); //отображаем их
		}
		PrintTree(node->right); //рекурсивна€ функци€ дл€ правого поддерева
	 }
}
// ---------------------------------------------------------------------------
