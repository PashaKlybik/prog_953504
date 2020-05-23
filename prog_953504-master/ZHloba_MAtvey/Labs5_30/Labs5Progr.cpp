// Labs5Progr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h> 

#include <string.h> 

struct Date
{
    int info;
    Date* next;
};

class List
{
private:
    Date* head;
public:
    List()
    {
        head = NULL;
      
    }
    void addList(Date *w)
    { 
        Date* per = new Date;
        per->info = w->info;
        per->next = w->next;
        if (head == NULL)
        {
            head = per;
        }
        else
        {
            Date* perr = head;
            while (perr->next != NULL)
                perr = perr->next;
            perr->next = per;
        }
    }
    void PrintInfo()
    {
        Date* per = head;
        while (per != NULL)
        {
            printf("%d ",per->info);
            per = per->next;
        }
    }
    
    Date Time(int i)
    {
        Date* per = head;
        while (per != NULL)
        {
            if (per->info == i)
                return *per->next;
            per = per->next;
        }
    }
    void Delete(int i)
    {
        Date* per = head;
        while (per != NULL)
        {
            
            if (per->info == i)
                per->next = NULL;
            per = per->next;
        }
    }
};

int main()
{
    Date* per = new Date();
    
    List St1, St2, PER;
    int per1=0, per2=0,per3=0;
    std::cout << "Hello World!\n";
    for (int i=1; i < 12;i++)
    {
        per->info = i;
        St1.addList(per);
        St2.addList(per);
    }
    St1.PrintInfo();
    printf("\n");
    St2.PrintInfo();
    while (per1 < 1 || per1 > 11)
    {
        printf("\n Plese give me first number between 0 and 12");
        printf("\n");
        std::cin>>(per1);
        while ((per1 > 1 && per1 < 12) && (per2<per1 || per2>11))
        { 
            printf("\n Plese give me second number between first number-1 and 12");
            printf("\n");
            std::cin >> (per2);        
        }
        
    }
    while (per3 < 1 || per3 > 11)
    {
        printf("\n Plese give me third number between 0 and 12");
        printf("\n");
        std::cin >> (per3);
    }
    Date out = St2.Time(per3); 

    St2.Delete(per3);
  //  St2.PrintInfo();
    per1--;
    for (; per1 < per2; ) 
    {
        Date out1 = St1.Time(per1);
        per = &out1;
        per->next = NULL;
        St2.addList(per);  
            per1++;
    }
    per = &out;
   // printf("\n %d\n", per->info);
    St2.addList(per);
    St2.PrintInfo();

     
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
