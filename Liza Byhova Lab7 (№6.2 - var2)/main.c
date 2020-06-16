#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define space " "

bool show1 = false, show2 = false, show3 = false;
int esc = 0;
typedef struct list_of_student
{
    char name[50];
	char faculty[50];
	int course;
	int group;
	char violation[200];
	int level;
	int room;
    int countViolation;
    int count;
} ListStudent;

typedef struct list_of_employees
{
    char position[20];
    char name[50];
	int room;
	char phone_number[20];
	int count;
} ListEmployees;

typedef struct list
{
    ListStudent student;
    ListEmployees employee;
    struct list *next;
    struct list *prev;
} List;

typedef struct database
{
    size_t size;
    int count_student;
    int count_employee;
    List *head;
    List *tail;
} Database;

Database* CreatList()
{
    Database *item = (Database*)malloc(sizeof(Database));
    item->size = 0;
    item->count_student = 0;
    item->count_employee = 0;
    item->head = item->tail = NULL;

    return item;
}

void FreeMemory(Database *item)
{
    List *temp = item->head, *temp2;

    while(temp)
    {
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
}

int MainMenu(Database *list)
{
	int flag, press;
	printf("\t ~BSUIR hostel database~");
	printf("\n\nMain menu:\n\n");
	printf("1.Read the information in the files.\n");
	if (show1)
    {
        printf("2.Put students in a hostel.\n");
        printf("3.Display the list of employees.\n");
    }
	if (show2)
    {
        printf("4.Display a list of settled students.\n");
        printf("5.Display the list of students who should be evicted.\n");
        printf("6.Search for rooms by sername.\n");
        printf("7.Search for sername by room.\n");
    }
	if (show3)
    {
        printf("8.Output a report.\n");
        printf("9.Write information to a file.\n");
    }
	printf("\nPress <esc> to exit or press <space> to continue.\n");
	press = _getch();
    switch (press)
    {
        case 32: printf("\nEnter the action number -> "); scanf("%d", &flag); system("cls"); return flag; break;
        case 27: system("cls"); FreeMemory(list); exit(0); break;
    }
}

void SubMenu(int numberAction, Database *item, int check)
{
    int subFlag, back = 0;

    while (1)
    {
        switch (numberAction)
        {
            case 1:
                printf("  >Files readed.\n\n"); show1 = true;
                printf("1.Display information about students from a file.\n");
                break;
            case 2:
                printf("  >Students are settled.\n\n"); show2 = true;
                printf("1.Display a list of settled students now.\n");
                break;
            case 5:
                DisplayEvictedStudents(item);
                printf("\n\n1.To evict students.\n");
                break;

        }
        printf("2.Return to main menu.\n");
        if (check == 0)
        {
            scanf("%d", &subFlag);
        }
        else
        {
            subFlag = 1;
        }
        if (subFlag == 1 || subFlag == 2)
        {
            break;
        }
        else
        {
            printf("Invalid input. Try again.\n");
        }
    }
    system("cls");
    if (subFlag == 1)
    {
        switch(numberAction)
        {
            case 1: FromFile(item);  break;
            case 2: DisplaySettledStudents(item); break;
            case 3: DisplayEmployees(item); break;
            case 4: DisplaySettledStudents(item); break;
            case 5: EvictingStudents(item); break;
            case 6: SearchBySername(item); break;
            case 7: SearchByRoom(item); break;
            case 8: Report(item); break;
            case 9: WriteToFile(item); break;
        }
        printf("\n\nEnter any number to return to the main menu.\n");
        scanf("%d", &back);
    }
    system("cls");
}

void AddStudents(Database *item, char N[50], char F[50], int C, int G, char V[200]);
int ReadFromStudensFile(Database *item);
int FreeRooms(int level, Database *item, int check, int j);
void PutStudents(Database *item, int new_student);
void DisplaySettledStudents(Database *item);
void DisplayEvictedStudents(Database *item);
void EvictingStudents(Database *item);

void AddEmployees(Database *item, char P[20], char N[50], int R, char PN[20]);
int ReadFromEmployeesFile(Database *item);
void DisplayEmployees(Database *item);

void FromFile(Database *item);
void SearchBySername(Database *item);
void SearchByRoom(Database *item);
void Report(Database *item);
int WriteToFile(Database *item);
//-----------------------------------------------------------------------------------------
int main()
{
    Database *list = CreatList();
    while(1)
    {
        switch(MainMenu(list))
        {
            case 1: ReadFromStudensFile(list) == 1 && ReadFromEmployeesFile(list) == 1 ? SubMenu(1, list, 0) : 0; break;
            case 2: PutStudents(list, 0); SubMenu(2, list, 0); break;
            case 3: SubMenu(3, list, 1); break;
            case 4: SubMenu(4, list, 1); break;
            case 5: SubMenu(5, list, 0); break;
            case 6: SubMenu(6, list, 1); break;
            case 7: SubMenu(7, list, 1); break;
            case 8: SubMenu(8, list, 1); break;
            case 9: WriteToFile(list) == 1 ? SubMenu(9, list, 0) : 0; break;
            default: system("cls"); printf("Invalid input. Try again.\n");
        }
    }
    return 0;
}
//-----------------------------------------------------------------------------------------
void AddStudents(Database *item, char N[50], char F[50], int C, int G, char V[200])
{
    List *temp = (List*)malloc(sizeof(List));

    temp->next = NULL;
    temp->prev = item->tail;
    for (int i = 0; i < 50; i++)
    {
        temp->student.name[i] = N[i];
    }
    for (int i = 0; i < 50; i++)
    {
        temp->student.faculty[i] = F[i];
    }
    temp->student.course = C;
    temp->student.group = G;
    for (int i = 0; i < 200; i++)
    {
        temp->student.violation[i] = V[i];
    }
    if(!item->head)
    {
        item->head = temp;
    }
    else
    {
        item->tail->next = temp;
    }

    item->tail = temp;
    item->count_student += 1;
}

int ReadFromStudensFile(Database *item)
{
    char name[50], faculty[50], violations[200];
    int course, group;
    int read = 0, time = 0;

    FILE *file;
    file = fopen("List of students.txt", "r");
    if (!file)
    {
        printf("Error! The program didn't find the file.");
        return 0;
    }
    else
    {
        char *file_inf = (char*)malloc(sizeof(char));
        char check_comparison[] = "Student";
        while (fscanf(file, "%s", file_inf) != EOF)
        {
            if (strcmp(file_inf, check_comparison) == 0)
            {
                read = 0;
                time++;
                if (time == 6)
                {
                    AddStudents(item, name, faculty, course, group, violations);
                    strcpy(check_comparison, "Student");
                    time = 0;
                }
            }
            switch(read)
            {
                case 1:
                    strcat(name, file_inf);
                    strcat(name, space);
                    break;
                case 2:
                    strcat(faculty, file_inf);
                    strcat(faculty, space);
                    break;
                case 3:
                    course = atoi(file_inf);
                    break;
                case 4:
                    group = atoi(file_inf);
                    break;
                case 5:
                    strcat(violations, file_inf);
                    strcat(violations, space);
                    break;
                default: read = 0;
            }
            if (strcmp(file_inf, ":") == 0)
            {
                switch(time)
                {
                    case 1: read = time; strcpy(name, space); strcpy(check_comparison, "Faculty"); break;
                    case 2: read = time; strcpy(faculty, space); strcpy(check_comparison, "Course"); break;
                    case 3: read = time; strcpy(check_comparison, "Group"); break;
                    case 4: read = time; strcpy(check_comparison, "Violations"); break;
                    case 5: read = time; strcpy(violations, space); strcpy(check_comparison, "-"); break;
                }
            }
        }
        return 1;
    }
    fclose(file);
}

int FreeRooms(int level, Database *item, int check, int j)
{
    List *temp = item->head;
    int k = 0;
    int freeRooms[] = {202, 215, 216, 219, 225, 231, 245,
                       306, 307, 312, 315, 322, 323, 326, 328, 336,
                       401, 429, 447, 448, 450,
                       510, 515, 524, 529, 532, 536, 547};
    while (k != item->count_student)
    {
        for (int i = 0; i < 26; i++)
        {
            if (freeRooms[i] == temp->student.room)
            {
                freeRooms[i] = 0;
            }
        }
        k++;
        temp = temp->next;
    }
    for(int i = 0; i < 26; i++)
    {
        if (freeRooms[i] != 0 && freeRooms[i] / 100 == level && check == 0)
        {
            return freeRooms[i];
        }
    }
    if (check == 1 && freeRooms[j] != 0)
    {
        return freeRooms[j];
    }
}

void PutStudents(Database *item, int new_student)
{
    List *temp = item->head;
    char V[200];
    int k = 0;
    if (new_student == 1)
    {
        k = item->count_student - 1;
    }
    while(k != item->count_student)
    {
        strcpy(V, temp->student.violation);
        temp->student.countViolation = 0;
        if(strcmp(temp->student.faculty, " The faculty of computer engineering ") == 0)
        {
            temp->student.level = 2;
            temp->student.room = FreeRooms(2, item, 0, 0);
        }
        if (strcmp(temp->student.faculty, " Faculty of radio engineering and electronics ") == 0)
        {
            temp->student.level = 3;
            temp->student.room = FreeRooms(3, item, 0, 0);
        }
        if (strcmp(temp->student.faculty, " Faculty of computer systems and networks ") == 0)
        {
            temp->student.level = 4;
            temp->student.room = FreeRooms(4, item, 0, 0);
        }
        if (strcmp(temp->student.faculty, " Faculty of information technology and management ") == 0)
        {
            temp->student.level = 5;
            temp->student.room = FreeRooms(5, item, 0, 0);
        }
        for (int i = 0; i < strlen(V); i++)
        {
            if (V[i] == ',')
            {
                temp->student.countViolation += 1;
            }
        }
        if (temp->student.countViolation > 0)
        {
            temp->student.countViolation += 1;
        }
        k++;
        temp = temp->next;
    }
}

void DisplaySettledStudents(Database *item)
{
    List *temp = item->head;
    int n = 54, k = 0;
    while(k != item->count_student)
    {
        printf("Student:%s\n", temp->student.name);
        printf("Faculty:%s\n", temp->student.faculty);
        printf("Level: %d\n", temp->student.level);
        printf("Room: %d\n", temp->student.room);
        printf("Course: %d\n", temp->student.course);
        printf("Group: %d\n", temp->student.group);
        if (temp->student.countViolation > 2)
        {
            printf("\nThe student has more than three violations! He must be evicted.\n\n");
        }
        printf("Violations:%s\n", temp->student.violation);
        while(n)
        {
            printf("- ");
            n--;
        }
        printf("\n");
        n = 54;
        k++;
        temp = temp->next;
    }
}

void DisplayEvictedStudents(Database *item)
{
    List *temp = item->head;
    int n = 54, k = 0, check = 0;
    while(k != item->count_student)
    {
        if (temp->student.countViolation > 2)
        {
            check = 1;
            printf("Student:%s\n", temp->student.name);
            printf("Faculty:%s\n", temp->student.faculty);
            printf("Level: %d\n", temp->student.level);
            printf("Room: %d\n", temp->student.room);
            printf("Course: %d\n", temp->student.course);
            printf("Group: %d\n", temp->student.group);
            printf("Violations:%s\n", temp->student.violation);
            while(n)
            {
                printf("- ");
                n--;
            }
            printf("\n");
            n = 54;
        }
        k++;
        temp = temp->next;
    }
    if (check == 0)
    {
        printf("There are no students who should be evicted.");
        show3 = true;
    }
}

void EvictingStudents(Database *item)
{
     List *temp = item->head;
     int k = 0, n = 0;
     List *next = NULL;
     while(k != item->count_student)
     {
        if (temp->student.countViolation > 2)
        {
            if (temp == item->head)
            {
                item->head = temp->next;
                free(temp);
            }
            else
            {
                next = temp->next;
                free(temp);
            }
            n++;
        }
        temp = temp->next;
        k++;
    }
    printf("  >Students are evicted.");
    item->count_student -= n;
}

void AddEmployees(Database *item, char P[20], char N[50], int R, char PN[20])
{
    List *temp = (List*)malloc(sizeof(List));

    temp->next = NULL;
    temp->prev = item->tail;
    for (int i = 0; i < 20; i++)
    {
        temp->employee.position[i] = P[i];
    }
    for (int i = 0; i < 50; i++)
    {
        temp->employee.name[i] = N[i];
    }
    temp->employee.room = R;
    for (int i = 0; i < 20; i++)
    {
        temp->employee.phone_number[i] = PN[i];
    }
    if(!item->head)
    {
        item->head = temp;
    }
    else
    {
        item->tail->next = temp;
    }

    item->tail = temp;
    item->count_employee += 1;
}

int ReadFromEmployeesFile(Database *item)
{
    char position[20], name[50], phone_number[20];
	int room = 0, read = 0, time = 1, time2 = 0;

    FILE *file;
    file = fopen("List of employees.txt", "r");
    if (!file)
    {
        printf("Error! The program didn't find the file.");
        return 0;
    }
    else
    {
        char *file_inf = (char*)malloc(sizeof(char));
        char check_comparison[20];
        strcpy(position, space);
        while (fscanf(file, "%s", file_inf) != EOF)
        {
            time == 0 ? time++ : 0;
            if (strcmp(file_inf, check_comparison) == 0)
            {
                read = 0;
                if (time == 26)
                {
                    AddEmployees(item, position, name, room, phone_number);
                    time = 0;
                    time2 = 0;
                    strcpy(position, space);
                }
                else
                {
                    time++;
                }
            }
            switch(read)
            {
                case 1:
                    strcat(name, file_inf);
                    strcat(name, space);
                    break;
                case 2:
                    room = atoi(file_inf);
                    read = 0;
                    break;
                case 3:
                    strcpy(phone_number, file_inf);
                    break;
                default: read = 0;
            }
            if (strcmp(file_inf, ":") == 0)
            {
                switch(time)
                {
                    case 1: read = time;  time2++; strcpy(name, space); strcpy(check_comparison, "Room"); break;
                    case 2: read = time; strcpy(check_comparison, "number"); break;
                    case 3: read = time; strcpy(check_comparison, "-"); break;
                }
            }
            if (time == 1 && time2 == 0)
            {
                strcat(position, file_inf);
                strcat(position, space);
            }
        }
        return 1;
    }
    fclose(file);
}

void DisplayEmployees(Database *item)
{
    List *temp = item->head;
    int n = 28, k = 0;
    while(temp)
    {
        if (k >= item->count_employee)
        {
            printf("Position:%s\n", temp->employee.position);
            printf("Name:%s\n", temp->employee.name);
            printf("Room: %d\n", temp->employee.room);
            printf("Phone number:%s\n", temp->employee.phone_number);
            while(n)
            {
                printf("- ");
                n--;
            }
            printf("\n");
            n = 28;
        }
        k++;
        temp = temp->next;
    }
}

void FromFile(Database *item)
{
    List *temp = item->head;
    int n1 = 54, n2 = 28, k = 0;
    while(temp)
    {
        if(k == item->count_student)
        {
            printf("Position:%s\n", temp->employee.position);
            printf("Name:%s\n", temp->employee.name);
            printf("Room: %d\n", temp->employee.room);
            printf("Phone number:%s\n", temp->employee.phone_number);
            while(n2)
            {
                printf("- ");
                n2--;
            }
            printf("\n");
            n2 = 28;
        }
        if(k < item->count_student)
        {
            printf("Student:%s\n", temp->student.name);
            printf("Faculty:%s\n", temp->student.faculty);
            printf("Course: %d\n", temp->student.course);
            printf("Group: %d\n", temp->student.group);
            printf("Violations:%s\n", temp->student.violation);
            while(n1)
            {
                printf("- ");
                n1--;
            }
            printf("\n");
            n1 = 54;
            k++;
        }
        temp = temp->next;
    }
}

void SearchBySername(Database *item)
{
    List *temp = item->head;
    char name[30], inputSername[30], *sername;
    int k = 0, check = 0;
    printf("Search: ");
    scanf("%s", inputSername);
    while(temp)
    {
        if(k == item->count_student)
        {
            check = 1;
            strcpy(name, temp->employee.name);
        }
        if(k < item->count_student)
        {
            strcpy(name, temp->student.name);
            k++;
        }
        sername = strtok(name, space);
        if (strcmp(inputSername, sername ) == 0 && check == 0)
        {
            printf("Result of search -> room #%d\n", temp->student.room);
        }
        if (strcmp(inputSername, sername ) == 0 && check == 1)
        {
            printf("\nResult of search -> room #%d\n", temp->employee.room);
        }
        temp = temp->next;
    }
}

void SearchByRoom(Database *item)
{
    List *temp = item->head;
    char *sername, name[30];
    int k = 0, inputRoom;
    printf("Search: ");
    scanf("%d", &inputRoom);
    while(temp)
    {
        if(k == item->count_student)
        {
            strcpy(name, temp->employee.name);
        }
        if(k < item->count_student)
        {
            strcpy(name, temp->student.name);
            k++;
        }
        sername = strtok(name, space);
        if (temp->student.room == inputRoom || temp->employee.room == inputRoom)
        {
            printf("Result of search -> sername - %s\n", sername);
        }
        temp = temp->next;
    }
}

void Report(Database *item)
{
    List *temp = item->head;
    int freeRooms[26 - item->count_student];
    int count = 0, time = 0, time2 = 0, time3 = 0;
    printf("  >Report:\n\n");
    printf("Number of residents -> %d\n", item->count_student);
    printf("Free rooms in the hostel -> ");
    for(int i = 0, n = 0; n < 26; n++)
    {
        if(FreeRooms(0, item, 1, n) != 0)
        {
            freeRooms[i] = FreeRooms(0, item, 1, n);
            printf("#%d ", FreeRooms(0, item, 1, n));
            i++;
        }
    }
    printf("\nNumber of available rooms in the hostel - > %d", 26 - item->count_student);
    for(int i = 0; i < 26 - item->count_student; i++)
    {
        if(freeRooms[i] / 100 == 2)
        {
            time == 0 ? printf("\n\nFree rooms for the faculty of computer engineering -> "), time++ : 0;
            printf("#%d ", freeRooms[i]);
            count++;
        }
        if(freeRooms[i] / 100 == 3)
        {
            time2 == 0 ? printf("\nNumber of available rooms -> %d", count), count = time = 0, time2++ : 0;
            time == 0 ? printf("\n\nFree rooms for the faculty of radio engineering and electronics -> "), time++ : 0;
            printf("#%d ", freeRooms[i]);
            count++;
        }
        if(freeRooms[i] / 100 == 4)
        {
            time3 == 0 ? printf("\nNumber of available rooms -> %d", count), count = time = time2 = 0, time3++ : 0;
            time == 0 ? printf("\n\nFree rooms for the faculty of computer systems and networks -> "), time++ : 0;
            printf("#%d ", freeRooms[i]);
            count++;
        }
        if(freeRooms[i] / 100 == 5)
        {
            time2 == 0 ? printf("\nNumber of available rooms -> %d", count), count = time = time3 = 0, time2++ : 0;
            time == 0 ? printf("\n\nFree rooms for the faculty of information technology and management -> "), time++ : 0;
            printf("#%d ", freeRooms[i]);
            count++;
            if(i == 26 - item->count_student - 1)
            {
                time3 == 0 ? printf("\nNumber of available rooms -> %d", count): 0;
            }
        }
    }
}

int WriteToFile(Database *item)
{
    List *temp = item->head;
    int n1 = 54, n2 = 28, k = 0, time = 0;
    FILE *file;

     file = fopen("BSUIR hostel database.TXT", "wb");

    if (!file)
    {
        printf("Error! The program didn't find the file.");
        return 0;
    }
    else
    {
        fprintf(file, "//////////////////////////////////////////////////////////////////////\n\n");
        fprintf(file, "List of residents in the BSUIR hostel:\n\n");
        fprintf(file, "//////////////////////////////////////////////////////////////////////\n\n");
        while(temp)
        {
            if(k == item->count_student && time == 0)
            {
                fprintf(file, "//////////////////////////////////////////////////////////////////////\n\n");
                fprintf(file, "List of employees of the BSUIR hostel:\n\n");
                fprintf(file, "//////////////////////////////////////////////////////////////////////\n\n");
                time++;
            }
            if(k == item->count_student && time != 0)
            {
                fprintf(file, "%s : ", temp->employee.position);
                fprintf(file, "%s\n", temp->employee.name);
                fprintf(file, "             -room : %d\n", temp->employee.room);
                fprintf(file, "             -phone number : %s\n", temp->employee.phone_number);
                while(n2)
                {
                    fprintf(file, "- ");
                    n2--;
                }
                fprintf(file, "\n");
                n2 = 28;
            }
            if(k < item->count_student)
            {
                fprintf(file, "Student : %s\n", temp->student.name);
                fprintf(file, "      > faculty : %s\n", temp->student.faculty);
                fprintf(file, "      > course : %d\n", temp->student.course);
                fprintf(file, "      > group : %d\n", temp->student.group);
                fprintf(file, "      > violations : %s\n", temp->student.violation);
                while(n1)
                {
                    fprintf(file, "- ");
                    n1--;
                }
                fprintf(file, "\n");
                n1 = 54;
                k++;
            }
            temp = temp->next;
        }
    }
    fclose(file);
    printf("  >The information is entered in a file.\n\n");
    return 1;
}
