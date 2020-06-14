#ifndef BOOK_STORE_BOOKREPO_H
#define BOOK_STORE_BOOKREPO_H

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include "../entities/Book.h"
#include "../utils/CSV.h"
#include "../utils/Helpers.h"
#include "../serializers/BookSerializer.h"

class BookRepo {
public:
    BookRepo() = default;
    const std::string BOOKS_DB = "db/books_db.csv";

    std::vector<Book> all() {
        books.clear();
        this->loadData();
        return books;
    }

    Book find(long id) {
        for (auto &it : all()) {
            if (it.getId() == id) {
                return it;
            }
        }
        throw std::exception("Книга не найдена");
    }

    void insert(std::string line) {
        CSV::write(BOOKS_DB, line);
    }

    void changeCount(long id, int count) {
        std::vector<std::vector<std::string>> csvData = CSV::read(BOOKS_DB);

        for(std::vector<std::string> vec : csvData)
        {
            Book *book = BookSerializer::fromCSV(vec);
            if(book->getId() == id) {
                book->setCount(book->getCount() - count);
                std::string existingRow = Helpers::vectorToString(vec);
                std::vector<std::string> bookVec = BookSerializer::toVector(book);
                std::string newRow = Helpers::vectorToString(bookVec);

                CSV::update(BOOKS_DB, existingRow, newRow);
            }
        }
    }

private:
    std::vector<Book> books;

    void loadData() {
        std::vector<std::vector<std::string>> csvData = CSV::read(BOOKS_DB);

        for(std::vector<std::string> vec : csvData)
        {
            Book *book = BookSerializer::fromCSV(vec);
            books.push_back(*book);
        }
    }
};


#endif //BOOK_STORE_BOOKREPO_H
