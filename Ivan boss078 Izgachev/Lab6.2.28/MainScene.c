#include "MainScene.h"

void viewAllFlighs() {
  for (int i = 0; i < flightList.used; i++) {
    printFlightInfo(&flightList.array[i]);
  }
}

bool mainMenu() {
  printf(">>>>>>Main Menu<<<<<<\n");
  printf("1. View all flights\n");
  printf("2. Find flight\n");
  printf("3. Add new flight(admin only)\n");
  printf("4. Exit\n");
  unsigned int choice;
  struct Flight* found;
  scanf("%u", &choice);
  switch (choice)
  {
  case 1:
    viewAllFlighs();
    break;
  case 2:
    found = FindFlightMenu();
    if (found == NULL) {
      return true;
    }
    while (true) {
      if (!flightMenu(found)) {
        break;
      }
    }
    break;
  case 3:
    AddNewFlightToFlightList();
    break;
  case 4:
    return false;
    break;
  default:
    printf("Wrong input\n");
    break;
  }
  return true;
}

struct Flight* FindFlightMenu() {
  printf(">>>>>>Find Flight<<<<<<\n");
  printf("1. Find flight by flight id\n");
  printf("2. Find flight by route\n");
  printf("3. Find flight by plane type\n");
  printf("4. Find flight by stop\n");
  printf("5. Find nearest flight by stop\n");
  printf("6. Exit\n");
  unsigned int choice;
  unsigned int targetID;
  char targetRoute[128];
  unsigned int targetPlaneTypeChoice;
  enum PlaneType targetPlaneType;
  char targetStop[32];
  char closestTargetStop[32];
  scanf("%u", &choice);
  switch (choice)
  {
  case 1:
    printf("Enter target id: ");
    scanf("%u", &targetID);
    return findById(&flightList, targetID);
    break;
  case 2:

    printf("Enter target route: ");
    scanf("%s", &targetRoute);
    return findByRoute(&flightList, targetRoute);
    break;
  case 3:
    printf("Select target plane type:\n");
    printf("1. Boeing787-8\n");
    printf("2. Boeing787-9\n");
    printf("3. Boeing787-10\n");
    printf("4. Cirrus SR22\n");
    printf("5. Airbus A380\n");

    scanf("%u", &targetPlaneTypeChoice);
    switch (targetPlaneTypeChoice)
    {
    case 1:
      targetPlaneType = BOEING787_8;
      break;
    case 2:
      targetPlaneType = BOEING787_9;
      break;
    case 3:
      targetPlaneType = BOEING787_10;
      break;
    case 4:
      targetPlaneType = CIRRUS_SR22;
      break;
    case 5:
      targetPlaneType = AIRBUS_A380;
      break;
    default:
      printf("Boeing787-8 was chosen\n");
      targetPlaneType = BOEING787_8;
    }
    return findByPlaneType(&flightList, targetPlaneType);
    break;
  case 4:

    printf("Enter target stop: ");
    scanf("%s", &targetStop);
    return findByStop(&flightList, targetStop);
    break;
  case 5:

    printf("Enter target stop: ");
    scanf("%s", &closestTargetStop);
    return findNearstByStop(&flightList, closestTargetStop);
    break;
  case 6:
    break;
  default:
    printf("Wrong input\n");
    break;
  }
  return NULL;
}

void AddNewFlightToFlightList() {
  unsigned int id;
  enum PlaneType planeType;
  time_t departureTime;
  enum Days dayOfFlight;
  char route[128];
  struct StopNode* stops = 0;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Adding new flight record...\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Enter flight id: ");
  scanf("%u", &id);
  printf("Enter flight route: ");
  scanf("%s", &route);
  printf("Select plane type:\n");
  printf("1. Boeing787-8\n");
  printf("2. Boeing787-9\n");
  printf("3. Boeing787-10\n");
  printf("4. Cirrus SR22\n");
  printf("5. Airbus A380\n");
  unsigned int planeTypeChoice;
  scanf("%u", &planeTypeChoice);
  switch (planeTypeChoice)
  {
  case 1:
    planeType = BOEING787_8;
    break;
  case 2:
    planeType = BOEING787_9;
    break;
  case 3:
    planeType = BOEING787_10;
    break;
  case 4:
    planeType = CIRRUS_SR22;
    break;
  case 5:
    planeType = AIRBUS_A380;
    break;
  default:
    printf("Boeing787-8 was chosen\n");
    planeType = BOEING787_8;
  }
  int minutes = 0, hours = 0, days = 0, months = 0, years = 0;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("Setting departure time...\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("month(number): ");
  scanf("%d", &months);
  printf("day: ");
  scanf("%d", &days);
  printf("year: ");
  scanf("%d", &years);
  printf("hours: ");
  scanf("%d", &hours);
  printf("minutes: ");
  scanf("%d", &minutes);

  struct tm* tm1;
  time_t tm2;
  tm2 = time(NULL);
  tm1 = localtime(&tm2);
  tm1->tm_mday = days;
  tm1->tm_mon = months;
  tm1->tm_year = years - 1900;
  tm1->tm_hour = hours;
  tm1->tm_min = minutes;
  tm1->tm_sec = 0;
  departureTime = mktime(tm1);
  dayOfFlight = tm1->tm_wday;
  bool isExiting = false;
  while (!isExiting) {
    struct StopNode stop;
    printf("Choose option:\n");
    printf("1. Create new stop\n");
    printf("2. Cancel\n");
    unsigned int choice;
    scanf("%u", &choice);
    switch (choice)
    {
    case 1:
      printf("Enter stop name: ");
      char stopName[32];
      scanf("%s", &stopName);
      struct StopNode* stop = initStopNode(stopName);
      stops = addStopNode(stops, stop);
      break;
    case 2:
    default:
      isExiting = true;
      break;
    }
  }
  struct Flight newFlight = initFlight(id, planeType, route, stops, departureTime, dayOfFlight);
  insertArray(&flightList, newFlight);
  printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("New flight record added\n");
  printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
}

int main() {
  initArray(&flightList, 1);
  while (true) {
    if (!mainMenu()) {
      break;
    }
  }
  return 0;
}