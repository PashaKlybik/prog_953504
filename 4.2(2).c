#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

double averageCounter(char str[], int size);

int main()
{
    FILE* f;
    errno_t err = fopen_s(&f,"text.txt", "r");

    if (err != 0)
    {
        printf("The file isnt opened yet!\n");
        return 0;
    }
    else
    {
        printf("Successful file opening!\n");
    }

    char b[100];
    double result;

    while (!feof(f)) {
        if (fgets(b, 100, f)) {
            printf("Entered string: %s \nThe result: ", &b);
            result = averageCounter(b, 100);
            printf("%f", result);
        }
    }

    fclose(f);

    return 0;
}

double averageCounter(char str[], int size)
{
    double dummy, result;
    int numberLength = 0, summ = 0, sizeNum = 0, counter = 0;

    //���������� ������ ������ � �������
    for (int i = 0; ; i++)
    {
        if (str[i] == ' ' || isdigit(str[i]) || str[i] == '-')
        {
            sizeNum += 1;
        }
        else
        {
            break;
        }
    }

    //�������
    for (int i = 0; i <= sizeNum; i++)
    {
        if (str[i] == '-')
        {
            for (int k = i; ; k++)
            {
                if (str[k] == ' ')
                {
                    i = k;
                    break;
                }
            }
        }
        else if (isdigit(str[i]))
        {
            //���������� ������ �����
            for (int j = i; ; j++)
            {
                if (str[j] == ' ' || j == sizeNum)
                {
                    numberLength += j - i;
                    break;
                }
            }

            //������� ����� �� char � int ����� �����������
            for (int z = i, l = numberLength - 1; ; z++, l--)
            {
                if (isdigit(str[i]))
                {
                    summ += (str[z] - '0') * pow(10, l);

                    if (l == 0)
                    {
                        i += numberLength;
                        counter += 1;
                        numberLength = 0;
                        break;
                    }
                }
            }
        }
    }

    result = summ / counter;

    return result;
}
