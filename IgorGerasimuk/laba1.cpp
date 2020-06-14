#include <iostream>
#include "stdio.h"
#include "math.h"
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

int main() {
	int n;

	printf("vvedite chislo: ");
	scanf_s("%d", &n);

	char ch[20];

	_itoa_s(n, ch, 10);
	bool flag1 = false;
	bool flag2 = false;
	for (int i = 0; i != strlen(ch) - 1; i++)
	{
		if (ch[i] > ch[i + 1])
			flag1 = true;

		if (ch[i] < ch[i + 1])
			flag2 = true;

		if (flag2 == flag1)
			break;
	}
	if (!flag2 == !flag1)
		printf("ne po vozrastaniju i ne po ubivaniu");
	else
		if (!flag1)
			printf("vse cifri uporjadocheni po vozrastaniju ");
		else
			printf("vse cifri uporjadocheni po ubivaniu ");
}