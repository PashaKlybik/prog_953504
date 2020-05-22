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

void Fill(struct Hotel* hotels, int iterator, const char* hotelsInfo, int stringSize);
void ArrCreate(struct Hotel* hotels, int size, const char* fileName);

int CountStrings(const char* fileName);