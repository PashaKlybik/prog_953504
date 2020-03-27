#include <iostream>
#include <math.h>
#include <ctime>

#define SIZE 11


void printMaze(int** maze) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int getClose(int** maze, int direction, int posX, int posY) { // вычислить ближнего своего
    switch (direction) {
    case 1:
        if (maze[posY - 1][posX] == 0 || maze[posY - 1][posX] == 1) return maze[posY - 1][posX];
        else return 2; // типо ошибка, типо такого нет
        break;
    case 2:
        if (maze[posY][posX + 1] == 0 || maze[posY][posX + 1] == 1) return maze[posY][posX + 1];
        else return 2;
        break;
    case 3:
        if (maze[posY + 1][posX] == 0 || maze[posY + 1][posX] == 1) return maze[posY + 1][posX];
        else return 2;
        break;
    case 4:
        if (maze[posY][posX - 1] == 0 || maze[posY][posX - 1] == 1) return maze[posY][posX - 1];
        else return 2;
        break;
    default:
        return 2;
        break;
    }
}

void step(int** maze, int direction, int& posX, int& posY) { // direction: 1 - вверх и по часовой до 4
    if (getClose(maze, direction, posX, posY) == 2 || getClose(maze, direction, posX, posY) == 1) return;


    switch (direction) {
    case 1:
        posY--;
        break;
    case 2:
        posX++;
        break;
    case 3:
        posY++;
        break;
    case 4:
        posX--;
        break;
    default:
        return;
        break;
    }

    std::cout << "Step: x = " << posX << "; y = " << posY << std::endl;
}

bool onBorder(int** maze, int posX, int posY) {
    if (posX == 0 || posX == SIZE - 1 || posY == 0 || posY == SIZE - 1)
        return true;

    return false;
}

int main() {
    srand(time(NULL)); // чтобы rand() не повторялась

    const int startPosX = 3;
    const int startPosY = 5;
    int posX = startPosX;
    int posY = startPosY;

    int steps = 0;

    int** maze = new int* [SIZE]; // массив лабиринта
    for (int i = 0; i < SIZE; i++) {
        maze[i] = new int[SIZE];
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = round(rand() % 2);
        }
    }

    maze[startPosY][startPosX] = 5; // похожа на букву 's' - "start"

    printMaze(maze);


    // правило лабиринта - всегда или по одной стороне. Так как мы любим
    // ходить налево, туда и пойдём. Шучу, я не буду писать этот ужасный
    // алгоритм) мы просто пойдём куда глаза глядят


    if (maze[posY + 1, posX] == 0) {
        step(maze, 3, posX, posY);
        system("pause");
        return 0; // если с первого шага победили
    }


    if (maze[posY - 1, posX] == 0) {
        step(maze, 1, posX, posY);
        system("pause");
        return 0; // если с первого шага победили
    }

    for (int i = 1; i < 4; i++) {
        step(maze, i, posX, posY); // первый шаг в любую сторону кроме левой
    }

    while (!onBorder(maze, posX, posY)) {
        step(maze, round(rand() % 4 + 1), posX, posY);
        steps++;
        if (steps > SIZE* SIZE* SIZE) {
            system("cls");
            printMaze(maze);
            system("pause");
            return 0;
        }
    }


    system("pause");
    return 0;
}