#ifndef BOOK_STORE_ORDERREPO_H
#define BOOK_STORE_ORDERREPO_H

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include "../entities/Order.h"
#include "../utils/CSV.h"

class OrderRepo {
public:
    OrderRepo() = default;
    const std::string ORDERS_DB = "db/orders_db.csv";

    std::vector<Order> all() {
        orders.clear();
        this->loadData();
        return orders;
    }

    void insert(std::string line) {
        CSV::write(ORDERS_DB, line);
    }

private:
    std::vector<Order> orders;

    void loadData() {
        std::vector<std::vector<std::string>> csvData = CSV::read(ORDERS_DB);

        for(std::vector<std::string> vec : csvData)
        {
            Order *order = new Order();

            order->setId(std::stol(vec[0]));

            std::string s = vec[1];
            std::vector<std::string> bcRaw;
            std::istringstream iss(s);
            for(std::string s; iss >> s; )
                bcRaw.push_back(s);

            std::vector<std::map<long, int>> orderBookCount;

            for(auto const& bc: bcRaw) {
                std::map<long, int> bookCount;

                std::istringstream ss(bc);
                std::string v;
                vector<string> values;
                while(std::getline(ss, v, ':')) {
                    values.push_back(v);
                }

                bookCount.insert(std::pair<long, int>(std::stol(values[0]), std::atoi(values[1].c_str())));

                orderBookCount.push_back(bookCount);
            }

            order->setOrderBookCount(orderBookCount);

            order->setTotalPrice(std::atoi(vec[2].c_str()));

            orders.push_back(*order);
        }
    }
};


#endif //BOOK_STORE_ORDERREPO_H
