
#include <iostream>
#include <cmath>
#include <time.h>
#include <locale>

void iteration(double, double);
void recursive(double, double);
double func(double, double, double);

int count = 1;

long int factorial(long int n)
{
	if (n == 0 || n == 1) return 1;
	return n * factorial(n - 1);
}

int main()
{
	setlocale(LC_ALL, "rus");

	double x;
	double error;
	int operation;
	while (true) {
		printf("Введите нужную вам операцию: \n");
		printf("1. Итерационный метод:\n");
		printf("2. Рекурсивный метод:\n");
		printf("3. Выход\n\n");
		scanf_s("%d", &operation);

		printf("Введите e: ");
		scanf_s("%le", &error);

		printf("e: %lf\n", error);

		printf("Введите X: ");
		scanf_s("%le", &x);
		printf("\nSIN(x) = %f\n", sin(x));

		switch (operation) {
		case 1: {
			clock_t begin = clock();
			iteration(x, error);
			clock_t end = clock();
			double time_spend1 = (double)(end - begin);
			printf("Время выполнения = %.1f", time_spend1);
			printf(" мс\n");
			break;
		}
		case 2:
			recursive(x, error);
			count = 1;
			break;
		case 3:
			exit(0);
			break;
		}
	}
}

void iteration(double x, double error) {

	double decompos = 0;

	int n = 0;
	int k = 1;
	do {
		decompos += -1 * ((pow(-1, k) * pow(x, 2 * k - 1)) / factorial(2 * k - 1));
		n++;
		k++;
	} while ((decompos - sin(x)) > error);

	printf("\nПогрешность е: %f\n", decompos - sin(x));
	printf("Итераций: %d\n\n", n);
}

void recursive(double x, double error) {

	double decompos = 0;
	clock_t begin = clock();
	decompos = func(decompos, x, error);

	printf("\nПогрешность e: %f\n", decompos - sin(x));
	printf("Итераций: %d\n\n", count - 1);

	clock_t end = clock();
	double time_spend = (double)(end - begin);
	printf("Времени затрачено: %.1f", time_spend);
	printf(" мс\n");
}

double func(double decompos, double x, double error) {

	decompos += -1 * ((pow(-1, count) * pow(x, 2 * count - 1)) / factorial(2 * count - 1));
	count++;

	if (abs((decompos - sin(x)) < error)) return decompos;

	return func(decompos, x, error);
}