//7lab 7 lab Социальная сеть. Множество людей организовано по принципу сети: 
//каждый человек имеет свой круг общения, у каждого из этого круга, в свою очередь, есть свой круг и т.д. 
//Добавление нового члена ( ФИО, контакты, город, образование, работа, интересы). Установление и удаление связей. 
//Поиск нужных людей по интересам, местонахождению, образованию или работе. 
//Возможность просмотра кругов общения, т.е. « путешествия» по социальной сети. 
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

char name[6][20] = { "Ilya","Roma","Dima","Evgen","Danik","Sasha" };
char surname[6][20] = { "Krivetskiy","Bortnovskiy","Semenuk","Kreidich","Kamornik","Kochurko" };
char patr[6][20] = { "Alexeevich","Nikolaevich","Alexandrovich","Mixailovich","Sergeevich","Danilovich" };
char town[6][20] = { "Brest","Gorodechno","Minsk","Pochaev","Piter","Pskov" };
char education[6][20] = { "Middle","Higher","No education","Base","Bakalavr","Special" };
char interests[6][20] = { "No","RealLife","Girls","Football","Fishing","Dancing" };
char work[6][20] = { "No","Doctor","Priest","Starosta","Programmer","Photographer" };
char contacts[6][20] = { "293115117","445578964","333167964","445334900","295761287","336547899" };



struct Person;

typedef struct Person
{
	char* name = nullptr;
	char* surname = nullptr;
	char* patr = nullptr;
	char* contacts = nullptr;
	char* city = nullptr;
	char* education = nullptr;
	char* work = nullptr;
	char* interests = nullptr;
	int countoffriends = 0;

	Person* friends = nullptr;
}Person;

Person PersonCreater(char* name, char* surname, char* patr, char* contacts, char* town, char* education, char* work, char* interests)
{
	Person Person;
	Person.name = name;
	Person.contacts = contacts;
	Person.education = education;
	Person.interests = interests;
	Person.patr = patr;
	Person.surname = surname;
	Person.city = town;
	Person.work = work;
	return Person;
}

Person AddPerson()
{
	char* name = (char*)malloc(sizeof(char*) * 20);
	char* surname = (char*)malloc(sizeof(char*) * 20);
	char* patr = (char*)malloc(sizeof(char*) * 20);
	char* contacts = (char*)malloc(sizeof(char*) * 20);
	char* town = (char*)malloc(sizeof(char*) * 20);
	char* education = (char*)malloc(sizeof(char*) * 20);
	char* work = (char*)malloc(sizeof(char*) * 20);
	char* interests = (char*)malloc(sizeof(char*) * 20);
	rewind(stdin);
	puts("Введите Фамилию человека");
	scanf("%[^\n]s", surname);
	rewind(stdin);
	puts("Введите Имя человека");
	scanf("%[^\n]s", name);
	rewind(stdin);
	puts("Введите Отчество человека");
	scanf("%[^\n]s", patr);
	rewind(stdin);
	puts("Введите контактные данные человека");
	scanf("%[^\n]s", contacts);
	rewind(stdin);
	puts("Введите Образование человека");
	scanf("%[^\n]s", education);
	rewind(stdin);
	puts("Введите работу человека");
	scanf("%[^\n]s", work);
	rewind(stdin);
	puts("Введите интересы человека");
	scanf("%[^\n]s", interests);
	rewind(stdin);
	puts("Введите город человека");

	scanf("%[^\n]s", town);

	Person man = PersonCreater(name, surname, patr, contacts, town, education, work, interests);

	//free(name);
	//free(surname);
	//free(patr);
	//free(contacts);
	//free(town);
	//free(education);
	//free(work);
	//free(interests);
	return man;
}

void* newPamyat(void* source,  size_t _Count,  size_t _Size)
{
	void* temp = source;
	source = calloc(_Count, sizeof(_Size));
	source = temp;
	return source;
}

void AddNewPerson(Person* man, int count)
{
	//добавить нового человека
	man = (Person*)newPamyat((void*)man, count, sizeof(Person));
	man[count - 1] = AddPerson();
}

void ShowPerson(Person man)
{
	printf("----------------------------------\n");
	printf("Имя - %s\n", man.name);
	printf("Фамилия - %s\n", man.surname);
	printf("Отчество - %s\n", man.patr);
	printf("Город - %s\n", man.city);
	printf("Работа - %s\n", man.work);
	printf("Контактные данные - %s\n", man.contacts);
	printf("Образование- %s\n", man.education);
	printf("Интересы - %s\n", man.interests);
	printf("---------------------------------------------------------------------\n");
	
	for (int i = 0; i < man.countoffriends; i++)
	{
		printf("\t %d друг\tИмя - %s\tФамилия - %s\n", i + 1, man.friends[i].name, man.friends[i].surname);
		printf("---------------------------------------------------------------------\n");
	}
}

void ShowFrends(Person* man, int length)
{
	for (int x = 0; x < length; x++)
	{
		printf("Друзья %d человека\n", x + 1);
		printf("---------------------------------------------------------------------\n");
		if (man[x].countoffriends == 0)
		{
			printf("Нет друзей у  %d человека\n", x + 1);
		}
		else
		{
			for (int i = 0; i < man[x].countoffriends; i++)
			{
				printf("\t %d друг \t Имя - %s \t Фамилия - %s\n", i + 1, man[x].friends[i].name, man[x].friends[i].surname);
				printf("---------------------------------------------------------------------\n");
			}
		}
	}
}

void ShowAllPeople(int peopleCount, Person* people)
{
	for (int i = 0; i < peopleCount; i++)
	{

		printf("%d-й человек:\n", i + 1);

		ShowPerson(people[i]);
	}
}

void ShowPeacePeople(Person man)
{
	puts("-------------------------------------------------------------");
	printf("\
Имя:%s\t\
\tФамилия:%s\t\
\tОтчество:%s\t\n", man.name, man.surname, man.patr);
	
}

void ShowAllPeacePeople(Person* people, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d человек\n", i + 1);

		ShowPeacePeople(people[i]);
		puts("-------------------------");
	}
}

int PersonCompare(Person man1, Person man2)
{
	if (!strcmp(man1.name, man2.name) &&
		!strcmp(man1.surname, man2.surname) &&
		!strcmp(man1.patr, man2.patr) &&
		!strcmp(man1.contacts, man2.contacts) &&
		!strcmp(man1.education, man2.education) &&
		!strcmp(man1.city, man2.city) &&
		!strcmp(man1.interests, man2.interests) &&
		!strcmp(man1.work, man2.work))
		return 1;
	else
		return 0;
}

Person* PersonLibrary(int count)
{
	srand(time(NULL));
	Person* temp = (Person*)malloc(sizeof(Person) * count);;
	
	for (int i = 0; i < count; i++)
	{
		temp[i] = PersonCreater((char*)name[rand() % 6], (char*)surname[rand() % 6], (char*)patr[rand() % 6],
			(char*)contacts[rand() % 6], (char*)town[rand() % 6],
			(char*)education[rand() % 6], (char*)work[rand() % 6], (char*)interests[rand() % 6]);
	}
	
	return temp;
}

void addFrends(Person* people, int count)
{
	ShowAllPeacePeople(people, count);
	int index = 0;
	while (index<1 || index>count + 1)
	{
		puts("Выберите человека");
		scanf("%d", &index);
	}
	index--;
	int number = 0;
	while (number<1 || number>count + 1)
	{
		puts("Выберите человека для добавления в друзья");
		ShowAllPeacePeople(people, count);
		scanf("%d", &number);
	}
	number--;
	int last = people[index].countoffriends;
	if (people[index].countoffriends == 0)
	{
		people[index].friends = (Person*)malloc(1 * sizeof(Person));
		people[index].countoffriends++;
	}
	else
	{
		people[index].countoffriends++;
		people[index].friends = (Person*)newPamyat((void*)people[index].friends, people[index].countoffriends, sizeof(Person));
	}
	int x = (people[number].countoffriends);
	if (people[number].countoffriends == 0)
	{
		people[number].friends = (Person*)malloc(1 * sizeof(Person));
		people[number].countoffriends++;
	}
	else
	{
		people[number].countoffriends++;
		people[number].friends = (Person*)newPamyat((void*)people[number].friends, people[number].countoffriends, sizeof(Person));

	}
	
	if (index != number)
	{
		if (people[index].countoffriends - 1 == 0)
		{
			if (PersonCompare(people[index], people[number]) == 0)
			{
				people[index].friends[last] = people[number];
				people[number].friends[x] = people[index];
				puts("Друг добавлен\n");
			}
			else
			{
				puts("Данный человек уже есть\n");
			}
		}
		else {
			for (int i = 0; i < people[index].countoffriends; i++)
			{
				if (PersonCompare(people[index].friends[i], people[number]) == 1)
				{
					people[index].friends[last] = people[number];
					people[number].friends[x] = people[index];
					puts("Друг добавлен\n");
				}
				else
				{
					puts("Данный человек уже есть\n");
				}
			}
		}
	}
	else
	{
		puts("Вы не можете добавить себя\n");
	}
}

void DeleteFriends(Person* people, int count)
{
	ShowAllPeacePeople(people, count);
	int index = 0;
	while (index<1 || index>count + 1)
	{
		puts("Выберите человека");
		scanf("%d", &index);
	}
	index--;
	int number = 0;
	if (people[index].countoffriends == 0)
	{
		puts("У него нет друзей");
		return;
	}
	while (number<1 || number> people[index].countoffriends)
	{
		puts("Выберите человека для удаления из друзей");
		ShowAllPeacePeople(people[index].friends, people[index].countoffriends);
		scanf("%d", &number);
	}
	for (int i = number; i < people[index].countoffriends; i++)
	{
		people[index].friends[i - 1] = people[index].friends[i];
	}
	people[index].countoffriends--;
	people[index].friends = (Person*)newPamyat((void*)people[index].friends, people[index].countoffriends, sizeof(Person));
}

int EditMenu()
{
	int point;
	printf("Выберите пункт для редактирования\n\
1 - Имя\n\
2 - Фамилия\n\
3 - Отчество\n\
4 - Контактные данные\n\
5 - Город\n\
6 - Образование\n\
7 - Работа\n\
8 - Интересы\n\
10 - Я передумал\n");
	scanf("%d", &point);
	return point;
}

Person ChangeInfo(Person man)
{
	char* str = (char*)malloc(20 * sizeof(char*));
	switch (EditMenu())
	{
	case 1:
		printf("Введите новое Имя\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.name = str;
		break;
	case 2:
		printf("Введите новую Фамилию\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.surname = str;
		break;
	case 3:
		printf("Введите новое Отчество\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.patr = str;
		break;
	case 4:
		printf("Введите новые контактные данные\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.contacts = str;
		break;
	case 5:
		printf("Введите новый Город\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.city = str;
		break;
	case 6:
		printf("Введите новое образование\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.education = str;
		break;
	case 7:
		printf("Введите новую работу\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.work = str;
		break;
	case 8:
		printf("Введите новыу интересы\n");
		rewind(stdin);
		scanf("%[^\n]s", str);
		man.interests = str;
		break;
	case 10:
		return man;
	}
	return man;
}

int menu()
{
	int n;
	puts("---------Главное меню---------");
	printf("\
1. Показать всех людей\n\
2. Добавить нового человека\n\
3. Добавить друзей \n\
4. Показать всех друзей\n\
5. Редактирование\n\
6. Поиск\n\
7. Удалить человека\n\
8. Удалить друзей\n\
9. Загрузить из файла\n\
10. Записать в файл\n\
11. Выход\n");
	scanf("%d", &n);
	rewind(stdin);
	return n;
}

int SearchMenu()
{
	int point;
	printf("Выберите пункт для поиска\n\
1 - Имя\n\
2 - Фамилия\n\
3 - Отчество\n\
4 - Контактные данные\n\
5 - Город\n\
6 - Образование\n\
7 - Работа\n\
8 - Интересы\n\
10 - Не ищи\n");
	scanf("%d", &point);
	return point;
}

void Search(Person* man, int length)
{
	int point = SearchMenu();
	char* str = (char*)malloc(20 * sizeof(char*));
	int repeats = 0;
	puts("Введите ключ для поиска");
	rewind(stdin);
	scanf("%[^\n]s", str);
	switch (point)
	{
	case 1: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].name, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}}
	case 2: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].surname, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 3: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].patr, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 4: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].contacts, str))
			{
				printf("человек под номером  %d", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 5: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].city, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 6: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].education, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено");
		}
		break; }
	case 7: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].work, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 8: {
		for (int i = 0; i < length; i++)
		{
			if (!strcmp(man[i].interests, str))
			{
				printf("человек под номером  %d\n", i);
				ShowPeacePeople(man[i]);
				repeats++;
			}
		}
		if (repeats == 0)
		{
			puts("Совпадений не найдено\n");
		}
		break; }
	case 10: {puts("Ваше решение принято");
		break; }
	default: puts("Вы не выбрали верный пункт"); break;
	}
}

void SearchBySNP(Person* man, int length)
{
	int repeats = 0;
	Person temp = AddPerson();
	for (int i = 0; i < length; i++)
	{
		if (!strcmp(man[i].name, temp.name) &&
			!strcmp(man[i].surname, temp.surname) &&
			!strcmp(man[i].patr, temp.patr)) {
			printf("Найден человек с такими параматрами\n\
			%d человек в листе\n", i);
			repeats++;
		}
	}
	if (repeats)
	{
		puts("Совпадений не найдено");
	}
}

void SearchByAllParametrs(Person* man, int length)
{
	int repeats = 0;
	Person temp = AddPerson();
	for (int i = 0; i < length; i++)
	{
		if (!strcmp(man[i].name, temp.name) &&
			!strcmp(man[i].surname, temp.surname) &&
			!strcmp(man[i].patr, temp.patr) &&
			!strcmp(man[i].contacts, temp.contacts) &&
			!strcmp(man[i].education, temp.education) &&
			!strcmp(man[i].city, temp.city) &&
			!strcmp(man[i].interests, temp.interests) &&
			!strcmp(man[i].work, temp.work))
		{
			printf("Найден человек с такими параматрами\n\
			%d человек в листе\n,", i);
			repeats++;
		}
	}
	if (repeats)
	{
		puts("совпадений не найдено");
	}
}

void TypeOfSearch(Person* man, int length)
{
	puts("1. По одному параметру\n\
2. По ФИО\n\
3. По всем параметрам\n");
	int switch_on;
	scanf("%d", &switch_on);
	while (switch_on < 1 || switch_on>3)
	{
		puts("Неверный ввод");
		scanf("%d", &switch_on);
	}
	switch (switch_on)
	{
	case 1: Search(man, length); break;
	case 2: SearchBySNP(man, length); break;
	case 3: SearchByAllParametrs(man, length); break;
	}
}

void DeletePerson(Person* man, int length)
{
	ShowAllPeacePeople(man, length);
	int index = 0;
	while (index<1 || index>length + 1)
	{
		puts("Выберите номер человека для удаления\n");
		scanf("%d", &index);
	}
	for (int i = index; i < length; i++)
	{
		man[i - 1] = man[i];
	}
	man = (Person*)newPamyat((void*)man, length - 1, sizeof(Person));
}

void ReadIsFaila(Person* man, int& count)
{
	FILE* file = fopen("Text.txt", "rb");
	if (!file)
	{
		puts("Файл не открыт");
		return;
	}
	char* name = (char*)malloc(sizeof(char*) * 20);
	char* surname = (char*)malloc(sizeof(char*) * 20);
	char* patr = (char*)malloc(sizeof(char*) * 20);
	char* contacts = (char*)malloc(sizeof(char*) * 20);
	char* town = (char*)malloc(sizeof(char*) * 20);
	char* education = (char*)malloc(sizeof(char*) * 20);
	char* work = (char*)malloc(sizeof(char*) * 20);
	char* interests = (char*)malloc(sizeof(char*) * 20);

	while (!feof(file))
	{
		fgets(name, 20, file);
		fgets(surname, 20, file);
		fgets(patr, 20, file);
		fgets(contacts, 20, file);
		fgets(town, 20, file);
		fgets(education, 20, file);
		fgets(work, 20, file);
		fgets(interests, 20, file);
		
		count++;
		man = (Person*)newPamyat((void*)man, count, sizeof(Person));
		printf("size is%d\n\n", _msize(man));
		man[count - 1] = PersonCreater(name, surname, patr, contacts, town, education, work, interests);
	}
	fclose(file);
}

void WriteToFile(Person* man, int length)
{
	FILE* file = fopen("End.txt", "a+");
	for (int i = 0; i < length; i++)
	{
		fputs(man[i].name, file);
		fputs(man[i].surname, file);
		fputs(man[i].patr, file);
		fputs(man[i].contacts, file);
		fputs(man[i].city, file);
		fputs(man[i].education, file);
		fputs(man[i].work, file);
		fputs(man[i].interests, file);
	}
	fclose(file);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int countOfpeople;
	Person* people;
	int index = 0;
	puts("Сколько людей вы хотите ввести? (не более 10)");
	rewind(stdin);
	scanf("%d", &countOfpeople);
	while (countOfpeople < 1 || countOfpeople>10)
	{
		puts("Неверный ввод, попробуйте заново\nСколько людей вы хотите ввести?");
		rewind(stdin);
		scanf("%d", &countOfpeople);
	}
	people = (Person*)malloc(sizeof(Person) * countOfpeople);
	int cheNado = 0;
	while (cheNado < 1 || cheNado>2) {
		puts("Вы желаете сами заполнить структуры или сгенировать\n\
1. Сам\n\
2. Сгенировать\n");
		scanf("%d", &cheNado);
	}
	if (cheNado == 1)
	{
		for (int i = 0; i < countOfpeople; i++)
		{
			people[i] = AddPerson();
		}
	}
	else
	{
		people = PersonLibrary(countOfpeople);
	}

	while (true)
	{
		switch (menu())
		{
		case 1:
			ShowAllPeople(countOfpeople, people);
			break;
		case 2:
			countOfpeople++;
			AddNewPerson(people, countOfpeople);
			break;
		case 3:
			addFrends(people, countOfpeople);
			break;
		case 4:
			ShowFrends(people, countOfpeople);
			break;
		case 5:
			while (index<1 || index>countOfpeople)
			{
				puts("Выберите человека");
				ShowAllPeacePeople(people, countOfpeople);
				scanf("%d", &index);
			}
			index--;
			people[index] = ChangeInfo(people[index]);
			break;
		case 6:			
			TypeOfSearch(people, countOfpeople);
			break;
		case 7:
			DeletePerson(people, countOfpeople);
			countOfpeople--;
			break;
		case 8:
			DeleteFriends(people, countOfpeople);
			break;
		case 9:
			ReadIsFaila(people, countOfpeople);
			break;
		case 10:
			WriteToFile(people, countOfpeople);
			break;
		case 11:
			free(people);
			return 0;
			break;
		}
	}
	free(people);
	return 0;
}
