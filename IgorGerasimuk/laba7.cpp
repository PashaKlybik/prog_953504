#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MEM_PARMS (struct Parms*)malloc(sizeof(struct Parms))
#define MEM_PERF  (struct Performer*)malloc(sizeof(struct Performer))
#define MEM_TASK  (struct Task*)malloc(sizeof(struct Task))
#define MEM_MILE  (struct Milestone*)malloc(sizeof(struct Milestone))
#define MEM_PROJ  (struct Project*)malloc(sizeof(struct Project))

struct Parms
{
    char title[200];
    int days;
    double resource;
};

struct Performer
{
    char name[30];
    struct Performer* next;
};

struct Task
{
    struct Performer* performer;
    struct Parms* parms;
    struct Task* next;
};

struct Milestone
{
    struct Task* task;
    struct Parms* parms;
    struct Milestone* next;
};

struct Project
{
    struct Milestone* milestone;
    struct Parms* parms;
    struct Project* next;
};

void ReadFromFile(struct Project** first);
void WriteFromFile(struct Project* project);
void NewProject(struct Project** first);
void NewMilestone(struct Milestone** first);
void NewTask(struct Task** first);
void NewPerformer(struct Performer** first);
void ProjTimeAndRes(struct Project** project);
void MileTimeAndRes(struct Milestone** milestone);
void CombineTasks(struct Task** task);
void PrintProject(struct Project* first);
void PrintMilestone(struct Milestone* first);
void PrintTask(struct Task* first);
void PrintPerformer(struct Performer* first);
struct Project* SelectProj(struct Project* first);
struct Milestone* SelectMile(struct Milestone* first);
struct Task* SelectTask(struct Task* first);
struct Project* AddProject(struct Project* first, struct Project* project);
struct Milestone* AddMilestone(struct Milestone* first, struct Milestone* milestone);
struct Task* AddTask(struct Task* first, struct Task* task);
struct Performer* AddPerformer(struct Performer* first, struct Performer* performer);
void DeleteTask(struct Task** first, struct Task** del);
struct tm Time(int day, int month, int year);
int Days(struct tm start, struct tm end);
int Exit(const char* str);
int Input(void);
char Menu(void);

int main(void)
{
    struct Project* project = MEM_PROJ;
    struct Project* temp_proj;
    struct Milestone* temp_mile;
    project = NULL;
    char flag;

    while (1) {
        flag = Menu();
        switch (flag) {

        case '1':
            ReadFromFile(&project);
            break;

        case '2':
            NewProject(&project);
            break;

        case '3':
            temp_proj = SelectProj(project);
            NewMilestone(&(temp_proj->milestone));

        case '4':
            temp_proj = SelectProj(project);
            temp_mile = SelectMile(temp_proj->milestone);
            NewTask(&(temp_mile->task));

        case '5':
            ProjTimeAndRes(&project);
            PrintProject(project);
            break;

        case '6':
            temp_proj = SelectProj(project);
            temp_mile = SelectMile(temp_proj->milestone);
            CombineTasks(&(temp_mile->task));
            break;

        case '7':
            WriteFromFile(project);
            break;

        case '8':
            printf("Goodbye:)");
            return 0;
        }
    }
}

char Menu(void)
{
    char flag;

    printf("1. Read the project from the file.\n");
    printf("2. Add project.\n");
    printf("3. Add a milestone.\n");
    printf("4. Add task.\n");
    printf("5. Display the project on the screen.\n");
    printf("6. Combine tasks.\n");
    printf("7. Write the project to a file.\n");
    printf("8. Exit.\n");
    getchar();

    while (!(scanf("%[1-8]", &flag))) {
        printf("Invalid input. Try again.\n");
        getchar();
    }
    return flag;
}

void ReadFromFile(struct Project** first)
{
    FILE* file;
    file = fopen("project.TXT", "rb");

    if (!file) {
        printf("Error: opening file.");
        exit(1);
    }

    char str[100], letter;
    int count = 0;
    int start_d, start_m, start_y, end_d, end_m, end_y;

    struct Project* project = MEM_PROJ;
    struct Milestone* temp_mile = NULL;
    struct Task* temp_task = NULL;
    struct Performer* temp_perf = NULL;

    project->parms = MEM_PARMS;
    fgets(str, 100, file);
    sscanf(str, "%[ -~]", project->parms->title);

    while (!feof(file)) {
        fread(&letter, sizeof(char), 1, file);

        if (letter == '-') {
            count++;
            continue;
        }

        switch (count) {

        case 6:

            if (!temp_mile) {
                temp_mile = MEM_MILE;
                project->milestone = temp_mile;
                temp_task = NULL;
            }

            else {
                temp_mile->next = MEM_MILE;
                temp_mile = temp_mile->next;
                temp_task = NULL;
            }

            temp_mile->next = NULL;
            temp_mile->parms = MEM_PARMS;
            fgets(str, 100, file);
            sscanf(str, "%[ -~]", temp_mile->parms->title);
            count = 0;
            break;

        case 16:

            if (!temp_task) {
                temp_task = MEM_TASK;
                temp_mile->task = temp_task;
                temp_perf = NULL;
            }

            else {
                temp_task->next = MEM_TASK;
                temp_task = temp_task->next;
                temp_perf = NULL;
            }

            temp_task->next = NULL;
            temp_task->parms = MEM_PARMS;

            fgets(str, 100, file);
            sscanf(str, "%[ -z] | %d.%d.%d - %d.%d.%d | %lf",
                temp_task->parms->title,
                &start_d, &start_m, &start_y,
                &end_d, &end_m, &end_y,
                &temp_task->parms->resource);

            struct tm start = Time(start_d, start_m, start_y);
            struct tm end = Time(end_d, end_m, end_y);
            temp_task->parms->days = Days(start, end);

            count = 0;
            break;

        case 28:

            if (!temp_perf) {
                temp_perf = MEM_PERF;
                temp_task->performer = temp_perf;
            }

            else {
                temp_perf->next = MEM_PERF;
                temp_perf = temp_perf->next;
            }

            temp_perf->next = NULL;
            fgets(str, 100, file);
            sscanf(str, "%[ -~]", temp_perf->name);
            count = 0;
            break;
        }
    }
    project->next = NULL;
    ProjTimeAndRes(&project);

    if (!(*first)) {
        *first = project;
        return;
    }
    struct Project* temp_proj = *first;

    while (temp_proj->next)
        temp_proj = temp_proj->next;

    temp_proj->next = project;
    fclose(file);
}

void WriteFromFile(struct Project* project)
{
    struct Project* temp_proj = project;
    FILE* file;

    file = fopen("project2.TXT", "wb");

    if (!file) {
        printf("Error: opening file.");
        exit(1);
    }

    while (temp_proj) {
        fprintf(file, "%s\n", temp_proj->parms->title);
        struct Milestone* temp_mile = temp_proj->milestone;

        while (temp_mile) {
            for (int i = 0; i < 10; i++) fprintf(file, "-");
            fprintf(file, "%s\n", temp_mile->parms->title);

            struct Task* temp_task = temp_mile->task;

            while (temp_task) {
                for (int i = 0; i < 20; i++) fprintf(file, "-");
                fprintf(file, "%s (%d days, %.2lf$)\n",
                    temp_task->parms->title,
                    temp_task->parms->days,
                    temp_task->parms->resource);

                struct Performer* temp_perf = temp_task->performer;

                while (temp_perf) {
                    for (int i = 0; i < 30; i++) fprintf(file, "-");
                    fprintf(file, "%s\n", temp_perf->name);

                    temp_perf = temp_perf->next;
                }
                temp_task = temp_task->next;
            }
            temp_mile = temp_mile->next;
        }
        temp_proj = temp_proj->next;
    }

    fclose(file);
}

void ProjTimeAndRes(struct Project** project)
{
    struct Milestone* temp_mile = (*project)->milestone;
    (*project)->parms->days = 0;
    (*project)->parms->resource = 0.0;

    while (temp_mile) {
        MileTimeAndRes(&temp_mile);
        (*project)->parms->days += temp_mile->parms->days;
        (*project)->parms->resource += temp_mile->parms->resource;

        temp_mile = temp_mile->next;
    }
}

void MileTimeAndRes(struct Milestone** milestone)
{
    struct Task* temp_task = (*milestone)->task;
    (*milestone)->parms->days = 0;
    (*milestone)->parms->resource = 0.0;

    while (temp_task) {
        (*milestone)->parms->days += temp_task->parms->days;
        (*milestone)->parms->resource += temp_task->parms->resource;

        temp_task = temp_task->next;
    }
}

void CombineTasks(struct Task** task)
{
    struct Task* temp_task = *task,
        * first_task = NULL,
        * second_task = NULL;
    int index1, index2;
    printf("Select the tasks you want to combine.\n");
    index1 = Input();

    for (int i = 1; i <= index1; i++) {

        if (!temp_task) {
            printf("The item under this index does not exist.\n");
            return;
        }
        first_task = temp_task;
        temp_task = temp_task->next;
    }

    temp_task = *task;
    index2 = Input();

    for (int i = 1; i <= index2; i++) {

        if (!temp_task) {
            printf("The item under this index does not exist.");
            return;
        }
        second_task = temp_task;
        temp_task = temp_task->next;
    }

    if (first_task->parms->days >= second_task->parms->days) {
        int i = 0;
        first_task->parms->resource += second_task->parms->resource;
        strcat(first_task->parms->title, "| ");

        for (; first_task->parms->title[i] != '\0'; i++);

        memcpy(first_task->parms->title + i, second_task->parms->title, 200 - i);
        first_task->performer = AddPerformer(first_task->performer, second_task->performer);
        DeleteTask(task, &second_task);
    }
    else {
        int i = 0;
        second_task->parms->resource += first_task->parms->resource;
        strcat(second_task->parms->title, "| ");

        for (; second_task->parms->title[i] != '\0'; i++);

        memcpy(second_task->parms->title + i, first_task->parms->title, 200 - i);
        second_task->performer = AddPerformer(second_task->performer, first_task->performer);
        DeleteTask(task, &first_task);
    }
}

void NewProject(struct Project** first)
{
    struct Project* project = MEM_PROJ;
    project->next = NULL;
    project->parms = MEM_PARMS;
    project->milestone = NULL;

    printf("Enter title of the project: ");
    scanf("%s", project->parms->title);
    NewMilestone(&(project->milestone));

    ProjTimeAndRes(&project);
    *first = AddProject(*first, project);
}

void NewMilestone(struct Milestone** first)
{
    int flag = 1;

    while (flag) {
        struct Milestone* milestone = MEM_MILE;
        milestone->parms = MEM_PARMS;
        milestone->task = NULL;

        printf("Enter title of the milestone: ");
        scanf("%s", milestone->parms->title);

        NewTask(&(milestone->task));
        *first = AddMilestone(*first, milestone);
        flag = Exit("milestone");
    }
}

void NewTask(struct Task** first)
{
    int flag = 1;
    char data[20];
    int day, month, year;

    while (flag) {
        struct Task* task = MEM_TASK;
        task->parms = MEM_PARMS;
        task->performer = NULL;

        printf("Enter task: ");
        scanf("%s", task->parms->title);

        printf("Enter start time: ");
        scanf("%s", data);
        sscanf(data, "%d.%d.%d", &day, &month, &year);
        struct tm start = Time(day, month, year);

        printf("Enter end time: ");
        scanf("%s", data);
        sscanf(data, "%d.%d.%d", &day, &month, &year);
        struct tm end = Time(day, month, year);

        task->parms->days = Days(start, end);

        printf("Enter resources: ");
        scanf("%lf", &task->parms->resource);

        NewPerformer(&(task->performer));

        *first = AddTask(*first, task);
        flag = Exit("task");
    }
}

void NewPerformer(struct Performer** first)
{
    int flag = 1;

    while (flag) {
        struct Performer* performer = MEM_PERF;

        printf("Enter name of performer: ");
        scanf("%s", performer->name);
        *first = AddPerformer(*first, performer);
        flag = Exit("performer");
    }
}

void PrintProject(struct Project* first)
{
    struct Project* project = first;

    for (int i = 1; project; i++) {
        printf("%d. %s (%d days, %.2lf$)\n", i,
            project->parms->title,
            project->parms->days,
            project->parms->resource);

        PrintMilestone(project->milestone);
        project = project->next;
    }
}

void PrintMilestone(struct Milestone* first)
{
    struct Milestone* milestone = first;

    for (int i = 1; milestone; i++) {
        for (int i = 0; i < 10; i++) printf("-");
        printf("%d. %s (%d days, %.2lf$)\n", i,
            milestone->parms->title,
            milestone->parms->days,
            milestone->parms->resource);

        PrintTask(milestone->task);
        milestone = milestone->next;
    }
}

void PrintTask(struct Task* first)
{
    struct Task* task = first;

    for (int i = 1; task; i++) {
        for (int i = 0; i < 25; i++) printf("-");
        printf("%d. %s (%d days, %.2lf$)\n", i,
            task->parms->title,
            task->parms->days,
            task->parms->resource);

        PrintPerformer(task->performer);
        task = task->next;
    }
}

void PrintPerformer(struct Performer* first)
{
    struct Performer* performer = first;

    for (int i = 1; performer; i++) {
        for (int i = 0; i < 40; i++) printf("-");
        printf("%d. %s\n", i, performer->name);

        performer = performer->next;
    }
}

struct Project* SelectProj(struct Project* first)
{
    int index;
    printf("Select a project.\n");
    index = Input();

    if (index == 1 || !first) {
        return first;
    }
    struct Project* project = first;

    for (int i = 1; i < index; i++) {

        if (!project->next) {
            printf("The item under this index does not exist.\n");
            return NULL;
        }
        project = project->next;
    }
    return project;
}

struct Milestone* SelectMile(struct Milestone* first)
{
    int index;
    printf("Select a milestone.\n");
    index = Input();

    if (index == 1 || !first) {
        return first;
    }
    struct Milestone* mile = first;

    for (int i = 1; i < index; i++) {

        if (!mile->next) {
            printf("The item under this index does not exist.\n");
            return NULL;
        }
        mile = mile->next;
    }
    return mile;
}

struct Task* SelectTask(struct Task* first)
{
    int index;
    printf("Select a task.\n");
    index = Input();

    if (index == 1) {
        return first;
    }
    struct Task* task = first;

    for (int i = 1; i < index; i++) {

        if (!task->next) {
            printf("The item under this index does not exist.\n");
            return NULL;
        }
        task = task->next;
    }
    return task;
}

struct Project* AddProject(struct Project* first, struct Project* project)
{
    project->next = NULL;
    if (!first) {
        first = project;
        return first;
    }

    struct Project* temp = first;

    while (temp->next)
        temp = temp->next;

    temp->next = project;
    return first;
}

struct Milestone* AddMilestone(struct Milestone* first, struct Milestone* milestone)
{
    milestone->next = NULL;
    if (!first) {
        first = milestone;
        return first;
    }
    struct Milestone* temp = first;

    while (temp->next)
        temp = temp->next;

    temp->next = milestone;
    return first;
}

struct Task* AddTask(struct Task* first, struct Task* task)
{
    task->next = NULL;
    if (!first) {
        first = task;
        return first;
    }
    struct Task* temp = first;

    while (temp->next)
        temp = temp->next;

    temp->next = task;
    return first;
}

struct Performer* AddPerformer(struct Performer* first, struct Performer* performer)
{
    performer->next = NULL;
    if (!first) {
        first = performer;
        return first;
    }
    struct Performer* temp = first;

    while (temp->next)
        temp = temp->next;

    temp->next = performer;
    return first;
}

void DeleteTask(struct Task** first, struct Task** del)
{
    struct Task* task = *first;

    if ((*first) == (*del)) {
        *first = (*first)->next;
        task = NULL;
        return;
    }

    while (task->next != (*del))
        task = task->next;

    task->next = (*del)->next;
    (*del) = NULL;


}

struct tm Time(int day, int month, int year)
{
    struct tm t;
    time_t now;
    time(&now);
    t = *localtime(&now);

    t.tm_mday = day;
    t.tm_mon = month;
    t.tm_year = year - 1900;

    return t;
}

int Days(struct tm start, struct tm end)
{
    double seconds = difftime(mktime(&end), mktime(&start));
    return seconds > 0 ? seconds / 86400 : 0;
}

int Exit(const char* str)
{
    char flag;
    printf("Add another %s - 1, finish - 0.\n", str);
    getchar();

    while (!(scanf("%[0-1]", &flag))) {
        printf("Invalid input. Try again.\n");
        getchar();
    }
    return atoi(&flag);
}

int Input(void)
{
    int index;

    while (!(scanf("%d", &index)) || index <= 0) {
        printf("Invalid input. Try again.\n");
        getchar();
    }
    return index;
}