#include <stdio.h>
#include <iostream>
//#include <conio.h>
//#include <stdlib.h>

int _tmain()
{
	int i = 0;
	char *character;
	character = (char *) malloc(1);

	do {
		character = (char *) realloc(character, 1 + i);
		character[i] = getchar();
		i++;
	}while(character[i - 1] != '.');

	for(;i >= 0; --i) {
		printf("%c", character[i]);
    }

	system("pause");
	return 0;
}
