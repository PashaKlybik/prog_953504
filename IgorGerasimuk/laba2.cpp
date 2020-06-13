#include <stdio.h>
#include <locale>

void ball_surface_area(float radius, float ball_area, float PI);
void ball_volume(float radius, float PI);
void tetrahedron_edge_length(float radius);
void cross_sectional_area(float radius, float PI);
void Feedback();

void main(void)
{
	setlocale(LC_ALL, "russian");
	float radius = 0;
	float ball_area = 0;
	float PI = 3.14;
	int function;
	while (true)
	{
		printf("----------------------------------");
		printf("\nВыберите нужную вам функцию:\n");
		printf("1. Ввод радиуса шара\n");
		printf("2. Вывод площади поверхности шара\n");
		printf("3. Вывод объема шара\n");
		printf("4. Вывод длины ребра вписанного правильного тетраэдра\n");
		printf("5. Вывод площади сечения, проведенного на расстоянии k от центра шара\n");
		printf("6. Информация о версии и автора программы\n");
		printf("7. Выход\n");

		scanf_s("%d", &function);
		printf("----------------------------------\n");

		switch (function)
		{
		case 1:
			printf("Введите радиус шара: ");
			scanf_s("%f", &radius);
			printf("\nРадиус шара: %.2f\n", radius);
			break;
		case 2:
			ball_surface_area(radius, ball_area, PI);
			break;
		case 3:
			ball_volume(radius, PI);
			break;
		case 4:
			tetrahedron_edge_length(radius);
			break;
		case 5:
			cross_sectional_area(radius, PI);
			break;
		case 6:
			Feedback();
			break;
		case 7:
			exit(0);
		}
	}
}

void ball_surface_area(float radius, float ball_area, float PI) {
	ball_area = 4 * PI * pow(radius, 2);
	printf("Радиус шара равна: %.2f\n", radius);
	printf("\nПлощадь поверхности шара равна: %.2f\n", ball_area);
}

void ball_volume(float radius, float PI) {
	float Volume;
	Volume = 4 / 3 * PI * pow(radius, 3);
	printf("Объем шара равен: %.2f\n", Volume);
}

void tetrahedron_edge_length(float radius) {
	float edge;
	edge = 4 * radius / sqrt(6);
	printf("Длина ребра вписанного тетраэдра: %.2f\n", edge);
}

void cross_sectional_area(float radius, float PI) {
	float k;
	float section_area;
	printf("Введите расстояние от центра шара: ");
	scanf_s("%f", &k);
	section_area = PI * pow(k, 2);
	printf("\nПлощадь сечения, проведенного на расстоянии k от центра шара, равна: %.2f\n", section_area);
}

void Feedback() {
	printf("\nВерсия программы: 1.1.0\n");
	printf("Автор: Герасимук Игорь Викторович\n");
	printf("Kонтактная информация: +375 44 123 45 67\n");
}