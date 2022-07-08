/*
 * Copyright(C)
 * All rights reserved.
 * Author : Ryclock 2102115 HDU
 * Date : 2022-02-21-08.54.14
 * Description : Sequence List Basic System for Sequence List class.
 */

#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "HanoiTower.h"
#include "Backpack.h"
#include "NQueen.h"
#include "Maze.h"

char lang = 'C';

void case11(void)
{
    printf("\nYou have 3 rods and N disks of different sizes which can slide onto any tower."
           "The disks are sorted in ascending order of size from top to bottom. You have the "
           "following constraints:\n");
    printf("\n*(A)Only one disk can be moved at a time."
           "\n*(B)A disk is slid off the top of one rod onto the next rod."
           "\n*(C)A disk can only be placed on top of a larger disk.\n");
    printf("\nWrite a program to move the N disks from the first rod to the last rod.\n");
    printInfoLine('=', "Press 8 to return to MENU");
    hanoiTowerTest();
}

void case13(void)
{
    printf("\nA backpack has a volume of T. There are N items with volumes of W0, W1...Wn-1. "
           "Ask if you can put some of these N items into the backpack so that the sum of their "
           "volumes is exactly T. For example:");
    printf("\n\t(A)The volume of the backpack is T=10."
           "\n\t(B)The number of the items is N=6."
           "\n\t(C)Each volume of the items is W[6]={1,8,4,3,5,2}."
           "\n\t(D)The solutions are: (1,4,3,2) (1,4,5) (8,2) (3,5,2)");
    system("pause");
    backpackTest();
}

void case14(void)
{
    printf("\nThe N-queen problem is the generalized problem of 8-queens or 4 queens' problem. "
           "Here, the N-queens are placed on a N * N chess board, which means that the chess board "
           "has N rows and N columns and the N queens are placed on thus N * N chess board such that"
           " no two queens are placed in the same row or in the same column or in same diagonal. So "
           "that, no two queens attack each other.");
    system("pause");
    nQueenTest();
}

void case15(void)
{
    printf("\nGiven a maze, find a path from start to goal.");
    system("pause");
    mazeTest();
}

void analysis_Choices(int choice)
{
    switch (choice)
    {
    case 11:
        case11();
        break;
    case 13:
        case13();
        break;
    case 14:
        case14();
        break;
    case 15:
        case15();
        break;
    case 16:
        exit(EXIT_SUCCESS);
        break;
    default:
        printf("\nWrong! Please choose another true number!\n\n");
    }
}

int main(void)
{
    while (1)
    {
        Menu(lang);
        analysis_Choices(inputChoice());
        system("pause");
    }
    return 0;
}
