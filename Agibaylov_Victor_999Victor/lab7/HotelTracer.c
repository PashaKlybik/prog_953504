#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <cstdio>
#include <cstring>

#include "HotelTracer.h"

//меню
void MenuChoiceGetter()
{
    while (true)
    {
        char menuChoice;

        printf("Press 1 to enter your request");
        printf("to find fitting hotel for you\n");
        printf("Or press 2 to left the main menu\n");
        printf("Press any key: ");

        scanf_s("%c", &menuChoice);

        if (menuChoice == '1')
        {
            break;
        }
        else if (menuChoice == '2')
        {
            return;
        }
        else
        {
            printf("Wrong button pressed, try again pls\n");
        }
    }
}

//обработка строки, введеной пользователем
void SearchStringProcessing()
{
    char enteredSearchString[100];
    char query[100];
    *query = '\0';

    int counter;
    counter = 0;

    getchar();

    printf("Please, enter your Query as stated below\n");
    printf("ћинск недурна€ комната на троих 14000\n");
    printf("There you can see a pattern query must be entered.");
    printf("Name of the city, class of the room, how many");
    printf("people must room accommodate,");
    printf("cena voprosa v ryblyah za noch'\n");
    printf("Please input your query: ");

    gets_s(enteredSearchString);

    while (enteredSearchString[counter] != -2)
    {
        counter++;
        continue;
    }

    enteredSearchString[counter] = '\0';

    strcat(query, StringParse(enteredSearchString));

    ResultFinder(query);
}

//получение результата сравнени€ 
//обработанной строки с базой данных
void ResultFinder(char* processedString)
{
    char query_addrass[100];
    *query_addrass = '\0';
    char query_room[100];
    *query_room = '\0';
    const char* fileName;
    fileName = "D://Programming//GitHub//C-Lab-Number7-Var9//hotelsDatabase.txt";

    int counter;
    counter = 0;
    int query_quantity = 0;
    query_quantity = 0;
    int query_price;
    query_price = 0;
    int hotelsQuantity;
    hotelsQuantity = FileStringCounter(fileName);

    struct Hotel* hotelsContainer;
    hotelsContainer = (Hotel*)malloc(hotelsQuantity * sizeof(Hotel));

    ArrayCreating(hotelsContainer, hotelsQuantity, fileName);

    while (processedString[counter] != '/')
    {
        counter++;
    }

    strncpy(query_addrass, processedString, counter);

    query_addrass[counter] = '\0';

    for (int j = 0; j < strlen(processedString) - counter + 1; j++)
    {
        processedString[j] = processedString[j + counter + 1];
    }

    counter = 0;

    while (processedString[counter] != '/')
    {
        counter++;
    }

    strncpy(query_room, processedString, counter);

    query_room[counter] = '\0';

    for (int j = 0; j < strlen(processedString) - counter + 1; j++)
    {
        processedString[j] = processedString[j + counter + 1];
    }

    counter = 0;

    while (processedString[counter] != '/')
    {
        query_quantity = query_quantity * 10 + (processedString[counter] - 48);

        counter++;
    }

    for (int j = 0; j < strlen(processedString) - counter + 1; j++)
    {
        processedString[j] = processedString[j + counter + 1];
    }

    counter = 0;

    while (processedString[counter] != '\0')
    {
        query_price = query_price * 10 + (processedString[counter] - 48);
        counter++;
    }

    for (int i = 0; i < hotelsQuantity; i++)
    {
        int suitability = 0;

        if (!strcmp(hotelsContainer[i].CityLocation, query_addrass))
        {
            suitability++;
        }

        bool isRoomSuitable;
        isRoomSuitable = false;

        for (int j = 0; j < strlen(query_room); j++)
        {
            if (query_room[j] == '1' &&
                strcmp(hotelsContainer[i].NumberClass, "NotLux") == 0)
            {
                isRoomSuitable = true;
            }

            if (query_room[j] == '2' &&
                strcmp(hotelsContainer[i].NumberClass, "Kruto") == 0)
            {
                isRoomSuitable = true;
            }

            if (query_room[j] == '3' &&
                strcmp(hotelsContainer[i].NumberClass, "Luxury") == 0)
            {
                isRoomSuitable = true;
            }

            if (query_room[j] == '4' &&
                strcmp(hotelsContainer[i].NumberClass, "Lux") == 0)
            {
                isRoomSuitable = true;
            }
        }

        if (isRoomSuitable)
        {
            suitability++;
        }

        if (query_quantity <=
            (int)(hotelsContainer[i].FreePlacesQuantity - '0'))
        {
            suitability++;
        }

        if (query_price >=
            (int)(hotelsContainer[i].NumberCost - '0'))
        {
            suitability++;
        }

        printf("Most suitable hotel for you is");
        printf("%s with numbers class %s for %s dollars per night\n",
            hotelsContainer[i].Name, hotelsContainer[i].NumberClass,
            hotelsContainer[i].NumberCost);
    }

    free(hotelsContainer);

    return;
}

//перевод из введенной пользователем строки в данные
//удобные дл€ обработки и подбора подход€щего варианта
char* StringParse(char* enteredSearchString)
{
    char parsedSearchString[100];
    *parsedSearchString = '\0';
    char previous_word[100];
    *previous_word = '\0';

    int j;
    j = 0;

    bool isCompleated;
    isCompleated = false;

    for (int i = 0; i < strlen(enteredSearchString); i++)
    {
        if (i == 0 || enteredSearchString[i] == ' ')
        {
            if (enteredSearchString[i] == ' ')
            {
                i++;
            }

            j = i;

            while (enteredSearchString[j] != ' ')
            {
                if (j == strlen(enteredSearchString))
                {
                    break;
                }

                j++;

                continue;
            }

            if (j != strlen(enteredSearchString))
            {
                j--;
            }

            char word[100] = {};

            for (int k = i; k <= j; k++)
            {
                word[k - i] = enteredSearchString[k];
            }

            if (i == 0)
            {
                strcat(parsedSearchString, word);
                strcat(parsedSearchString, "/");
            }

            if (!strcmp(word, "room"))
            {
                if (strcmp(previous_word, "expensive") == 0 ||
                    strcmp(previous_word, "luxurious") == 0 ||
                    strcmp(previous_word, "rich") == 0)
                {
                    strcat(parsedSearchString, "34/");
                }

                if (strcmp(previous_word, "notshamefull") == 0 ||
                    strcmp(previous_word, "norm") == 0 ||
                    strcmp(previous_word, "usual") == 0)
                {
                    strcat(parsedSearchString, "2/");
                }

                if (!strcmp(previous_word, "cheap"))
                {
                    strcat(parsedSearchString, "1/");
                }

                if (!strcmp(previous_word, "any"))
                {
                    strcat(parsedSearchString, "0/");
                }
            }

            if (!strcmp(previous_word, "for"))
            {
                if (!strcmp(word, "one"))
                {
                    strcat(parsedSearchString, "1/");
                }
                else
                {
                    if (!strcmp(word, "two"))
                    {
                        strcat(parsedSearchString, "2/");
                    }
                    else
                    {
                        if (!strcmp(word, "three"))
                        {
                            strcat(parsedSearchString, "3/");
                        }
                        else
                        {
                            if (!strcmp(word, "four"))
                            {
                                strcat(parsedSearchString, "4/");
                            }
                            else
                            {
                                if (!strcmp(word, "company"))
                                {
                                    strcat(parsedSearchString, "5/");
                                }
                            }
                        }
                    }
                }
            }

            if (word[0] > 47 && word[0] < 59)
            {
                strcat(parsedSearchString, word);

                isCompleated = true;
            }

            int letterCounter = 0;

            while (word[letterCounter] != '\0')
            {
                previous_word[letterCounter] = word[letterCounter];

                letterCounter++;
            }

            previous_word[letterCounter] = '\0';
        }

        if (isCompleated) 
        {
            return parsedSearchString;
        }
    }
}

//заполнение конкретного элемента массива отелей информацией из файла 
void ExampleFilling(struct Hotel* hotelsContainer, int iterator, 
    const char* hotelsInfo, int stringSize)
{
    int fieldNumber;
    fieldNumber = 0;

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
            if (hotelsInfo[i] != '\n')
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

//подсчет количества отелей в текстовом документе
int FileStringCounter(const char* fileName)
{
    FILE* dataBaseFile;

    int counter;
    counter = 0;

    char characterIdentify[100];

    errno_t fileOpenError;
    fileOpenError = fopen_s(&dataBaseFile, fileName, "r");

    if (fileOpenError != 0)
    {
        return 0;
    }

    while (!feof(dataBaseFile))
    {
        if (fgets(characterIdentify, 100, dataBaseFile))
        {
            counter++;
        }
    }

    fclose(dataBaseFile);

    return counter;
}

//создание и поочередное ызаполнение массива отелей
void ArrayCreating(struct Hotel* hotelsContainer, 
    int size, const char* fileName)
{
    FILE* dataBaseFile;

    char hotelInfoString[50];

    int arrayIterator;
    arrayIterator = 0;
    int stringArraySize;
    stringArraySize = sizeof(hotelInfoString) / 
        sizeof(hotelInfoString[0]);

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
            ExampleFilling(hotelsContainer, arrayIterator,
                hotelInfoString, stringArraySize);

            arrayIterator++;
        }
    }

    fclose(dataBaseFile);

    return;
}