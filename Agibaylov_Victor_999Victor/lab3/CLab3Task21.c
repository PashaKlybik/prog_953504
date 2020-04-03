/*3.2 (21).Обратная матрица.Найти матрицу, обратную заданной a(n, n),
методом Гаусса(в любой модификации).*/

#include <iostream>
#include <math.h>
#include <ctype.h>
#include <malloc.h>

using namespace std;

int inverseMatrix(double** matrix, int size);

//заполнение массива, вызов функции
int main()
{
    long int n, a;

    //проверка вводимого числа
    do
    {
        printf("Enter matrix's size: ");
        scanf_s("%d", &n);

        if (n > 1 && n < 2147483647)
        {
            break;
        }
        else
        {
            printf("\nWrong value!\n");
        }
    } while (true);

    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }

    //заполнение и проверка(на строку, на число, более 1000)
    for (int i = 0, j = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            //проверка вводимого числа
            do
            {
                printf("matrix[%d][%d] = ", i, j);
                scanf_s("%lf", &(matrix[i][j]));

                if (matrix[i][j] > -2147483648 && matrix[i][j] < 2147483647)
                {
                    break;
                }
                else
                {
                    printf("\nWrong value!\n");
                }
            } while (true);
        }
    }

    //вывод заполненного массива
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf ", (matrix[i][j]));
        }
        printf("\n");
    }

    inverseMatrix(matrix, n);

    //выводим уже единичную матрицу
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf ", (matrix[i][j]));
        }
        printf("\n");
    }

    free(matrix);

    return 0;
}

//функция рассчета обратной матрицы методом Гаусса
int inverseMatrix(double** matrix, int size)
{
    //создаем единничную матрицу
    double** eMatrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++)
    {
        eMatrix[i] = (double*)malloc(size * sizeof(double));
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                eMatrix[i][j] = 1;
            }
            else
            {
                eMatrix[i][j] = 0;
            }
        }
    }

   //функционал
   for (int i = 0; i < size; i++)
   {

       if (i != 0)
       {
           double dummy = matrix[i][0];

           for (int j = 0; j < size; j++)
           {
               matrix[i][j] -= matrix[0][j] * dummy;
               eMatrix[i][j] -= eMatrix[0][j] * dummy;
           }
       }

      double dummy = matrix[i][i];

       //делим всю строку на направляющий элемент
       for (int j = 0; j < size; j++)
       {
           matrix[i][j] /= dummy;
           eMatrix[i][j] /= dummy;
       }
   }

   //проходится по элементам диагонали(итая строка итый столбец) 
  for (int i = 1; i < size; i++)
   {
      double dummy = matrix[i][i];
      //проверка на детерминант(если равно нулю - заканчиваем операцию)
      if (dummy == 0)
      {
          printf("\nThe determinant of matrix is equal to zero. It's impossible to count an inverse matrix.\n");

          //вывод получившейся в итоге матрицы
          printf("\n--------------------------------\n");
          //вывод заполненного массива
          for (int i = 0; i < size; i++)
          {
              for (int j = 0; j < size; j++)
              {
                  printf("%lf ", (eMatrix[i][j]));
              }
              printf("\n");
          }

          printf("\n--------------------------------\n");
          return 0;
      }

      //делим всю строку на направляющий элемент
      for (int j = 0; j < size; j++)
      {
          matrix[i][j] /= dummy;
          eMatrix[i][j] /= dummy;
      }

       //проходится по итому столбцу по итым элементам(элементы над и под элементом диагонали, один столбец)
       for (int k = 0; k < size; k++)
       {
           double dummy = matrix[k][i];
           if (k != i)
           {    
               //проходится по элементам итой строки 
               for (int j = 0; j < size; j++)
               {
                   matrix[k][j] -= matrix[i][j] * dummy;
                   eMatrix[k][j] -= eMatrix[i][j] * dummy;
               }
           }
       }
   }

   printf("\n--------------------------------\n");
   printf("Inverced matrix: \n");

    //вывод заполненного массива
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%lf ", (eMatrix[i][j]));
        }
        printf("\n");
    }

    printf("\n--------------------------------\n");

    free(eMatrix);

    return 0;
}