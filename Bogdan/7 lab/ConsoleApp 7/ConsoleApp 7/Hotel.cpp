#include <iostream>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

#include "Hotel.h"

void ExampleFilling(struct Hotel* hotelsContainer, int iterator, const char* hotelsInfo, int stringSize)
{
    int fieldNumber = 0;

    for (int i = 0, j = 0; i < stringSize; i++, j++)
    {
        if (fieldNumber == 0)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotelsContainer[iterator].Name[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].Name[j] = '\0';
                fieldNumber++;
                i += 2;
                j = -1;
            }
        }
        else if (fieldNumber == 1)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotelsContainer[iterator].CityLocation[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].CityLocation[j] = '\0';
                fieldNumber++;
                i += 2;
                j = -1;
            }
        }
        else if (fieldNumber == 2)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotelsContainer[iterator].Addrass[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].Addrass[j] = '\0';
                fieldNumber++;
                i += 2;
                j = -1;
            }
        }
        else if (fieldNumber == 3)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotelsContainer[iterator].NumberClass[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].NumberClass[j] = '\0';
                fieldNumber++;
                i += 2;
                j = -1;
            }
        }
        else if (fieldNumber == 4)
        {
            if (hotelsInfo[i + 1] != '|')
            {
                hotelsContainer[iterator].FreePlacesQuantity[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].FreePlacesQuantity[j] = '\0';
                fieldNumber++;
                i += 2;
                j = -1;
            }
        }
        else if (fieldNumber == 5)
        {
            if (hotelsInfo[i + 1] != '\n')
            {
                hotelsContainer[iterator].NumberCost[j] = hotelsInfo[i];
            }
            else
            {
                hotelsContainer[iterator].NumberCost[j] = '\0';

                return;
            }
        }
    }
}

int FileStringCounter(const char* fileName)
{
    FILE* dataBaseFile;

    int counter = 0;

    char characterIdentify[100];

    errno_t fileOpenError;
    fileOpenError = fopen_s(&dataBaseFile, fileName, "r");

    if (fileOpenError != 0)
    {
        printf("================PROGRAM MESSAGE================\n");
        printf("The file isn't opened yet!\n");
        printf("================PROGRAM MESSAGE================\n");

        return 0;
    }
    else
    {
        printf("================PROGRAM MESSAGE================\n");
        printf("Successful file opening!\n");
        printf("================PROGRAM MESSAGE================\n");
    }

    printf("================PROGRAM MESSAGE================\n");
    printf("String counting process is started!\n");
    printf("================PROGRAM MESSAGE================\n");

    while (!feof(dataBaseFile))
    {
        if (fgets(characterIdentify, 100, dataBaseFile))
        {
            counter++;
        }
    }

    printf("================PROGRAM MESSAGE================\n");
    printf("String counting process is ended!\n");
    printf("================PROGRAM MESSAGE================\n");

    fclose(dataBaseFile);

    return counter;
}

void ArrayCreating(struct Hotel* hotelsContainer, int size, const char* fileName)
{
    FILE* dataBaseFile;

    char hotelInfoString[50];

    int arrayIterator = 0;
    int stringArraySize;
    stringArraySize = sizeof(hotelInfoString) / sizeof(hotelInfoString[0]);

    errno_t fileOpenError;
    fileOpenError = fopen_s(&dataBaseFile, fileName, "r");

    if (fileOpenError != 0)
    {
        printf("================PROGRAM MESSAGE================\n");
        printf("The file isn't opened yet!\n");
        printf("================PROGRAM MESSAGE================\n");

        return;
    }
    else
    {
        printf("================PROGRAM MESSAGE================\n");
        printf("Successful file opening!\n");
        printf("================PROGRAM MESSAGE================\n");
    }

    while (!feof(dataBaseFile) && arrayIterator < size)
    {
        if (fgets(hotelInfoString, stringArraySize, dataBaseFile))
        {
            ExampleFilling(hotelsContainer, arrayIterator, hotelInfoString, stringArraySize);

            arrayIterator++;
        }
    }

    fclose(dataBaseFile);

    return;
}