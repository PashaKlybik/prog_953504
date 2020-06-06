#include <iostream.h>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

void search(const string& s, const vector<string>& v, vector<const string*>& r)
{
    for (const string& x : v)
    {
        if (x.size() != s.size())
            continue;

        bool success = true;

        for (int i = 0; i < s.size(); ++i)
        {
            if (x[i] != s[i] && s[i] != '*' && s[i] != '_')
            {
                success = false;
                break;
            }
        }

        if (success)
            r.push_back(&x);
    }
}

int main()
{
    vector<string> v;
    vector<const string*> r;
    string s;
    ifstream fin("dic.txt");

    if (!fin)
    {
        cerr << "Error open dictionary file" << endl;
        system("pause");
        exit(EXIT_FAILURE);
    }

    while (fin >> s)
        v.push_back(s);

    cin >> s;
    search(s, v, r);
    cout << endl << r.size() << " matches found" << endl;

    for (const string* x : r)
        cout << *x << endl;

    system("pause");
    return 0;
}
