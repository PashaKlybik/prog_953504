#include <stdio.h>
#include <stdlib.h>
int func (int k)         //рекурсия ,которая преобразует строку десятичных цифр в целое число
{
   if(k==0) return 1;
    else return func(k-1)*10;
}
int Stol(char a[10],int n)
{
    int s=strlen(a);
if(n>0)
 return  (a[-1+n]-'0')*func(s-n)+Stol(a,n-1);
 else return 0;


}
int main()
{
   char a1[10];
    int n;
     printf("input string:");

scanf("%s",a1);
for(int i=0;i<strlen(a1);i++)
if(a1[i]>'9' || a1[i]<'0')
    {
      printf("wrong string");
        return 0;
    }

 printf("count= %d",Stol(a1,strlen(a1)));
    return 0;
}
