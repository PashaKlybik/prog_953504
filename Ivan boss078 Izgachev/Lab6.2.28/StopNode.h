#pragma once

struct StopNode {
  char stopName[32];
  struct StopNode* next;
};

struct StopNode* initStopNode(char aStopName[32]);
struct StopNode* addStopNode(struct StopNode* stopNode, struct StopNode* newStopNode);
int getStopsSize(struct StopNode* stopNode);
struct StopNode* getStopByIndex(struct StopNode* stopNode, int index);