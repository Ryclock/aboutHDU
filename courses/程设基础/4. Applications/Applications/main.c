/* Applications.c -- C Project 4 - Applications of C programming. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<姜曜楠> 2102115 <学号> HDU
 * Date : 2021-11-22-11.47.17
 * Description : Applications of C programming.
 */

#define WIDTH 55
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '$'

void Menu(void);
void top_line(char ch, char  * pch);
void every_line(char ch, char * pch);
void show_n_char(char ch,int num);
void Hundred(void);
void Books(void);
void Criminal(void);
void Nine_Nine_Table(void);
void Chess(void);
void Factorization(void);
void Character(void);

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
        case 1:Hundred() ;break;
        case 2:Books() ;break;
        case 3:Criminal() ;break;
        case 4:Nine_Nine_Table() ;break;
        case 5:Chess() ;break;
        case 6:Factorization() ;break;
        case 7:Character() ;break;
        case 8: break;
        default: {printf("\n"),printf("Wrong! Please choose another true number!!\n"),printf("\n"),main();};
    }

    return 0;
}

void Menu(void)
{
    int spaces;
    int middle;

    char * top = "THE MENU";
    char * start = "Applications";
    char * end = "CopyRight@JIANG YAONAN<姜曜楠> HDU";
    char * choice1 = "1-Hundred Dollars & Hundred Chickens<百鸡百钱>";
    char * choice2 = "2-Five Books to Three Children<借书方案>";
    char * choice3 = "3-Criminal's Car Plate<逃犯的车牌>";
    char * choice4 = "4-Times Table 9x9<打印九九乘法表>";
    char * choice5 = "5-Chess Board<国际象棋棋盘>";
    char * choice6 = "6-Factoreization<分解质因数>";
    char * choice7 = "7-Character Analysis<字符统计>";
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
    show_n_char(ch,m);
    //printf("%s", pch);
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

void Hundred(void)
{
    int roost_price = 5;
    int hen_price = 3;
    int three_chick_price = 1;
    int money = 100;
    int number = 100;
    int sum = 0;
    int price = 0;
    int roost_number = 0;
    int hen_number = 0;
    int three_chick_number = 0;
    int i = 1;
    char ch;

    printf("\n\tZhang Qiujian, an ancient Chinese "
           "mathematician, once put forward \n\n\tthe famous"
           " problem of \"a hundred dollars buys a hundred"
           " chickens\"\n\n\tA rooster's price is 5 dollars; "
           "a hen's price is 3 dollars; \n\n\tthree chicks' "
           "price is one dollar. Question: To buy 100 "
           "chickens\n\n\twith 100 dollars, how many are "
           "each of the roosters, hens and chickens?");

    for(roost_number = 0; roost_number <= money / roost_price; roost_number++){
        for(hen_number = 0; hen_number <= money / hen_price; hen_number++){
            for(three_chick_number = 0; three_chick_number <= money / three_chick_price; three_chick_number++){
                if(roost_number + hen_number + three_chick_number * 3 == number && roost_number * roost_price + hen_number * hen_price + three_chick_number * three_chick_price == money){
                    printf("\n\n\tSolution %d: Rooster %d; Hen %d; Chick %d", i, roost_number, hen_number, three_chick_number * 3);
                    i++;
                }
            }
        }
    }

    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Books(void)
{
    int a,b,c;
    int i = 0;
    int books = 5;

    printf("\n\n\tThere are five books to lend to A,B and C.\
            \n\n\tIf everyone could borrow only one book,\
            \n\n\thow many different ways could they borrow the books?\
            \n\n");

    for(a = 1; a <= 5; a++){
        for(b = 1; b <= 5; b++){
            if(b != a){
                for(c = 1; c <= 5; c++){
                    if(c != a && c != b){
                        if(i % 3 == 0) printf("\n\t");
                        i++;
                        printf("   Solution %3d:%d,%d,%d",i,a,b,c);
                    }
                }
            }
        }
    }
    printf("\n");

    char ch;
    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Criminal(void)
{
    double a,b;

    printf("\n\tA car hit a man and ran away. No one remembers the \
            \n\tcar plate number, only some characteristics of it.\
            \n\n\tA said: the first two Numbers of the licence are the same;\
            \
            \n\n\tB said: the last two Numbers of the licence are the same,\
           \n\tbut different from the first two.\
            \
            \n\n\tC is a mathematician, and he said: the four-digit car number \
            \n\tis exactly the square of an integer.\
            \
            \n\n\tWhat is the car plate number?");

    for(a = 1; a <= 9; a++){
        for(b = 0; b <= 9; b++){
            if((int)sqrt(a * 1100 + b * 11) == sqrt(a * 1100 + b * 11)){
                printf("\n\n\n\n\tThe criminal's Car Plate is: %d",
                       (int)(a * 1100 + b * 11));
                break;
            }
        }
    }

    char ch;
    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Nine_Nine_Table(void)
{
    int a,b;

    for(a = 1; a <= 9; a++){
        for(b = 1; b <= a; b++){
            printf("\t%dx%d=%d", b, a, b * a);
        }
        printf("\n");
    }

    char ch;
    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Chess(void)
{
    int a,b;
    char * pch = "Printf a Chess Board";
    top_line('-',pch);

    for(a = 1; a <= 17; a++){
        printf("\n\t");
        for(b = 1; b <= 17; b++){
            if(a % 2 == b % 2){
                printf("■");
            }
            else{
                printf("  ");
            }
        }
    }

    char ch;
    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Factorization(void)
{
    int a,k,i,ant,t;

    printf("\tInput 888 to end Prime Factorization.\
           \n\tPlease input a positive integer:");
    scanf("%d",&a);

    while(a != 888){
        i = 2;
        t = 0;
        printf("\n\t%d =",a);
        while(a != 1){
            ant = 0;
            for(k = 1; k <= i; k++){
                if(i % k == 0) ant++;
            }
            if(ant == 2 && a % i ==0){
                t++;
                if(t != 1) printf("x");
                printf(" %d ",i);
                a = a / i;
            }
            else i++;
        }
        printf("\n\n\tPlease input a positive integer:");
        fflush(stdin);
        scanf("%d",&a);
    }

    char ch;
    printf("\n\n\tPress Q to Exit the program, others to the Menu:");
    fflush(stdin);
    if((ch = getchar()) != 'Q') main();
}

void Character(void)
{
    char ch;
    char c1 = '0';
    char c2 = '0';
    int i = 0;
    int letter_ant, number_ant, space_ant, others_ant;

    printf("\tString ending in 8 will return to the Menu.");

    while(c1 != '8' || c2 != '\n'){
        letter_ant = 0;
        number_ant = 0;
        space_ant = 0;
        others_ant = 0;

        printf("\n\n\tPlease input a string:");
        fflush(stdin);
        while((ch = getchar()) != EOF){
            if(ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z'){
                letter_ant++;
            }
            else if(ch >= '0' && ch <= '9') {
                number_ant++;
            }
            else if(ch == ' '){
                space_ant++;
            }
            else{
                others_ant++;
            }
            c1 = c2;
            c2 = ch;
        }
        printf("\n\tLetters:%d",letter_ant);
        printf("\n\n\tNumbers:%d",number_ant);
        printf("\n\n\tSpaces :%d",space_ant);
        printf("\n\n\tOthers :%d7",others_ant);
    }
    printf("\n");
    main();
}

