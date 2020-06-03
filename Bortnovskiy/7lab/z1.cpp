//7lab 7 lab Социальная сеть. Множество людей организовано по принципу сети: 
//каждый человек имеет свой круг общения, у каждого из этого круга, в свою очередь, есть свой круг и т.д. 
//Добавление нового члена ( ФИО, контакты, город, образование, работа, интересы). Установление и удаление связей. 
//Поиск нужных людей по интересам, местонахождению, образованию или работе. 
//Возможность просмотра кругов общения, т.е. « путешествия» по социальной сети. 
#include <stdio.h>
#include <Windows.h>
#include <time.h>

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
	int SkolkoFriends = 0;
    Person* friends = nullptr;

}Person;

Person PersonCreater(char* name, char* surname, char* patr, char* contacts, char* work, char* education, char* city, char* interests)
{
	Person Person;
	Person.name = name;
	Person.surname = surname;
	Person.patr = patr;
	Person.contacts = contacts;
	Person.education = education;
	Person.interests = interests;
	Person.patr = patr;
	Person.city = city;
	Person.work = work;
	return Person;
}

void ReadIsFaila(Person* chelovek, int& vsego)
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

		vsego++;
		chelovek = (Person*)newPamyat((void*)chelovek, vsego, sizeof(Person));
		printf("size is%d\n\n", _msize(chelovek));
		chelovek[vsego - 1] = PersonCreater(name, surname, patr, contacts, town, education, work, interests);
	}
	fclose(file);
}

void WriteToFile(Person* chelovek, int length)
{
	FILE* file = fopen("End.txt", "a+");
	for (int i = 0; i < length; i++)
	{
		fputs(chelovek[i].name, file);
		fputs(chelovek[i].surname, file);
		fputs(chelovek[i].patr, file);
		fputs(chelovek[i].contacts, file);
		fputs(chelovek[i].city, file);
		fputs(chelovek[i].education, file);
		fputs(chelovek[i].work, file);
		fputs(chelovek[i].interests, file);
	}
	fclose(file);
}

void ShowPerson(Person chelovek)
{
	printf("---\n");
	printf("Имя - %s\n", chelovek.name);
	printf("Фамилия - %s\n", chelovek.surname);
	printf("Отчество - %s\n", chelovek.patr);
	printf("Город - %s\n", chelovek.city);
	printf("Работа - %s\n", chelovek.work);
	printf("Контактные данные - %s\n", chelovek.contacts);
	printf("Образование- %s\n", chelovek.education);
	printf("Интересы - %s\n", chelovek.interests);
	printf("---\n");
}

Person AddPerson()
{
	char* name = (char*)malloc(sizeof(char*) * 20);
	char* surname = (char*)malloc(sizeof(char*) * 20);
	char* patr = (char*)malloc(sizeof(char*) * 20);
	char* contacts = (char*)malloc(sizeof(char*) * 20);
	char* city = (char*)malloc(sizeof(char*) * 20);
	char* education = (char*)malloc(sizeof(char*) * 20);
	char* work = (char*)malloc(sizeof(char*) * 20);
	char* interests = (char*)malloc(sizeof(char*) * 20);
	rewind(stdin);

	puts("Фамилия:");
	scanf("%[^\n]s", surname);
	rewind(stdin);
	puts("Имя:");
	scanf("%[^\n]s", name);
	rewind(stdin);
	puts("Отчество:");
	scanf("%[^\n]s", patr);
	rewind(stdin);
	puts("Контактные данные:");
	scanf("%[^\n]s", contacts);
	rewind(stdin);
	puts("Образование:");
	scanf("%[^\n]s", education);
	rewind(stdin);
	puts("Профессия:");
	scanf("%[^\n]s", work);
	rewind(stdin);
	puts("Хобби:");
	scanf("%[^\n]s", interests);
	rewind(stdin);
	puts("Город:");
	scanf("%[^\n]s", city);

	Person chelovek = PersonCreater(name, surname, patr, contacts, city, education, work, interests);

	free(name);
	free(surname);
	free(patr);
	free(contacts);
	free(city);
	free(education);
	free(work);
	free(interests);

	return chelovek;
}

void* newPamyat(void* z,  int c,  int size)
{
	void* NewPerem = z;
	z = calloc(c, sizeof(size));
	z = NewPerem;
	return z;
}

void AddNewPerson(Person* chelovek, int count)
{
	chelovek = (Person*)newPamyat((void*)chelovek, count, sizeof(Person));
	chelovek[count - 1] = AddPerson();
}

void ShowFriends(Person* chelovek, int length)
{
	for (int x = 0; x < length; x++)
	{
		printf("Друзья %d человека\n---\n", x + 1);
		if (chelovek[x].SkolkoFriends == 0)
		{
			printf("Одиночество-скука");
		}
		else
		{
			for (int i = 0; i < chelovek[x].SkolkoFriends; i++)
			{
				printf("\t %d друг \t Имя - %s \t Фамилия - %s\n", i + 1, chelovek[x].friends[i].name, chelovek[x].friends[i].surname);
				printf("---\n");
			}
		}
	}
}

void ShowAllPeople(int vsego, Person* people)
{
	for (int i = 0; i < vsego; i++)
	{
		printf("%d-й человек:\n", i + 1);
		ShowPerson(people[i]);
	}
}

void NachDan(Person man)
{
	puts("-------------------------------------------------------------");
	printf("\
Имя:%s\t\
\tФамилия:%s\t\
\tОтчество:%s\t\n", man.name, man.surname, man.patr);
	
}

void PersonDestroyer(Person chel)
{
	free(chel.name);
	free(chel.surname);
	free(chel.patr);
	free(chel.contacts);
	free(chel.education);
	free(chel.interests);	
	free(chel.city);
	free(chel.work);
	if (chel.SkolkoFriends > 0)
		for (int i = 0; i < chel.SkolkoFriends; i++)
		{			
			free(chel.friends[i].name);
			free(chel.friends[i].surname);
			free(chel.friends[i].patr);
			free(chel.friends[i].interests);
			free(chel.friends[i].contacts);
			free(chel.friends[i].city);
			free(chel.friends[i].work);
			free(chel.friends[i].education);
		}

}

void VsehDoloy(Person* ludi, int kolvo)
{
	for (int i = 0; i < kolvo; i++)	
		PersonDestroyer(ludi[i]);	
}

void PokazhFrVse(Person* people, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d человек\n", i + 1);

		NachDan(people[i]);
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

Person* MoiLudi(int count)
{
	char name[6][20] = { "Ilya","Roma","Dima","Evgen","Danik","Sasha" };
	char surname[6][20] = { "Krivetskiy","Bortnovskiy","Semenuk","Kreidich","Kamornik","Kochurko" };
	char patr[6][20] = { "Alexeevich","Nikolaevich","Alexandrovich","Mixailovich","Sergeevich","Danilovich" };
	char town[6][20] = { "Brest","Gorodechno","Minsk","Pochaev","Piter","Pskov" };
	char education[6][20] = { "Middle","Higher","No education","Base","Bakalavr","Special" };
	char interests[6][20] = { "No","RealLife","Girls","Football","Fishing","Dancing" };
	char work[6][20] = { "No","Doctor","Priest","Starosta","Programmer","Photographer" };
	char contacts[6][20] = { "293115117","445578964","333167964","445334900","295761287","336547899" };

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
	PokazhFrVse(people, count);
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
		PokazhFrVse(people, count);
		scanf("%d", &number);
	}
	number--;
	int last = people[index].SkolkoFriends;
	if (people[index].SkolkoFriends == 0)
	{
		people[index].friends = (Person*)malloc(1 * sizeof(Person));
		people[index].SkolkoFriends++;
	}
	else
	{
		people[index].SkolkoFriends++;
		people[index].friends = (Person*)newPamyat((void*)people[index].friends, people[index].SkolkoFriends, sizeof(Person));
	}
	int x = (people[number].SkolkoFriends);
	if (people[number].SkolkoFriends == 0)
	{
		people[number].friends = (Person*)malloc(1 * sizeof(Person));
		people[number].SkolkoFriends++;
	}
	else
	{
		people[number].SkolkoFriends++;
		people[number].friends = (Person*)newPamyat((void*)people[number].friends, people[number].SkolkoFriends, sizeof(Person));

	}
	
	if (index != number)
	{
		if (people[index].SkolkoFriends - 1 == 0)
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
			for (int i = 0; i < people[index].SkolkoFriends; i++)
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
	PokazhFrVse(people, count);
	int index = 0;
	while (index<1 || index>count + 1)
	{
		puts("Выберите человека");
		scanf("%d", &index);
	}
	index--;
	int number = 0;
	if (people[index].SkolkoFriends == 0)
	{
		puts("У него нет друзей");
		return;
	}
	while (number<1 || number> people[index].SkolkoFriends)
	{
		puts("Выберите человека для удаления из друзей");
		PokazhFrVse(people[index].friends, people[index].SkolkoFriends);
		scanf("%d", &number);
	}
	for (int i = number; i < people[index].SkolkoFriends; i++)
	{
		people[index].friends[i - 1] = people[index].friends[i];
	}
	people[index].SkolkoFriends--;
	people[index].friends = (Person*)newPamyat((void*)people[index].friends, people[index].SkolkoFriends, sizeof(Person));
}

int EditMenu()
{
	int point;
	printf("Что редактируем?\n\
1 - Имя\n\
2 - Фамилия\n\
3 - Отчество\n\
4 - Контактные данные\n\
5 - Город\n\
6 - Образование\n\
7 - Работа\n\
8 - Интересы\n\
10 - Ничего\n");
	scanf("%d", &point);
	return point;
}

Person ChangeInfo(Person man)
{
	char* s = (char*)malloc(20 * sizeof(char*));
	switch (EditMenu())
	{
	case 1:
		printf("Новое Имя\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.name = s;
		break;
	case 2:
		printf("Новая Фамилия\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.surname = s;
		break;
	case 3:
		printf("Новое Отчество\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.patr = s;
		break;
	case 4:
		printf("Новые контактные данные\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.contacts = s;
		break;
	case 5:
		printf("Новый Город\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.city = s;
		break;
	case 6:
		printf("Новое образование\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.education = s;
		break;
	case 7:
		printf("Новая работу\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.work = s;
		break;
	case 8:
		printf("Новый интерес\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.interests = s;
		break;
	case 10:
		return man;
	}
	return man;
}

int menu()
{
	int n;
	puts("-Меню-");
	printf("\
1. Показать всех\n\
2. Добавить нового человека\n\
3. Добавить друзей \n\
4. Показать всех друзей\n\
5. Изменить инфу\n\
6. Поиск\n\
7. Удалить человека\n\
8. Удалить из друзей\n\
9. Загрузить из файла\n\
10. Записать в файл\n\
11. Выход\n");
	scanf("%d", &n);
	rewind(stdin);
	return n;
}

int Ishem()
{
	int item;
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
	scanf("%d", &item);
	return item;
}

void Search(Person* man, int dli)
{
	int point = Ishem();
	char* str = (char*)malloc(20 * sizeof(char*));
	int repeats = 0;
	puts("Введите слово для поиска");
	rewind(stdin);
	scanf("%[^\n]s", str);
	switch (point)
	{
	case 1: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].name, str))
			{
				printf("Человек номер  %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); }
	case 2: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].surname, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");break; }
	case 3: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].patr, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");break; }
	case 4: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].contacts, str))
			{
				printf("Человек номер %d", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");break; }
	case 5: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].city, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); break; }
	case 6: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].education, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); break; }
	case 7: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].work, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");
		break; }
	case 8: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].interests, str))
			{
				printf("Человек номер %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");
		break; }
	case 10: {puts("Зачем тогда звал?"); break; }
	default: puts("Лажа"); break;
	}
}

void SearchByN(Person* man, int length)
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
	if (repeats) puts("404err");
	
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
			printf("Найден человек с такими параматрами %d человек \n,", i);
			repeats++;
		}
	}
	if (repeats) puts("404err");
	
}

void TypeOfSearch(Person* chelovek, int vsego)
{
	puts("1. По одному параметру\n\
2. По ФИО\n\
3. По всем параметрам\n");
	int item;
	scanf("%d", &item);
	while (item < 1 || item>3)
	{
		puts("Лажа");
		scanf("%d", &item);
	}
	switch (item)
	{
	case 1: Search(chelovek, vsego); break;
	case 2: SearchByN(chelovek, vsego); break;
	case 3: SearchByAllParametrs(chelovek, vsego); break;
	}
}

void DeletePerson(Person* man, int vsego)
{
	PokazhFrVse(man, vsego);
	int index = 0;
	while (index<1 || index>vsego + 1)
	{
		puts("Выберите номер человека для уничтожения\n");
		scanf("%d", &index);
	}
	for (int i = index; i < vsego; i++)
	{
		man[i - 1] = man[i];
	}
	man = (Person*)newPamyat((void*)man, vsego - 1, sizeof(Person));
}

int main()
{
	int vsego;
	Person* people;
	int index = 0;
	puts("Сколько людей вы хотите ввести? (не более 10)");
	rewind(stdin);
	scanf("%d", &vsego);
	while (vsego < 1 || vsego>10)
	{
		puts("Лажа, попробуйте заново\nСколько людей вы хотите ввести?");
		rewind(stdin);
		scanf("%d", &vsego);
	}
	people = (Person*)malloc(sizeof(Person) * vsego);
	int cheNado = 0;
	while (cheNado < 1 || cheNado>2) {
		puts("Вы желаете сами заполнить структуры или сгенировать\n\
1. Самостоятельно\n\
2. Сгенировать\n");
		scanf("%d", &cheNado);
	}
	if (cheNado == 1)
	{
		for (int i = 0; i < vsego; i++)
		{
			people[i] = AddPerson();
		}
	}
	else people = MoiLudi(vsego);
	

	while (true)
	{
		switch (menu())
		{
		case 1:
			ShowAllPeople(vsego, people); break;
		case 2:
			vsego++;
			AddNewPerson(people, vsego); break;
		case 3:
			addFrends(people, vsego); break;
		case 4:
			ShowFriends(people, vsego); break;
		case 5:
			while (index<1 || index>vsego)
			{
				puts("Выберите человека");
				PokazhFrVse(people, vsego);
				scanf("%d", &index);
			}
			index--;
			people[index] = ChangeInfo(people[index]); break;
		case 6:			
			TypeOfSearch(people, vsego); break;
		case 7:
			DeletePerson(people, vsego); 
			vsego--; break;
		case 8:
			DeleteFriends(people, vsego); break;
		case 9:
			ReadIsFaila(people, vsego); break;
		case 10:
			WriteToFile(people, vsego); break;
		case 11:
			if (cheNado == 1)
			{
				VsehDoloy(people, vsego);
				free(people);
			}
			else
			  free(people);
			return 0;
		}
	}
	free(people);
	return 0;
}
