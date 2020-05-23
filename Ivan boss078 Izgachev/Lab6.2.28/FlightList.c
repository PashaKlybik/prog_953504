#include "FlightList.h"

void initArray(FlightList* a, size_t initialSize) {
  a->array = (struct Flight*)malloc(initialSize * sizeof(struct Flight));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(FlightList* a, struct Flight element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (struct Flight*)realloc(a->array, a->size * sizeof(struct Flight));
  }
  a->array[a->used++] = element;
}

void freeArray(FlightList* a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

struct Flight* findById(FlightList* flightList, unsigned int aId) {
  if (flightList->used == 0) {
    return NULL;
  }
  else {
    for (int i = 0; i < flightList->used; i++) {
      if (flightList->array[i].id == aId) {
        return &flightList->array[i];
      }
    }
    return NULL;
  }
}

struct Flight* findByPlaneType(FlightList* flightList, enum PlaneType aPlaneType) {
  if (flightList->used == 0) {
    return NULL;
  }
  else {
    for (int i = 0; i < flightList->used; i++) {
      if (flightList->array[i].planeType == aPlaneType) {
        return &flightList->array[i];
      }
    }
    return NULL;
  }
}

struct Flight* findByRoute(FlightList* flightList, char aRoute[128]) {
  if (flightList->used == 0) {
    return NULL;
  }
  else {
    for (int i = 0; i < flightList->used; i++) {
      if (strcmp(flightList->array[i].route, aRoute) == 0) {
        return &flightList->array[i];
      }
    }
    return NULL;
  }
}

struct Flight* findByStop(FlightList* flightList, char Stop[32]) {
  if (flightList->used == 0) {
    return NULL;
  }
  else {
    for (int i = 0; i < flightList->used; i++) {
      for (int j = 0; j < getStopsSize(flightList->array[i].stops); j++) {
        if (strcmp(getStopByIndex(flightList->array[i].stops, j)->stopName, Stop) == 0) {
          return &flightList->array[i];
        }
      }
    }
    return NULL;
  }
}

struct Flight* findNearstByStop(FlightList* flightList, char Stop[32]) {
  if (flightList->used == 0) {
    return NULL;
  }
  else {
    unsigned long currDifference = ULONG_MAX;
    time_t currTime = time(0);
    struct Flight* currAnsw = NULL;
    for (int i = 0; i < flightList->used; i++) {
      if (flightList->array[i].departureTime - currTime <= 0 || flightList->array[i].departureTime - currTime > currDifference) {
        continue;
      }
      for (int j = 0; j < getStopsSize(flightList->array[i].stops); j++) {
        if (strcmp(getStopByIndex(flightList->array[i].stops, j)->stopName, Stop) == 0) {
          currDifference = flightList->array[i].departureTime - currTime;
          currAnsw = &flightList->array[i];
          break;
        }
      }
    }
    return currAnsw;
  }
}
