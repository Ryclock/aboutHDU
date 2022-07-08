#include <stdio.h>
#include <stdlib.h>
#include "HanoiTower.h"

void hanoiTowerTest(void)
{
    int input;
    do
    {
        printf("\n\nPlease input a number: ");
        scanf("%d", &input);
        int stepCount = 0;
        hanoiTower(input, 'A', 'B', 'C', &stepCount);
        printf("\n\nThe total steps are: %d", stepCount);
    } while (input != 8);
}

void hanoiTower(int num, char src, char hub, char dest, int *pCount)
{
    if (num == 1)
    {
        (*pCount)++;
        printf("\nStep%d: Move from %c to %c", *pCount, src, dest);
    }
    else
    {
        hanoiTower(num - 1, src, dest, hub, pCount);
        hanoiTower(1, src, hub, dest, pCount);
        hanoiTower(num - 1, hub, src, dest, pCount);
    }
}
