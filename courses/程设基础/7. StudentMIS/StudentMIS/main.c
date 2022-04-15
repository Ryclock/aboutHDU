/*  StudentMIS.c -- C Project 7 - Students MIS */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

#include "menu.h"
#include "student.h"
#include "show.h"
#include "others.h"
#include "add.h"
#include "modify.h"
#include "delete.h"
#include "sort.h"


/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<½ªê×éª> 2102115 <Ñ§ºÅ> HDU
 * Date : 2021-11-29-14.43.14
 * Description : Student Management Information System(MIS).
 */

int main(void)
{
    int choice;
    Menu();
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    scanf("%d",&choice);
    printf("\n");

    switch(choice)
    {
        case 1:
            system("color 5f");
            load();
            break;

        case 2:
            show_top();
            show('R',0);
            system("pause");
            main();
            break;

        case 3:
            sear();
            break;

        case 4:
            add();
            break;

        case 5:
            mod();
            break;

        case 6:
            del();
            break;

        case 7:
            sor_stuno();
            break;

        case 8:
            sor_name();
            break;

        case 9:
            sor_gen();
            break;

        case 10:
            sor_pho();
            break;

        case 11:
            sor_wec();
            break;

        case 12:
            sor_dor();
            break;

        case 13:
            sor_sco();
            break;

        case 14:
            statis();
            break;

        case 15:
            clear();
            break;

        case 16:
            save();
            break;

        case 17:
            show_sel();
            break;

        case 18:
            break;

        default:
            printf("\nWrong! Please choose another true number!\n\n");
            main();
    }

    return 0;
}

