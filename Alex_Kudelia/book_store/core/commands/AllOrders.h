#ifndef BOOK_STORE_ALLORDERS_H
#define BOOK_STORE_ALLORDERS_H

#include "Command.h"

class AllOrders : public Command {
public:
    AllOrders(Context ctx) {
        this->ctx = ctx;
    }

    string exec(Query query) override {
        OrderService orderService = ctx.getOrderService();
        return orderService.getOrders();
    }

    string toString() override {
        return "all-orders : Показать все заказы ";
    }

private:
    Context ctx;
};


#endif //BOOK_STORE_ALLORDERS_H
