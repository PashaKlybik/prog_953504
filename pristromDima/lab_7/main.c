#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "cars_menu.h"
#include "consumers_menu.h"
#include "service.h"

#define UP_ARROW    72
#define DOWN_ARROW  80
#define ENTER       13
#define ESCAPE      27
#define YES         121
#define NO          110

void showIntro(void);
void about(void);

void scrollUp(COORD *marker);
void scrollDown(COORD *marker);

void mark(int line);
void demark(int line);


int main()
{
    showIntro();
    CONSOLE_CURSOR_INFO info = { 100, FALSE };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    CarList *car_list = NULL;
    ConsumerList *consumer_list = NULL;

    Begin:
    while (1)
    {
        system("cls");
        print("ATLANT-M DATABASE SOFTWARE\t\n", 1);

        COORD marker = { .X = 0, .Y = 1 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), marker);

        print("\t", 0); print("Cars\n", 1);
        print("\t", 0); print("Consumers\n", 0);
        print("\t", 0); print("About software\n", 0);
        print("\t", 0); print("Exit\n", 0);

        while (1)
        {
            int action = getch();
            if (action == UP_ARROW)
                scrollUp(&marker);
            if (action == DOWN_ARROW)
                scrollDown(&marker);

            if (action == ENTER)
            {
                switch (marker.Y)
                {
                    case 1:
                        showCarsMenu(&car_list);
                        break;
                    case 2:
                        showConsumersMenu(&car_list, &consumer_list);
                        break;
                    case 3:
                        about();
                        break;
                    case 4:
                        printf("Unsaved data will be lost. Are you sure? Yes[y] | No[n]");
                        while (1)
                        {
                            int action = getch();
                            if (action == YES)
                                break;
                            if (action == NO)
                                goto Begin;
                        }
                        deallocCarList(car_list);
                        deallocConsumerList(consumer_list);
                        exit(EXIT_SUCCESS);
                }
                break;
            }
        }
    }
}

void scrollUp(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    demark(marker->Y);
    if (marker->Y == 1)
        marker->Y = 4;
    else
        marker->Y--;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    mark(marker->Y);
}

void scrollDown(COORD *marker)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    demark(marker->Y);
    if (marker->Y == 4)
        marker->Y = 1;
    else
        marker->Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *marker);
    mark(marker->Y);
}

void mark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("Cars\n", 1); break;
        case 2: print("\r\t", 0); print("Consumers\n", 1); break;
        case 3: print("\r\t", 0); print("About software\n", 1); break;
        case 4: print("\r\t", 0); print("Exit\n", 1); break;
    }
}

void demark(int line)
{
    switch (line)
    {
        case 1: print("\r\t", 0); print("Cars\n", 0); break;
        case 2: print("\r\t", 0); print("Consumers\n", 0); break;
        case 3: print("\r\t", 0); print("About software\n", 0); break;
        case 4: print("\r\t", 0); print("Exit\n", 0); break;
    }
}

void showIntro()
{
    printf("\n\n\n\n\n\n");
    printf("\t\t\t"); printf("       _______ _               _   _ _______            __  __ \n");
    printf("\t\t\t"); printf("    /\\|__   __| |        /\\   | \\ | |__   __|          |  \\/  |\n");
    printf("\t\t\t"); printf("   /  \\  | |  | |       /  \\  |  \\| |  | |     ______  | \\  / |\n");
    printf("\t\t\t"); printf("  / /\\ \\ | |  | |      / /\\ \\ | . ` |  | |    |______| | |\\/| |\n");
    printf("\t\t\t"); printf(" / ____ \\| |  | |____ / ____ \\| |\\  |  | |             | |  | |\n");
    printf("\t\t\t"); printf("/_/    \\_\\_|  |______/_/    \\_\\_| \\_|  |_|             |_|  |_|\n");
    printf("\n\t\t\t\t\t\t"); printf("PRESS ANY KEY");
    getch();
}

void about()
{
    system("cls");
    print("About software", 1);
    printf("\nATLANT-M TECHNOLOGINES LTD., 2020\nDatabase software for managing\nVersion: 1.0");
    while (1)
    {
        int action = getch();
        if (action == ESCAPE)
            break;
    }

}
