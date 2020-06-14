#ifndef BOOK_STORE_BOOKSERIALIZER_H
#define BOOK_STORE_BOOKSERIALIZER_H

#include "../entities/Book.h"

class BookSerializer {
public:
    static Book* fromCSV(std::vector<std::string> vec)  {
        Book *book = new Book();

        book->setId(std::stol(vec[0]));
        book->setAuthor(vec[1]);
        book->setName(vec[2]);
        book->setRequisites(vec[3]);
        book->setAcceptancePrice(std::atoi(vec[4].c_str()));
        book->setSellingPrice(std::atoi(vec[5].c_str()));
        book->setCount(std::atoi(vec[6].c_str()));

        return book;
    }

    static std::vector<std::string> toVector(Book *book) {
        vector<std::string> v;
        v.push_back(std::to_string(book->getId()));
        v.push_back(book->getAuthor());
        v.push_back(book->getName());
        v.push_back(book->getRequisites());
        v.push_back(std::to_string(book->getAcceptancePrice()));
        v.push_back(std::to_string(book->getSellingPrice()));
        v.push_back(std::to_string(book->getCount()));

        return v;
    }
};


#endif //BOOK_STORE_BOOKSERIALIZER_H
