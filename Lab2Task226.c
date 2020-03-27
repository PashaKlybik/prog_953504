/*2.2 (6). Численно убедиться в справедливости равенства, для чего для
заданного значения х вычислить его левую часть и разложение,
стоящее в правой части. При каком n исследуемое выражение
отличается от sin x менее, чем на заданную погрешность ε?
Испытать разложение на сходимость при разных значениях х. 
*/

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

double funcFormula(int x, int n);
void factorial(int num, int& factorialNumber);

int main()
{
    int x, numberOfTimes; 
    double e;

    //беск. цикл пока пользователь не введет нужное значение
    for (;;)
    {
        printf("Enter x number: ");

        std::cin >> x;

        if ((x <= 2147483647) & (x >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    for (;;)
    {
        printf("Enter number of times: ");

        std::cin >> numberOfTimes;

        if ((numberOfTimes <= 2147483647) & (numberOfTimes >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    for (;;)
    {
        printf("Enter e number: ");

        std::cin >> e;

        if ((e <= 2147483647) & (e >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    for (int i = 1; i <= numberOfTimes; i++) 
    {
        if (sin(x) - (funcFormula(x, i)) < e)
        {
            printf("%f", sin(x));
            printf("\n");
            printf("%f", funcFormula(x, i));
            printf("\n");
            printf("The n is: \n");
            printf("%d", i);
            printf("\n");
        }
    }
}

//осн. функция
double funcFormula(int x, int n)
{
    double result = 0;

    for (int i = 1; i <= n; i++)
    {
        int factorialNum = 1;
        factorial(2 * i - 1, factorialNum);
        //std::cout << "Factorial: " << factorialNum << "\n";
        result += pow(-1, i - 1) * pow(x, 2 * i - 1) / factorialNum;
    }

    return result;
}

//отлельная фкнкция вычисления факториала
void factorial(int num, int &factorialNumber)
{
    if (num >= 1)
    {
        factorialNumber *= num;
        factorial(num - 1, factorialNumber);
    }
}