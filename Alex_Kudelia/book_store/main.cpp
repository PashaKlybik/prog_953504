#include <iostream>
#include <windows.h>
#include "core/Bookstore.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Bookstore *b = new Bookstore();
    b->start();
    return 0;
}
