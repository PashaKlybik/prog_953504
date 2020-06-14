#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Info //Заказ/предложение 
{
    char FIO[20];
    char phoneNumber[20];
    char district[30];
    char adress[40];
    int numberOfRooms;
    int area;
    float price;
}Info;

struct Node
{
    int ID;
    Info data;
    struct Node* next;
    struct Node* prev;
};

int IsFileRead = 0;

void Menu();
int CheckInput();
void ClearConsole();
Info* EnterData();
void OwnerMenu(struct Node**, struct Node**, struct Node**, struct Node**);
void BuyerMenu(struct Node**, struct Node**, struct Node**, struct Node**);
void SearchBuyer(struct Node*, struct Node*);
void ReadFromFile(struct Node**, struct Node**, char*);
void WriteToFile(struct Node*, struct Node*, char*);
void Add(struct Node**, struct Node**, struct Info*);
void PrintSupplyBase(struct Node*);
void PrintDemandBase(struct Node*);
void PrintContracts(struct Node*);
void PrintNode(struct Node*);
void GetContract(struct Node**, struct Node**, struct Node**, struct Node**);
void DeleteNode(struct Node*, struct Node**, struct Node**);
void FreeMemory(struct Node**, struct Node**, struct Node**);
void Registration(struct Node**, struct Node**, struct Node**, struct Node**);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Menu();

    system("pause");
    return 0;
}

void ClearConsole()
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
    SetConsoleCursorPosition(console, topLeft);
}

int CheckInput()
{
    int value; 

    do
    {
        rewind(stdin);
    } while (!scanf("%d", &value));

    return value;
}

void Menu()
{
    struct Node* SupplyBaseHead = NULL; // база предложений
    struct Node* SupplyBaseTail = NULL; // база предложений
    struct Node* DemandBaseHead = NULL; // база спроса
    struct Node* DemandBaseTail = NULL; // база спроса
    struct Node* conclAgreementHead = NULL; // заключенные договора
    struct Node* conclAgreementTail = NULL; // заключенные договора

    int count = 0;
    char* menu[5] = { "Список заявок на продажу", "Список заявок на покупку",
                      "Заключенные контракты", "Регистрация", "Выход" };

    while (1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("Меню\n");
        for (int i = 0; i < 5; ++i)
        {
            if (i == count)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                printf("%s\n", menu[i]);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                printf("%s\n", menu[i]);
            }
        }

        while (1)
        {
            char symbol = getch();

            if (symbol == 'w')
            {
                count -= 1;
                count = (count == -1) ? 4 : count;
                break;
            }
            else if (symbol == 's')
            {
                count += 1;
                count = (count == 5) ? 0 : count;
                break;
            }
            else if (symbol == 'f')
            {
                switch (count)
                {
                case 0:
                {
                    if (!IsFileRead)
                    {
                        ReadFromFile(&SupplyBaseHead, &SupplyBaseTail, "SupplyBase.csv");
                        IsFileRead = 1;
                    }
                    PrintSupplyBase(SupplyBaseHead);
                    GetContract(&conclAgreementHead, &conclAgreementHead, &SupplyBaseHead, &SupplyBaseTail);
                    break;
                }
                case 1:
                {
                    if (!DemandBaseHead)
                        ReadFromFile(&DemandBaseHead, &DemandBaseTail, "DemandBase.csv");
                    PrintDemandBase(DemandBaseHead);
                    break;
                }
                case 2:
                {
                    PrintContracts(conclAgreementHead);
                    break;
                }
                case 3:
                {
                    Registration(&SupplyBaseHead, &SupplyBaseTail, &DemandBaseHead, &DemandBaseTail);
                    break;
                }
                case 4:
                {
                    WriteToFile(SupplyBaseHead, SupplyBaseTail, "SupplyBase.csv");
                    WriteToFile(DemandBaseHead, DemandBaseTail, "DemandBase.csv");
                    FreeMemory(&SupplyBaseHead, &DemandBaseHead, &conclAgreementHead);
                    exit(1);
                }
                }
            }
        }
        ClearConsole();
        rewind(stdin);
    }
}

void Add(struct Node** pHead, struct Node** pTail, struct Info* init)
{
    struct Node* newElem = NULL;

    if (!(newElem = (struct Node*)calloc(1, sizeof(struct Node))))
    {
        printf("Ошибка: Нехватка памяти\n");
        return;
    }

    newElem->data = *init;

    //Если новый элемент первый в очереди
    if (*pTail == NULL || *pHead == NULL)
    {
        newElem->ID = 1;
        *pHead = newElem;
        *pTail = newElem;
    }
    else
    {
        newElem->prev = *pTail; //Для нового элемента хвост становиться предыдущим
        (*pTail)->next = newElem; //Для хвоста новый элемент становиться следующим
        *pTail = newElem; //Теперь хвост указывает на новый элемент
        newElem->ID = newElem->prev->ID + 1;
    }
}

void ReadFromFile(struct Node** pHead, struct Node** pTail, char* fileName)
{
    FILE* list = fopen(fileName, "rb");

    if (list == NULL) {
        printf("Ошибка открытия файла");
        return;
    }

    int code;
    //Счётчик слешей
    int seperate_count = 0;
    //Текущий символ
    char symbol;

    Info* init = (Info*)calloc(1, sizeof(Info));

    char* numberOfRooms_s = (char*)calloc(80, sizeof(char));
    char* area_s = (char*)calloc(80, sizeof(char));
    char* price_s = (char*)calloc(80, sizeof(char));

    //Считываем посимвольно из файла
    while ((code = getc(list)) != EOF)
    {
        symbol = (char)code;

        //Если встречаем слеш, меняем слеш-счётчик и пропускаем итерацию
        if (symbol == ';')
        {
            seperate_count++;
            continue;
        }
        if (symbol == '\n') {
            seperate_count = 0;

            init->numberOfRooms = atoi(numberOfRooms_s);
            init->area = atoi(area_s);
            init->price = atof(price_s);

            Add(&(*pHead), &(*pTail), init);

            free(init);

            memset(numberOfRooms_s, '\0', 80);
            memset(area_s, '\0', 80);
            memset(price_s, '\0', 80);

            Info* init = (Info*)calloc(1, sizeof(Info));

            continue;
        }

        //Переключатель по счётчику слешей
        switch (seperate_count)
        {
            //Пишем фамилию
        case 0:
            strcpy(init->FIO, strncat(init->FIO, &symbol, 1));
            break;
            //Имя
        case 1:
            strcpy(init->phoneNumber, strncat(init->phoneNumber, &symbol, 1));
            break;
            //Отчество
        case 2:
            strcpy(init->district, strncat(init->district, &symbol, 1));
            break;
            //Адрес
        case 3:
            strcpy(init->adress, strncat(init->adress, &symbol, 1));
            break;
        case 4:
            strcpy(numberOfRooms_s, strncat(numberOfRooms_s, &symbol, 1));
            break;
        case 5:
            strcpy(area_s, strncat(area_s, &symbol, 1));
            break;
        case 6:
            strcpy(price_s, strncat(price_s, &symbol, 1));
            break;
        }
    }

    free(init);
    fclose(list);
}

void WriteToFile(struct Node* pHead, struct Node* pTail, char* fileName)
{
    if (!pHead)
        return;

    FILE* list = fopen(fileName, "w+");

    if (list == NULL) {
        printf("Ошибка открытия файла");
        return;
    }

    struct Node* temp = pHead;

    while (temp)
    {
        fprintf(list, "%s;%s;%s;%s;%d;%d;%f\n",
            temp->data.FIO, temp->data.phoneNumber, temp->data.district,
            temp->data.adress, temp->data.numberOfRooms, temp->data.area,
            temp->data.price);

        temp = temp->next;
    }

    free(temp);
    fclose(list);
}

void PrintSupplyBase(struct Node* pHead)
{
    struct Node* temp = pHead;

    ClearConsole();

    printf("%-4s%-18s%-15s%-15s%-28s%-7s%-7s%-7s \n",
        "ID", "ФИО", "Номер Тел.", "Район", "Адресс",
        "Комнат", "Площ.", "Цена(USD)");

    while (temp)
    {
        printf("%-4d%-18s%-15s%-15s%-28s%-7d%-7d%-7.3f\n",
            temp->ID, temp->data.FIO, temp->data.phoneNumber, temp->data.district,
            temp->data.adress, temp->data.numberOfRooms, temp->data.area,
            temp->data.price);
        temp = temp->next;
    }

    return;
}

void PrintDemandBase(struct Node* pHead)
{
    struct Node* temp = pHead;

    ClearConsole();

    printf("%-18s%-15s%-20s%-28s%-7s%-7s%-7s \n",
        "ФИО", "Номер Тел.", "Желаемый Район", "Адресс",
        "Комнат", "Площ.", "Макс.Цена(USD)");

    while (temp)
    {
        printf("%-18s%-15s%-20s%-28s%-7d%-7d%-7.3f\n",
            temp->data.FIO, temp->data.phoneNumber, temp->data.district,
            temp->data.adress, temp->data.numberOfRooms, temp->data.area,
            temp->data.price);
        temp = temp->next;
    }

    return;
}

void PrintContracts(struct Node* contrHead)
{
    struct Node* temp = contrHead;

    ClearConsole();

    printf("%-20s", "Заключенные договора\n");

    while (temp)
    {
        printf("%-18s%-15s%-20s%-28s%-7d%-7d%-7.3f\n",
            temp->data.FIO, temp->data.phoneNumber, temp->data.district,
            temp->data.adress, temp->data.numberOfRooms, temp->data.area,
            temp->data.price);
        temp = temp->prev;
    }

    return;
}

void PrintNode(struct Node* temp)
{
    printf("%-18s%-15s%-20s%-28s%-7s%-7s%-7s \n",
        "ФИО", "Номер Тел.", "Желаемый Район", "Адресс",
        "Комнат", "Площ.", "Макс.Цена(USD)");

    printf("%-18s%-15s%-20s%-28s%-7d%-7d%-7.3f\n",
        temp->data.FIO, temp->data.phoneNumber, temp->data.district,
        temp->data.adress, temp->data.numberOfRooms, temp->data.area,
        temp->data.price);
}

void GetContract(struct Node** contractHead, struct Node** contractTail, struct Node** BaseHead, struct Node** BaseTail)
{
    printf("Хотите оформить договор(д/н)?\n");
    char answer;
    int ID;
    struct Node* temp = *BaseHead;
    Info* init = (Info*)calloc(1, sizeof(Info));

    while (1)
    {
        answer = getch();
        if (answer == 'н')
            return;
        else if (answer == 'д')
            break;
    }

    printf("Введите номер договора:\n");
    scanf("%d", &ID);

    while (temp)
    {
        if (temp->ID == ID)
        {
            *init = temp->data;
            Add(&(*contractHead), &(*contractTail), init);
            DeleteNode(temp, &(*BaseHead), &(*BaseTail));
            free(init);
            printf("Договор заключен!");
            break;
        }
        else if (!temp->next)
        {
            printf("Такого договора нет\n");
        }

        temp = temp->next;
    }
}

void Registration(struct Node** suppHead, struct Node** suppTail, struct Node** demHead, struct Node** demTail)
{
    int answer;

    ClearConsole();

    printf("Войти под видом:\n");
    printf("1. Собственника\n");
    printf("2. Покупатель\n");

    while (!scanf("%d", &answer) && (answer != 1 || answer != 2))
        rewind(stdin);

    if (answer == 1)
        OwnerMenu(&(*suppHead), &(*suppTail), &(*demHead), &(*demTail));
    else if (answer == 2)
        BuyerMenu(&(*suppHead), &(*suppTail), &(*demHead), &(*demTail));

}

Info* EnterData()
{
    Info* data = (Info*)malloc(sizeof(Info));

    //printf("ФИО:\n");
    gets(data->FIO);

    printf("ФИО:\n");
    gets(data->FIO);

    printf("Номер телефона:\n");
    gets(data->phoneNumber);

    printf("Район:\n");
    gets(data->district);

    printf("Адрес:\n");
    gets(data->adress);

    printf("Количество комнат:\n");
    data->numberOfRooms = CheckInput();

    printf("Площадь:\n");
    data->area = CheckInput();

    printf("Желаемая цена(USD):\n");
    scanf("%f", &data->price);

    return data;
}

void BuyerMenu(struct Node** supHead, struct Node** supTail, struct Node** demHead, struct Node** demTail)
{
    int answer;
    ClearConsole();
    printf("1. Оставить заявку\n");
    printf("2. Поиск жилья\n");

    answer = CheckInput();

    if (answer == 1)
    {
        //system("cls");
        Info* init = EnterData();
        Add(&(*demHead), &(*demTail), init);

        //system("cls");
        printf("Предложение создано!");

        free(init);
    }
    else if (answer == 2)
        SearchBuyer(*supHead, *supTail);
}

void OwnerMenu(struct Node** supHead, struct Node** supTail, struct Node** demHead, struct Node** demTail)
{
    int answer;
    ClearConsole();
    printf("1. Создать предложение\n");
    printf("2. Поиск потенциалного покупателя\n");

    answer = CheckInput();

    if (answer == 1)
    {
        //system("cls");
        Info* init = EnterData();
        Add(&(*supHead), &(*supTail), init);

        //system("cls");
        printf("Предложение создано!");

        free(init);
    }
    else if (answer == 2)
        SearchBuyer(*demHead, *demTail);

}

void SearchBuyer(struct Node* demHead, struct Node* demTail)
{
    char* district = (char*)malloc(sizeof(char));
    float sum;
    int area;

    printf("Какой предпочитаемый район\n");
    scanf("%s", district);
    printf("Площадь\n");
    area = CheckInput();
    printf("Сумма:\n");
    scanf("%f", &sum);

    struct Node* temp = demHead; // было demHead

    printf("Все сопадающие заказы\n");

    while (temp)
    {
        if (!strcmp(temp->data.district, district) ||
            (area > temp->data.area - 5 && area < temp->data.area + 5) ||
            (sum > temp->data.price - 5 && sum < temp->data.price + 5))
            PrintNode(temp);

        temp = temp->next;
    }
    
    //free(district);////
}

void DeleteNode(struct Node* del, struct Node** Head, struct Node** Tail)
{
    struct Node* temp = *Head;

    while (temp->ID != del->ID)
        temp = temp->next;

    if (!temp->prev)
    {
        *Head = (*Head)->next;
        free(temp);
    }
    else if (!temp->next)
    {
        *Tail = (*Tail)->prev;
        free(temp);
    }
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }

    (*Head)->ID = 1;
    temp = (*Head)->next;

    while (temp)
    {
        temp->ID = temp->prev->ID + 1;
        temp = temp->next;
    }
}

void FreeMemory(struct Node** suppHead, struct Node** demHead, struct Node** cotractHead)
{
    struct Node* temp1;

    while (*suppHead)
    {
        temp1 = *suppHead;
        *suppHead = (*suppHead)->next;
        free(temp1);
    }

    while (*demHead)
    {
        temp1 = *demHead;
        *demHead = (*demHead)->next;
        free(temp1);
    }

    while (*cotractHead)
    {
        temp1 = *cotractHead;
        *cotractHead = (*cotractHead)->next;
        free(temp1);
    }
}
