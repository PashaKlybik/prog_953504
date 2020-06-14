#ifndef BOOK_STORE_BOOKSERVICE_H
#define BOOK_STORE_BOOKSERVICE_H

#include <stdio.h>
#include <map>
#include <algorithm>
#include "../repositories/BookRepo.h"

class BookService {
public:
    explicit BookService(BookRepo *bookRepo) {
        this->bookRepo = bookRepo;
    }

    std::vector<Book> getBooks() {
        std::vector<Book> books = bookRepo->all();
        return books;
    }

    string getAllBooks() {
        std::vector<Book> books = this->getBooks();
        string booksPresentation;

        if (books.size() < 1) {
            return "На складе нет книг";
        }

        booksPresentation += "Всего книг: " + std::to_string(books.size()) + "\n";

        for (auto &it : books) {
            booksPresentation += "ID: " + std::to_string(it.getId()) + ", Название: " + it.getName() + ", Автор: " + it.getAuthor() + ", Цена приемки: " + std::to_string(it.getAcceptancePrice()) + ", Отпускная цена: " + std::to_string(it.getSellingPrice()) + ", Кол-во на складе: " + std::to_string(it.getCount()) + "\n";
        }

        return booksPresentation;
    }

    void addBook(std::map<std::string, std::string> bookData) {
        const std::string delimeter = ",";
        long id = findNextId();

        std::string book = std::to_string(id) + delimeter + bookData["author"] + delimeter + bookData["name"] + delimeter + bookData["requisites"] + delimeter + bookData["acceptancePrice"] + delimeter + bookData["sellingPrice"] + delimeter + bookData["count"];

        bookRepo->insert(book);
    }

    void changeCount(long id, int count) {
        bookRepo->changeCount(id, count);
    }

    Book find(long id) {
        return bookRepo->find(id);
    }

private:
    BookRepo *bookRepo;

    long findNextId() {
        std::vector<long> bookIds;

        for (auto &it : bookRepo->all()) {
            bookIds.push_back(it.getId());
        }

        if (bookIds.size() == 0)
            return 1;

        std::cout << bookIds.size() << std::endl;
        long max = *std::max_element(bookIds.begin(), bookIds.end());
        return max + 1;
    }
};



#endif //BOOK_STORE_BOOKSERVICE_H
