#include <stdio.h>

int * getCount (int rubles, int last) {
	int threeCount, fiveCount; 
  int count[] = { 0, 0 }, *ptr = count;
	if (rubles % 5 == 0) {
		count[0] = rubles / 5 + last;
		return ptr;
	}
	else if (rubles % 3 == 0) {
		count[0] = last;
		count[1] = rubles / 3;
		return ptr;
	}
	else getCount(rubles - 5, ++last);
}

int main () {
	int rubles;
  while (1) {
    printf("Enter the count of rubles: "); scanf("%i", &rubles);
    if (rubles <= 7) continue;
    printf("Fives: %i Threes: %i\n", getCount(rubles, 0)[0], getCount(rubles, 0)[1]);
    break;
  }
	system("pause");
	return 0;
}