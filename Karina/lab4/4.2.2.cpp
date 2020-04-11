#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int n = 0;

void Push()
{
    n++;
}

void Pop()
{
    n--;
}

bool Empty()
{
    return n == 0;
}

int main()
{
    ifstream fin("12.txt");
    string str;
    getline(fin, str);
    int level = 0;
    string strNew = "";
    
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(')
        {
            level++;
            Push();
            if (level == 1)
                strNew += '(';
            else
                if (level == 2)
                    strNew += '[';
                else
                    strNew += '{';
            continue;
        }

        if (str[i] == ')')
        {
            if (!Empty())
            {
               
                Pop();
                if (level == 1)
                    strNew += ')';
                else
                    if (level == 2)
                        strNew += ']';
                    else
                        strNew += '}';
                level--;
              
            }
            continue;
        }
        strNew += str[i];
    }
    while (!Empty()) {
        
        Pop();
        if (level == 1)
            strNew += ')';
        else
            if (level == 2)
                strNew += ']';
            else
                strNew += '}';
        level--;
    }
    cout << strNew;
    fin.close();

}
