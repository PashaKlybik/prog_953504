#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "Days.h"
#include "PlaneType.h"
#include "StopNode.h"


struct Flight {
  unsigned int id;
  enum PlaneType planeType;
  unsigned int freeSeatCount;
  time_t departureTime;
  enum Days dayOfFlight;
  struct Flight* next;
  char route[128];
  struct StopNode* stops;
};

struct Flight initFlight(unsigned int aId, enum PlaneType aPlaneType, char aRoute[128], struct StopNode* aStops, time_t aDepartureTime, enum Days aDayOfFlight);
void printFlightInfo(struct Flight* flight);
bool flightMenu(struct Flight* flight);
void addNewFlight(struct Flight* flightList, struct Flight* newFlight);

bool orderTicket(struct Flight* flight);
bool returnTicket(struct Flight* flight);