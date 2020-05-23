#pragma once

void ExampleFilling(struct Hotel* hotelsContainer,
	int iterator, const char* hotelsInfo, int stringSize);
void ArrayCreating(struct Hotel* hotelsContainer,
	int size, const char* fileName);
void MenuChoiceGetter();
void SearchStringProcessing();
void ResultFinder(char* processedString);

int FileStringCounter(const char* fileName);

char* StringParse(char* enteredSearchString);

struct Hotel
{
	char Name[20];
	char CityLocation[20];
	char Addrass[20];
	char NumberClass[20];
	char FreePlacesQuantity[20];
	char NumberCost[20];
};