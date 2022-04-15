/* Conjecturses.c -- C Project 6- Conjecturses & Theorems */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<姜曜楠> 2102115 <学号> HDU
 * Date : 2021-11-22-11.56.59
 * Description : Different Kinds of Prime Numbers, Conjecture & Theorems. */

#define WIDTH 60
#define MIDDLE 25
#define LEFT 8
#define SPACE ' '
#define SIGN '*'

void goldbach(void);
int prime(int);
void collatz(void);
void nico(void);
void four(void);
void sieve(void);
void bride(void);
void truth(void);

 void main(void)
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
             goldbach();
             break;

         case 2:
             collatz();
             break;

         case 3:
             nico();
             break;

         case 4:
             four();
             break;

         case 5:
             sieve();
             break;

         case 6:
             bride();
             break;

         case 7:
             truth();
             break;

         case 8:
             break;

         default:
             printf("\nWrong! Please choose another true number!\n\n");
             main();
     }

     return 0;
 }

 void Menu(void)
 {
     int spaces;
     int middle;

     char * top = "THE MENU";
     char * start = "Conjectures";
     char * end = "CopyRight@JIANG YAONAN<姜曜楠> HDU";
     char * choice1 = "1-Goldbach's Conjecture<哥德巴赫猜想>";
     char * choice2 = "2-CollatzConjecture<考拉兹猜想>";
     char * choice3 = "3-Nico Chester Theorem<尼彻斯特定理>";
     char * choice4 = "4-Four Square Theorem<四平方数和定理>";
     char * choice5 = "5-Sieve of Eratosthenes<埃拉托斯特尼筛选法找质数>";
     char * choice6 = "6-Bride & Groom<新娘和新郎>";
     char * choice7 = "7-Truth or Lie<真实或谎言>";
     char * choice8 = "8-Exit";

     top_line('=', top);
     printf("\n\n");

     top_line('*', start);

     printf("\n\t%c",SIGN);
     show_n_char(SPACE,WIDTH);
     printf("%c",SIGN);
     printf("\n\t%c",SIGN);
     show_n_char(SPACE,WIDTH);
     printf("%c",SIGN);

     every_line('$',choice1);
     every_line('$',choice2);
     every_line('$',choice3);
     every_line('$',choice4);
     every_line('$',choice5);
     every_line('$',choice6);
     every_line('$',choice7);
     every_line('$',choice8);

     printf("\n\t%c",SIGN);
     show_n_char(SPACE,WIDTH);
     printf("%c",SIGN);

     top_line('*', end);
 }

 void top_line(char ch,char * pch)//头尾行输出
 {
     int m,i;

     m = (WIDTH - strlen(pch)) / 2;

     printf("\n\t%c",ch);
     show_n_char(ch,m);            //printf("%s", pch);
     for(i = 0; i < strlen(pch); i++){
         printf("%c",*(pch + i));
     }
     show_n_char(ch,WIDTH + 1 - strlen(pch) - m);
 }

 void every_line(char ch, char * pch)
 {
     printf("\n\t%c",ch);
     show_n_char(SPACE,LEFT);
     printf("%s",pch);
     show_n_char(SPACE,WIDTH - strlen(pch) - LEFT);
     printf("%c",ch);
     printf("\n\t%c",ch);
     show_n_char(SPACE,WIDTH);
     printf("%c",ch);
 }

 void show_n_char(char ch,int num)//输出num个ch字符
 {
     int count;

     for(count = 1; count <= num; count++){
         putchar(ch);
     }
 }

void goldbach(void)
{
    puts("For any even number N greater than or equal to 4,"
         "there exists\nat least one pair of prime numbers p1"
         "and p2 such that N = p1 + p2.");

    int sum;
    int count = 0;

    puts("NOTICE: Input 888 to Return to the Main Menu.");
    printf("\nPlease input a positive even integer:");
    fflush(stdin);
    scanf("%d",&sum);
    while(sum != 888){
        for (int i = 2; i < sum / 2; i++) {
            if ((prime(i) && prime(sum - i)) != 0) {
                printf("\n%d = %d + %d", sum, i, sum - i);
                count++;
            }
        }
        printf("\n\nThere are %d pair(s) of Prime Numbers "
               "that add up to %d", count, sum);
        puts("\n\nNOTICE: Input 888 to Return to the Main Menu.");
        printf("\nPlease input a positive even integer:");
        fflush(stdin);
        scanf("%d",&sum);
    }

    main();
}

int prime(int a)
{
    for (int i = 2; i <= a / 2; i++) {
        if (0 == a % i) {
            return 0;
        }
    }

    return 1;
}

void collatz(void)
{
    puts("Take any positive number: if it's even you divide "
         "it by 2 and if it's odd multiply\nit by 3 and add 1."
         "Repeat this process indefinitely, no matter what number"
         "you\nstart with, you will always end up at 1.\n\n"
          "The conjecture remains stubbornly unproven. "
          "Mathematics is not yet ready for such\nproblems.");

    int end, sta;
    int step = 0;

    puts("NOTICE: Input 888 to Return to the Main Menu.");
    printf("\nPlease input a positive even integer:");
    fflush(stdin);
    scanf("%d",&end);
    while(end != 888){
        sta = end;
        printf("%d ",sta);
        while(sta != 1){
            if(0 == sta % 2){
                sta = sta / 2;
                printf("-> %d ",sta);
            }
            else{
                sta = sta * 3 + 1;
                printf("-> %d ",sta);
            }

            step ++;
        }

        printf("\n\nThere are %d steps to get to %d for %d.",
               step, sta, end);
        puts("\n\nNOTICE: Input 888 to Return to the Main Menu.");
        printf("\nPlease input a positive even integer:");
        fflush(stdin);
        scanf("%d",&end);
    }

    main();
}

void nico(void)
{
    puts("Any integer to the third power can be represented "
         "as the sum of a series\nof consecutive odd Numbers.");

    int a, count = 0, num, sum = 0;
    int k[100] = {0};

    puts("NOTICE: Input 888 to Return to the Main Menu.");
    printf("\nPlease input a positive even integer:");
    fflush(stdin);
    scanf("%d",&a);
     while(a != 888){
        num = a * a * a;
        for (int i = 1; i < num ; i++) {
            for (int j = i; j < num; j++) {
                sum += j;
                if (sum == num) {
                    k[count] = i;
                    k[++count] = j;
                    count++;
                }
                j++;
            }
            sum = 0;
            i++;
        }
        for (int t = 0; t < count; t++) {
            printf("\t%d = ", num);
            for (int i = k[t]; i <= k[t + 1]; i++) {
                if (i == k[t]) {
                    printf("%d", i);;
                }
                else{
                    printf(" + %d", i);
                }
                i++;
            }
            printf("\n\n");
            t++;
        }

        puts("\n\nNOTICE: Input 888 to Return to the Main Menu.");
        printf("\nPlease input a positive even integer:");
        fflush(stdin);
        scanf("%d",&a);
    }

    main();
}

void four(void)
{
    puts("Four-square Theorem: Each positive integer may be "
         "expressed\nas the sum of the squares of four "
         "integers.");

    int sum, end;
    int k[4];

    puts("NOTICE: Input 888 to Return to the Main Menu.");
    printf("\nPlease input a positive even integer:");
    fflush(stdin);
    scanf("%d",&sum);
    while(sum != 888){
        end = (int)sqrt(sum);
        for (int a = 0; a <= end; a++) {
            for (int b = 0; b <= a; b++) {
                for (int c = 0; c <= b; c++) {
                    for (int d = 0; d <= c; d++) {
                        if (a * a + b * b + c * c + d * d == sum) {
                            printf("\n%d = %d x %d + %d x %d + "
                                    "%d x %d + %d x %d", sum,
                                    a, a, b, b, c, c, d, d);
                        }
                    }
                }
            }
        }
        puts("\n\nNOTICE: Input 888 to Return to the Main Menu.");
        printf("\nPlease input a positive even integer:");
        fflush(stdin);
        scanf("%d",&sum);
    }
    main();
}

void sieve(void)
{
    int end;
    char ch;

    puts("NOTICE: Input 888 to Return to the Main Menu.");
    printf("\nStart from 1, please input the end number:");
    fflush(stdin);
    scanf("%d",&end);
    while(end != 888){
        int k[10000] = {0};

        for (int i = 2; i <= end; i++) {
            k[i] = 1;
        }

        int t = 1;
        int count = 0;

        while (t <= end) {
            t++;
            if(0 == k[t]){
                continue;
            }

            count++;
            for (int i = t + 1; i < end + 1; i++) {
                if (0 == i % t) {
                    k[i] = 0;
                };
            }

        }
        printf("There are %d prime number between 1 and %d.",
                count, end);
        puts("\nPrint all these prime number<Y/N>:");
        fflush(stdin);
        if((ch = getchar()) == 'Y'){
            t = 2;
            while (t <= end) {
                if(1 == k[t]){
                    printf("%-10d", t);
                }
                t++;
            }
        }

        puts("\n\nNOTICE: Input 888 to Return to the Main Menu.");
        printf("\nStart from 1, please input the end number:");
        fflush(stdin);
        scanf("%d",&end);
    }
    main();
}

void bride(void)
{
    char ch;
    puts("There are 3 brides (A, B, C) and 3 grooms (X, Y, Z)."
         "\n\nA: I will marry X.\n\nX: My fiance is C."
         "\n\nC: I will marry Z.\n\nIt is known that they are"
         " all kidding.\n\nThen, do you know who and who are "
         "a couple?");
    puts("\nPress any key to show the answer.");
    fflush(stdin);
    scanf("%c",&ch);

    puts("\n\n\n\nThe groom X's bride is B."
         "\nThe groom Y's bride is C.");
    system("pause");
    main();
}

void truth(void)
{
    char ch;
    puts("Ben says that Bob is lying.\n\nBob says that Bill "
         "is lying.\n\nBill says that they are all lying.\n\n"
         "Then, do you know who is lying?");
    puts("\nPress any key to show the answer.");
    fflush(stdin);
    scanf("%c",&ch);

    puts("\n\n\n\nBen is lying.\n\nBob is true.\n\nBill is lying.");
    system("pause");
    main();
}

