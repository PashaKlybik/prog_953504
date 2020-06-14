#ifndef BOOK_STORE_BOOK_H
#define BOOK_STORE_BOOK_H

#include <string>

using std::string;

class Book {
public:
    Book() = default;

    Book(long id, string author, string name, string requisites, int acceptancePrice, int sellingPrice, int count) {
        this ->id = id;
        this->author = std::move(author);
        this->name = std::move(name);
        this->requisites = std::move(requisites);
        this->acceptancePrice = acceptancePrice;
        this->sellingPrice = sellingPrice;
        this->count = count;
    }

    void setId(long id) {
        this->id = id;
    }

    void setName(string name) {
        this->name = name;
    }

    void setAuthor(string author) {
        this->author = author;
    }

    void setRequisites(string requisites) {
        this->requisites = requisites;
    }

    void setAcceptancePrice(int price) {
        this->acceptancePrice = price;
    }

    void setSellingPrice(int price) {
        this->sellingPrice = price;
    }

    void setCount(int count) {
        this->count = count;
    }

    long getId() const {
        return id;
    }

    string getAuthor() const {
        return author;
    }

    string getName() const {
        return name;
    }

    string getRequisites() const {
        return requisites;
    }

    int getAcceptancePrice() const {
        return acceptancePrice;
    }

    int getSellingPrice() const {
        return sellingPrice;
    }

    int getCount() const {
        return count;
    }

private:
    long id{};
    string author;
    string name;
    string requisites;
    int acceptancePrice{};
    int sellingPrice{};
    int count{};
};


#endif //BOOK_STORE_BOOK_H
