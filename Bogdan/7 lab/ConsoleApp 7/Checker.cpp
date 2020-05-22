#include <stdio.h>
#include <Windows.h>
#define USER_PATH "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Test.txt";

int Checker()
{
	while (1)
	{
		FILE* fp1;
		fopen_s(&fp1, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Text.txt", "r");  //Thread for user

		FILE* fp2;
		fopen_s(&fp2, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Text_for_array.txt", "r");		//Thread for hotel array

		char ch = 0;
		char ch1 = 0;

		int flag = 1;

		do
		{
			ch = getc(fp1);
			ch1 = getc(fp2);

			if (ch != ch1)
				flag = 0;

		} while (ch != EOF && ch1 != EOF);

		if (flag != 1)		//If something is missing we remake Text_for_array
		{
			fclose(fp1);
			fclose(fp2);

			FILE* log;

			fopen_s(&log, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//log//Log", "w");		//creating Log file
			fopen_s(&fp1, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Text.txt", "r");
			fopen_s(&fp2, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Text_for_array.txt", "r");

			do
			{
				ch = getc(fp2);			//filling log file
				putc(ch, log);
			} while (ch != EOF);

			fclose(fp2);
			fopen_s(&fp2, "C://Users//Lenovo//Documents//GitHub//Проектик//Работай2//C-Lab-Number7-Var9//Lab7C//Text_for_array.txt", "w");

			do
			{
				ch = getc(fp1);
				putc(ch, fp2);
			} while (ch != EOF);

		}

		Sleep(600);
	}
}