#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    ifstream fin("12.txt");
    string str;
    getline(fin, str);
	int left = 0;
	int right = 0;
	bool isGood = true;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
			left++;
		if (str[i] == ')')
			right++;
	}

	if (left != right)
	{
		isGood = false;
		printf("Balance is wrong: ");
		cout << str;
		return -1;
	}
	

	int level = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
		{
			level++;
			if (level == 2)
				str[i] = '[';
			if (level > 2)
				str[i] = '{';
		}
		if (str[i] == ')')
		{
			level--;
			if (level == 1)
				str[i] = ']';
			if (level > 1)
				str[i] = '}';
		}
	}
	printf("Balance is true: ");
    cout << str;
    fin.close();
}
