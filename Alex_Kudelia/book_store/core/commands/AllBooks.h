#ifndef BOOK_STORE_ALLBOOKS_H
#define BOOK_STORE_ALLBOOKS_H

#include "Command.h"

class AllBooks : public Command {
public:
    AllBooks(Context ctx) {
        this->ctx = ctx;
    }

    string exec(Query query) override {
        BookService bookService = ctx.getBookService();
        return bookService.getAllBooks();
    }

    string toString() override {
        return "all-books : Показать все книги";
    }

private:
    Context ctx;
};


#endif //BOOK_STORE_ALLBOOKS_H
