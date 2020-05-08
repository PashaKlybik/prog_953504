#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include < stdlib.h >
#include <xutility>
//N6.2 variant 14
struct DoctorsData
{
	char* firstName;
	char* lastName;
	char* position;
	char* specialty;
};
struct Date
{
	int day;
	int moth;
	int year;
};
struct CourseOfTreatment
{
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		char* data;
	};
	Node* head;
	Node* tail;
	int Size;

	CourseOfTreatment()
	{
		Size = 0;
		head = nullptr;
		tail = nullptr;
	}

	void Add(char* course)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data = _strdup(course);
			head->pNext = nullptr;
			head->pPrev = nullptr;
			tail = head;
		}
		else
		{
			Node* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = (Node*)malloc(sizeof(Node));
			current->pNext->data = _strdup(course);
			current->pNext->pNext = nullptr;
			current->pNext->pPrev = tail;
			tail = current->pNext;
		}
		Size++;
	}
	void pop_back(char* lastname)
	{
		Node* previous = this->tail;

		if (previous != nullptr)
		{
			if (previous->pPrev == nullptr && previous->pNext == nullptr)
			{
				free(previous);
				head = nullptr;
				tail = nullptr;
				Size--;
			}
			else
				if (previous->pNext == nullptr)
				{
					tail = previous->pPrev;
					tail->pNext = nullptr;
					free(previous);
					Size--;
				}
		}
	}
	void Print()
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			printf(" %s ", temp->data);
			temp = temp->pNext;
		}
	}
};
struct PatientData
{
	char* firstName;
	char* lastName;
	char* adress;
	Date dateOfBirth;
	char* diagnosis;
	Date inputDate;
	Date outputDate;
	CourseOfTreatment course;
	int numberofChamber;
};
struct ListPatients
{
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		PatientData data;
	};
	Node* head;
	Node* tail;
	int Size;

	ListPatients()
	{
		Size = 0;
		head = nullptr;
		tail = nullptr;
	}
	int GetSize()
	{
		return Size;
	}
	void Add(
		char* firstname, char* lastname, char* adress,
		int dateOfBirthday, int dateOfBirthmonth, int dateOfBirthyear, char* diagnosis,
		int  inputDateday, int  inputDatemonth, int  inputDateyear,
		int outputDateday, int outputDatemonth, int outputDateyear,
		int numberofChamber)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.firstName = _strdup(firstname);
			head->data.lastName = _strdup(lastname);
			head->data.adress = _strdup(adress);

			head->data.dateOfBirth.day = dateOfBirthday;
			head->data.dateOfBirth.moth = dateOfBirthmonth;
			head->data.dateOfBirth.year = dateOfBirthyear;

			head->data.diagnosis = _strdup(diagnosis);

			head->data.inputDate.day = inputDateday;
			head->data.inputDate.moth = inputDatemonth;
			head->data.inputDate.year = inputDateyear;
			head->data.outputDate.day = outputDateday;
			head->data.outputDate.moth = outputDatemonth;
			head->data.outputDate.year = outputDateyear;

			head->data.numberofChamber = numberofChamber;
			head->pNext = nullptr;
			head->pPrev = nullptr;
			tail = head;
			head->data.course.head = nullptr;
			head->data.course.tail = nullptr;
			head->data.course.Size = 0;

		}
		else
		{
			Node* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = (Node*)malloc(sizeof(Node));
			current->pNext->data.firstName = _strdup(firstname);
			current->pNext->data.lastName = _strdup(lastname);
			current->pNext->data.adress = _strdup(adress);

			current->pNext->data.dateOfBirth.day = dateOfBirthday;
			current->pNext->data.dateOfBirth.moth = dateOfBirthmonth;
			current->pNext->data.dateOfBirth.year = dateOfBirthyear;

			current->pNext->data.diagnosis = _strdup(diagnosis);

			current->pNext->data.inputDate.day = inputDateday;
			current->pNext->data.inputDate.moth = inputDatemonth;
			current->pNext->data.inputDate.year = inputDateyear;
			current->pNext->data.outputDate.day = outputDateday;
			current->pNext->data.outputDate.moth = outputDatemonth;
			current->pNext->data.outputDate.year = outputDateyear;

			current->pNext->data.numberofChamber = numberofChamber;
			current->pNext->pNext = nullptr;
			current->pNext->pPrev = tail;
			tail = current->pNext;
			current->pNext->data.course.head = nullptr;
			current->pNext->data.course.tail = nullptr;
			current->pNext->data.course.Size = 0;
		}
		Size++;
	}
	void removeAt(char* lastname, char* firstname)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.lastName, lastname) == 0) && (strcmp(previous->data.firstName, firstname) == 0))
				break;
			previous = previous->pNext;
		}

		if (previous != nullptr)
		{
			if (previous->pPrev == nullptr && previous->pNext != nullptr)
			{
				head = previous->pNext;
				head->pPrev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->pPrev == nullptr && previous->pNext == nullptr)
				{
					head = nullptr;
					tail = nullptr;
					free(previous);
					Size--;
				}
				else
					if (previous->pNext == nullptr)
					{
						tail = previous->pPrev;
						tail->pNext = nullptr;
						free(previous);
						Size--;
					}
					else
					{
						previous->pNext->pPrev = previous->pPrev;
						previous->pPrev->pNext = previous->pNext;
						free(previous);
						Size--;
					}
		}
		else
		{
			printf("Wrong data");
		}
	}
	Node* Search(char* lastname, char* firstname)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.lastName, lastname) == 0) && (strcmp(previous->data.firstName, firstname) == 0))
				break;
			previous = previous->pNext;
		}
		return previous;
	}
	void AddCoursepatient(char* lastname, char* firstname, char* course)
	{
		Node* patient = Search(lastname, firstname);
		if (patient != nullptr)
			patient->data.course.Add(course);
	}
	void MinDateSerach()
	{
		Node* temp = this->head;
		int day = temp->data.outputDate.day, month = temp->data.outputDate.moth, year = temp->data.outputDate.year;
		while (temp != nullptr)
		{
			if (temp->data.outputDate.day < day && temp->data.outputDate.moth <= month && temp->data.outputDate.year <= year)
			{
				day = temp->data.outputDate.day;
				month = temp->data.outputDate.moth;
				year = temp->data.outputDate.year;
			}
			temp = temp->pNext;
		}
		printf("Day:%d Month:%d Year:%d", day, month, year);
	}
	void Print()
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			printf("\nPatient : \n");
			printf("%s\n", temp->data.firstName);
			printf("%s\n", temp->data.lastName);
			printf("%d.%d.%d\n", temp->data.dateOfBirth.day, temp->data.dateOfBirth.moth, temp->data.dateOfBirth.year);
			printf("%s\n", temp->data.adress);
			printf("%s\n", temp->data.diagnosis);
			printf("%d\n", temp->data.numberofChamber);
			printf("%d.%d.%d\n", temp->data.inputDate.day, temp->data.inputDate.moth, temp->data.inputDate.year);
			printf("%d.%d.%d\n", temp->data.outputDate.day, temp->data.outputDate.moth, temp->data.outputDate.year);
			printf("course of treatment:\n");
			temp->data.course.Print();
			temp = temp->pNext;
		}
	}
};
struct ListDoctors
{
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		DoctorsData data;
	};
	Node* head;
	Node* tail;
	int Size;

	void listDoctors()
	{
		Size = 0;
		head = nullptr;
		tail = nullptr;
	}
	int GetSize()
	{
		return Size;
	}
	void Add(char* firstname, char* lastname, char* position, char* specialty)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.firstName = _strdup(firstname);
			head->data.lastName = _strdup(lastname);
			head->data.position = _strdup(position);
			head->data.specialty = _strdup(specialty);
			head->pNext = nullptr;
			head->pPrev = nullptr;
			tail = head;
		}
		else
		{
			Node* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = (Node*)malloc(sizeof(Node));
			current->pNext->data.firstName = _strdup(firstname);
			current->pNext->data.lastName = _strdup(lastname);
			current->pNext->data.position = _strdup(position);
			current->pNext->data.specialty = _strdup(specialty);
			current->pNext->pNext = nullptr;
			current->pNext->pPrev = tail;
			tail = current->pNext;
		}
		Size++;
	}
	void removeAt(char* lastname, char* firstname)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.lastName, lastname) == 0) && (strcmp(previous->data.firstName, firstname) == 0))
				break;
			previous = previous->pNext;
		}

		if (previous != nullptr)
		{
			if (previous->pPrev == nullptr && previous->pNext != nullptr)
			{
				head = previous->pNext;
				head->pPrev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->pPrev == nullptr && previous->pNext == nullptr)
				{
					head = nullptr;
					tail = nullptr;
					free(previous);
					Size--;
				}
				else
					if (previous->pNext == nullptr)
					{
						tail = previous->pPrev;
						tail->pNext = nullptr;
						free(previous);
						Size--;
					}
					else
					{
						previous->pNext->pPrev = previous->pPrev;
						previous->pPrev->pNext = previous->pNext;
						free(previous);
						Size--;
					}
		}
		else
		{
			printf("Wrong data");
		}
	}
	void Print()
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			printf("\nDoctor : \n");
			printf("%s\n", temp->data.firstName);
			printf("%s\n", temp->data.lastName);
			printf("%s\n", temp->data.position);
			printf("%s\n", temp->data.specialty);
			temp = temp->pNext;
		}
	}
};
struct Branch
{
	char* name;
	char* adress;
	int numberOfChambers;
	bool* Filled;
	int checkFill;
	ListDoctors doctrors;
	ListPatients patients;
};
struct ListBranch
{
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		Branch data;
	};
	Node* head;
	Node* tail;
	int Size;

	ListBranch()
	{
		Size = 0;
		head = nullptr;
		tail = nullptr;
	}
	int GetSize()
	{
		return Size;
	}
	void Add(char* name, char* adress, int data)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.name = _strdup(name);
			head->data.adress = _strdup(adress);
			head->data.numberOfChambers = data;
			head->pNext = nullptr;
			head->pPrev = nullptr;
			tail = head;

			head->data.doctrors.head = nullptr;
			head->data.doctrors.tail = nullptr;
			head->data.doctrors.Size = 0;
			head->data.patients.head = nullptr;
			head->data.patients.tail = nullptr;
			head->data.patients.Size = 0;
			head->data.Filled = (bool*)calloc(data, sizeof(bool));
			for (int i = 0; i < data; i++)
				head->data.Filled[i] = false;
			head->data.checkFill = 0;
		}
		else
		{
			Node* current = this->head;
			while (current->pNext != nullptr)
			{
				current = current->pNext;
			}
			current->pNext = (Node*)malloc(sizeof(Node));
			current->pNext->data.adress = _strdup(adress);
			current->pNext->data.name = _strdup(name);
			current->pNext->data.numberOfChambers = data;
			current->pNext->pNext = nullptr;
			current->pNext->pPrev = tail;
			tail = current->pNext;

			current->pNext->data.doctrors.head = nullptr;
			current->pNext->data.doctrors.tail = nullptr;
			current->pNext->data.doctrors.Size = 0;
			current->pNext->data.patients.head = nullptr;
			current->pNext->data.patients.tail = nullptr;
			current->pNext->data.patients.Size = 0;
			current->pNext->data.Filled = (bool*)calloc(data, sizeof(bool));
			for (int i = 0; i < data; i++)
				current->pNext->data.Filled[i] = false;
		}
		Size++;
	}
	void removeAt(char* name)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if (strcmp(previous->data.name, name) == 0)
				break;
			previous = previous->pNext;
		}

		if (previous != nullptr)
		{
			if (previous->pPrev == nullptr)
			{
				head = previous->pNext;
				head->pPrev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->pNext == nullptr)
				{
					tail = previous->pPrev;
					tail->pNext = nullptr;
					free(previous);
					Size--;
				}
				else
				{
					previous->pNext->pPrev = previous->pPrev;
					previous->pPrev->pNext = previous->pNext;
					free(previous);
					Size--;
				}
		}
		else
		{
			printf("Wrong data");
		}
	}
	Node* Search(char* name)
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			if (strcmp(temp->data.name, name) == 0)
				break;
			temp = temp->pNext;
		}
		return temp;
	}
	void AddDoctors(Node* temp, char* firstname, char* lastname, char* position, char* specialty)
	{
		if (temp != nullptr)
			temp->data.doctrors.Add(firstname, lastname, position, specialty);
	}
	void DeleteDoctor(Node* temp, char* lastname, char* firstname)
	{
		if (temp != nullptr)
			temp->data.doctrors.removeAt(lastname, firstname);
	}
	void Deletepatient(Node* temp, char* lastname, char* firstname)
	{
		if (temp != nullptr)
			temp->data.patients.removeAt(lastname, firstname);
	}
	void AddCourse(Node* temp, char* course, char* lastname, char* firstname)
	{
		temp->data.patients.AddCoursepatient(lastname, firstname, course);
	}
	double NagrDoctor(char* branch)
	{
		float sizePatients = 0;
		float sizeDoctors = 0;
		Node* temp = this->head;
		while (temp != nullptr)
		{
			if (strcmp(temp->data.name, branch) == 0)
				break;
			temp = temp->pNext;
		}

		while (temp != nullptr)
		{
			sizePatients += temp->data.patients.GetSize();
			sizeDoctors += temp->data.doctrors.GetSize();
			temp = temp->pNext;
		}

		if (sizeDoctors > 0)
			return sizePatients / sizeDoctors;
		else return 0;
	}
	double nagrBranch(char* branch)
	{
		float sizePatients = 0;
		Node* temp = this->head;
		while (temp != nullptr)
		{
			if (strcmp(temp->data.name, branch) == 0)
				break;
			temp = temp->pNext;
		}

		while (temp != nullptr)
		{
			sizePatients += temp->data.patients.GetSize();
			temp = temp->pNext;
		}
		int sizeBranch = GetSize();
		return sizePatients / sizeBranch;
	}
	void AddPatients(Node* temp, char* firstname, char* lastname, char* adress,
		int dateOfBirthday, int dateOfBirthmonth, int dateOfBirthyear, char* diagnosis,
		int  inputDateday, int  inputDatemonth, int  inputDateyear,
		int outputDateday, int outputDatemonth, int outputDateyear,
		int numberofChamber)
	{
		if (temp != nullptr)

			if (temp->data.checkFill == temp->data.numberOfChambers)
			{
				temp->data.patients.MinDateSerach();
			}
			else
			{
				if (temp->data.Filled[numberofChamber] != true && numberofChamber > 0 && numberofChamber <= temp->data.numberOfChambers)
				{
					temp->data.patients.Add(firstname, lastname, adress,
						dateOfBirthday, dateOfBirthmonth, dateOfBirthyear, diagnosis,
						inputDateday, inputDatemonth, inputDateyear,
						outputDateday, outputDatemonth, outputDateyear,
						numberofChamber);
					temp->data.Filled[numberofChamber] = true;
					temp->data.checkFill++;
				}
			}
	}
	void Print()
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			printf("Branch: %s\n", temp->data.name);
			printf("%s\n", temp->data.adress);
			printf("%d\n", temp->data.numberOfChambers);
			temp->data.patients.Print();
			temp->data.doctrors.Print();
			temp = temp->pNext;
		}
	}
};


int main()
{
	ListBranch temp;
	char nameb[30], adressb[40];
	char namedo[30], lastdo[30], posdo[30], specdo[30], namebranch[30];
	char namepa[30], lastpa[30], adresspa[30], diagnospa[30], course[100];
	int dayb, monthb, yearb, dayin, monthin, yearin, dayout, monthout, yearout, chamber;
	int  chambers, i = 0;
	double nagr;


	while (true)
	{
		system("cls");
		rewind(stdin);
		printf("1-Add branch\n");
		printf("2-Add doctor\n");
		printf("3-Add patient\n");
		printf("4-Delete doctor data\n");
		printf("5-Delete patient data\n");
		printf("6-Add course of treatment:\n");
		printf("7-Load\n");
		printf("8-Show all info\n");
		printf("0-exit\n");
		switch ((int)getchar() - 48)
		{
		case 1:
			system("cls");
			printf("Enter Name of branch:\n");

			rewind(stdin);
			scanf("%s", nameb);

			printf("Enter adress:\n");
			rewind(stdin);
			scanf("%s", adressb);

			printf("Enter number of chambers:\n");
			rewind(stdin);
			if (scanf_s("%d", &chambers))
			{
				temp.Add(nameb, adressb, chambers);
			}
			else
			{
				printf("Wrong data!\n");
				break;
			}
			break;
		case 2:
			if (temp.head != nullptr)
			{
				system("cls");
				printf("Enter name branch:");
				rewind(stdin);
				scanf("%s", namebranch);
				printf("Enter Firstname doctor:");
				rewind(stdin);
				scanf("%s", namedo);
				printf("Enter Lastname doctor:");
				rewind(stdin);
				scanf("%s", lastdo);
				printf("Enter position doctor:");
				rewind(stdin);
				scanf("%s", posdo);
				printf("Enter Specialty doctor:");
				rewind(stdin);
				scanf("%s", specdo);
				if (temp.Search(namebranch) != nullptr)
					temp.AddDoctors(temp.Search(namebranch), namedo, lastdo, posdo, specdo);
			}
			break;
		case 3:
			if (temp.head != nullptr)
			{
				system("cls");
				printf("Enter name branch:");
				rewind(stdin);
				scanf("%s", namebranch);
				printf("Enter name patient:");
				rewind(stdin);
				scanf("%s", namepa);
				printf("Enter Lastname patirnt:");
				rewind(stdin);
				scanf("%s", lastpa);
				printf("Enter adress patient:");
				rewind(stdin);
				scanf("%s", adresspa);
				printf("Enter birthday:\n");
				printf("Day:");
				rewind(stdin);
				scanf_s("%d", &dayb);
				printf("Month:");
				rewind(stdin);
				scanf_s("%d", &monthb);
				printf("Year:");
				rewind(stdin);
				scanf_s("%d", &yearb);
				printf("Enter date:\n");
				printf("Day:");
				rewind(stdin);
				scanf_s("%d", &dayin);
				printf("Month:");
				rewind(stdin);
				scanf_s("%d", &monthin);
				printf("Year:");
				rewind(stdin);
				scanf_s("%d", &yearin);
				printf("Enter outdate:\n");
				printf("Day:");
				rewind(stdin);
				scanf_s("%d", &dayout);
				printf("Month:");
				rewind(stdin);
				scanf_s("%d", &monthout);
				printf("Year:");
				rewind(stdin);
				scanf_s("%d", &yearout);
				printf("Enter chamber:");
				rewind(stdin);
				scanf_s("%d", &chamber);
				printf("Enter diagnosis:");
				rewind(stdin);
				scanf("%s", diagnospa);
				if (temp.Search(namebranch) != nullptr)
				{
					if (((dayin < dayout && monthin <= monthout && yearin <= yearout) ||
						(dayin >= dayout && monthin < monthout && yearin <= yearout)) &&
						dayin > 0 && dayin < 32 && monthin>0 && monthin < 13 && dayout>0 &&
						dayout < 32 && monthout>0 && monthout < 13)
					{
						temp.AddPatients(temp.Search(namebranch), namepa, lastpa, adresspa, dayb,
							monthb, yearb, diagnospa, dayin, monthin,
							yearin, dayout, monthout, yearout, chamber);
					}
				}
			}
			break;
		case 4:
			if (temp.head != nullptr)
			{
				system("cls");
				printf("Enter name branch:");
				rewind(stdin);
				scanf("%s", namebranch);
				printf("Enter Firstname doctor:");
				rewind(stdin);
				scanf("%s", namedo);
				printf("Enter Lastname doctor:");
				rewind(stdin);
				scanf("%s", lastdo);
				if (temp.Search(namebranch) != nullptr)
					temp.DeleteDoctor(temp.Search(namebranch), lastdo, namedo);
			}
			break;
		case 5:
			if (temp.head != nullptr)
			{
				system("cls");
				rewind(stdin);
				printf("Enter name branch:");
				scanf("%s", namebranch);
				rewind(stdin);
				printf("Enter Firstname patient:");
				scanf("%s", namepa);
				rewind(stdin);
				printf("Enter Lastname patient:");
				rewind(stdin);
				scanf("%s", lastpa);
				if (temp.Search(namebranch) != nullptr)
					temp.Deletepatient(temp.Search(namebranch), lastpa, namepa);
			}
			break;
		case 6:
			if (temp.head != nullptr)
			{
				system("cls");
				rewind(stdin);
				printf("Enter name branch:");
				scanf("%s", namebranch);
				printf("Enter Firstname patient:");
				scanf("%s", namepa);
				printf("Enter Lastname patient:");
				scanf("%s", lastpa);
				printf("Enter course of treatment:");
				rewind(stdin);
				scanf("%[^\n]s", course);
				if (temp.Search(namebranch) != nullptr)
					temp.AddCourse(temp.Search(namebranch), course, lastpa, namepa);
			}
			break;
		case 7:
			if (temp.head != nullptr)
			{
				rewind(stdin);
				printf("Enter name branch:");
				scanf("%s", namebranch);
				nagr = temp.nagrBranch(namebranch);
				printf("Branch load:%lf\n", nagr);
				nagr = temp.NagrDoctor(namebranch);
				printf("Doctor load:%lf\n", nagr);
				system("pause");
			}
			break;
		case 8:
			if (temp.head != nullptr)
			{
				system("cls");
				temp.Print();
				system("pause");
			}
			break;
		case 0:
			return 0;
		default:
			break;
		}
	}
}

