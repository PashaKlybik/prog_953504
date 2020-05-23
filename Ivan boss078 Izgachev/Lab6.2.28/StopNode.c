#include "StopNode.h"

struct StopNode* initStopNode(char aStopName[32]) {
  struct StopNode* newStopNode = (struct StopNode*)malloc(sizeof(struct StopNode));
  strcpy(newStopNode->stopName, aStopName);
  newStopNode->next = 0;
  return newStopNode;
}

struct StopNode* addStopNode(struct StopNode* stopNode, struct StopNode* newStopNode) {
  if (stopNode == 0) {
    stopNode = newStopNode;
    return stopNode;
  }
  struct StopNode* curr = stopNode;
  while (curr->next != 0) {
    curr = curr->next;
  }
  curr->next = newStopNode;
  return stopNode;
}

int getStopsSize(struct StopNode* stopNode) {
  int answ = 0;
  while (stopNode != 0) {
    answ++;
    stopNode = stopNode->next;
  }
  return answ;
}

struct StopNode* getStopByIndex(struct StopNode* stopNode, int index) {
  int i = 0;
  while (stopNode != 0) {
    if (i == index) {
      return stopNode;
    }
    stopNode = stopNode->next;
    i++;
  }
  return 0;
}