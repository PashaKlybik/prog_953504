/*8 ферзей. Можно ли разместить на пустой шахматной доске 8
ферзей так, чтобы ни один из них не «нападал» на другого?*/

#include <stdio.h>
#include <stdlib.h>

int board[8][8];

void Reset (int i, int j)
{
    for(int x = 0; x < 8; ++x)
    {
        --board [x][j];
        --board [i][x];

        int k;
        k = j - i + x;

        if (k >= 0 && k<8)
        {
            --board[x][k];
        }

        k = j + i - x;

        if (k >= 0 && k < 8)
        {
            --board[x][k];
        }
    }

    board[i][j] = 0;
}

void Set (int i, int j)
{
    for(int x = 0; x < 8; ++x)
    {
        ++board [x][j];
        ++board [i][x];

        int k;
        k = j - i + x;

        if (k >= 0 && k < 8)
        {
            ++board[x][k];
        }

        k = j + i - x;

        if (k >= 0 && k < 8)
        {
            ++board[x][k];
        }
    }

    board[i][j] = -1;
}

int Try (int i)
{
    int result = 0;
    for (int j = 0; j < 8; ++j)
    {
        if (board[i][j] == 0)
        {
            Set (i,j);
            if(i == 7)
            {
                result = 1;
            }
            else if(!(result = Try(i + 1)))
            {
                Reset (i,j);
            }
        }
        if(result)
        {
             break;
        }
    }

    return result;
}

int main()
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            board[i][j] = 0;
        }
    }

    Try (0);

    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if (board[i][j] == -1)
            {
                printf(" + ");
            }
            else
            {
                printf(" 0 ");
            }
        }
        printf("\n");
    }

    return 0;
}
