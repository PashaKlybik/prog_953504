/*2.1 (2). Рациональные числа. Разработать программу, меню которой
позволяет выполнить следующие функции:
1. Ввод (числитель и знаменатель) двух рациональных чисел.
2. Вывод двух рациональных чисел (в форме: m n).
3. Сложение чисел.
4. Вычитание чисел.
5. Умножение чисел.
6. Деление чисел.
7. Получение гармонического значения двух чисел.
8. Информация о версии и авторе программы.
9. Выход из программы.
Справка: Гармоническое значение двух чисел получается путем
получения обратных значений двух чисел, усреднения их и
получения обратного значения результата. */

#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <Math.h>

void info();
void input(long int& a, long int& b);
void output(long int a, long int b);
void sum();
void substraction();
void multiply();
void division();
void harmonicValue();

int main()
{
    long int a = 0, b = 0;

    //беск. цикл пока пользователь не введет правильное значение
    for (;;)
    {
        char fuse;

        printf("Choose any function\n");
        printf("1) Enter two numbers;\n");
        printf("2) Output of two numbers;\n");
        printf("3) Addition;\n");
        printf("4) Substraction;\n");
        printf("5) Multiplication;\n");
        printf("6) Division;\n");
        printf("7) Harmonic value;\n");
        printf("8) Information about the version of program and its creator;\n");
        printf("9) EXIT;\n");

        std::cin >> fuse;
        int trigger = 0;

        if (isdigit(fuse) != 0)
        {
            trigger = 1;
        }

        if (trigger == 1)
        {
            if ((fuse - '0') < 10)
            {

                if (fuse == '9')
                {
                    printf("User stopperd program\n");
                    return 0;
                }
                else
                {
                    switch (fuse)
                    {
                    case '1': input(a, b); break;
                    case '2': output(a, b); break;
                    case '3': sum(); break;
                    case '4': substraction(); break;
                    case '5': multiply(); break;
                    case '6': division(); break;
                    case '7': harmonicValue(); break;
                    case '8': info(); break;
                    }

                    printf("Done successfully\n");
                }
            }
            else
            {
                printf("Too big number entered\n");
            }
        } 
        else
        {
            printf("Incorrect value entered, pls try again");
        }
    }
}

//инфа о создателе и проге
void info()
{
    printf("Program version: 1.0.0\nProgram author: Agibaylov Victor\n");
}

//ввод данных
void input(long int &a, long int &b) 
{
    long int aNum, bNum;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> aNum;

        if ((aNum <= 2147483647) & (aNum >= -2147483648))
        {
             a = aNum;
             break;
        }
        else
        {
             printf("Incorrect number, enter again pls\n");
        }
    }

    for (;;)
    {
        printf("Enter b number: ");

        std::cin >> bNum;

            if ((bNum <= 2147483647) & (bNum >= -2147483648))
            {
                b = bNum;
                break;
            }
            else
            {
                printf("Incorrect number, enter again pls\n");
            }
    }
}

void output(long int a, long int b)
{
    printf("The number is: \n");
    printf("%d", a);
    printf("\n");
    printf("-");
    printf("\n");
    printf("%d", b);
    printf("\n");
}

//вывод суммы
void sum() 
{
    long int a, b, sum;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> a;

        if ((a <= 2147483647) & (a >= -2147483648))
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
        printf("Enter b number: ");

        std::cin >> b;


        if ((b <= 2147483647) & (b >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    sum = a + b;

    printf("%d", sum);
    printf("\n");
}

//вывод рвзницы
void substraction()
{ 
    long int a, b, sub;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> a;

        if ((a <= 2147483647) & (a >= -2147483648))
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
        printf("Enter b number: ");

        std::cin >> b;

        if ((b <= 2147483647) & (b >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    sub = a - b;

    printf("%d", sub);
    printf("\n");
}

//умножение
void multiply() 
{
    long int a, b, mult;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> a;

        if ((a <= 2147483647) & (a >= -2147483648))
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
        printf("Enter b number: ");

        std::cin >> b;

        if ((b <= 2147483647) & (b >= -2147483648))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    mult = a * b;

    printf("%d", mult);
    printf("\n");
}

//деление
void division()
{
    double div;
    long int a, b;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> a;

        if ((a <= 2147483647) & (a >= -2147483648))
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
        printf("Enter b number: ");

        std::cin >> b;

        if ((b <= 2147483647) & (b >= -2147483648) & (b > 0))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    div = a * pow(b, -1);

    printf("%f", div);
    printf("\n");
}

//гармоническое число
void harmonicValue()
{
    long int a, b;

    for (;;)
    {
        printf("Enter a number: ");

        std::cin >> a;

        if ((a <= 2147483647) & (a >= -2147483648))
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
        printf("Enter b number: ");

        std::cin >> b;

        if ((b <= 2147483647) & (b >= -2147483648) & (b > 0))
        {
            break;
        }
        else
        {
            printf("Incorrect number, enter again pls\n");
        }
    }

    double aChanged = pow(a, -1);
    double bChanged = pow(b, -1);
    double midVal = (aChanged + bChanged) / 2;
    double harmonicValue = pow(midVal, -1);

    printf("%f \n", harmonicValue);
}
