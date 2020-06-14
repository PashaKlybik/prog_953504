#ifndef BOOK_STORE_COMMAND_H
#define BOOK_STORE_COMMAND_H

#include "iostream"
#include "../Query.h"

using namespace std;

class Command {
public:
    virtual string exec(Query q) = 0;
    virtual string toString() = 0;
};


#endif //BOOK_STORE_COMMAND_H
