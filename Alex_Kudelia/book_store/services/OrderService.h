#ifndef BOOK_STORE_ORDERSERVICE_H
#define BOOK_STORE_ORDERSERVICE_H
\
#include <stdio.h>
#include <map>
#include "../repositories/OrderRepo.h"

class OrderService {
public:
    OrderService() = default;

    OrderService(OrderRepo *orderRepo, BookService *bookService) {
        this->orderRepo = orderRepo;
        this->bookService = bookService;
    }

    void create(std::vector<std::map<std::string, std::string>> bookCount) {
        const std::string delimeter = ",";
        long id = findNextId();

        std::string aggregateBookCount;
        int totalPrice = 0;
        std::vector<std::map<long, int>> bookCountDict;

        for(auto& bc: bookCount) {
            aggregateBookCount += bc["bookID"] + ":" + bc["count"] + " ";
            Book b = bookService->find(std::stol(bc["bookID"]));
            int sellingPrice = b.getSellingPrice();
            int count = std::atoi(bc["count"].c_str());
            totalPrice += sellingPrice * count;

            bookCountDict.push_back({std::make_pair(b.getId(), count)});
        }

        std::string order = std::to_string(id) + delimeter + aggregateBookCount + delimeter + std::to_string(totalPrice);

        orderRepo->insert(order);

        for (auto& bc : bookCountDict) {
            for (auto& m : bc) {
                bookService->changeCount(m.first, m.second);
            }
        }
    }

    std::string getOrders() {
        std::vector<Order> orders = orderRepo->all();
        string ordersPresentation;

        if (orders.size() < 1) {
            return "Заказов нет";
        }

        ordersPresentation += "Всего заказов: " + std::to_string(orders.size()) + "\n";

        for (auto &it : orders) {
            std::vector<std::map<long, int>> orderBookCount = it.getOrderBookCount();
            ordersPresentation += "Заказ №: " + std::to_string(it.getId()) + "\n";
            ordersPresentation += "Книги: \n";
            for(auto& obc: orderBookCount) {
                for (auto& pair : obc) {
                    Book b = bookService->find(pair.first);
                    long bookId = b.getId();
                    std::string name = b.getName();

                    ordersPresentation += "-- ID " + std::to_string(bookId) + ", Название : " + name + ", кол-во: " + std::to_string(pair.second) + "\n";
                }
            }

            ordersPresentation += " Сумма заказа: " + std::to_string(it.getTotalPrice()) + "\n";
        }

        return ordersPresentation;
    }

    std::string report() {
        std::string reportPresentation;
        int totalPrice = 0;
        int numberOfBooksSold = 0;
        int totalProfit = 0;

        std::vector<Book> books = bookService->getBooks();
        reportPresentation += "Всего книг: " + std::to_string(books.size()) + "\n";
        reportPresentation += "В том числе: \n";
        for (auto &it : books) {
            reportPresentation += "-- ID " + std::to_string(it.getId()) + ": " + it.getName() + ", кол-во: " +  std::to_string(it.getCount()) + "\n";
            totalPrice += (it.getAcceptancePrice() * it.getCount());
        }
        reportPresentation += "Общая стоимость книг: " + std::to_string(totalPrice) + "\n";

        std::vector<Order> orders = orderRepo->all();
        reportPresentation += "Всего заказов: " + std::to_string(orders.size()) + "\n";

        for (auto &it : orders) {
            std::vector<std::map<long, int>> orderBookCount = it.getOrderBookCount();
            for(auto& obc: orderBookCount) {
                for (auto& pair : obc) {
                    numberOfBooksSold += pair.second;

                    Book b = bookService->find(pair.first);
                    totalProfit += (b.getSellingPrice() * pair.second);
                }
            }
        }

        reportPresentation += "Количество проданных книг: " + std::to_string(numberOfBooksSold) + "\n";
        reportPresentation += "Общая прибыль: " + std::to_string(totalProfit) + "\n";
        reportPresentation += "Для просмотра деталей заказов введите команду all-orders";

        return reportPresentation;
    }

private:
    OrderRepo *orderRepo;
    BookService *bookService;

    long findNextId() {
        std::vector<long> orderIds;

        for (auto &it : orderRepo->all()) {
            orderIds.push_back(it.getId());
        }

        std::cout << orderIds.size() << std::endl;

        if (orderIds.size() == 0)
            return 1;

        long max = *std::max_element(orderIds.begin(), orderIds.end());
        return max + 1;
    }
};


#endif //BOOK_STORE_ORDERSERVICE_H
