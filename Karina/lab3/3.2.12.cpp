#include <stdio.h>
#include <malloc.h>

int Func(int n, int i, int j)
{   
    int** mas;
    mas = (int**) malloc (n*sizeof(int*));
    for (i = 0; i < n; i = i + 1)
    {
        mas[i] = (int*)malloc(n * sizeof(int));
    }

    for (i = 0; i < n; i = i + 1)
    {
        for (j = 0; j < n; j = j + 1)
        {
            mas[i][j] = (i + j) % n + 1;
        }
    }


    for (i = 0; i < n; i = i + 1)
    {
        for (j = 0; j < n; j= j+1)
        printf_s("%d\t", mas[i][j]);
        printf_s("\n");

    }
    return mas[i][j];

    for (i = 0; i < n; i++) 
    free(mas[i]);  
    free(mas);
    getchar(); 
    return 0;
}

int main()
{
    int** mas, n=0, i=0, j=0;
    printf_s("Enter n:");
    scanf_s("%d", &n);
    Func(n,i,j);

    return 0;
}

