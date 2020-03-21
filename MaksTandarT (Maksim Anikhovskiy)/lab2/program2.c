#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

unsigned long long int fact(int number) {
  unsigned long long int factor = 1;
  for(int i = factor; i <= number; i++){
    factor *= i;
  }
  return factor;
}

double * getArgs(double x, double goal, double e){
  double arg = 0;
  double argWithE = 0;
  double nWithE;
  int trigger = 1;

  for(int n = 1; ; n++){
    arg += pow(-1, n - 1) * (pow(x, 2 * n - 1) / fact(2 * n - 1));
    if(fabs(fabs(goal) - fabs(arg)) <= e && trigger == 1) {
      trigger = 0;
      argWithE = arg;
      nWithE = (double)n;
      break;
    }
  }

  double toReturn[] = {argWithE, nWithE}; 
  double * ptr = toReturn;

  return ptr;
}

int main () {
  double x;
  double e;

  printf("Enter the x and e: ");
  scanf("%lf%lf", &x, &e);
  
  while(x > M_PI * 2) x -= M_PI * 2;
  
  double *args = getArgs(x, sin(x), e);

  printf("\nsin(x): %f\nf(x) with e: %f\nn with e: %d\n"
    , sin(x)
    , args[0]
    , (int)args[1]
    );

  system("pause");
  return 0;
}