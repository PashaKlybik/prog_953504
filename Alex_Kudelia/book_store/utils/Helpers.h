#ifndef BOOK_STORE_HELPERS_H
#define BOOK_STORE_HELPERS_H

#include <string>
#include <vector>

using namespace std;

class Helpers {
public:
    static string vectorToString(vector<string> v) {
        ostringstream s;
        copy(v.begin(), v.end()-1,
             ostream_iterator<string>(s, ","));
        s << v.back();
        return s.str();
    }

    static bool isNumber(const std::string& s) {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
    }
};


#endif //BOOK_STORE_HELPERS_H
