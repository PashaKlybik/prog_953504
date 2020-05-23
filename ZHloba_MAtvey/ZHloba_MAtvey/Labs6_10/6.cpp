// 6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// ProgramingLab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>



struct Date {
	std::string data;
	
	struct Date* left;
	struct Date* right;
};



int Check(std::string str)
{
	int m = 1;
	for (int i = 0; i <= str.length() - 1; i++)
	{
		if (str[i] != str[str.length() - 1 - i])
			m++;
	}
	return m;
}


void Add(std::string data, Date** node)
{
	if (*node == NULL) {
		*node = (Date*)calloc(1, sizeof(Date));
		(*node)->data = (*node)->data+data;
		(*node)->left = (*node)->right = NULL;
	}
	else {
		if (data < (*node)->data)
			Add(data, &(*node)->left);
		else if (data > (*node)->data)
			Add(data, &(*node)->right);
		else
			puts("There is such element in the tree");
	}
}

void Print(Date* head)
{
	if (head != NULL)
	{
		Print(head->left);
		if (Check(head->data) == 1)
			std::cout << head->data<<" ";
		Print(head->right);
	}
}








int main()
{
	std::string info = "b";
	Date* tree = NULL;
	while (info != "end")
	{
		std::cin >> info;
		if (info !="end")
			Add(info, &tree);
	}
	Print(tree);
	

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
