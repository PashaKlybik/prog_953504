#include <stdio.h>
#include <math.h>

int main () {
  const int MIN_COST = 25000;
  const int MAX_CARRIAGE_WEIGHT = 50; 

  const int cementCost[] = {230, 160};
  const int gravelCost[] = {142, 96};
  const int concreteCost[] = {260, 205};

  const int countryCosts[] = {
    200,
    320,
    320,
    360
  };

  int tones[] = {0, 0, 0};
  int countryNumber;

  printf("How much tones of cement You want to buy: "); scanf("%d", &tones[0]);
  printf("How much tones of gravel You want to buy: "); scanf("%d", &tones[1]);
  printf("How much tones of concrete You want to buy: "); scanf("%d", &tones[2]);

  const int orderTones = tones[0] + tones[1] + tones[2];
  const int carriagesNeed = ceil((orderTones + .0) / MAX_CARRIAGE_WEIGHT);

  printf("\nChoose your country(\"1\" - Belarus, \"2\" - Russia, \"3\" - Ukraine, \"4\" - Moldova): "); 
  scanf("%d", &countryNumber);

  printf("\n\nYour order:\nCement - %d tones(Cost: $%d/1 tone).\nGravel - %d tones(Cost: $%d/1 tone).\nConcrete - %d tones(Cost: $%d/1 tone).\nYour order`s weight: %d. Count of Carrieges your order need: %d.\nTransportation cost: $%d/carriage.\n", 
          tones[0], cementCost[0],
          tones[1], gravelCost[0],
          tones[2], concreteCost[0],
          orderTones, carriagesNeed, countryCosts[countryNumber - 1]
          );
  printf("\n\nDo you want to continue?(\"1\" - Yes, \"2\" - No): ");
  const int cont;
  scanf("%d", &cont);

  if(cont == 2) {
    printf("Okay, bye!");
    return 0;
  }


  const int orderCost = tones[0] * cementCost[0]
                      + tones[1] * gravelCost[0]
                      + tones[2] * concreteCost[0]
                      + countryCosts[countryNumber - 1] * carriagesNeed;

  printf("Your order cost: $%d(-$%d: company is paying for transportation)\n", orderCost, countryCosts[countryNumber - 1] * carriagesNeed);
  printf("Cost(profit): $%d.\n", orderCost - (countryCosts[countryNumber - 1] * carriagesNeed));
  if(orderCost - (countryCosts[countryNumber - 1] * carriagesNeed) < 25000) {
    printf("Sorry, we accept orders only with cost higher then $%d.\n", MIN_COST);
    system("pause");
    return 0;
  }
  system("pause");
  printf("\n--version: 1.0.0; author: Maksim Anikhovskiy <anikhovskiy00@mail.ru>;\n\n");

  system("pause");
  return 0;
}
