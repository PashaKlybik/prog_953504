//
//  main.c
//  lab4.1
//
//  Created by Tomashik Daniil on 3/23/20.
//  Copyright © 2020 Tomashik Daniil. All rights reserved.
//
/*
 с клвывы вволиться текст посчитать длянну сатого короткого и самого длинного слова плиенять месиами саиое короткое м самое длинное слово в роеддож
 
 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    char mas1[1200];
    char mas2[1200];
    char mas3[1200];
    printf("Enter string:\n");
    fgets(mas1,120,stdin);
    printf("Your string is: %s\n",mas1);
    int count=0,count1=0,max=0,i=0,min=100,st=0;
    while (mas1[i] !='\0')
    {
        i++;
        count++;
    }
    for ( i=0;i<count-1;i++)
    {
        if (mas1[i]!=' '&& mas1[i]!='.')
        {
            count1++;
            if (max<=count1)
            {
                max=count1;
            }
            
        }
        else
        {
            count1=0;
            st++;
        }
       
    }
    int *a=(int*)malloc(st*sizeof(int));
    for (int j=0 ,i=0;(void)(j<count-1) ,i<st;j++)
        {
        
            if (mas1[j]!=' '&&mas1[j]!='.')
            {
            count1++;
            a[i]=count1;
            }
            else
            {
            count1=0;
            i++;
            }
        }
    
    for (i=0;i<st;i++)
    {
        if(min>a[i])
        {
            min=a[i];
        }
    }
    
    
    printf("max: %d\n",max);
    printf("min: %d\n",min);
    return 0;
}
