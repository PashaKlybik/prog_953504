//Дано кольцо, элементы которого содержат целые числа.
//Сформировать на основе кольца бинарное дерево поиска.Вывести самую длинную ветвь в получившемся дереве.

#include <stdio.h>
#include <stdlib.h>

struct dvusp
{
    public:

	int x;
	dvusp* prev, * next;
};

	void pri(dvusp* head)
	{
		if (head)
		{
			dvusp* curr = head;
			while (curr)
			{
				printf("%d   ",curr->x);
				curr = curr->next;
			}
		}
		printf("\n");
	}


	void makeQ(dvusp** head, int r)
	{
		dvusp* ne = (dvusp*)malloc(sizeof(dvusp));
		ne->x = r;
		ne->next = NULL;
		ne->prev = NULL;
		if (!*head)
			*head = ne;
		else
		{
			dvusp* curr = *head;
			while (curr->next) curr = curr->next;
			curr->next = ne;
			ne->prev = curr;
		}
	}

	bool isEl(dvusp* head, int t)
	{
		dvusp* ne = (dvusp*)malloc(sizeof(dvusp));
		ne = head;
		while (ne)
		{
			if (ne->x == t) return true;
			ne = ne->next;
		}
		return false;
	}


struct tree
	{
	public:

		int key;
		tree* l, * r;
	};

	void push(tree** t, int x)
	{
		if ((*t) == NULL)
		{
			tree* st = (tree*)malloc(sizeof(tree*));
			st->key = x;
			st->l = st->r = NULL;
			*t = st;
			return;
		}

		if (x > (*t)->key) push(&((*t)->r), x);
		else push(&((*t)->l), x);
	}

	int max(int a, int b)
	{
		return (a >= b) ? a : b;
	}

	int height(tree* t)
	{
		if (t == NULL) return 0;
		else return 1 + max(height(t->l), height(t->r));
	}

	void print(tree* t, int u) {
		if (t == NULL) return; 
		else 
		{
			print(t->l, ++u); 	
			for (int i = 0; i < u; ++i) printf("|");
			printf("%d\n", t->key);
		}
		print(t->r, ++u); 
    }



int main()
{
	int n = 0, k;
	dvusp* head = (dvusp*)malloc(sizeof(dvusp));
	head = NULL;
	printf("How much numbers do you want to enter?\n");
	while (true)
	{
		scanf_s("%d",&n);
		if (n == 0) return 0;
		if (n > 0) break;
		printf("Try again!\n");
	}
	for (int i = 0; i < n; i++)//создаём двусвязный список
	{
		while (true)
		{
			printf("#%d=", i + 1);
			scanf_s("%d", &k);
			if (isEl(head, k) == 0)
			{
				makeQ(&head, k);
				break;
			}
			else printf("You have already enter this number!\n");
		}
	}
	dvusp* curr = (dvusp*)malloc(sizeof(dvusp));
	curr = head;
	while (curr->next) curr = curr->next;
	//замыкаем его в кольцо
	curr->next = head;
	head->prev = curr;
	//с созданием кольца покончено

	//начинаем переводить его в дерево
	tree* root = (tree*)malloc(sizeof(tree));
	root = NULL;
	dvusp* ne = (dvusp*)malloc(sizeof(dvusp));
	ne = head;
	push(&root, ne->x);
	ne = ne->next;
	while (ne!=head)
	{
		push(&root, ne->x);
		ne = ne->next;
	}

	print(root, 0);//метод отображения всего дерева

	//вывод самой длинной ветки 
	int h = height(root);
	tree* re = (tree*)malloc(sizeof(tree));
	re = root;
	printf("The most long branch:\n%d ", re->key);
	int i = 1, z = 0;
	while (re->l||re->r)
	{
		z = height(re->r);
		if (z + i == h)
		{
			re = re->r;
			printf("%d ",re->key);
		}
		else
		{
			re = re->l;
			printf("%d ", re->key);
		}
		i++;
	}

	free(re);
	free(root);
	free(ne);
	free(head);
	free(curr);

	return 0;
}