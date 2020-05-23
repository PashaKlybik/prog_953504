//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit24.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <string>

 //на ошибку вначале не смотрим
using namespace std;

struct Date{string year; int days;}   ;


int frb (char z)
{  int n;
if(z=='0') n=0;
if(z=='1') n=1;
if(z=='2') n=2;
if(z=='3') n=3;
if(z=='4') n=4;
if(z=='5') n=5;
if(z=='6') n=6;
if(z=='7') n=7;
if(z=='8') n=8;
if(z=='9') n=9;
return n;
}

int _tmain(int argc, _TCHAR* argv[])
{
		int str=0,i;
		Date Days[20]  ;
		int max=100, min=99999999, nmin,nmax;
		string path = "Dates.txt";
		ifstream fin ;
		fin.open(path);
			   while (!fin.eof())
				{
				getline(fin,Days[str].year);
				str=str+1;
				}
	   str=str+1;
	   fin.close();
	   for (i = 0; i < str-1; i++) {
		 Days[i].days=frb(Days[i].year[0])*10+frb(Days[i].year[1])
		 +31*(frb(Days[i].year[3])*10+frb(Days[i].year[4]))
		 +365*(frb(Days[i].year[6])*1000+frb(Days[i].year[7])*100+
		 frb(Days[i].year[8])*10+frb(Days[i].year[9]))   ;

		 if(max<Days[i].days)
		 {
		 max=Days[i].days;
		 nmax=i;
		 }
		if(min>Days[i].days)
		 {
		 min=Days[i].days;
		 nmin=i;
		 }
	   }


	cout<<"\nMax="<<Days[nmax].year;


	cout<<"\nMin="<<Days[nmin].year;

	_getch();
	return 0;
}
