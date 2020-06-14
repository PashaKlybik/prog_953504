#ifndef BOOK_STORE_BOOKSTORE_H
#define BOOK_STORE_BOOKSTORE_H

#include <stdio.h>
#include <iostream>
#include "Context.h"
#include "Controller.h"

class Bookstore {
public:
    void start() {
        auto ctx = new Context();
        auto *controller = new Controller(*ctx);
        std::cout << welcomeScreen() << std::endl;
        std::cout << controller->exec("menu") << std::endl;
        std::string cmd;
        for(;;) {
            std::cout << "Введите команду" << std::endl;
            std::getline(std::cin >> std::ws, cmd);
            if (cmd == "exit")
                break;

            std::cout << controller->exec(cmd) << endl;
        }
    }

private:
    Context *ctx;

    const string welcomeScreen() {
        return "Введите команду для продолжения:";
    }
};


#endif //BOOK_STORE_BOOKSTORE_H
