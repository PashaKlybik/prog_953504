#ifndef BOOK_STORE_CONTAINER_H
#define BOOK_STORE_CONTAINER_H


#include <utility>
#include "map"
#include "Command.h"
#include "MenuCommand.h"
#include "../Context.h"
#include "AllBooks.h"
#include "AddBook.h"
#include "CreateOrder.h"
#include "AllOrders.h"
#include "Report.h"

class Container {
public:
    explicit Container(const Context &ctx) {
        string showAllBooks = "all-books";
        Command *showAllBooksCommand = new AllBooks(ctx);
        commands.insert(pair<string, Command *>(showAllBooks, showAllBooksCommand));

        string addBook = "add-book";
        Command *addBookCommand = new AddBook(ctx);
        commands.insert(pair<string, Command *>(addBook, addBookCommand));

        string createOrder = "create-order";
        Command *createOrderCommand = new CreateOrder(ctx);
        commands.insert(pair<string, Command *>(createOrder, createOrderCommand));

        string allOrders = "all-orders";
        Command *showAllOrdersCommand = new AllOrders(ctx);
        commands.insert(pair<string, Command *>(allOrders, showAllOrdersCommand));

        string report = "report";
        Command *reportCommand = new Report(ctx);
        commands.insert(pair<string, Command *>(report, reportCommand));
    }

    Command *getCmd(Query q) {
        if (commands.count(q.getCmd()) == 0) {
            string allCommands;
            for (auto &it:commands) {
                allCommands += it.second->toString();
                allCommands += "\n";
            }
            allCommands += "exit : Выход";

            return new MenuCommand(allCommands);
        }

        return (*commands.find(q.getCmd())).second;
    }

private:
    map<string, Command *> commands;
};


#endif //BOOK_STORE_CONTAINER_H
