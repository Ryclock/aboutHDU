/* Bit operation.c --  to do some bit operations of numbers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : Ryclock
 * Date : 2021-12-27-10.54.29
 * Description : to do some bit operations of numbers
 */

#include "menu.h"
#include "expasion.h"
#include "basic.h"
#include "application.h"

int main(void)
{
    int choice;
    Menu();
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        system("color 5f");
        bit_and();
        system("pause");
        main();
        break;

    case 2:
        bit_or;
        system("pause");
        main();
        break;

    case 3:
        bit_not_or;
        system("pause");
        main();
        break;

    case 4:
        bit_not;
        system("pause");
        main();
        break;

    case 5:
        bit_left();
        system("pause");
        main();
        break;

    case 6:
        bit_right();
        system("pause");
        main();
        break;

    case 7:
        printfBinary();
        system("pause");
        main();
        break;

    case 8:
        encryption();
        system("pause");
        main();
        break;

    case 9:
        decrypt();
        system("pause");
        main();
        break;

    case 10:
        C_E_devision();
        system("pause");
        main();
        break;

    default:
        printf("\nWrong! Please choose another true number!\n\n");
        system("pause");
        main();
    }

    return 0;
}
