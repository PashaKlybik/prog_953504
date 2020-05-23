
#include "Flight.h"


struct Flight initFlight(unsigned int aId, enum PlaneType aPlaneType,
  char aRoute[128], struct StopNode* aStops,
  time_t aDepartureTime, enum Days aDayOfFlight) {
  struct Flight newFlight;
  newFlight.id = aId;
  newFlight.planeType = aPlaneType;
  newFlight.freeSeatCount = (unsigned int)newFlight.planeType;
  strcpy(newFlight.route, aRoute);
  newFlight.stops = aStops;
  newFlight.departureTime = aDepartureTime;
  newFlight.dayOfFlight = aDayOfFlight;
  return newFlight;
}

void printFlightInfo(struct Flight* flight) {
  printf("~~~~~~~~~~~~~~~~~~~~~\n");
  printf(">>>>>Flight info<<<<<\n");
  printf("~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Flight id: %u\n", flight->id);
  printf("Route: %s\n", flight->route);
  printf("Plane type: %s\n", PlaneType_str[flight->planeType]);
  printf("Free seat count: %u\n", flight->freeSeatCount);
  printf("Departure time: %s", ctime(&flight->departureTime));
  printf("Day of flight: %s\n", Days_str[flight->dayOfFlight]);
  printf("Stops: ");
  struct StopNode* curr = flight->stops;
  while (curr != NULL) {
    printf("%s ", curr->stopName);
    curr = curr->next;
  }
  printf("\n");
}

bool flightMenu(struct Flight* flight) {
  printf(">>>>>>Flight Menu<<<<<<\n");
  printf("1. Print info\n");
  printf("2. Order ticket\n");
  printf("3. Cancel ticket\n");
  printf("4. Remove current flight from list(admin only)\n");
  printf("5. Exit\n");
  unsigned int choice;
  scanf("%u", &choice);
  switch (choice)
  {
  case 1:
    printFlightInfo(flight);
    break;
  case 2:
    if (orderTicket(flight) == true) {
      printf("Ticket ordered\n");
    }
    else {
      printf("There is no free seats\n");
    }
    break;
  case 3:
    if (returnTicket(flight)) {
      printf("Ticket returned\n");
    }
    else {
      printf("You can\'t retunr ticket because you haven\'t ordered it yet\n");
    }
    break;
  case 4:
    printf("You don\'t have permission to do that\n");
    break;
  case 5:
    return false;
    break;

  default:
    printf("Wrong input\n");
    break;
  }
  return true;
}

void addNewFlight(struct Flight* flightList, struct Flight* newFlight) {
  if (flightList == NULL) {
    flightList = newFlight;
    return;
  }
  else {
    struct Flight* curr = flightList;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = newFlight;
    return;
  }
}






bool orderTicket(struct Flight* flight) {
  if (flight->freeSeatCount > 0) {
    flight->freeSeatCount--;
    return true;
  }
  else {
    return false;
  }
}

bool returnTicket(struct Flight* flight) {
  if (flight->freeSeatCount < flight->planeType) {
    flight->freeSeatCount++;
    return true;
  }
  else {
    return false;
  }
}
