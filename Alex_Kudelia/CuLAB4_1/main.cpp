#include <stdio.h>
#include <iostream>


#define MAX 100
#define LEN 80



int main(void)
{
    char text[MAX][LEN];

int t;
    printf("Enter text and press double <Enter>: \n");

    for (t = 0; t < MAX; t++) {
        fgets(text[t], LEN, stdin);
        if(*text[t] == '\n') break;
    }

/*    printf("Entered text: \n");

    for (int i = 0; i < t; i++) {
        for (int j = 0; text[i][j]; j++) {
            putchar(text[i][j]);
        }
    }
    */
 std::cout<<std::endl<<text[1][2]<<"\t"<<text[3][1];
float gl = 0;
float num =0;
 for (int i = 0; i < t; i++) {
     for (int j = 0; text[i][j]; j++) {
       num++;
         if (text[i][j] == 'a'|| text[i][j] == 'e'|| text [i][j] == 'y'||text [i][j] == 'u'|| text[i][j] == 'i'|| text[i][j] == 'o' )
             gl++;

     }
 }
 printf("\nnum=%f",gl);
 printf("\nall=%f",num);

double p = (gl/num)*100*0.2;
 int s =p;
 int ss=p*10;
int temp = ss % (s*10);
int pp = 0;
std::cout<<std::endl<<p<<std::endl;

if (temp>=5)
    p=p+0.5;
pp=p;

printf("All         ");
for(int i=0;i<20;i++)
    printf("|");

printf("\nConsonants  ");
for(int i=0;i<(20-pp);i++)
   printf("|");


printf("\nVowels      ");
for(int i=0;i<pp;i++)
   printf("|");

printf("\n");

    return 0;
}
