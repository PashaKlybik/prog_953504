#pragma hdrstop
#pragma argsused

#ifdef _WIN32
#include <tchar.h>
#else
  typedef char _TCHAR;
  #define _tmain main
#endif

#include <stdio.h>
#include <conio.h>
#include <math.h>

int _tmain(int argc, _TCHAR* argv[])
{   double x=2, ryd,sn;
long int fact,t;

 printf("\nGive me a number\n");
 scanf("%lf",&x);
		while (x>1.58 || x<-1.58){
	 if(x>0)x=x-1;
	   if(x<0)x=x+1;

 }

 sn=sin(x);
 for(int i=1; i<=12; i++)
 {    t=2*i-1;
	  fact=1;
   for (int f = 1; f <=t; f++) {
		fact=fact*f;
	  }
	 ryd=ryd+(pow(-1,i-1)*pow(x,2*i-1))/fact;

 }
  printf("\nBy sin we have %lf\n", sn);
   printf("\nBy ryd we have %lf\n", ryd);
 //	scanf("%d", &i);
 _getch();
	return 0;
}
