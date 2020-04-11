#include <stdio.h> 
#include <string.h>

int main()
{
    char str[80], str1[80];
    int k=0; 
    printf_s("Enter the string:");
    gets_s(str);
    printf_s("%s\n", str);
      
        for (int i = 0; i< strlen(str); i++)
        {
            if ((str[i] == ':' || str[i] == ',' || str[i] == ';') && str[i + 1] != ' ')
            {
                str1[k] = str[i];
                str1[k + 1] = ' ';
                k += 2;
                continue;
            }
            if (str[i] == '!' || str[i] == '?' || str[i]=='.') {
                str1[k] = str[i];
                k++;
                i++;
                str1[k] = ' ';
                k++;
                if (str[i] == ' ') {
                    i++;
                }
                if (str[i] >= 97 && str[i] <= 122) {
                    str1[k] = str[i] - 32;
                    k++;
                }
                else {
                    str1[k] = str[i];
                    k++;
                }
                continue;
            }
            str1[k] = str[i];
            k++;
        }

    
    
    str1[k] = '\0'; 
    puts(str1);
    return 0;
}