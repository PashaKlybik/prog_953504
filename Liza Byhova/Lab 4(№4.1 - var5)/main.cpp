/*Разнобуквица. С клавиатуры вводится многострочный текст. Распечатать самое длинное слово, в котором все буквы разные.*/
//hhhhhhh fgh qwerty defdd zxcvbn

#include <iostream>
#include <string>

using namespace std;

void Max_word (string &new_text)
{
    //cout << new_text << endl;
    int count_of_symbols = 0, end = 0, begin = 0, max = 0;

    for (int i = 0; i < new_text.length(); i++)
    {
        if ((new_text[i] >= 'A' && new_text[i] <= 'Z') || (new_text[i] >= 'a' && new_text[i] <= 'z'))
        {
            count_of_symbols++;
        }
        if (max < count_of_symbols)
        {
            max = count_of_symbols;
            end = i;
            begin = end - count_of_symbols + 1;
        }

        if (((i + 1 == new_text.length()) || (new_text[i + 1] == ' ' || new_text[i + 1] == '.' || new_text[i + 1] == '!' || new_text[i + 1] == '?')))
        {
            count_of_symbols = 0;
        }
    }

    for (int i = begin; i <= end; i++)
    {
        cout << new_text[i];
    }
    cout << ' ';
}

void checking_letters (int begin, int end, string text, string &new_text)
{
    int control = 0, check = 0, count_of_symbols = 0;
    for (int i = begin; i < end; i++)
    {
        control += end - i;

        for (int j = i + 1; j <= end; j++)
        {
            if (text[i] != text[j])
            {
               check += 1;
            }
            else
            {
                check += 0;
            }
        }

        count_of_symbols++;
    }

    if (check == control)
    {
        for (int i = begin, j = 0; i <= end; i++, j++)
        {
           new_text += text[i];
        }

        new_text += ' ';
    }
}

int main ()
{
    string text, new_text;

    cout << "String: ";
    getline(cin, text);

    int count_of_symbols = 0, end = 0, begin = 0, max = 0;

    for (int i = 0; i < text.length(); i++)
    {
        count_of_symbols++;
        end = i;
        begin = end - count_of_symbols + 1;

        if (((i + 1 == text.length()) || (text[i + 1] == ' ' || text[i + 1] == '.' || text[i + 1] == '!' || text[i + 1] == '?')))
        {
            checking_letters (begin, end, text, new_text);
            count_of_symbols = 0;
            i += 1;
        }
    }

    Max_word (new_text);

    return 0;
}

