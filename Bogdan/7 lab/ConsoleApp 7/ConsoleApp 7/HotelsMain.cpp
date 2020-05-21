#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <malloc.h>
#include <locale.h>
#include "Hotel.h"

char* StringParse(char* str, Hotel** hotel_array);




int main()
{
	setlocale(LC_ALL, "Rus");
	char choice = NULL;
	char str[100];

	const char* fileName = "D://Laby//C//C-Lab-Number7-Var9-master//hotels.txt";

	int hotelsQuantity;
	hotelsQuantity = FileStringCounter(fileName);

	struct Hotel* hotelsContainer;
	hotelsContainer = (Hotel*)malloc(hotelsQuantity * sizeof(Hotel));

	ArrayCreating(hotelsContainer, hotelsQuantity, fileName);

	printf("Welcome to HotelFinder2020\nBy pressing f key you can enter your query in order to find a really nice place to rest!");
	printf("Press any key: ");
	scanf_s("%c", &choice);
	getchar();
	printf("Please, enter your Query as stated below\n Минск недурная комната на троих 14000\n There you can see a pattern query must be entered. Name of the city, class of the room, how many people must room accommodate, Cena voprosa v ryblyah za noch'\n");
	printf("Please input your query: ");
	gets_s(str);
	

	int k = 0;
	while (str[k] != -2)
	{
		k++;
		continue;
	}
	str[k] = '\0';

	char query[100];
	*query = '\0';
	
	if (choice == 'f')
	{
		strcat(query, StringParse(str, &hotelsContainer));
	}
	else
	{
		printf("Don't know this command yet.");
		
	}

	char query_addrass[100];
	char query_room[100];
	int query_quantity = 0;
	int query_price = 0;
	*query_addrass = '\0';
	*query_room = '\0';

	int i = 0;	
	while(query[i]!='/')					//Finding and tearing off adrass
	{
		i++;
	}
	strncpy(query_addrass, query, i);		//Tearing off
	query_addrass[i] = '\0';

	for(int j=0; j<strlen(query) - i + 1; j++)			//Deleting addrass from query
	{
		query[j] = query[j + i + 1];
	}

	i = 0;
	while (query[i] != '/')
	{
		i++;
	}
	strncpy(query_room, query, i);
	query_room[i] = '\0';
		
	for (int j = 0; j < strlen(query) - i + 1; j++)		//Deleting room from query
	{
		query[j] = query[j + i + 1];
	}

	i = 0;
	while (query[i] != '/')
	{
		query_quantity = query_quantity * 10 + (query[i] - 48);
		i++;
	}

	for (int j = 0; j < strlen(query) - i + 1; j++)		//Deleting quantity from query
	{
		query[j] = query[j + i + 1];
	}

	i = 0;
	while (query[i] != '\0')
	{
		query_price = query_price * 10 + (query[i] - 48);
		i++;
	}

	for (int i=0; i<hotelsQuantity; i++)
	{
		int isOk = 0;
		
		if (!strcmp(hotelsContainer[i].CityLocation, query_addrass))
			isOk++;

		bool flag = false;
		for(int j=0; j<strlen(query_room); j++)
		{
			if (query_room[j] == '1' && strcmp(hotelsContainer[i].NumberClass, "Usuall") == 0)
				flag = true;
			if (query_room[j] == '2' && strcmp(hotelsContainer[i].NumberClass, "Good") == 0)
				flag = true;
			if (query_room[j] == '3' && strcmp(hotelsContainer[i].NumberClass, "Cool") == 0)
				flag = true;
			if (query_room[j] == '4' && strcmp(hotelsContainer[i].NumberClass, "Perfect") == 0)
				flag = true;
		}
		if (flag)
			isOk++;

		if (query_quantity <= (int)(hotelsContainer[i].FreePlacesQuantity-'\0'))
			isOk++;

		if (query_price >= (int)(hotelsContainer[i].NumberCost-'\0'))
			isOk++;

		if(isOk == 4)
		{
			printf("Подойдёт отель %s с номерами типа %s за %d рублей за ночь", hotelsContainer[i].Name, hotelsContainer[i].NumberClass, hotelsContainer[i].NumberCost);
		}
	}
	
	
	return 0;
}

char* StringParse(char* str, Hotel** hotel_array)
{
	char final_word[100];
	*final_word = '\0';
	char previous_word[100];
	*previous_word = '\0';

	int j = 0;
	bool is_all = false;

	for (int i = 0; i < strlen(str); i++)
	{
		if (i == 0 || str[i] == ' ')				//If encountering a start of new word
		{
			if (str[i] == ' ')
			{
				i++;
			}

			j = i;									//Marking the end of the word

			while (str[j] != ' ')
			{
				if (j == strlen(str))
				{
					break;
				}

				j++;

				continue;
			}

			if (j != strlen(str))				//if it is not the end of the string - minus 1
			{
				j--;
			}

			char word[100] = {};

			for (int k = i; k <= j; k++)		//For my comfort i made a new word
			{
				word[k - i] = str[k];
			}

			int k = 0;

			k = 0;

			if(i == 0)
			{
				strcat(final_word, word);				//Adding city name of the hotel
				strcat(final_word, "/");
			}
			
			if (!strcmp(word, "room"))
			{
				if (strcmp(previous_word, "expensive") == 0 || strcmp(previous_word, "luxurious") == 0 || strcmp(previous_word, "rich") == 0)		//Checking for room type
					strcat(final_word, "34/");
				if (strcmp(previous_word, "notshamefull") == 0 || strcmp(previous_word, "norm") == 0 || strcmp(previous_word, "usual") == 0)
					strcat(final_word, "2/");
				if (!strcmp(previous_word, "cheap"))
					strcat(final_word, "1/");
				if (!strcmp(previous_word, "any"))
					strcat(final_word, "0/");
			}

			if (!strcmp(previous_word, "for"))				//Checking Quantity
			{
				if (!strcmp(word, "one"))
					strcat(final_word, "1/");
				else
					if (!strcmp(word, "two"))
						strcat(final_word, "2/");
					else
						if (!strcmp(word, "three"))
							strcat(final_word, "3/");
						else
							if (!strcmp(word, "four"))
								strcat(final_word, "4/");
							else
								if (!strcmp(word, "company"))
									strcat(final_word, "5/");

			}

			if (word[0] > 47 && word[0] < 59)			//Check for price input
			{
				strcat(final_word, word);
				is_all = true;
			}

			int l = 0;
			while(word[l]!='\0')
			{
				previous_word[l] = word[l];				//Swapping word and previous word
				l++;
			}
			previous_word[l] = '\0';
		}

		if(is_all)
			return final_word;
	}
}