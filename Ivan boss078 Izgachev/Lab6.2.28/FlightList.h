#pragma once

#include "Flight.h"
typedef struct {
  struct Flight* array;
  size_t used;
  size_t size;
} FlightList;

void initArray(FlightList* a, size_t initialSize);
void insertArray(FlightList* a, struct Flight element);
void freeArray(FlightList* a);
struct Flight* findById(FlightList* flightList, unsigned int aId);
struct Flight* findByPlaneType(FlightList* flightList, enum PlaneType aPlaneType);
struct Flight* findByRoute(FlightList* flightList, char aRoute[128]);
struct Flight* findByStop(FlightList* flightList, char Stop[32]);
struct Flight* findByDepartureTime(FlightList* flightList, time_t aDepartureTime);
struct Flight* findByDayOfFlight(FlightList* flightList, enum Days aDayOfFlight);
struct Flight* findNearstByStop(FlightList* flightList, char Stop[32]);