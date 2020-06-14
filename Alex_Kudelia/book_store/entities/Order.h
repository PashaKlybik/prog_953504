#ifndef BOOK_STORE_ORDER_H
#define BOOK_STORE_ORDER_H

class Order {
public:
    long getId() const {
        return id;
    }

    std::vector<std::map<long, int>> getOrderBookCount() const {
        return orderBookCount;
    }

    int getTotalPrice() const {
        return totalPrice;
    }

    void setId(long id) {
        Order::id = id;
    }

    void setOrderBookCount(std::vector<std::map<long, int>> orderBookCount) {
        Order::orderBookCount = orderBookCount;
    }

    void setTotalPrice(int totalPrice) {
        Order::totalPrice = totalPrice;
    }

private:
    long id;
    std::vector<std::map<long, int>> orderBookCount;
    int totalPrice;
};


#endif //BOOK_STORE_ORDER_H
