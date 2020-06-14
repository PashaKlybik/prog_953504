#ifndef BOOK_STORE_CONTROLLER_H
#define BOOK_STORE_CONTROLLER_H

#include <utility>
#include "commands/Container.h"

#include "Query.h"

using namespace std;

class Controller {
public:
    explicit Controller(Context ctx) {
        container = new Container(ctx);
    }

    string exec(string q) {
        Query query = Query(q);
        Command *cmd = container->getCmd(query);
        return cmd->exec(query);
    }

private:
    Container *container;
};


#endif //BOOK_STORE_CONTROLLER_H
