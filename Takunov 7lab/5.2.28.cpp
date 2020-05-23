#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <exception>
//#include <iostream>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

char name[6][20] = { "Pavel","Peter","Dima","Evgen","Ivan","Sasha" };
char surname[6][20] = { "Takunov","Bortnovskiy","Pristrom","Vinuk","Stupak","Puskash" };
char patryotic[6][20] = { "Alexeevich","Andeevich","Ivanovich","Mixailovich","Sergeevich"," Anatolevich" };
char town[6][20] = { "Minsk","Brest","Gomel","Piter","Moscow","Donbas" };
char education[6][20] = { "Middle","Higher","No education","Base","Bakalavr","Special" };
char interests[6][20] = { "No","Programming","Football","Hockey","Fishhing","Diving" };
char work[6][20] = { "No","Soft Developer","Individual work","Policeman","Businessman","Photographer" };
char contacts[6][20] = { "293556787","296805830","333167964","445334900","297634113","296682431" };

void* newrealloc(void* source, _In_ _CRT_GUARDOVERFLOW size_t _Count, _In_ _CRT_GUARDOVERFLOW size_t _Size)
{
	void* temp = source;
	source = calloc(_Count, sizeof(_Size));
	source = temp;
	//printf("начальная память %d", _msize((int*)temp));v
	//printf("конечная память %d", _msize((int*)source));
	return source;
}

struct Person;

struct Circle;

typedef struct Circle
{
	Person* circle;
}Circle;

typedef struct Person
{
	char* name = nullptr;
	char* surname = nullptr;
	char* patryotic = nullptr;
	char* contacts = nullptr;
	char* town = nullptr;
	char* education = nullptr;
	char* work = nullptr;
	char* interests = nullptr;
	int countoffrends = 0;
	//Circle* myfrends=nullptr;
	Person* frends = nullptr;/*=(Person*)malloc(20*sizeof(Person*))*/;
}Person;

Person PersonInitializer(char* name, char* surname, char* patryotic, char* contacts, char* town, char* education, char* work, char* interests/*, char* languages, Organisation* organisations, int organisationCount, Crime* crimeList, int crimeCount*/)
{
	Person Person;
	Person.name = name;
	Person.contacts = contacts;
	Person.education = education;
	Person.interests = interests;
	Person.patryotic = patryotic;
	Person.surname = surname;
	Person.town = town;
	Person.work = work;
	return Person;
}

Person AddPerson()
{
	char* name = (char*)malloc(sizeof(char*) * 200000);
	char* surname = (char*)malloc(sizeof(char*) * 200000);
	char* patryotic = (char*)malloc(sizeof(char*) * 200000);
	char* contacts = (char*)malloc(sizeof(char*) * 200000);
	char* town = (char*)malloc(sizeof(char*) * 200000);
	char* education = (char*)malloc(sizeof(char*) * 200000);
	char* work = (char*)malloc(sizeof(char*) * 200000);
	char* interests = (char*)malloc(sizeof(char*) * 200000);
	rewind(stdin);
	puts("Введите Фамилию человека");
	scanf("%[^\n]s", surname);
	rewind(stdin);
	puts("Введите Имя человека");
	scanf("%[^\n]s", name);
	rewind(stdin);
	puts("Введите Отчество человека");
	scanf("%[^\n]s", patryotic);
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

	Person man = PersonInitializer(name, surname, patryotic, contacts, town, education, work, interests);
	//printf("size is%d\n", sizeof(man));
	//free(name);
	//free(surname);
	//free(patryotic);
	//free(contacts);
	//free(town);
	//free(education);
	//free(work);
	//free(interests);
	return man;
}

void AddNewPerson(Person* man, int count)
{
	//добавить нового человека
	man = (Person*)newrealloc((void*)man, count, sizeof(Person));
	man[count - 1] = AddPerson();
}

void ShowPerson(Person man)
{
	printf("----------------------------------\n");
	printf("Имя - %s\n", man.name);
	printf("Фамилия - %s\n", man.surname);
	printf("Отчество - %s\n", man.patryotic);
	printf("Город - %s\n", man.town);
	printf("Работа - %s\n", man.work);
	printf("Контактные данные - %s\n", man.contacts);
	printf("Образование- %s\n", man.education);
	printf("Интересы - %s\n", man.interests);
	printf("---------------------------------------------------------------------\n");
	//int x = man.countoffrends; x--;
	for (int i = 0; i < man.countoffrends; i++)
	{
		printf("\t %d друг\tИмя - %s\tФамилия - %s\n", i + 1, man.frends[i].name, man.frends[i].surname);
		printf("---------------------------------------------------------------------\n");
	}

	//printf("----------------------------------\n");
}

void ShowFrends(Person* man, int length)
{
	for (int x = 0; x < length; x++)
	{
		printf("Друзья %d человека\n", x + 1);
		printf("---------------------------------------------------------------------\n");
		if (man[x].countoffrends == 0)
		{
			printf("Нету друзей у  %d человека\n", x + 1);
		}
		else
		{
			for (int i = 0; i < man[x].countoffrends; i++)
			{
				printf("\t %d друг \t Имя - %s \t Фамилия - %s\n", i + 1, man[x].frends[i].name, man[x].frends[i].surname);
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
	//puts("------------------------------");
	puts("-------------------------------------------------------------");
	printf("\
Имя:%s\t\
\tФамилия:%s\t\
\tОтчество:%s\t\n", man.name, man.surname, man.patryotic);
	//puts("-------------------------");
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
		!strcmp(man1.patryotic, man2.patryotic) &&
		!strcmp(man1.contacts, man2.contacts) &&
		!strcmp(man1.education, man2.education) &&
		!strcmp(man1.town, man2.town) &&
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
	//char name[6][20] = { "Pavel","Peter","Dima","Evgen","Ivan","Sasha" };
	//char surname[6][20] = { "Takunov","Bortnovskiy","Pristrom","Vinuk","Stupak","Puskash" };
	//char patryotic[6][20] = { "Alexeevich","Andeevich","Ivanovich","Mixailovich","Sergeevich"," Anatolevich" };
	//char town[6][20] = { "Minsk","'Brest","Gomel","Piter","Moscow","Donbas" };
	//char education[6][20] = { "Middle","Higher","No education","Base","Bakalavr","Special" };
	//char interests[6][20] = { "No","Programming","Football","Hockey","Fishhing","Diving" };
	//char work[6][20] = { "No","Soft Developer","Individual work","Policeman","Businessman" };
	//char contacts[6][20] = { "293556787","296805830","333167964","445334900","297634113","296682431" };
	for (int i = 0; i < count; i++)
	{
		temp[i] = PersonInitializer((char*)name[rand() % 6], (char*)surname[rand() % 6], (char*)patryotic[rand() % 6],
			(char*)contacts[rand() % 6], (char*)town[rand() % 6],
			(char*)education[rand() % 6], (char*)work[rand() % 6], (char*)interests[rand() % 6]);
	}
	//temp.name = (char*)name[a[1]];
	//temp.surname = (char*)surname[a[2]];
	//temp.patryotic = (char*)patryotic[a[3]];
	//temp.contacts = (char*)contacts[a[4]];
	//temp.interests = (char*)interests[a[5]];
	//temp.town = (char*)town[a[6]];
	//temp.work = (char*)work[a[7]];
	//temp.education = (char*)education[a[0]];
	return temp;
}

Person Standart()
{
	Person standart;
	standart.name = (char*)"Pavel";
	standart.contacts = (char*)"251775225";
	standart.countoffrends = 0;
	standart.education = (char*)"middle";
	standart.interests = (char*)"programming";
	standart.patryotic = (char*)"no";
	standart.surname = (char*)"Takunov";
	standart.town = (char*)"Minsk";
	standart.work = (char*)"without";
	return standart;
}

Person StandartFrend()
{
	Person standart;
	standart.name = (char*)"Nikita";
	standart.contacts = (char*)"296682431";
	standart.countoffrends = 0;
	standart.education = (char*)"middle";
	standart.interests = (char*)"programming";
	standart.patryotic = (char*)"Mixailov";
	standart.surname = (char*)"Klybik";
	standart.town = (char*)"Minsk";
	standart.work = (char*)"Soft Developer";
	return standart;
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
	int last = people[index].countoffrends;
	if (people[index].countoffrends == 0)
	{
		people[index].frends = (Person*)malloc(1 * sizeof(Person));
		people[index].countoffrends++;
	}
	else
	{
		people[index].countoffrends++;
		people[index].frends = (Person*)newrealloc((void*)people[index].frends, people[index].countoffrends, sizeof(Person));
	}
	int x = (people[number].countoffrends);
	if (people[number].countoffrends == 0)
	{
		people[number].frends = (Person*)malloc(1 * sizeof(Person));
		people[number].countoffrends++;
	}
	else
	{
		people[number].countoffrends++;
		people[number].frends = (Person*)newrealloc((void*)people[number].frends, people[number].countoffrends, sizeof(Person));

	}
	/*people[index].frends[last] = people[number];
	people[number].frends[x] = people[index];
	puts("Друг добавлен\n")*/;
	//выделение памяти под круг друзей
	//people[index].frends[last] = StandartFrend();
	if (index != number)
	{
		if (people[index].countoffrends - 1 == 0)
		{
			if (PersonCompare(people[index], people[number]) == 0)
			{
				people[index].frends[last] = people[number];
				people[number].frends[x] = people[index];
				puts("Друг добавлен\n");
			}
			else
			{
				puts("Данный человек уже есть\n");
			}
		}
		else {
			for (int i = 0; i < people[index].countoffrends; i++)
			{
				if (PersonCompare(people[index].frends[i], people[number]) == 1)
				{
					people[index].frends[last] = people[number];
					people[number].frends[x] = people[index];
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

void DeleteFrends(Person* people, int count)
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
	if (people[index].countoffrends == 0)
	{
		puts("у него нету друзей");
		return;
	}
	while (number<1 || number> people[index].countoffrends)
	{
		puts("Выберите человека для удаления из друзей");
		ShowAllPeacePeople(people[index].frends, people[index].countoffrends);
		scanf("%d", &number);
	}
	for (int i = number; i < people[index].countoffrends; i++)
	{
		people[index].frends[i - 1] = people[index].frends[i];
	}
	people[index].countoffrends--;
	people[index].frends = (Person*)newrealloc((void*)people[index].frends, people[index].countoffrends, sizeof(Person));
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
		man.patryotic = str;
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
		man.town = str;
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
	//puts("------------------------------");
	puts("---------Главное меню---------");
	printf("\
1. Показать всех людей\n\
2. Добавить нового человека\n\
3. Добавить друзей \n\
4. Поиск\n\
5. Редактирование\n\
6. Показать всех друзей\n\
7. Выход\n\
8. Удалить человека\n\
9. Удалить друзей\n\
10. Загрузить из файла\n\
11. Записать в файл\n");
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
10 - Я передумал\n");
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
			if (!strcmp(man[i].patryotic, str))
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
			if (!strcmp(man[i].town, str))
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
			!strcmp(man[i].patryotic, temp.patryotic)) {
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
			!strcmp(man[i].patryotic, temp.patryotic) &&
			!strcmp(man[i].contacts, temp.contacts) &&
			!strcmp(man[i].education, temp.education) &&
			!strcmp(man[i].town, temp.town) &&
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
	default:
		break;
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
	man = (Person*)newrealloc((void*)man, length - 1, sizeof(Person));
}

void FreeOne(Person man) 
{
	free(man.name);
	free(man.contacts);
	free(man.education);
	free(man.interests);
	free(man.patryotic);
	free(man.surname);
	free(man.town);
	free(man.work);
	if (man.countoffrends > -1)
		for (int j = 0; j < man.countoffrends; j++)
		{
			free(man.frends[j].contacts);
			free(man.frends[j].name);
			free(man.frends[j].surname);
			free(man.frends[j].patryotic);
			free(man.frends[j].interests);
			free(man.frends[j].town);
			free(man.frends[j].work);
			free(man.frends[j].education);
		}
}
void FreeList(Person* man, int size) 
{
	for (int i = 0; i < size; i++)
	{
		FreeOne(man[i]);
	}
}

void ReadInformation(Person* man, int& count)
{
	FILE* file = fopen("temp.TXT", "rb");
	if (!file)
	{
		puts("Файл не открыт");
		return;
	}
	char* name = (char*)malloc(sizeof(char*) * 20);
	char* surname = (char*)malloc(sizeof(char*) * 20);
	char* patryotic = (char*)malloc(sizeof(char*) * 20);
	char* contacts = (char*)malloc(sizeof(char*) * 20);
	char* town = (char*)malloc(sizeof(char*) * 20);
	char* education = (char*)malloc(sizeof(char*) * 20);
	char* work = (char*)malloc(sizeof(char*) * 20);
	char* interests = (char*)malloc(sizeof(char*) * 20);
	while (!feof(file))
	{
		fgets(name, 20, file);
		fgets(surname, 20, file);
		fgets(patryotic, 20, file);
		fgets(contacts, 20, file);
		fgets(town, 20, file);
		fgets(education, 20, file);
		fgets(work, 20, file);
		fgets(interests, 20, file);
		//fscanf(file, "%[^\n]s,%[^\n]s,%[^\n]s,%[^\n]s,%[^\n]s,%[^\n]s,%[^\n]s,%[^\n]s", name, surname, patryotic, contacts, town, education, work, interests);
		count++;
		man = (Person*)newrealloc((void*)man, count, sizeof(Person));
		printf("size is%d\n\n", _msize(man));
		man[count - 1] = PersonInitializer(name, surname, patryotic, contacts, town, education, work, interests);
	}
	fclose(file);
}

void WriteInforamtion(Person* man, int length)
{
	FILE* file = fopen("infofile.TXT", "a+");
	for (int i = 0; i < length; i++)
	{
		fputs(man[i].name, file);
		fputs(man[i].surname, file);
		fputs(man[i].patryotic, file);
		fputs(man[i].contacts, file);
		fputs(man[i].town, file);
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
	system("color 0A");
	int countOfpeople,current;
	Person* people;
	int index = 0;
	int* a = new int(6);
	a = new int();
	puts("Сколько людей вы хотите ввести?");
	rewind(stdin);
	scanf("%d", &countOfpeople);
	while (countOfpeople < 1)
	{
		puts("Неверный ввод, попробуйте заново\nСколько людей вы хотите ввести?");
		rewind(stdin);
		scanf("%d", &countOfpeople);
		
	}
	current = countOfpeople;
	people = (Person*)malloc(sizeof(Person) * countOfpeople);
	int resolution = 0;
	while (resolution < 1 || resolution>2) {
		puts("Вы желаете сами заполнить структуры или сгенировать\n\
1. Сам\n\
2. Сгенировать\n");
		scanf("%d", &resolution);
	}
	if (resolution == 1)
	{
		for (int i = 0; i < countOfpeople; i++)
		{   
			people[i] = AddPerson();
			//people[i] = Standart();
		}
	}
	else
	{
		people = PersonLibrary(countOfpeople);
	}
	for (;;)
	{
		//puts("---------Главное меню---------");
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
			TypeOfSearch(people, countOfpeople);
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
			ShowFrends(people, countOfpeople);
			break;
		case 7:
			if (resolution==1)
			{
				FreeList(people, countOfpeople);
				free(people);
			}
			else
			{

				free(people);
			}
			return 0;
			break;
		case 8:
			DeletePerson(people, countOfpeople);
			countOfpeople--;
			break;
		case 9:
			DeleteFrends(people, countOfpeople);
			break;
		case 10:
			ReadInformation(people, countOfpeople);
			//ShowPerson(people[countOfpeople + 1]);
			break;
		case 11:
			WriteInforamtion(people, countOfpeople);
			break;
		}
	}
	free(people);
	return 0;
}
