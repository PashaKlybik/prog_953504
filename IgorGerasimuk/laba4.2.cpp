#include <fstream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int main()
{

    ifstream infile("text1.txt");
    ofstream outfile("text2.txt", ios::trunc);

    string buffer;

    while (getline(infile, buffer))//буффер под строку
    {
        if (buffer > "P", "M", "A", "C", "O", "B", "E", "K" && buffer < "П")

            outfile << buffer << endl;//записываем строку в выходной файл

    }

    infile.close();//закрываем
    outfile.close(); //файлы

    return 0;
}
