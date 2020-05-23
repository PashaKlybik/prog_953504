#include <stdio.h>
#include <stdlib.h>
int f_data(char a[11])//функция определения просроченного лекарства
{                           //тут текущая дата указана как 20.02.2020 т.е. с ней идет сравнение
    int d,m,y,r;
    d=10*(a[0]-'0')+a[1]-'0';
    m=10*(a[3]-'0')+a[4]-'0';
    y=1000*(a[6]-'0') +100*(a[7]-'0') +10*(a[8]-'0') +(a[9]-'0');
    if(y>2020)r=1;
    if(y==2020)
        if((m==2 && d>=20) || (m>2) )r=1;
    else r=0;
    else if(y<2020)r=0;
    return r;
}
int main()
{
  FILE *S1;
//char arr[20];
char name[12];
char data[11];
int num;
int cost;
char name1[12];
char data1[11];
int num1;
int cost1;
  S1 = fopen("S1.txt", "w");
  //int n=2;
  int n;
  printf("input number of drugs \n");
  scanf ("%d", &n);
   while ((n--)>0)
	 {
	     scanf ("%s%s%d%d", name,data ,&num,&cost); //считывание данных(наименование срок годности количество цена)
                                                        //например "lekarstvo1 20.05.2020 24 45 "

		fprintf(S1, "%s %s %d %d\n", name,data ,num,cost);
     }
  fclose(S1);

 int sum=0;

  S1 = fopen("S1.txt", "r");
  while ((fscanf (S1, "%s%s%d%d",name1,data1 ,&num1,&cost1 )) != EOF)
  {

   if(f_data( data1)<1) {printf("drugs ,out of use:%s %s %d %d\n", name1,data1 ,num1,cost1 );

   sum+=cost1*num1;}

  }
fclose(S1);
printf("\n sum=%d",sum);

  return 0;
}
