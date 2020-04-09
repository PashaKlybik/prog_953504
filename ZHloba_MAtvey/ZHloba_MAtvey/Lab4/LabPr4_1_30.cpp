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


#include <stdio.h>
#include <string>
# include <iomanip>
#include <stdio.h>
 # include <conio.h>
# include <math.h>
# include <iostream>
# include <ctime>
#include <locale.h>
using namespace std;

enum letters {
letter_j=-90,
letter_sh=-24,
letter_ch=-25,
letter_shh=-23,
letter_y=-29,
letter_ii=-88,
letter_a=-96
} ;

int _tmain(int argc, _TCHAR* argv[])
{
	 setlocale(LC_ALL, "Russian");
	char str[200] ;
	scanf("%200[^\n]",str) ;

	for (int n = 0; str[n] != 0; n++) {
	int test=str[n];
	printf("%d ",test);


	if ((str[n]==letter_j||str[n]==letter_shh||
	str[n]==letter_ch||str[n]==letter_sh)&&str[n+1]!=' ')
	 {

	 if(str[n]==letter_j)
	  {
	  str[n+1]=letter_ii;
	   }
	 if(str[n]==letter_sh)
	 {
	 str[n+1]=letter_ii;
	 }
	 if(str[n]==letter_shh&&str[n+1]!=letter_y)
	 {
	  str[n+1]=letter_a;
	 }
	 if(str[n]==letter_ch&&str[n+1]!=letter_y)
	 {
	 str[n+1]=letter_a;
		}
	}
	}
  printf("\n\n%s",str)  ;
	_getch();
	return 0;
}
