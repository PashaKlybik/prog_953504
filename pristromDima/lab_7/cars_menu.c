#include "cars_menu.h"

void showCarsMenu(CarList **car_list)
{
    if (*car_list == NULL)
    {
        *car_list = malloc(sizeof **car_list);
        **car_list = (CarList) { .first = NULL, .last = NULL, .size = 0, .sold = 0, .obtained = 0, .income = 0.0f };
    }

    while (1)
    {
        system("cls");
        COORD marker = { .X = 0, .Y = 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), marker);
        print("Cars\n", 1);
        marker.Y = 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), marker);
        print("\t", 0); print("View database\n", 1);
        print("\t", 0); print("Load from file\n", 0);
        print("\t", 0); print("Dump to file\n", 0);
        print("\t", 0); print("Add new data\n", 0);
        print("\t", 0); print("Remove existing data\n", 0);
        print("\t", 0); print("Search\n", 0);
        print("\t", 0); print("Make order for new car\n", 0);
        print("\t", 0); print("Show statistics\n", 0);

        while (1)
        {
            int action = getch();
            if (action == UP_ARROW)
                cars_scrollUp(&marker);
            if (action == DOWN_ARROW)
                cars_scrollDown(&marker);
            if (action == ENTER)
            {
                system("cls");
                fflush(stdin);
                switch (marker.Y)
                {
                    case 1:
                        print("Cars >> View database", 1);
                        cars_showDatabase(*car_list);
                        if ((*car_list)->size != 0)
                            print("Sort by: [Y] - year, [P] - price", 1);
                        break;
                    case 2:
                        cars_loadFromFile(*car_list);
                        break;
                    case 3:
                        cars_dumpToFile(*car_list);
                        break;
                    case 4:
                        print("Cars >> Add new data", 1);
                        printf("\nEnter new data.");
                        addCar(*car_list, scanCarInfo());
                        printf("\nInput data is succesfully recorded to temporary memory!");
                        break;
                    case 5:
                        print("Cars >> Remove existing data", 1);
                        printf("\nEnter approproate information to remove: ");
                        if (removeCar(*car_list, (*car_list)->first, scanCarInfo()))
                            printf("\nSomething went wrong... Check if input data is correct and retry operation.");
                        else
                            printf("\nSuccessfully removed.");
                        break;
                    case 6:
                        print("Cars >> Search", 1);
                        cars_search(*car_list);
                        break;
                    case 7:
                        print("Cars >> Make order for new car | [F1] - more information, any another key - continue", 1);
                        if (getch() == 0)
                            if (getch() == F1)
                                getHelp();
                        system("cls");
                        print("Cars >> Make order for new car", 1);
                        obtainCar(*car_list, scanCarInfo());
                        printf("\nCar is successfully ordered.");
                        break;
                    case 8:
                        print("Cars >> Show statistics", 1);
                        printf("\nSold: %d\nObtained: %d\nClear income: %.3f EUR", (*car_list)->sold, (*car_list)->obtained, (double)(*car_list)->income);
                        break;
                }
                if (marker.Y == 1 && (*car_list)->size != 0)
                {
                    while (1)
                    {
                        int sort = getch();
                        if (sort == Y_KEY)
                        {
                            sortByField(*car_list, YEAR);
                            system("cls");
                            print("Cars >> View database", 1);
                            cars_showDatabase(*car_list);
                            print("Sort by: [Y] - year, [P] - price", 1);
                            continue;
                        }
                        if (sort == P_KEY)
                        {
                            sortByField(*car_list, PRICE);
                            system("cls");
                            print("Cars >> View database", 1);
                            cars_showDatabase(*car_list);
                            print("Sort by: [Y] - year, [P] - price", 1);
                            continue;
                        }
                        if (sort == ESCAPE)
                            break;
                    }
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

void cars_scrollUp(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cars_demark(marker->Y);
    if (marker->Y == 1)
        marker->Y = 8;
    else
        marker->Y--;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cars_mark(marker->Y);
}

void cars_scrollDown(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cars_demark(marker->Y);
    if (marker->Y == 8)
        marker->Y = 1;
    else
        marker->Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    cars_mark(marker->Y);
}

void cars_mark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("View database\n", 1); break;
        case 2: print("\r\t", 0); print("Load from file\n", 1); break;
        case 3: print("\r\t", 0); print("Dump to file\n", 1); break;
        case 4: print("\r\t", 0); print("Add new data\n", 1); break;
        case 5: print("\r\t", 0); print("Remove existing data\n", 1); break;
        case 6: print("\r\t", 0); print("Search\n", 1); break;
        case 7: print("\r\t", 0); print("Make order for new car\n", 1); break;
        case 8: print("\t", 0); print("Show statistics\n", 1); break;
    }
}

void cars_demark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("View database\n", 0); break;
        case 2: print("\r\t", 0); print("Load from file\n", 0); break;
        case 3: print("\r\t", 0); print("Dump to file\n", 0); break;
        case 4: print("\r\t", 0); print("Add new data\n", 0); break;
        case 5: print("\r\t", 0); print("Remove existing data\n", 0); break;
        case 6: print("\r\t", 0); print("Search\n", 0); break;
        case 7: print("\r\t", 0); print("Make order for new car\n", 0); break;
        case 8: print("\t", 0); print("Show statistics\n", 0); break;
    }
}

void cars_showDatabase(CarList *car_list)
{
    if (car_list->size != 0)
    {
        struct CarListNode *current = car_list->first;
        while (current != NULL)
        {
            printf("\nModel: %s | ", current->value.model);
            if (current->value.state == NEW)
                printf("State: new | ");
            else
                printf("State: used | ");
            printf("YEAR: %d\nENGINE CAPACITY: %d qubic cm | POWER: %d hp | MILEAGE: %d km\nPRICE: %.3f EUR", current->value.year,
                   current->value.engine_capacity, current->value.power, current->value.mileage, (double)current->value.price);
            printf("\n______________________________________________________________\n\n");
            current = current->next;
        }
    }
    else
        printf("\nEmpty. Have you loaded information?");
}

CarUnit scanCarInfo()
{
    CarUnit new_car;
    printf("\nModel (20 characters - maximum, replace space characters with '_'): ");
    scanf("%s", new_car.model);
    rewind(stdin);
    printf("\nState: new(1) or used(2): ");
    while (1)
    {
        int state;
        scanf("%d", &state);
        switch (state)
        {
            case 1: new_car.state = NEW; break;
            case 2: new_car.state = USED; break;
            default:
                printf("\nSomething went wrong... Is your input correct?\nState: new(1) or used(2)? ");
                rewind(stdin);
                continue;
        }
        break;
    }
    rewind(stdin);
    printf("\nYear: ");
    while (scanf("%d", &new_car.year) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nYear: ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    printf("\nEngine capacity: (qubic cm) ");
    while (scanf("%d", &new_car.engine_capacity) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nEngine capacity: (qubic cm) ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    printf("\nMileage: (km) ");
    while (scanf("%d", &new_car.mileage) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nMileage: (km) ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    printf("\nPower: (hp) ");
    while (scanf("%d", &new_car.power) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nPower: (hp) ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    printf("\nPrice: (EUR) ");
    while (scanf("%f", &new_car.price) != 1)
    {
        printf("\nSomething went wrong... Is your input correct?\nPrice: (€) ");
        rewind(stdin);
        continue;
    }
    rewind(stdin);
    return new_car;
}

void cars_loadFromFile(CarList *car_list)
{
    print("Cars >> Load from file", 1);
    printf("\nPath to file (.car extension) (200 characters - maximum): ");
    char path[200];
    fgets(path, 200, stdin);
    path[strlen(path) - 1] = '\0';
    if (loadCarBase(car_list, path))
        printf("\nSomething went wrong... Check if path & file extension are correct and retry operation.");
    else
        printf("\nSuccessfully loaded.");
}

void cars_dumpToFile(CarList *car_list)
{
    print("Cars >> Dump to file", 1);
    printf("\nPath to target directory & file name (200 characters - maximum): ");
    char path[200];
    fgets(path, 200, stdin);
    path[strlen(path) - 1] = '\0';
    if (dumpCarBase(car_list, path))
        printf("\nSomething went wrong... Check if path is correct and retry operation.");
    else
        printf("\nSuccessfully dumped.");
}

void cars_search(CarList *car_list)
{
    CarList *target = NULL;
    char field_value[20];
    printf("\nValue to search: (20 characters - maximum, replace space characters with '_'): ");
    fgets(field_value, 20, stdin);
    field_value[strlen(field_value) - 1] = '\0';

    while (1)
    {
        printf("\nSearch by field:\nmodel(1), state(2), year(3), engine capacity(4), power(5), mileage(6), price(7) ");
        int field;
        rewind(stdin);
        scanf("%d", &field);
        switch (field)
        {
            case 1: target = searchCars(car_list, MODEL, field_value); break;
            case 2:
                if (!strcmp(field_value, "new"))
                    target = searchCars(car_list, STATE, "0");
                if (!strcmp(field_value, "used"))
                    target = searchCars(car_list, STATE, "1");
            break;
            case 3: target = searchCars(car_list, YEAR, field_value); break;
            case 4: target = searchCars(car_list, ENGINE_CAPACITY, field_value); break;
            case 5: target = searchCars(car_list, POWER, field_value); break;
            case 6: target = searchCars(car_list, MILEAGE, field_value); break;
            case 7: target = searchCars(car_list, PRICE, field_value); break;
            default: printf("\nSomething went wrong... Check if path is correct and retry operation."); continue;
        }
        break;
    }
    system("cls");
    print("Cars >> Search", 1);
    if (target != NULL)
    {
        cars_showDatabase(target);
        deallocCarList(target);
    }
    else
        printf("\nNo result.");
}

void getHelp(void)
{
    system("cls");
    print("Cars >> Make order for new car >> Help", 1);
    printf("\nCost of the car delivery from Europe averages 250 EUR for the company.\n");
    printf("Also customs clearing price depending on engine capacity and \"age\" of the car is included to final cost:\n");
    printf("- 3 years or less – 0.6 EUR per 1 qubic cm; \n");
    printf("- from 3 to 10 years inclusive: with a cylinder capacity engine\n to 2500 qubic cm - 0.35 EUR for 1 qubic cm & 2500 cm.cub. and more - 0.6 EUR per 1 qubic cm;\n");
    printf("- from 10 to 14 years - 0.6 EUR per 1 qubic cm;\n");
    printf("- 14 years or more - 2 EUR per 1 qubic cm.\n");
    printf("The final price is set to ensure the company 15 %% profit.");
    while (1)
    {
        if (getch() == ESCAPE)
            break;
    }
}
