#include <stdio.h>

int main (void)
{
    char pattern[10] = "apdren***";     // шаблон
    char words[10][10] = {              // набор слов из файла
        "apdrenone",    // + совпадает
        "apdre",
        "epddsntwo",
        "apdrentwo",    // + совпадает
        "epdrinale",
        "apd",
        "spddekale",
        "renrenone",
        "apdrensix"};   // + совпадает

    /* ищем все слова, которые совпадают с шаблоном */
    printf("equals:\n");
    int i, k;               // переменные - счетчики
    int equal;              // контроль совпадающих
    for (i=0; i<10; i++)    // проходим по всему списку слов
    {
        equal = 1;          // предполагаем, что слова совпадают
        for (k=0; pattern[k] && words[i][k] && equal; k++)
        {
            if (pattern[k] == '*') continue; // пропускаем шаблонный символ
            if (pattern[k] != words[i][k]) equal = 0;
        }
        if (pattern[k] || words[i][k]) equal = 0;   // проверим совпадают ли слова по длине
        if (equal>0) printf("%s\n", words[i]);
    }

    return 0;
}
