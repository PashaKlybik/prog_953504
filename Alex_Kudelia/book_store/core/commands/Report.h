#ifndef BOOK_STORE_REPORT_H
#define BOOK_STORE_REPORT_H

#include "Command.h"

class Report : public Command {
public:
    Report(Context ctx) {
        this->ctx = ctx;
    }

    string exec(Query query) override {
        OrderService orderService = ctx.getOrderService();
        return orderService.report();
    }

    string toString() override {
        return "report : Отчетность";
    }

private:
    Context ctx;
};


#endif //BOOK_STORE_REPORT_H
