#ifndef BOOK_STORE_QUERY_H
#define BOOK_STORE_QUERY_H

#include "iostream"
#include "vector"
#include "regex"


using namespace std;

class Query {
public:
    explicit Query(string q) {
        if (q.find_first_of(' ') != -1) {
            int i = q.find_first_of(' ');
            cmd = q.substr(0, i);
            q = q.substr(i+1);
            args = split(q, ' ');
        } else {
            cmd = q;
        }
    }

    string getCmd() {
        return cmd;
    }

    string getArg(int i) {
        return args[i];
    }

    vector<string> getArgs() {
        return args;
    }

private:
    string cmd;
    vector<string> args;

    vector<string> &split(const string &s, char delim, vector<string> &elems) {
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            if (item.length() > 0) {
                elems.push_back(item);
            }
        }
        return elems;
    }

    vector<string> split(const string &s, char delim) {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }
};



#endif //BOOK_STORE_QUERY_H
