//7lab 7 lab Социальная сеть. Множество людей организовано по принципу сети: 
//каждый человек имеет свой круг общения, у каждого из этого круга, в свою очередь, есть свой круг и т.д. 
//Добавление нового члена ( ФИО, контакты, город, образование, работа, интересы). Установление и удаление связей. 
//Поиск нужных людей по интересам, местонахождению, образованию или работе. 
//Возможность просмотра кругов общения, т.е. « путешествия» по социальной сети. 
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <clocale>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

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

void ShowPerson(Person chelovek)
{
	printf("\n");
	printf("Nmae - %s\n", chelovek.name);
	printf("Fam - %s\n", chelovek.surname);
	printf("otchesvo - %s\n", chelovek.patr);
	printf("City - %s\n", chelovek.city);
	printf("Work - %s\n", chelovek.work);
	printf("Contact data - %s\n", chelovek.contacts);
	printf("Obrazovanie- %s\n", chelovek.education);
	printf("Interes - %s\n", chelovek.interests);
	printf("\n");
}

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


void* newPamyat(void* z, int c, int size)
{
	void* NewPerem = z;
	z = calloc(c, sizeof(size));
	z = NewPerem;
	return z;
}

void ReadIsFaila(Person* chelovek, int& vsego)
{
	FILE* file = fopen("Text.txt", "rb");
	if (!file)
	{
		puts("File open:");
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

	puts("Fam:");
	scanf("%[^\n]s", surname);
	rewind(stdin);
	puts("Name:");
	scanf("%[^\n]s", name);
	rewind(stdin);
	puts("Otchestvo:");
	scanf("%[^\n]s", patr);
	rewind(stdin);
	puts("Contact data:");
	scanf("%[^\n]s", contacts);
	rewind(stdin);
	puts("Obrazovanie:");
	scanf("%[^\n]s", education);
	rewind(stdin);
	puts("Profesion:");
	scanf("%[^\n]s", work);
	rewind(stdin);
	puts("Hooby:");
	scanf("%[^\n]s", interests);
	rewind(stdin);
	puts("City:");
	scanf("%[^\n]s", city);

	Person chelovek = PersonCreater(name, surname, patr, contacts, work, education, city, interests);

	/*free(name);
	free(surname);
	free(patr);
	free(contacts);
	free(city);
	free(education);
	free(work);
	free(interests);*/

	return chelovek;
}
void AddNewPerson(Person* chelovek, int count)
{
	chelovek = (Person*)newPamyat((void*)chelovek, count, sizeof(Person));
	chelovek[count - 1] = AddPerson();
}

char name[6][20] = { "Ivan","Max","Lisha","Evgen","Dima","Sasha" };
char surname[6][20] = { "Ivanov","Sidorov","Petrov","Zyionov","Shmelev","Kochurko" };
char patr[6][20] = { "Alexeevich","Nikolaevich","Alexandrovich","Mixailovich","Sergeevich","Danilovich" };
char town[6][20] = { "Brest","Gorodechno","Minsk","Moscow","Piter","Lipetch" };
char education[6][20] = { "Middle","Higher","No education","Base","Bakalavr","Special" };
char interests[6][20] = { "No","RealLife","Girls","Football","Fishing","Dancing" };
char work[6][20] = { "No","Doctor","Priest","Starosta","Programmer","Photographer" };
char contacts[6][20] = { "293115117","445578964","333167964","445334900","295761287","336547899" };


void ShowAllPeople(int vsego, Person* people)
{
	for (int i = 0; i < vsego; i++)
	{
		printf("%d person:\n", i + 1);
		ShowPerson(people[i]);
	}
}

void ShowFriends(Person* chelovek, int length)
{
	for (int x = 0; x < length; x++)
	{
		printf("Friends %d of person\n---\n", x + 1);
		if (chelovek[x].SkolkoFriends == 0)
		{
			printf("YYYYYffff no friebds\n");
		}
		else
		{
			for (int i = 0; i < chelovek[x].SkolkoFriends; i++)
			{
				printf("\t %d Friend \t Name - %s \t Fam - %s\n", i + 1, chelovek[x].friends[i].name, chelovek[x].friends[i].surname);
				printf("---\n");
			}
		}
	}
}



void NachDan(Person man)
{
	puts("-------------------------------------------------------------");
	printf("\
Name:%s\t\
\tFam:%s\t\
\tOtchestvo:%s\t\n", man.name, man.surname, man.patr);

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

void PokazhAllFriends(Person* people, int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d Persone\n", i + 1);

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

	srand(time(NULL));
	Person* temp = (Person*)malloc(sizeof(Person) * count);;

	for (int i = 0; i < count; i++)
	{
		temp[i] = PersonCreater((char*)name[rand() % 6], (char*)surname[rand() % 6], (char*)patr[rand() % 6],
			(char*)contacts[rand() % 6], (char*)work[rand() % 6],
			(char*)education[rand() % 6], (char*)town[rand() % 6], (char*)interests[rand() % 6]);
	}

	return temp;
}

void addFrends(Person* people, int count)
{
	PokazhAllFriends(people, count);
	int index = 0;
	while (index<1 || index>count + 1)
	{
		puts("Choose person");
		scanf("%d", &index);
	}
	index--;
	int number = 0;
	while (number<1 || number>count + 1)
	{
		puts("Choose person to add friend");
		PokazhAllFriends(people, count);
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
				puts("Friend added\n");
			}
			else
			{
				puts("We have this persone\n");
			}
		}
		else {
			for (int i = 0; i < people[index].SkolkoFriends; i++)
			{
				if (PersonCompare(people[index].friends[i], people[number]) == 1)
				{
					people[index].friends[last] = people[number];
					people[number].friends[x] = people[index];
					puts("Friend added\n");
				}
				else
				{
					puts("We have this persone\n");
				}
			}
		}
	}
	else
	{
		puts("Your couldn't add your sels \n");
	}
}

void DeleteFriends(Person* people, int count)
{
	PokazhAllFriends(people, count);
	int index = 0;
	while (index<1 || index>count + 1)
	{
		puts("Choose person");
		scanf("%d", &index);
	}
	index--;
	int number = 0;
	if (people[index].SkolkoFriends == 0)
	{
		puts("no friends");
		return;
	}
	while (number<1 || number> people[index].SkolkoFriends)
	{
		puts("Enter persen ta delete from friends");
		PokazhAllFriends(people[index].friends, people[index].SkolkoFriends);
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
	printf("What correct?\n\
1 - Nmae\n\
2 - Famil\n\
3 - Otchectvo\n\
4 - Contact Data\n\
5 - City\n\
6 - Obraz\n\
7 - Work\n\
8 - Hobby\n\
10 - Nathing\n");
	scanf("%d", &point);
	return point;
}

Person ChangeInfo(Person man)
{
	char* s = (char*)malloc(20 * sizeof(char*));
	switch (EditMenu())
	{
	case 1:
		printf("New name\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.name = s;
		break;
	case 2:
		printf("New fam\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.surname = s;
		break;
	case 3:
		printf("New otchestvo\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.patr = s;
		break;
	case 4:
		printf("New contact data\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.contacts = s;
		break;
	case 5:
		printf("New City\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.city = s;
		break;
	case 6:
		printf("New obrazovanie\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.education = s;
		break;
	case 7:
		printf("New work\n");
		rewind(stdin);
		scanf("%[^\n]s", s);
		man.work = s;
		break;
	case 8:
		printf("New hobby\n");
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
	puts("-Menu-");
	printf("\
1. Show all\n\
2. Add new person\n\
3. Add friend \n\
4. Show all friends\n\
5. Change information\n\
6. Shertch\n\
7. Delete person\n\
8. Delete from person\n\
9. Exit\n");
	scanf("%d", &n);
	rewind(stdin);
	return n;
}

int Ishem()
{
	int item;
	printf("Inter point to shortch\n\
1 - Name\n\
2 - Surname\n\
3 - Otchestvo\n\
4 - Contactnie dannie\n\
5 - City\n\
6 - Obrazovanie\n\
7 - work\n\
8 - Hobby\n\
10 - NO sertch\n");
	scanf("%d", &item);
	return item;
}

void Search(Person* man, int dli)
{
	int point = Ishem();
	char* str = (char*)malloc(20 * sizeof(char*));
	int repeats = 0;
	puts("Enter world to shortch");
	rewind(stdin);
	scanf("%[^\n]s", str);
	switch (point)
	{
	case 1: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].name, str))
			{
				printf("Person Namber  %d\n", i);
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
				printf("Person namber %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); break; }
	case 3: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].patr, str))
			{
				printf("Person namber %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); break; }
	case 4: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].contacts, str))
			{
				printf("Person namber %d", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err"); break; }
	case 5: {
		for (int i = 0; i < dli; i++)
		{
			if (!strcmp(man[i].city, str))
			{
				printf("Person namber %d\n", i);
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
				printf("Person namber %d\n", i);
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
				printf("Person namberр %d\n", i);
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
				printf("Person namber %d\n", i);
				NachDan(man[i]);
				repeats++;
			}
		}
		if (repeats == 0) puts("404err");
		break; }
	case 10: {puts("Good bay:)"); break; }
	default: puts("Yps"); break;
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
			printf("find person with this parametars\n\
			%d person in list\n", i);
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
			printf("Find Person with this parametars %d person \n,", i);
			repeats++;
		}
	}
	if (repeats) puts("404err");

}

void Search1(Person* chelovek, int vsego)
{
	puts("1. On 1 parametarese\n\
2. On FIO\n\
3. All parametarse\n");
	int item;
	scanf("%d", &item);
	while (item < 1 || item>3)
	{
		puts("Err");
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
	PokazhAllFriends(man, vsego);
	int index = 0;
	while (index<1 || index>vsego + 1)
	{
		puts("Choose person to destroy\n");
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
	setlocale(LC_CTYPE, "rus");
	int all;
	Person* people;
	int index = 0;
	puts("How many peopplw ypu vould like to add? (no more then 10)");
	rewind(stdin);
	scanf("%d", &all);
	while (all < 1 || all>10)
	{
		puts("Yps!\nHow many peopplw ypu vould like to add?");
		rewind(stdin);
		scanf("%d", &all);
	}
	people = (Person*)malloc(sizeof(Person) * all);
	int che = 0;
	while (che < 1 || che>2) {
		puts("You wonte create yuer solf ore auto?\n\
1. make your self\n\
2. auto\n");
		scanf("%d", &che);
	}
	if (che == 1)
	{
		for (int i = 0; i < all; i++)
		{
			people[i] = AddPerson();
		}
	}
	else people = MoiLudi(all);


	while (true)
	{
		switch (menu())
		{
		case 1:
			ShowAllPeople(all, people); break;
		case 2:
			all++;
			AddNewPerson(people, all); break;
		case 3:
			addFrends(people, all); break;
		case 4:
			ShowFriends(people, all); break;
		case 5:
			while (index<1 || index>all)
			{
				puts("Choose person");
				PokazhAllFriends(people, all);
				scanf("%d", &index);
			}
			index--;
			people[index] = ChangeInfo(people[index]); break;
		case 6:
			Search(people, all); break;
		case 7:
			DeletePerson(people, all);
			all--; break;
		case 8:
			DeleteFriends(people, all); break;
			/*case 9:
				ReadIsFaila(people, vsego); break;
			case 10:
				WriteToFile(people, vsego); break;*/
		case 9:
			if (che == 1)
			{
				VsehDoloy(people, all);
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
