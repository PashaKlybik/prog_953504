#include <stdio.h>
#include <Windows.h>

int Checker()
{
	while (true)
	{
		FILE* vaniliaVersion;
		fopen_s(&vaniliaVersion, 
			"D://Programming//GitHub//C-Lab-Number7-Var9//Text.txt", "r");

		FILE* changedVersion;
		fopen_s(&changedVersion, 
			"D://Programming//GitHub//C-Lab-Number7-Var9//TextForArray.txt", "r");

		char _vaniliaVersion;
		char _changedVersion;

		int flag;
		flag = 1;

		do
		{
			_vaniliaVersion = getc(vaniliaVersion);
			_changedVersion = getc(changedVersion);

			if (_vaniliaVersion != _changedVersion)
			{
				flag = 0;
			}

		} while (_vaniliaVersion != EOF && 
			_changedVersion != EOF);

		if (flag != 1)
		{
			fclose(vaniliaVersion);
			fclose(changedVersion);

			FILE* log;

			fopen_s(&log, 
				"D://Programming//GitHub//C-Lab-Number7-Var9//Log.txt", "w");
			fopen_s(&vaniliaVersion, 
				"D://Programming//GitHub//C-Lab-Number7-Var9//Text.txt", "r");
			fopen_s(&changedVersion,
				"D://Programming//GitHub//C-Lab-Number7-Var9//TextForArray.txt", "r");

			do
			{
				_vaniliaVersion = getc(changedVersion);
				putc(_vaniliaVersion, log);
			} while (_vaniliaVersion != EOF);

			fclose(changedVersion);
			fopen_s(&changedVersion, 
				"D://Programming//GitHub//C-Lab-Number7-Var9//TextForArray.txt", "w");

			do
			{
				_vaniliaVersion = getc(vaniliaVersion);
				putc(_vaniliaVersion, changedVersion);
			} while (_vaniliaVersion != EOF);

		}

		Sleep(600);
	}
}