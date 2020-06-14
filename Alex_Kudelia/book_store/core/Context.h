#ifndef BOOK_STORE_CONTEXT_H
#define BOOK_STORE_CONTEXT_H

#include "../services/BookService.h"
#include "../services/OrderService.h"

class Context {
public:
    explicit Context() {
        this->initialize();
    }

    BookService getBookService() {
        return *bookService;
    }

    OrderService getOrderService() {
        return *orderService;
    }
private:
    BookService *bookService{};
    OrderService *orderService{};

    void initialize() {
        this->bookService = new BookService(std::invoke([]() {
            auto *bookRepo = new BookRepo();
            return bookRepo;
        }));

        this->orderService = new OrderService(std::invoke([]() {
            auto *orderRepo = new OrderRepo();
            return orderRepo;
        }), this->bookService);
    }
};


#endif //BOOK_STORE_CONTEXT_H
