#include <iostream>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "Hotel.h"

void Fill(struct Hotel* hotels, int iterator, const char* hotelsInfo, int stringSize)
{
    int num = 0;

    for (int i = 0, j = 0; i < stringSize; i++, j++)
    {
        if (num == 0)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotels[iterator].Name[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].Name[j] = '\0';
                num++;
                i += 2;
                j = -1;
            }
        }
        else if (num == 1)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotels[iterator].CityLocation[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].CityLocation[j] = '\0';
                num++;
                i += 2;
                j = -1;
            }
        }
        else if (num == 2)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotels[iterator].Addrass[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].Addrass[j] = '\0';
                num++;
                i += 2;
                j = -1;
            }
        }
        else if (num == 3)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotels[iterator].NumberClass[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].NumberClass[j] = '\0';
                num++;
                i += 2;
                j = -1;
            }
        }
        else if (num == 4)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotels[iterator].FreePlacesQuantity[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].FreePlacesQuantity[j] = '\0';
                num++;
                i += 2;
                j = -1;
            }
        }
        else if (num == 5)
        {
            if (hotelsInfo[i + 1] != '\n')
            {
                hotels[iterator].NumberCost[j] = hotelsInfo[i];
            }
            else
            {
                hotels[iterator].NumberCost[j] = '\0';

                return;
            }
        }
    }
}

int CountStrings(const char* fileName)
{
    FILE* dataBaSs;

    int counter = 0;

    char charID[100];

    errno_t fileOpenError;
    fileOpenError = fopen_s(&dataBaSs, fileName, "r");

    if (fileOpenError != 0)
    {
        printf("Не открыли пока что!\n");
        printf("***-----------------------------------------***\n");

        return 0;
    }
    else
    {
        printf("Открыли файлик!\n");
        printf("***-----------------------------------------***\n");
    }

    printf("начинаем подсчёт строк!\n");
    printf("***-----------------------------------------***\n");

    while (!feof(dataBaSs))
    {
        if (fgets(charID, 100, dataBaSs))
        {
            counter++;
        }
    }

    printf("Подсчёт строк завершён!\n");
    printf("***-----------------------------------------***\n");

    fclose(dataBaSs);

    return counter;
}

void ArrCreate(struct Hotel* hotels, int size, const char* fileName)
{
    FILE* dataBaSs;

    char hotelInfoString[50];

    int arrayIterator = 0;
    int stringArraySize;
    stringArraySize = sizeof(hotelInfoString) / sizeof(hotelInfoString[0]);

    errno_t fileOpenError;
    fileOpenError = fopen_s(&dataBaSs, fileName, "r");

    if (fileOpenError != 0)
    {
        printf("Не открылся парень нам пока что!\n");
        printf("***-----------------------------------------***\n");
        return;
    }
    else
    {
        printf("Успешное открытие!\n");
        printf("***-----------------------------------------***\n");
    }

    while (!feof(dataBaSs) && arrayIterator < size)
    {
        if (fgets(hotelInfoString, stringArraySize, dataBaSs))
        {
            Fill(hotels, arrayIterator, hotelInfoString, stringArraySize);

            arrayIterator++;
        }
    }

    fclose(dataBaSs);

    return;
}