#ifndef BOOK_STORE_ADDBOOK_H
#define BOOK_STORE_ADDBOOK_H

#include "Command.h"
#include "../../utils/Helpers.h"

class AddBook : public Command {
public:
    explicit AddBook(Context ctx) {
        this->ctx = std::move(ctx);
    }

    string exec(Query q) override {
        std::string author;
        while (author == "") {
            std::cout << "Введите автора: " << std::endl;
            std::getline(std::cin, author);
        }

        std::string name;
        while (name == "") {
            std::cout << "Введите название книги: " << std::endl;
            std::getline(std::cin, name);
        }

        std::string requisites;
        while (requisites == "") {
            std::cout << "Введите реквизиты: " << std::endl;
            std::getline(std::cin, requisites);
        }

        std::string acceptancePrice;
        while (acceptancePrice == "") {
            std::cout << "Введите цену приемки: " << std::endl;
            std::getline(std::cin, acceptancePrice);
            if (!Helpers::isNumber(acceptancePrice)) {
                acceptancePrice = "";
            }
        }

        std::string sellingPrice;
        while (sellingPrice == "") {
            std::cout << "Введите отпускную цену: " << std::endl;
            std::getline(std::cin, sellingPrice);
            if (!Helpers::isNumber(sellingPrice)) {
                sellingPrice = "";
            }
        }

        std::string count;
        while (count == "") {
            std::cout << "Введите количество: " << std::endl;
            std::getline(std::cin, count);
            if (!Helpers::isNumber(count)) {
                count = "";
            }
        }

        std::map<std::string, std::string> book;

        book.insert(std::pair<std::string, std::string>("author", author));
        book.insert(std::pair<std::string, std::string>("name", name));
        book.insert(std::pair<std::string, std::string>("requisites", requisites));
        book.insert(std::pair<std::string, std::string>("acceptancePrice", acceptancePrice));
        book.insert(std::pair<std::string, std::string>("sellingPrice", sellingPrice));
        book.insert(std::pair<std::string, std::string>("count", count));

        BookService bookService = ctx.getBookService();

        bookService.addBook(book);

        return "Книга успешно добавлена";
    }

    string toString() override {
        return "add-book : Добавить книгу";
    }

private:
    Context ctx;
};



#endif //BOOK_STORE_ADDBOOK_H
