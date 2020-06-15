#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <xutility>
//6.2 (14).Областная больница.Больница состоит из нескольких отделений.
//В каждом отделении находится определенное количество палат.
//Программа формирует список отделений(название,
//	месторасположение), список врачей(ФИО, должность,
//		специальность), списки пациентов(ФИО, адрес, год рождения,
//			диагноз, дата поступления, дата выписки номер палаты).Для
//	каждого пациента назначается свой курс лечения, он вводится
//	пользователем программы.Подготовка к печати истории болезни.
//	Расчет нагрузка на врача и отделение.Если отделение переполнено
//	– вывод возможной даты принятия нового больного.

struct Doctors
{
	char* name;
	char* surname;
	char* position;
	char* specialty;
};
struct Date
{
	int day;
	int month;
	int year;
};
struct CourseOfTreatment
{
	struct Node
	{
		Node* next;
		Node* prev;
		char* data;
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	int Size = 0;

	void Add(char* course)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data = _strdup(course);
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
		}
		else
		{
			Node* current = this->head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = (Node*)malloc(sizeof(Node));
			current->next->data = _strdup(course);
			current->next->next = nullptr;
			current->next->prev = tail;
			tail = current->next;
		}
		Size++;
	}
	void pop_back(char* surname)
	{
		Node* previous = this->tail;

		if (previous != nullptr)
		{
			if (previous->prev == nullptr && previous->next == nullptr)
			{
				free(previous);
				head = nullptr;
				tail = nullptr;
				Size--;
			}
			else
				if (previous->next == nullptr)
				{
					tail = previous->prev;
					tail->next = nullptr;
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
			printf("\nCourse: %s ", temp->data);
			temp = temp->next;
		}
	}
};
struct Patients
{
	char* name;
	char* surname;
	char* address;
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
		Node* next;
		Node* prev;
		Patients data;
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
		char* name, char* surname, char* address, int dateOfBirthday, int dateOfBirthmonth, int dateOfBirthyear, char* diagnosis,
		int  inputDateday, int  inputDatemonth, int  inputDateyear, int outputDateday, int outputDatemonth,
		int outputDateyear, int numberofChamber)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.name = _strdup(name);
			head->data.surname = _strdup(surname);
			head->data.address = _strdup(address);

			head->data.dateOfBirth.day = dateOfBirthday;
			head->data.dateOfBirth.month = dateOfBirthmonth;
			head->data.dateOfBirth.year = dateOfBirthyear;

			head->data.diagnosis = _strdup(diagnosis);

			head->data.inputDate.day = inputDateday;
			head->data.inputDate.month = inputDatemonth;
			head->data.inputDate.year = inputDateyear;
			head->data.outputDate.day = outputDateday;
			head->data.outputDate.month = outputDatemonth;
			head->data.outputDate.year = outputDateyear;

			head->data.numberofChamber = numberofChamber;
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
			head->data.course.head = nullptr;
			head->data.course.tail = nullptr;
			head->data.course.Size = 0;

		}
		else
		{
			Node* current = this->head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = (Node*)malloc(sizeof(Node));
			current->next->data.name = _strdup(name);
			current->next->data.surname = _strdup(surname);
			current->next->data.address = _strdup(address);

			current->next->data.dateOfBirth.day = dateOfBirthday;
			current->next->data.dateOfBirth.month = dateOfBirthmonth;
			current->next->data.dateOfBirth.year = dateOfBirthyear;

			current->next->data.diagnosis = _strdup(diagnosis);

			current->next->data.inputDate.day = inputDateday;
			current->next->data.inputDate.month = inputDatemonth;
			current->next->data.inputDate.year = inputDateyear;
			current->next->data.outputDate.day = outputDateday;
			current->next->data.outputDate.month = outputDatemonth;
			current->next->data.outputDate.year = outputDateyear;

			current->next->data.numberofChamber = numberofChamber;
			current->next->next = nullptr;
			current->next->prev = tail;
			tail = current->next;
			current->next->data.course.head = nullptr;
			current->next->data.course.tail = nullptr;
			current->next->data.course.Size = 0;
		}
		Size++;
	}
	void RemoveAt(char* surname, char* name)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.surname, surname) == 0) && (strcmp(previous->data.name, name) == 0))
				break;
			previous = previous->next;
		}

		if (previous != nullptr)
		{
			if (previous->prev == nullptr && previous->next != nullptr)
			{
				head = previous->next;
				head->prev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->prev == nullptr && previous->next == nullptr)
				{
					head = nullptr;
					tail = nullptr;
					free(previous);
					Size--;
				}
				else
					if (previous->next == nullptr)
					{
						tail = previous->prev;
						tail->next = nullptr;
						free(previous);
						Size--;
					}
					else
					{
						previous->next->prev = previous->prev;
						previous->prev->next = previous->next;
						free(previous);
						Size--;
					}
		}
		else
		{
			printf("Wrong data");
		}
	}
	Node* Search(char* surname, char* name)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.surname, surname) == 0) && (strcmp(previous->data.name, name) == 0))
				break;
			previous = previous->next;
		}
		return previous;
	}
	void AddCoursepatient(char* surname, char* name, char* course)
	{
		Node* patient = Search(surname, name);
		if (patient != nullptr)
			patient->data.course.Add(course);
	}
	void MinDateSerach()
	{
		Node* temp = this->head;
		int day = temp->data.outputDate.day, month = temp->data.outputDate.month, year = temp->data.outputDate.year;
		while (temp != nullptr)
		{
			if (temp->data.outputDate.day < day && temp->data.outputDate.month <= month && temp->data.outputDate.year <= year)
			{
				day = temp->data.outputDate.day;
				month = temp->data.outputDate.month;
				year = temp->data.outputDate.year;
			}
			temp = temp->next;
		}
		printf("Day:%d Month:%d Year:%d", day, month, year);
	}
	void Print()
	{
		Node* temp = this->head;
		while (temp != nullptr)
		{
			printf("\nPatient : \n");
			printf("Name: %s\n", temp->data.name);
			printf("Surname %s\n", temp->data.surname);
			printf("Data of Birth: %d.%d.%d\n", temp->data.dateOfBirth.day, temp->data.dateOfBirth.month, temp->data.dateOfBirth.year);
			printf("Address: %s\n", temp->data.address);
			printf("Diagnosis: %s\n", temp->data.diagnosis);
			printf("Number of Chamber: %d\n", temp->data.numberofChamber);
			printf("Input data: %d.%d.%d\n", temp->data.inputDate.day, temp->data.inputDate.month, temp->data.inputDate.year);
			printf("Output data: %d.%d.%d\n", temp->data.outputDate.day, temp->data.outputDate.month, temp->data.outputDate.year);
			printf("course of treatment:\n");
			temp->data.course.Print();
			temp = temp->next;
		}
	}
};
struct ListDoctors
{
	struct Node
	{
		Node* next;
		Node* prev;
		Doctors data;
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
	void Add(char* name, char* surname, char* position, char* specialty)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.name = _strdup(name);
			head->data.surname = _strdup(surname);
			head->data.position = _strdup(position);
			head->data.specialty = _strdup(specialty);
			head->next = nullptr;
			head->prev = nullptr;
			tail = head;
		}
		else
		{
			Node* current = this->head;
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = (Node*)malloc(sizeof(Node));
			current->next->data.name = _strdup(name);
			current->next->data.surname = _strdup(surname);
			current->next->data.position = _strdup(position);
			current->next->data.specialty = _strdup(specialty);
			current->next->next = nullptr;
			current->next->prev = tail;
			tail = current->next;
		}
		Size++;
	}
	void RemoveAt(char* surname, char* name)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if ((strcmp(previous->data.surname, surname) == 0) && (strcmp(previous->data.name, name) == 0))
				break;
			previous = previous->next;
		}

		if (previous != nullptr)
		{
			if (previous->prev == nullptr && previous->next != nullptr)
			{
				head = previous->next;
				head->prev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->prev == nullptr && previous->next == nullptr)
				{
					head = nullptr;
					tail = nullptr;
					free(previous);
					Size--;
				}
				else
					if (previous->next == nullptr)
					{
						tail = previous->prev;
						tail->next = nullptr;
						free(previous);
						Size--;
					}
					else
					{
						previous->next->prev = previous->prev;
						previous->prev->next = previous->next;
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
			printf("Name: %s\n", temp->data.name);
			printf("Surname %s\n", temp->data.surname);
			printf("Position: %s\n", temp->data.position);
			printf("Speciality: %s\n", temp->data.specialty);
			temp = temp->next;
		}
	}
};

struct Branch
{
	char* name;
	char* address;
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
		Node* next;
		Node* prev;
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
	void Add(char* name, char* address, int data)
	{
		if (head == nullptr)
		{
			head = (Node*)malloc(sizeof(Node));
			head->data.name = _strdup(name);
			head->data.address = _strdup(address);
			head->data.numberOfChambers = data;
			head->next = nullptr;
			head->prev = nullptr;
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
			while (current->next != nullptr)
			{
				current = current->next;
			}
			current->next = (Node*)malloc(sizeof(Node));
			current->next->data.address = _strdup(address);
			current->next->data.name = _strdup(name);
			current->next->data.numberOfChambers = data;
			current->next->next = nullptr;
			current->next->prev = tail;
			tail = current->next;

			current->next->data.doctrors.head = nullptr;
			current->next->data.doctrors.tail = nullptr;
			current->next->data.doctrors.Size = 0;
			current->next->data.patients.head = nullptr;
			current->next->data.patients.tail = nullptr;
			current->next->data.patients.Size = 0;
			current->next->data.Filled = (bool*)calloc(data, sizeof(bool));
			for (int i = 0; i < data; i++)
				current->next->data.Filled[i] = false;
		}
		Size++;
	}
	void RemoveAt(char* name)
	{
		Node* previous = this->head;
		for (int i = 0; i < Size; i++)
		{
			if (strcmp(previous->data.name, name) == 0)
				break;
			previous = previous->next;
		}

		if (previous != nullptr)
		{
			if (previous->prev == nullptr)
			{
				head = previous->next;
				head->prev = nullptr;
				free(previous);
				Size--;
			}
			else
				if (previous->next == nullptr)
				{
					tail = previous->prev;
					tail->next = nullptr;
					free(previous);
					Size--;
				}
				else
				{
					previous->next->prev = previous->prev;
					previous->prev->next = previous->next;
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
			temp = temp->next;
		}
		return temp;
	}
	void AddDoctors(Node* temp, char* name, char* surname, char* position, char* specialty)
	{
		if (temp != nullptr)
			temp->data.doctrors.Add(name, surname, position, specialty);
	}
	void DeleteDoctor(Node* temp, char* surname, char* name)
	{
		if (temp != nullptr)
			temp->data.doctrors.RemoveAt(surname, name);
	}
	void DeletePatient(Node* temp, char* surname, char* name)
	{
		if (temp != nullptr)
			temp->data.patients.RemoveAt(surname, name);
	}
	void AddCourse(Node* temp, char* course, char* surname, char* name)
	{
		temp->data.patients.AddCoursepatient(surname, name, course);
	}
	double DoctorLoad(char* branch)
	{
		float sizePatients = 0;
		float sizeDoctors = 0;
		Node* temp = this->head;
		while (temp != nullptr)
		{
			if (strcmp(temp->data.name, branch) == 0)
				break;
			temp = temp->next;
		}

		while (temp != nullptr)
		{
			sizePatients += temp->data.patients.GetSize();
			sizeDoctors += temp->data.doctrors.GetSize();
			temp = temp->next;
		}

		if (sizeDoctors > 0)
			return sizePatients / sizeDoctors;
		else return 0;
	}
	double BranchLoad(char* branch)
	{
		float sizePatients = 0;
		Node* temp = this->head;
		while (temp != nullptr)
		{
			if (strcmp(temp->data.name, branch) == 0)
				break;
			temp = temp->next;
		}

		while (temp != nullptr)
		{
			sizePatients += temp->data.patients.GetSize();
			temp = temp->next;
		}
		int sizeBranch = GetSize();
		return sizePatients / sizeBranch;
	}
	void AddPatients(Node* temp, char* name, char* surname, char* address,
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
					temp->data.patients.Add(name, surname, address,
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
			printf("Address: %s\n", temp->data.address);
			printf("Number of chamber: %d\n", temp->data.numberOfChambers);
			temp->data.patients.Print();
			temp->data.doctrors.Print();
			temp = temp->next;
		}
	}
};

int main()
{
	ListBranch temp;
	char branchName[30], branchAddress[30];
	char doctorName[30], doctorSurname[30], doctorPosition[30], doctorSpeciality[30], nameBrunch[30];
	char patientName[30], patientSurname[30], patientAddress[30], patientDiagnosis[30], course[100];
	int dayBirth, monthBirth, ageBirth, inputDay, inputMonth, inputAge, outputDay, outputMonth, outputAge, chamber;
	int  chambers, i = 0;
	double load;


	while (true)
	{
		system("cls");
		rewind(stdin);
		printf("1: Add branch\n");
		printf("2: Add doctor\n");
		printf("3: Add patient\n");
		printf("4: Delete doctor\n");
		printf("5: Delete patient\n");
		printf("6: Add the course of treatment:\n");
		printf("7: Load on the brunch and the doctor\n");
		printf("8: Show all info\n");
		printf("0: exit\n");
		switch ((int)getchar() - 48)
		{
		case 1:
			system("cls");
			printf("Enter branch name: \n");

			rewind(stdin);
			scanf("%s", branchName);

			printf("Enter address: \n");
			rewind(stdin);
			scanf("%s", branchAddress);

			printf("Enter the number of chambers: \n");
			rewind(stdin);
			if (scanf_s("%d", &chambers))
			{
				temp.Add(branchName, branchAddress, chambers);
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
				printf("Enter branch name: ");
				rewind(stdin);
				scanf("%s", nameBrunch);
				printf("Enter doctor name: ");
				rewind(stdin);
				scanf("%s", doctorName);
				printf("Enter doctor surname: ");
				rewind(stdin);
				scanf("%s", doctorSurname);
				printf("Enter doctor position: ");
				rewind(stdin);
				scanf("%s", doctorPosition);
				printf("Enter doctor specialty: ");
				rewind(stdin);
				scanf("%s", doctorSpeciality);
				if (temp.Search(nameBrunch) != nullptr)
					temp.AddDoctors(temp.Search(branchName), doctorName, doctorSurname, doctorPosition, doctorSpeciality);
			}
			break;
		case 3:
			if (temp.head != nullptr)
			{
				system("cls");
				printf("Enter branch name: ");
				rewind(stdin);
				scanf("%s", nameBrunch);
				printf("Enter patient name: ");
				rewind(stdin);
				scanf("%s", patientName);
				printf("Enter patient surname ");
				rewind(stdin);
				scanf("%s", patientSurname);
				printf("Enter patient address: ");
				rewind(stdin);
				scanf("%s", patientAddress);
				printf("Enter patient's date of birth: \n");
				printf("Day: ");
				rewind(stdin);
				scanf_s("%d", &dayBirth);
				printf("Month: ");
				rewind(stdin);
				scanf_s("%d", &monthBirth);
				printf("Year :");
				rewind(stdin);
				scanf_s("%d", &ageBirth);
				printf("Enter input date: \n");
				printf("Day: ");
				rewind(stdin);
				scanf_s("%d", &inputDay);
				printf("Month: ");
				rewind(stdin);
				scanf_s("%d", &inputMonth);
				printf("Year: ");
				rewind(stdin);
				scanf_s("%d", &inputAge);
				printf("Enter output date: \n");
				printf("Day:");
				rewind(stdin);
				scanf_s("%d", &outputDay);
				printf("Month: ");
				rewind(stdin);
				scanf_s("%d", &outputMonth);
				printf("Year: ");
				rewind(stdin);
				scanf_s("%d", &outputAge);
				printf("Enter chamber: ");
				rewind(stdin);
				scanf_s("%d", &chamber);
				printf("Enter diagnosis: ");
				rewind(stdin);
				scanf("%s", patientDiagnosis);
				if (temp.Search(nameBrunch) != nullptr)
				{
					if (((inputDay < outputDay && inputMonth <= outputMonth && inputAge <= outputAge) ||
						(inputDay >= outputDay && inputMonth < outputMonth && inputAge <= outputAge)) &&
						inputDay > 0 && inputDay < 32 && inputMonth>0 && inputMonth < 13 && outputDay>0 &&
						outputDay < 32 && outputMonth>0 && outputMonth < 13)
					{
						temp.AddPatients(temp.Search(branchName), patientName, patientSurname, patientAddress, dayBirth,
							monthBirth, ageBirth, patientDiagnosis, inputDay, inputMonth,
							inputAge, outputDay, outputMonth, outputAge, chamber);
					}
				}
			}
			break;
		case 4:
			if (temp.head != nullptr)
			{
				system("cls");
				printf("Enter branch name: ");
				rewind(stdin);
				scanf("%s", nameBrunch);
				printf("Enter doctor name: ");
				rewind(stdin);
				scanf("%s", doctorName);
				printf("Enter doctor surname: ");
				rewind(stdin);
				scanf("%s", doctorSurname);
				if (temp.Search(nameBrunch) != nullptr)
					temp.DeleteDoctor(temp.Search(branchName), doctorSurname, doctorName);
			}
			break;
		case 5:
			if (temp.head != nullptr)
			{
				system("cls");
				rewind(stdin);
				printf("Enter branch name: ");
				scanf("%s", nameBrunch);
				rewind(stdin);
				printf("Enter patient name: ");
				scanf("%s", patientName);
				rewind(stdin);
				printf("Enter patient surname: ");
				rewind(stdin);
				scanf("%s", patientSurname);
				if (temp.Search(nameBrunch) != nullptr)
					temp.DeletePatient(temp.Search(branchName), patientSurname, patientName);
			}
			break;
		case 6:
			if (temp.head != nullptr)
			{
				system("cls");
				rewind(stdin);
				printf("Enter branch name ");
				scanf("%s", nameBrunch);
				printf("Enter patient name: ");
				scanf("%s", patientName);
				printf("Enter patient surname: ");
				scanf("%s", patientSurname);
				printf("Enter the course of treatment: ");
				rewind(stdin);
				scanf("%[^\n]s", course);
				if (temp.Search(nameBrunch) != nullptr)
					temp.AddCourse(temp.Search(branchName), course, patientSurname, patientName);
			}
			break;
		case 7:
			if (temp.head != nullptr)
			{
				rewind(stdin);
				printf("Enter branch name: ");
				scanf("%s", nameBrunch);
				load = temp.BranchLoad(nameBrunch);
				printf("Branch load: %lf\n", load);
				load = temp.DoctorLoad(nameBrunch);
				printf("Doctor load: %lf\n", load);
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