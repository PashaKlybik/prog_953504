#ifndef BOOK_STORE_CREATEORDER_H
#define BOOK_STORE_CREATEORDER_H

#include "map"
#include "Command.h"
#include "../../utils/Helpers.h"

class CreateOrder : public Command {
public:
    explicit CreateOrder(Context ctx) {
        this->ctx = std::move(ctx);
    }

    string exec(Query q) override {
        std::vector<std::map<std::string, std::string>> bookCount;
        BookService bookService = ctx.getBookService();
        OrderService orderService = ctx.getOrderService();

        for (;;) {
            std::string bookID;
            while (bookID == "") {
                std::cout << "Введите ID книги: " << std::endl;
                std::getline(std::cin, bookID);

                if (!Helpers::isNumber(bookID)) {
                    bookID = "";
                } else {
                    try {
                        Book book = bookService.find(std::stol(bookID));
                    } catch (const std::exception& e) {
                        std::cout << "Книги с ID: " << bookID << " не существует" << std::endl;
                        bookID = "";
                    }
                }
            }

            std::string count;
            while (count == "") {
                std::cout << "Введите количество: " << std::endl;
                std::getline(std::cin, count);
                if (!Helpers::isNumber(count)) {
                    count = "";
                } else {
                    Book book = bookService.find(std::stol(bookID));
                    if (std::stoi(count) > book.getCount()) {
                        std::cout << "Такого кол-ва нет на складе" << std::endl;
                        count = "";
                    }
                }
            }

            std::map<std::string, std::string> bc = {
                    {"bookID", bookID},
                    {"count", count}
            };

            bookCount.push_back(bc);

            std::string continueShopping;
            while (continueShopping == "") {
                std::cout << "Добавить еще книгу? (да/нет) : " << std::endl;
                std::getline(std::cin, continueShopping);
            }

            if (continueShopping == "да") {
                continueShopping = "";
                continue;
            } else {
                break;
            }
        }

        orderService.create(bookCount);

        return "Заказ успешно добавлен";
    }

    string toString() override {
        return "create-order : Создать заказ";
    }

private:
    Context ctx;
};


#endif //BOOK_STORE_CREATEORDER_H
