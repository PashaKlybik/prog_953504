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

void KSIS(void);
void ITIU(void);
void RE(void);
void TK(void);
void KP(void);
void RECOM(void);
int exit(void);

int _tmain(int argc, _TCHAR* argv[]) 
{   int check=0;
	char choose;
	while(check==0)
	{printf("\nSay me, what you would like:Information about KSIS(1),ITIU(2), RE(3), TK(4), KP(5), or you would like to take recomandation(6), or like end this program(7). ");
	scanf("%s", &choose);
	switch (choose)
		{
			case '1': KSIS();  break;
			case '2': ITIU();  break;
			case '3': RE();  break;
			case '4': TK();  break;
			case '5': KP();  break;
			case '6': RECOM();  break;
			case '7': check=exit(); break;
			default: printf("\nYou make mistake, pkease, repeat your choose");

        }
	}
	return 0;
}


void KSIS(void)
{
 printf("\nInforamtion about KSIS")   ;
 printf("\nHere 4 profession.");
 printf("\nVMSIS, free 341, pay 265 point required.");
 printf("\nPOIT, free 360, pay 309 point required.");
 printf("\nIITP, free 356, pay 290 point required.");
 printf("\nPOIT, free 335, pay 246 point required.");
}

void ITIU(void)
{
 printf("\nInforamtion about ITIU")   ;
 printf("\nHere 5 profession.");
 printf("\nACOI, free 351, pay 288 point required.");
 printf("\nII, free 342, pay 271 point required.");
 printf("\nITUTC, free 331, pay 257 point required.");
 printf("\nIIT(in game industry), free 364, pay 296 point required.");
 printf("\nPE, free 319, pay 250 point required.");
}

void RE(void)
{
 printf("\nInforamtion about RE");
 printf("\nHere 4 profession.");
 printf("\nMNTC, free 308, pay 243 point required.");
 printf("\nKIS, free 253, pay 190 point required.");
 printf("\nNNE, free 301, pay 241 point required.");
 printf("\nRadio, free 304, pay 251 point required.");
}

void TK(void)
{
 printf("\nSory, we dont have information about this facultet now");

}
void KP(void)
{
 printf("\nInforamtion about KP");
 printf("\nHere 5 profession.");
 printf("\nPPPUES, free 333, pay 272 point required.");
 printf("\nMKPRS, free 323, pay 268 point required.");
 printf("\nPMS, free 339, pay 266 point required.");
 printf("\nPUEOS, free 325, pay 247 point required.");
 printf("\nMedEl, free 327, pay 269 point required.");
}

void RECOM(void)
{
 int math=-1, ph=-1, ln=-1, att=-1, fin=-1;
 while (math==-1){
 printf("\nGive me your math point\n");
 scanf("%d", &math);
 if(math>100||math<0){
 math=-1;
 printf("Good joke. Say true.");
 }
  }

 while (ph==-1){
 printf("\nGive me your phisyc point\n");
 scanf("%d", &ph);
 if(ph>100||ph<0)    {
 ph=-1;
 printf("Good joke. Say true.");
 }
  }

 while (ln==-1){
 printf("\nGive me your language point\n");
 scanf("%d", &ln);
  if(ln>100||ln<0)   {
  ln=-1;
   printf("Good joke. Say true.");
  }
   }

 while (att==-1){
 printf("\nGive me your attistaion point\n");
 scanf("%d", &att);
 if(att>100||att<0) {
 att=-1;
 printf("Good joke. Say true.");
 }
   }
 if (ln*2>=math+ph) {
	printf("\nWhat you do here? You gumanitary!!!") ;   return ;
 }
 fin=math+ph+ln+att;
 if (fin>=307 && fin<313) {
 printf("\nWhy not look ITIU");
 }
 if (fin>313) {
 printf("\nWhy not look KSIS");
 }
 if (fin>262 && fin<=297) {
 printf("\nWhy not look RE");
 }
 if (fin>297 && fin<307) {
 printf("\nWhy not look KP");
 }
 if (fin<261) {
 printf("\nWhy not look another univercity;");
 }
 }


int exit(void)
{
	return 1;
}
