#pragma once

struct Hotel
{
public:
	char Name[20];
	char CityLocation[20];
	char Addrass[20];
	char NumberClass[20];
	char FreePlacesQuantity[20];
	char NumberCost[20];
	
	
};

void ExampleFilling(struct Hotel* hotelsContainer, int iterator, const char* hotelsInfo, int stringSize);
void ArrayCreating(struct Hotel* hotelsContainer, int size, const char* fileName);

int FileStringCounter(const char* fileName);