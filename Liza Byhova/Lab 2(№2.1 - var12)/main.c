/*Треугольник. Разработать программу, меню которой позволяет
выполнить следующие функции:
1. Ввод координат вершин треугольника.
2. Определить вид треугольника (правильный, прямоугольный,
равнобедренный, произвольного вида).
3. Вывод периметра треугольника.
4. Вывод площади треугольника.
5. Вычислить и вывести радиусы вписанной и описанной вокруг
треугольника окружностей.
6. Информация о версии и авторе программы.
7. Выход из программы.
*/

#include <stdio.h>
#include <stdlib.h>

void Input (int *Ax, int *Ay, int *Bx, int *By, int *Cx, int *Cy)
{
    printf("Ax: ");
    scanf("%d", *&Ax);
    printf("Ay: ");
    scanf("%d", *&Ay);
    printf("\nBx: ");
    scanf("%d", *&Bx);
    printf("By: ");
    scanf("%d", *&By);
    printf("\nCx: ");
    scanf("%d", *&Cx);
    printf("Cy: ");
    scanf("%d", *&Cy);
}

void Type (int AB, int BC, int AC)
{
    if (AB == BC == AC)
    {
        printf("correct.\n\n"); //правильный
    }
    else if ((AB == sqrt(BC*BC + AC*AC)) || (BC == sqrt(AB*AB + AC*AC)) || (AC == sqrt(BC*BC + AB*AB)))
    {
        printf("rectangular.\n\n"); //прямоугольный
    }
    else if ((AB == BC) || (BC == AC) || (AC == AB))
    {
        printf("isosceles.\n\n"); //равнобедренный
    }
    else
    {
        printf("any.\n\n"); //произвольный
    }
}

void Perimeter (int AB, int BC, int AC)
{
    printf("Triangle perimeter: %d \n\n", AB + BC + AC);
}

void Square (int AB, int BC, int AC)
{
    float p = (AB + BC + AC) / 2;
    printf("Square of the triangle: %f \n\n",  sqrt(p * (p - AB) * (p - BC) * (p - AC)));
}

void Radius (int AB, int BC, int AC)

{
    float p = (AB + BC + AC) / 2;
    //вписанная окружность
    if ((((p - AB)*(p - BC)*(p - AC)) / p) < 0)
    {
        printf("Radius of the inscribed circle: can't calculate the radius.\n\n");
    }
    else
    {
        printf("Radius of the inscribed circle: %f \n\n", sqrt(((p-AB)*(p-BC)*(p-AC)) / p));
    }
    //описанная окружность
    if (((4 * sqrt(p * (p - AB) * (p - BC) * (p - AC))) == 0) || ((p * (p - AB) * (p - BC) * (p - AC)) < 0))
    {
        printf("Radius of the circumscribed circle: can't calculate the radius.\n\n");
    }
    else
    {
        printf("Radius of the circumscribed circle: %f \n\n", (AB * BC * AC) / (4 * sqrt(p * (p - AB) * (p - BC) * (p - AC))));
    }
}

void Inf ()
{
    printf("Program version: Code::Blocks 17.12.\n\n");
    printf("Author: Byhova Lizaveta.\n\n");
}

int main()
{
    int exit = 1;
    while(exit == 1)
    {
        printf("\nEnter the coordinates  of the vertices of the triangle.\n\n");

        int Ax, Ay, Bx, By, Cx, Cy;
        Input (&Ax, &Ay, &Bx, &By, &Cx, &Cy);

        int AB, BC, AC;
        AB = sqrt(powf((Bx - Ax), 2) + powf((By - Ay),2));
        BC = sqrt(powf((Cx - Bx), 2) + powf((Cy - Bx),2));
        AC = sqrt(powf((Ax - Cx), 2) + powf((Ay - Cy),2));

        printf("\nType of a triangle: ");
        Type (AB, BC, AC);

        Perimeter (AB, BC, AC);
        Square (AB, BC, AC);
        Radius (AB, BC, AC);
        Inf ();

        char answer[3];

        printf("Do you want to exit?\n");

        scanf("%s",&answer);

        if (answer[0] == 'Y')
        {
            exit = 0;
        }
    }
    return 0;
}
