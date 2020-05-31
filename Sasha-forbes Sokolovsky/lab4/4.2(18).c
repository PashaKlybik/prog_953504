#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct info
{
    char name[20];
    int day;
    int month;
    int year;
    int stand;
    int price;
};

void printStruct(struct info* arr)
{
    for(int i = 0; i < 2; i++)
    {
        printf("%i - %i - %i\n", arr[i].stand, arr[i].price, arr[i].year);
    }
}

void check(struct info* arr)
{
    int currentDayHash = 20 + 5*100 + 2020*1000;

    for(int i = 0; i < 2; i++)
    {
        int arrHash = arr[i].day + arr[i].month * 100 + arr[i].year * 1000;
        if(currentDayHash > arrHash)
        {
            printf("%s is outdated, ", arr[i].name);
        }else
        {
            printf("%s is good, ", arr[i].name);
        }
        
        printf("price is %i \n", arr[i].stand * arr[i].price);
    }
}

int main()
{
    FILE* file;
    file = fopen("tmp.txt", "r");

    
    struct info* _info = malloc(2*sizeof(struct info));

    int index = 0;

    while(_info[index].price != EOF)
    {
        if(feof(file)) break;
        fscanf(file, "%s", &_info[index].name);
        fscanf(file, " %i.%i.%i ", &_info[index].day, &_info[index].month, &_info[index].year);
        fscanf(file, "%i", &_info[index].stand);
        fscanf(file, "%i", &_info[index].price);
         
        index++;
    }

    check(_info);
    
    free(_info);
    fclose(file);
}