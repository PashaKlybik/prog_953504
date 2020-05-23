#include <stdio.h>
#include <iostream>
#include <conio.h>


using namespace std;


typedef struct AppList {
	int count;
	char name[20];
	char date[15];
	char educ[10];
	char city[10];
	char salary[10];
	AppList* next, * prev;
	AppList* head;
};



typedef struct Vacancies {
	char comp[20];
	char city[10];
	char educ[10];
	char spec[20];
	int age;
	int count;
	Vacancies* prev, * next;
	Vacancies* head;
};



typedef struct Employers {
	char name[20] = "";
	char comp[20] = "";
	int age;
	int count;
	Employers* prev, * next;
	Employers* head;
};



void addToArchive(Employers* emp);
Vacancies* addVacancy(Vacancies* vac, char[], char[], char[], char[], int);
Employers* addEmployer(Employers* emp, char[], char[], char[]);
void showEmp(Employers* emp);
Employers* deleteEmp(Employers* emp, char name[]);
Vacancies* deleteVac(Vacancies* vac, char comp[]);
struct AppList* init(AppList* list, char name[], char date[], char educ[], char city[], char salary[]);
AppList* registry(AppList* list, char name[], char date[], char educ[], char city[], char salary[]);
struct AppList* search(AppList* list, int age, char city[], char educ[]);
struct AppList* delApp(AppList* list, AppList* del);
Employers* searchForJob(AppList** app, Vacancies* vac, Employers** emp);
void printApp(AppList* list);
AppList* getInfApp();
Vacancies* getInfVac();
void showVac(Vacancies* vac);
void updateAppInf(AppList* app);
void updateVacInf(Vacancies* vac);
Vacancies* addVacDialog(Vacancies* vac);
Vacancies* delVacDialog(Vacancies* vac);
AppList* addAppDialog(AppList* app);
Employers* delAppDialog(Employers* list);






int main() {
	AppList* app = NULL;
	Vacancies* vac = NULL;
	Employers* emp = NULL;
	while (true) {
		int ch;
		printf("\t\t\t-----MAIN MENU-----\n\n");
		printf("\t\t\tChoose variant:\n\t\t\t1)VACANCIES LIST\n\t\t\t2)APPLICANTS LIST\n\t\t\t3)GET EMPLOYERS");
		printf("\n\t\t\t4)ADD APPLICANT\n\t\t\t5)DISMISS EMPLOYEE\n\t\t\t6)ADD VACANCY\n\t\t\t7)DELETE VACANCY");
		scanf("%d", &ch);
		switch (ch) {
			case 1: vac = getInfVac(); showVac(vac); break;
			case 2: app = getInfApp(); printApp(app);  break;
			case 3: emp = searchForJob(&app, vac, &emp); showEmp(emp); addToArchive(emp); updateAppInf(app); break;
			case 4: app = addAppDialog(app); updateAppInf(app); break;
			case 5: emp = delAppDialog(emp); showEmp(emp); addToArchive(emp); updateAppInf(app); break;
			case 6: vac = addVacDialog(vac); showVac(vac); updateVacInf(vac); break;
			case 7: vac = delVacDialog(vac); showVac(vac); updateVacInf(vac); break;
		}
	}
}




void addToArchive(Employers* emp) {
	if (emp == NULL) return;
	Employers* tmp = emp->head;
	FILE* p = fopen("Archive.txt", "w");
	while (tmp != NULL) {
		fprintf(p, "%s %s %d\n", tmp->name, tmp->comp, tmp->age);
		tmp = tmp->next;
	}
	Employers *buf;
	while (tmp != NULL) {
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
	fclose(p);
}




Vacancies* addVacancy(Vacancies* vac, char comp[], char city[], char educ[], char spec[], int age) {
	if (vac == NULL) {
		vac = (Vacancies*)malloc(sizeof(Vacancies));
		strcpy(vac->comp, comp);
		vac->age = age;
		strcpy(vac->city, city);
		strcpy(vac->educ, educ);
		strcpy(vac->spec, spec);
		vac->head = vac;
		vac->next = NULL;
		vac->prev = NULL;
		vac->count = 1;
	}
	else {
		Vacancies* tmp = (Vacancies*)malloc(sizeof(Vacancies));
		strcpy(tmp->comp, comp);
		tmp->age = age;
		strcpy(tmp->city, city);
		strcpy(tmp->educ, educ);
		strcpy(tmp->spec, spec);
		Vacancies* buf = vac->head;
		while (buf->next != NULL) {
			buf = buf->next;
		}
		tmp->prev = buf;
		tmp->next = NULL;
		buf->next = tmp;
		vac->count++;
		
		Vacancies * t;
		while (tmp != NULL) {
			t = tmp;
			tmp = tmp->next;
			free(t);
		}

		Vacancies * del;
		while (buf != NULL) {
			del = buf;
			buf = buf->next;
			free(del);
		}
	}
	return vac;
}






Employers* addEmployer(Employers* emp, char name[], char comp[], char date[]) {
	Employers* tmp;
	if (emp == NULL) {
		emp = (Employers*)malloc(sizeof(Employers));
		strcpy(emp->name, name);
		char currAge[5] = "";
		strncpy(currAge, date + 6, 4);
		int currA = 2020 - atoi(currAge);
		emp->age = currA;
		strcpy(emp->comp, "");
		strcpy(emp->comp, comp);
		emp->head = emp;
		emp->next = NULL;
		emp->prev = NULL;
		emp->count = 1;
		return emp;
	}
	else {
		tmp = (Employers*)malloc(sizeof(Employers));
		strcpy(tmp->name, name);
		char currAge[5] = "";
		strncpy(currAge, date + 6, 4);
		int currA = 2020 - atoi(currAge);
		tmp->age = currA;
		strcpy(tmp->comp, comp);
		tmp->prev = NULL;
		tmp->next = emp->head;
		tmp->next->prev = tmp;
		tmp->head = tmp;
		tmp->count++;
	}
	return tmp;
}



void showEmp(Employers* emp) {
	Employers* tmp;
	if (emp != NULL) tmp = emp->head;
	else {
		printf("\n\nNO EMPLOYEES NOW :(\n\n");
		return;
	}
	printf("\n\n%-15s %-15s %-3s\n", "Name:", "Company:", "Age:");
	while (tmp != NULL) {
		printf("%-15s %-15s %-3d\n", tmp->name, tmp->comp, tmp->age);
		tmp = tmp->next;
	}
	printf("\n\n");
	Employers* buf;
	while (tmp != NULL) {
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
}



Employers* deleteEmp(Employers* emp, char name[]) {
	if (emp->head == NULL) return NULL;
	Employers* tmp = emp->head;
	int count = tmp->count - 1;
	while (strcmp(tmp->name, name) != 0 && tmp != NULL) {
		tmp = tmp->next;
	}
	if (tmp == NULL) return emp;
	if (tmp == emp->head) {
		if (tmp->next) tmp->next->prev = NULL;
		else {
			return NULL;
		}
		tmp = tmp->next;
		tmp->head = tmp;
		tmp->count = count;
	}
	else {
		if (tmp->next && tmp->prev) {
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
		}
		else {
			tmp = tmp->prev;
			tmp->next = NULL;
			tmp->head->count = count;
		}
	}
	return tmp;
}




Vacancies* deleteVac(Vacancies* vac, char comp[]) {
	if (vac->head == NULL && vac == NULL) return vac;
	Vacancies* tmp = vac->head;
	int count = tmp->count - 1;
	while (strcmp(tmp->comp, comp) != 0 && tmp != NULL) {
		tmp = tmp->next;
	}
	if (tmp == NULL) return vac;
	if (tmp == vac->head) {
		if (tmp->next) tmp->next->prev = NULL;
		else {
			return NULL;
		}
		tmp = tmp->next;
		tmp->head = tmp;
		tmp->count = count;
	}
	else {
		if (tmp->next && tmp->prev) {
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
			tmp = vac;
		}
		else {
			tmp = tmp->prev;
			tmp->next = NULL;
			tmp->head->count = count;
		}
	}
	return tmp;
}




struct AppList* init(AppList* list, char name[], char date[], char educ[], char city[], char salary[]) {
	list->count++;
	strcpy(list->name, name);
	strcpy(list->date, date);
	strcpy(list->educ, educ);
	strcpy(list->city, city);
	strcpy(list->salary, salary);
	list->next = NULL;
	list->prev = NULL;
	list->head = list;
	list->count = 1;
	return list;
}




AppList* registry(AppList* list, char name[], char date[], char educ[], char city[], char salary[]) {
	AppList* tmp = (AppList*)malloc(sizeof(AppList));
	strcpy(tmp->name, name);
	strcpy(tmp->date, date);
	strcpy(tmp->educ, educ);
	strcpy(tmp->city, city);
	strcpy(tmp->salary, salary);
	AppList* buf = list->head;
	while (buf->next != NULL) {
		buf = buf->next;
	}
	tmp->prev = buf;
	tmp->next = NULL;
	buf->next = tmp;
	list->count++;
    
	AppList* t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
	AppList* del;
	while (buf != NULL) {
		del = buf;
		buf = buf->next;
		free(del);
	}

	return list;
}



struct AppList* search(AppList* list, int age, char city[], char educ[]) {
	AppList* tmp = list->head;
	while (tmp != NULL) {
		char currAge[5] = "";
		strncpy(currAge, tmp->date + 6, 4);
		int currA = 2020 - atoi(currAge);
		if (currA <= age + 5 && currA >= age - 5 && strcmp(tmp->city, city) == 0 && strcmp(tmp->educ, educ) == 0) return tmp;
		tmp = tmp->next;
	}
	return NULL;
}





struct AppList* delApp(AppList* list, AppList* del) {
	if (list->head == NULL) return list;
	AppList* tmp = list->head;
	int count = tmp->count - 1;
	while (strcmp(tmp->name, del->name) != 0) {
		tmp = tmp->next;
	}
	if (tmp == list->head) {
		if (tmp->next) tmp->next->prev = NULL;
		else {
			return NULL;
		}
		tmp = tmp->next;
		tmp->head = tmp;
		tmp->count = count;
	}
	else {
		if (tmp->next && tmp->prev) {
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
		}
		else {
			tmp = tmp->prev;
			tmp->next = NULL;
			list->head->count = count;
		}
	}

	AppList* t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}

	return list;
}



Employers* searchForJob(AppList** app, Vacancies* vac, Employers** emp) {
	if (*app == NULL || vac == NULL) return NULL;
	Vacancies* tmp = vac->head;
	while (tmp != NULL && *app != NULL) {
		AppList* buf = NULL;
		buf = search(*app, tmp->age, tmp->city, tmp->educ);
		if (buf != NULL) {
			*emp = addEmployer(*emp, buf->name, vac->comp, buf->date);
			*app = delApp(*app, buf);
		}
		tmp = tmp->next;
	}

	Vacancies * t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}

	return *emp;
}



void printApp(AppList* list) {
	printf("\n\n\n\t\t\tAPPLICANTS LIST: \n\n");
	if (list == NULL) return;
	AppList* tmp = list->head;
	int i = 1;
	char s = (char)248;
	printf("  N%c %-15s %-15s %-15s %-15s\n", s, "Name:", "Date of birth:", "Education:", "City:");
	while (tmp != NULL) {
		printf("  %d) %-15s %-15s %-15s %-15s\n", i, tmp->name, tmp->date, tmp->educ, tmp->city);
		tmp = tmp->next;
		i++;
	}
	cout << "\n\n";
}




AppList* getInfApp() {
	FILE* app = fopen("Applicants.txt", "r");
	char ch = fgetc(app);
	if (ch == EOF) {
		printf("EMPTY FILE");
		return NULL;
	}
	fseek(app, 0, SEEK_SET);
	fputc(ch, app);

	AppList* tmp = (AppList*)malloc(sizeof(AppList));
	int i = 0;
	char name[20];
	char date[15];
	char educ[10];
	char city[10];
	char salary[10];
	while (fscanf(app, "%s%s%s%s%s", name, date, educ, city, salary) != EOF) {
		if (i == 0) {
			tmp = init(tmp, name, date, educ, city, salary);
			i++;
		}
		else registry(tmp, name, date, educ, city, salary);
	}
	fclose(app);
	return tmp;
}




Vacancies* getInfVac() {
	FILE* vac = fopen("Vacancies.txt", "r");
	char ch = fgetc(vac);
	if (ch == EOF) {
		printf("EMPTY FILE");
		return NULL;
	}
	fseek(vac, 0, SEEK_SET);
	fputc(ch, vac);

	Vacancies* tmp = NULL;
	char comp[20];
	char city[10];
	char educ[10];
	char spec[20];
	int age;
	while (fscanf(vac, "%s%s%s%s%d", comp, city, educ, spec, &age) != EOF) {
		tmp = addVacancy(tmp, comp, city, educ, spec, age);
	}
	return tmp;
}




void showVac(Vacancies* vac) {
	printf("\n\n\n\t\t\tVACANCY LIST:\n\n ");
	if (vac == NULL) {
		printf("NO VACANCIES :(");
		return;
	}
	Vacancies* tmp = vac->head;
	int i = 1;
	char s = (char)248;
	printf("N%c  %-10s  %-10s  %-10s  %-10s  %-3s\n", s, "Company:", "City:", "Education:", "Speciality:", "Age:");
	while (tmp != NULL) {
		printf(" %d)  %-10s  %-10s  %-10s  %-10s   %-3d\n", i, tmp->comp, tmp->city, tmp->educ, tmp->spec, tmp->age);
		tmp = tmp->next;
		i++;
	}
	Vacancies* t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
	cout << "\n\n";
}




void updateAppInf(AppList* app) {
	FILE* list = fopen("Applicants.txt", "w+t");
	if (app == NULL) return;
	AppList* tmp = app->head;
	while (tmp != NULL) {
		fprintf(list, "%s %s %s %s %s\n", tmp->name, tmp->date, tmp->educ, tmp->city, tmp->salary);
		tmp = tmp->next;
	}
	AppList* t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
	fclose(list);
}




Vacancies* addVacDialog(Vacancies* vac) {
	char comp[20];
	char city[10];
	char educ[10];
	char spec[20];
	int age;
	Vacancies* tmp;
	printf("Write information about new vacancy:\n\n");
	printf("Company:");
	scanf("%s", comp);
	printf("City:");
	scanf("%s", city);
	printf("Required level of education:");
	scanf("%s", educ);
	printf("Speciality:");
	scanf("%s", spec);
	printf("Required age:");
	scanf("%d", &age);
	tmp = addVacancy(vac, comp, city, educ, spec, age);
	return tmp;
}


Vacancies* delVacDialog(Vacancies* vac) {
	if (vac == NULL) {
		return vac;
	}
	Vacancies* tmp = vac->head;
	printf("Choose the vacancy you want to delete:\n ");
	int i = 1;
	while (tmp != NULL) {
		printf("%d)  %s\n", i, tmp->comp);
		i++;
		tmp = tmp->next;
	}
	int ch;
	cin >> ch;
	if (ch > i) {
		cout << "ERROR!!!INCORRECT INPUT!!!";
		exit(1);
	}
	i = 1;
	tmp = vac->head;
	while (i != ch) {
		tmp = tmp->next;
		i++;
	}
	Vacancies* buf = vac;
	tmp = deleteVac(vac, tmp->comp);
	return tmp;
}




AppList* addAppDialog(AppList* app) {
	char name[20];
	char date[15];
	char educ[10];
	char city[10];
	char salary[10];
	printf("Write information about new applicant:\n\n");
	printf("Surname:");
	scanf("%s", name);
	printf("Date of birth(XX.XX.XXXX format):");
	scanf("%s", date);
	printf("Education:");
	scanf("%s", educ);
	printf("City:");
	scanf("%s", city);
	printf("Salary:(Dollars)");
	scanf("%s", salary);
	if (app == NULL) {
		app = (AppList*)malloc(sizeof(AppList));
		app = init(app, name, date, educ, city, salary);
	}
	else app = registry(app, name, date, educ, city, salary);
	return app;
}



Employers* delAppDialog(Employers* list) {
	if (list == NULL) {
		return list;
	}
	Employers* tmp = list->head;
	printf("Choose the employee you want to dismiss:\n ");
	int i = 1;
	while (tmp != NULL) {
		printf("%d)  %s\n", i, tmp->name);
		i++;
		tmp = tmp->next;
	}
	int ch;
	cin >> ch;
	if (ch > i) {
		cout << "ERROR!!!INCORRECT INPUT!!!";
		exit(1);
	}
	i = 1;
	tmp = list->head;
	while (i != ch) {
		tmp = tmp->next;
		i++;
	}
	Employers* buf = list;
	tmp = deleteEmp(buf, tmp->name);
	Vacancies* t;
	while (buf != NULL) {
		t = buf;
		buf = buf->next;
		free(t);
	}
	return tmp;
}



void updateVacInf(Vacancies* vac) {
	FILE* list = fopen("Vacancies.txt", "w+t");
	if (vac == NULL) {
		fprintf(list, "");
		return;
	}
	Vacancies* tmp = vac->head;
	while (tmp != NULL) {
		fprintf(list, "%s %s %s %s %d\n", tmp->comp, tmp->city, tmp->educ, tmp->spec, tmp->age);
		tmp = tmp->next;
	}
	Vacancies* t;
	while (tmp != NULL) {
		t = tmp;
		tmp = tmp->next;
		free(t);
	}
	fclose(list);
}
