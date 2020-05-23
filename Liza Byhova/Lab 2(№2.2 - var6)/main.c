#include <stdio.h>
#include <math.h>

unsigned long long int Factorial(int number)
{
    unsigned long long int fact = 1;

    for(int i = fact; i <= number; i++)
    {
        fact *= i;
    }

    return fact;
}

void Calculation(double x, double e)
{
    double Decomposition = 0;

    for(int n = 1; ; n++)
    {
        Decomposition += pow(-1, n - 1) * (pow(x, 2 * n - 1) / Factorial(2 * n - 1));

        if(fabs(fabs(sin(x)) - fabs(Decomposition)) <= e)
        {
            printf("\n\nsin(x): %f\n\nsin(x) with e: %f\n\nn with e: %d\n", sin(x), Decomposition, n);

            break;
        }
    }
}

int main ()
{
    double x, e;

    printf("Enter the x: ");
    scanf("%lf", &x);

    printf("Enter the e: ");
    scanf("%lf", &e);

    while(x > M_PI * 2)
    {
        x -= M_PI * 2;
    }

    Calculation(x, e);

    return 0;
}
