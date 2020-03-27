#include <stdio.h>
#include <fstream>

bool Check(char *line, int count) {
	for(int i = 0; i < count; i++) {
		if(line[i] != '0') {
			return false;
		}
	}
	return true;
}

int _tmain()
{
	FILE *file;
	char *line = new char [2];
	char checkOut[] = "{}[]()";
	int count = 0;
	int colom = 1;
	char el = '0';

	file = fopen("test.txt", "r");


	do {
		el = fgetc(file);
		if(el == '\n') {
			colom++;
			continue;
		}

		for	(int i = 0; i < 6; i++) {
		   if (el == checkOut[i]) {
			   line = (char *) realloc(line, 2 + count);
			   line[count] = el;
			   line[++count] = colom + 48;
			   ++count;
		   }
		}

	}while(el != EOF);

	printf("%s\n", line);

	do	{
			for(int k = 0; k < count;) {

				for(int i = 0; i < 6; i += 2) {
					if(line[k] == checkOut[i] && line[k + 2] == checkOut[i + 1]) {
						line[k] = '0';
						line[k + 1] = '0';
						line[k + 2] = '0';
						line[k + 3] = '0';
						k += 2;
						break;
					}

				}
				k++;
			}

			int value = count;

			for(int i = 0, k = 0; i < value - 2;) {
				if(line[i] == '0') {
					i += 4;
					count -= 4;
				}
				else  {
					line[k] = line[i];
					line[i] = '0';
					i++; k++;
				}
			}

			printf("%s\n", line);
            system("pause");

			if(Check(line, count)) {
				continue;
			}
			else if (value == count){
				printf("%s : %c", "Syntax error", line[1]);
				break;
			}

		}while(true);

	//printf("%s", line);



	system("pause");
	return 0;
}
