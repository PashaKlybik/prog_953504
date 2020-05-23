#include "consumers_menu.h"

void showConsumersMenu(CarList **car_list, ConsumerList **consumer_list)
{
    if (*consumer_list == NULL)
    {
        *consumer_list = malloc(sizeof **consumer_list);
        **consumer_list = (ConsumerList) { .first = NULL, .last = NULL, .size = 0 };
    }

    while (1)
    {
        system("cls");
        COORD marker = { .X = 0, .Y = 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), marker);
        print("Consumers\n", 1);
        marker.Y = 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), marker);
        print("\t", 0); print("View database\n", 1);
        print("\t", 0); print("Load from file\n", 0);
        print("\t", 0); print("Dump to file\n", 0);
        print("\t", 0); print("Add new data\n", 0);
        print("\t", 0); print("Remove existing data\n", 0);
        print("\t", 0); print("Select car\n", 0);
        print("\t", 0); print("Make order\n", 0);
        print("\t", 0); print("Search\n", 0);

        while (1)
        {
            int action = getch();
            if (action == UP_ARROW)
                cons_scrollUp(&marker);
            if (action == DOWN_ARROW)
                cons_scrollDown(&marker);
            if (action == ENTER)
            {
                system("cls");
                fflush(stdin);
                switch (marker.Y)
                {
                    case 1:
                        print("Consumers >> View database", 1);
                        cons_showDatabase(*consumer_list);
                        break;
                    case 2:
                        print("Consumers >> Load from file", 1);
                        cons_loadFromFile(*consumer_list);
                        break;
                    case 3:
                        print("Cars >> Dump to file", 1);
                        cons_dumpToFile(*consumer_list);
                        break;
                    case 4:
                        print("Consumers >> Add new data", 1);
                        printf("\nEnter new data.");
                        addConsumer(*consumer_list, scanConsumerInfo());
                        printf("\nInput data is succesfully recorded to temporary memory!");
                        break;
                    case 5:
                        print("Consumers >> Remove existing data", 1);
                        printf("\nEnter approproate information to remove: ");
                        if (removeConsumer(*consumer_list, (*consumer_list)->first, scanConsumerInfo()))
                            printf("\nSomething went wrong... Check if input data is correct and retry operation.");
                        else
                            printf("\nSuccessfully removed.");
                        break;
                    case 6:
                        print("Consumers >> Select car", 1);
                        if (*car_list != NULL)
                        {
                            if (!cons_select(*car_list, *consumer_list))
                                printf("\nOrder is successfully made.");
                            else
                                printf("\nSomething went wrong... Have you already made order?");
                        }
                        else
                            printf("\nCar database is empty now.");
                        break;
                    case 7:
                        print("Cars >> Make order", 1);
                        if (*car_list != NULL)
                        {
                            printf("\nEnter consumer's data: ");
                            Consumer *consumer = getConsumer(*consumer_list, (*consumer_list)->first, scanConsumerInfo());
                            if (!buyCar(*consumer_list, *car_list, consumer->request, consumer))
                                printf("\nOrder is successfully made.");
                            else
                                printf("\nSomething went wrong... Have you selected car?");
                        }
                        else
                            printf("\nCar database is empty now.");
                        break;
                    case 8:
                        print("Consumers >> Search", 1);
                        cons_search(*consumer_list);
                        break;
                }
                while (getch() != ESCAPE);
                break;
            }
            if (action == ESCAPE)
                return;
        }
    }
}

void cons_scrollUp(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cons_demark(marker->Y);
    if (marker->Y == 1)
        marker->Y = 8;
    else
        marker->Y--;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cons_mark(marker->Y);
}

void cons_scrollDown(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cons_demark(marker->Y);
    if (marker->Y == 8)
        marker->Y = 1;
    else
        marker->Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cons_mark(marker->Y);
}

void cons_mark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("View database\n", 1); break;
        case 2: print("\r\t", 0); print("Load from file\n", 1); break;
        case 3: print("\r\t", 0); print("Dump to file\n", 1); break;
        case 4: print("\r\t", 0); print("Add new information\n", 1); break;
        case 5: print("\r\t", 0); print("Remove existing information\n", 1); break;
        case 6: print("\r\t", 0); print("Select car\n", 1); break;
        case 7: print("\r\t", 0); print("Make order\n", 1); break;
        case 8: print("\t", 0); print("Search\n", 1); break;
    }
}

void cons_demark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("View database\n", 0); break;
        case 2: print("\r\t", 0); print("Load from file\n", 0); break;
        case 3: print("\r\t", 0); print("Dump to file\n", 0); break;
        case 4: print("\r\t", 0); print("Add new information\n", 0); break;
        case 5: print("\r\t", 0); print("Remove existing information\n", 0); break;
        case 6: print("\r\t", 0); print("Select car\n", 0); break;
        case 7: print("\r\t", 0); print("Make order\n", 0); break;
        case 8: print("\t", 0); print("Search\n", 0); break;
    }
}

void cons_showDatabase(ConsumerList *consumer_list)
{
    if (consumer_list->size != 0)
    {
        struct ConsumerListNode *current = consumer_list->first;
        while (current != NULL)
        {
            printf("\nName: %s | Contact: %d | Finanses: %.3f EUR", current->value.name, current->value.contacts, (double)current->value.finances);
            printf("\nREQUEST.");
            if (current->value.request != NULL)
            {
                printf("\nModel: %s | ", current->value.request->model);
                if (current->value.request->state == NEW)
                    printf("State: new | ");
                else
                    printf("State: used | ");
                    printf("YEAR: %d\nENGINE CAPACITY: %d qubic cm | POWER: %d hp | MILEAGE: %d km\nPRICE: %.3f EUR", current->value.request->year,
                           current->value.request->engine_capacity, current->value.request->power, current->value.request->mileage,
                           (double)current->value.request->price);
            }
            else
                printf("\nnone");
            printf("\n______________________________________________________________\n\n");
            current = current->next;
        }
    }
    else
        printf("\nEmpty. Have you loaded information?");
}

void cons_loadFromFile(ConsumerList *consumer_list)
{
    printf("\nPath to file (.con extension) (200 characters - maximum): ");
    char path[200];
    fgets(path, 200, stdin);
    path[strlen(path) - 1] = '\0';
    if (loadConsumerBase(consumer_list, path))
        printf("\nSomething went wrong... Check if path & file extension are correct and retry operation.");
    else
        printf("\nSuccessfully loaded.");
}

void cons_dumpToFile(ConsumerList *consumer_list)
{
    printf("\nPath to target directory & file name (200 characters - maximum): ");
    char path[200];
    fgets(path, 200, stdin);
    path[strlen(path) - 1] = '\0';
    if (dumpConsumerBase(consumer_list, path))
        printf("\nSomething went wrong... Check if path is correct and retry operation.");
    else
        printf("\nSuccessfully dumped.");
}

Consumer scanConsumerInfo(void)
{
    Consumer new_consumer;
    new_consumer.request = NULL;
    printf("\nName & surname (100 characters - maximum, replace space characters with '_'): ");
    scanf("%s", new_consumer.name);
    rewind(stdin);
    printf("\nContacts: ");
    while (scanf("%d", &new_consumer.contacts) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nContacts: ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    printf("\nFinances: (EUR) ");
    while (scanf("%f", &new_consumer.finances) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nFinances: (EUR) ");
        rewind(stdin);
        continue;
    }
    return new_consumer;
}

int cons_select(CarList *cars, ConsumerList *consumer_list)
{
    printf("\nEnter consumer's data: ");
    Consumer consumer = scanConsumerInfo();
    printf("\nEnter information about your order: ");
    CarUnit order = scanCarInfo();
    CarUnit *in_stock = selectCar(cars, order);
    if (addOrder(consumer_list, consumer, in_stock))
    {
        consumer.request = NULL; return 1;
    }
    return 0;
}

void cons_search(ConsumerList *consumer_list)
{
    ConsumerList *target = NULL;
    char field_value[20];
    printf("\nValue to search: (20 characters - maximum, replace space characters with '_'): ");
    fgets(field_value, 20, stdin);
    field_value[strlen(field_value) - 1] = '\0';

    while (1)
    {
        printf("\nSearch by field:\nname(1), contacts(2), finances(3) ");
        int field;
        rewind(stdin);
        scanf("%d", &field);
        switch (field)
        {
            case 1: target = searchConsumers(consumer_list, NAME, field_value); break;
            case 2: target = searchConsumers(consumer_list, CONTACTS, field_value); break;
            case 3: target = searchConsumers(consumer_list, FINANCES, field_value); break;
            default: printf("\nSomething went wrong... Check if path is correct and retry operation."); continue;
        }
        break;
    }
    system("cls");
    print("Consumers >> Search", 1);
    if (target != NULL)
    {
        cons_showDatabase(target);
        deallocConsumerList(target);
    }
    else
        printf("\nNo result.");
}
