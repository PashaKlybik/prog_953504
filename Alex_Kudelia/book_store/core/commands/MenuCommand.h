#ifndef BOOK_STORE_MENUCOMMAND_H
#define BOOK_STORE_MENUCOMMAND_H

#include "Command.h"

class MenuCommand : public Command {
public:
    MenuCommand(string commands) {
        this->commands = commands;
    }

    string exec(Query q) override {
        return commands;
    }

    string toString() override {
        return "Введите команду";
    }

private:
    string commands;
};


#endif //BOOK_STORE_MENUCOMMAND_H
