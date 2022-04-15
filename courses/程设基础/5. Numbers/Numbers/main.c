/* Numbers.c -- C Project 5 - Numbers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<姜曜楠> 2102115 <学号> HDU
 * Date : 2021-11-22-11.45.29
 * Description : Interesting Numbers.
 */

#define WIDTH 58
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '$'

void Menu(void);
void top_line(char ch, char  * pch);
void every_line(char ch, char * pch);
void show_n_char(char ch,int num);
void Perfect(void);
void Perfect_att(void);
void Friendly(void);
void Friendly_att(void);
void Narcissistic(void);
void Armstrong(void);
void Triple(void);
void Mantissa(void);
void LM_GD(void);

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
        case 1:Perfect() ;break;
        case 2:Friendly() ;break;
        case 3:Narcissistic() ;break;
        case 4:Armstrong() ;break;
        case 5:Triple() ;break;
        case 6:Mantissa() ;break;
        case 7:LM_GD() ;break;
        case 8: break;
        default: {printf("\n"),printf("Wrong! Please choose another true number!!\n"),printf("\n"),main();};
    }

    return 0;
}

//打印菜单
void Menu(void)
{
    int spaces;
    int middle;

    char * top = "THE MENU";
    char * start = "Applications";
    char * end = "CopyRight@JIANG YAONAN<姜曜楠> HDU";
    char * choice1 = "1-Perfect Number<完数>";
    char * choice2 = "2-Friendly Number<亲密数>";
    char * choice3 = "3-Narcissistic Number<水仙花数>";
    char * choice4 = "4-Armstrong Number<阿姆斯特朗数>";
    char * choice5 = "5-Pythagorean Triple<勾股数>";
    char * choice6 = "6-Mantissa<高次方数的尾数>";
    char * choice7 = "7-Lowest Common Multiple & Greatest Common Divisor";
    char * choice7_att = "              <最小公倍数和最大公约数>";
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
    every_line('$',choice7_att);
    every_line('$',choice8);


    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);

    top_line('*', end);
}

//头尾行输出
void top_line(char ch,char * pch)
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

//每行的输出
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

//输出num个ch字符
void show_n_char(char ch,int num)
{
    int count;

    for(count = 1; count <= num; count++){
        putchar(ch);
    }
}

void Perfect(void)
{
    char * ppch = "Perfect Numbers";

    top_line('-', ppch);
    printf("\n\n\tA perfect number is a positive integer that is "
           "equal\n\tto the sum of all its proper divisors<真因子>."
           " For example, 6,\n\twhose proper divisors are 1, 2, "
           "and 3, and indeed 6 = 1 + 2 + 3.");
    printf("\n\n\tNOTICE: Input 888 to Return to the Main Menu.");

    Perfect_att();
}

void Perfect_att(void)
{
    int sta_num, end_num;
    int i; // 可能的完数
    int k; // 完数可能的因子
    int sum; // 完数因子的和（除去本身）
    int ant = 0; // 完数个数
    int m;

    printf("\n\n\tPlease input the start number:");
    scanf("%d", &sta_num);
    if(sta_num == 888){
        printf("\nYou will return to the Main Menu!\n");
        main();
    }
    printf("\n\n\tPlease input the end number:");
    scanf("%d", &end_num);
    if(end_num == 888){
        printf("\nYou will return to the Main Menu!\n");
        main();
    }

    int a[end_num]; // 完数因子


    for(i = sta_num; i <= end_num; i++){
        memset(a, 0, sizeof(a)); //将a数组所有元素赋值为零
        sum = 1;
        m = 0;
        // 寻找因子
        for(k = 2; k <= i / 2; k++){
            if(i % k == 0){
                sum += k;
                a[m] = k;
                m++;
            }
        }
        // 判断完数（按格式输出）
        if(sum == i && i != 1){
            printf("\n\n\t%d is a perfect numbers: 1", i);
            m = 0;
            while(a[m] != 0){
                printf("+%d",a[m]);
                m++;
            }
            ant++;
        }
    }
    //总结
    printf("\n\n\tThere are %d perfect numbers between %d "
           "and %d.",ant,sta_num,end_num);

    // 回环
    Perfect_att();
}

void Friendly(void)
{
    char * ppch = "Friendly Numbers";

    top_line('-', ppch);
    printf("\n\n\tThere are two integers a and b. If the sum "
            "of b's divisors"
            "\n\tequals to a, and the sum of a's divisors "
            "equals to b, we call"
            "\n\tthese two integers are \"Friendly Numbers"
            "\n\n\tE.g:"
            "\n\n\t284 and 220"
            "\n\n\t284's divisors: 1+2+4+71+142=220"
            "\n\n\t220's divisors: 1+2+4+5+10+11+20+22+44+55+110=284"
            "\n\n\tSo 9 and 4 are not Friendly numbers.");

    printf("\n\n\tNOTICE: Input 888 to Return to the Main Menu.");

    Friendly_att();
}

void Friendly_att(void)
{
    int sta_num,end_num;
    int a,b; // 可能的亲密数
    int k; // 可能的因子
    int sum_a, sum_b; // 因子和
    int fri_ant = 0; // 亲密数组数

    // 输入起点和终点
    printf("\n\n\tPlease input the start number:");
    scanf("%d", &sta_num);
    if(sta_num == 888){
        printf("\nYou will return to the Main Menu!\n");
        main();
    }
    printf("\n\tPlease input the end number:");
    scanf("%d", &end_num);
    if(end_num == 888){
        printf("\nYou will return to the Main Menu!\n");
        main();
    }

    // 寻找亲密数
    int a_d[end_num],b_d[end_num];
    int m;

    for(a = sta_num; a <= end_num; a++){
        sum_a = 1;
        m = 0;
        // 寻找因子
        for(k = 2; k <= a / 2; k++){
            if(a % k == 0){
                a_d[m] = k;
                sum_a += k;
            }
        }
        for(b = a + 1; b <= end_num; b++){
            if(sum_a == b){
                sum_b = 1;
                m = 0;
                // 寻找因子
                for(k = 2; k <= b / 2; k++){
                    if(b % k == 0){
                        b_d[m] = k;
                        sum_b += k;
                    }
                }
                // 亲密数输出
                if(sum_b == a){
                    printf("\n\n\t%d and %d are friendly numbers.",
                            a, b);

                    printf("\n\n\t%d's divisors: 1", a);
                    m = 0;

                    // 输出证明
                    while(a_d[m] != 0){
                        printf("+%d",a_d[m]);
                        m++;
                    }
                    printf("=%d",b);

                    printf("\n\n\t%d's divisors: 1", b);
                    m = 0;
                    while(b_d[m] != 0){
                        printf("+%d",b_d[m]);
                        m++;
                    }
                    printf("=%d",a);

                    // 计数
                    fri_ant++;
                }
            }
        }
    }

    // 总结
    printf("\n\n\tThere are %d pairs of friendly numbers between %d "
           "and %d.",fri_ant,sta_num,end_num);

    // 回环
    Friendly_att();
}

void Narcissistic(void)
{
    printf("\tIf a positive 3-digits integer is equal to the sum"
           " of its every"
           "\nfigure's 3th power, we call the number Narcissistic"
           " Number.");

    int a,b,c,i;
    int nn[999 - 100 + 1] = {0}; // 用于记录水仙花数
    int m = 0;

    // 寻找水仙花数
    for(i = 100; i < 1000; i++){
        a = i /100;
        b = (i % 100) / 10;
        c = i % 10;
        if(pow(a,3) + pow(b,3) + pow(c,3) == i){
            nn[m] = i;
            m++;
        }
    }
    //输出
    printf("\n\n\tThe Narcissistic Numbers are:");
    m = 0;
    while(nn[m] != 0){
        printf(" %d",nn[m]);
        m++;
    }

    // 返回
    printf("\n\n\tPRESS ANY KEY TO RETURN TO THE MENU.");
    fflush(stdin);
    getchar();
    main();
}

void Armstrong(void)
{
    printf("\n\tAn Armstrong number is a number that is equal to the"
           "sum of \ndigits raise to the power total number of "
           "digits in the number.");

    const int sta_digits = 1;
    const int end_digits = 8;
    int i, t, sum, k, b, n;
    int m = 0;
    int a[100] = {0}; // 记录对应位数的阿姆斯特朗数

    for(i = sta_digits; i <= end_digits; i++){
        n = m;
        // 寻找阿姆斯特朗数
        for(t = (int)pow(10,i - 1); t < (int)pow(10,i); t++){
            k = t;
            b = i;
            sum = 0;
            for(b; b > 0; b--){
                sum += (int)pow(k / (int)pow(10,b - 1),i);
                k = k % (int)pow(10, b -1);
            }
            sum += (int)pow(k,i);

            if(sum == t){
                a[m] = t;
                m++;
            }
        }
        //输出
        printf("\n\n\tThe Armstrong numbers of %d digits are:",i);
        while(a[n] != 0){
            printf(" %d",a[n]);
            n++;
        }
    }

    // 返回
    printf("\n\n\tPRESS ANY KEY TO RETURN TO THE MENU.");
    fflush(stdin);
    getchar();
    main();
}

void Triple(void)
{
    printf("\n\tTriples of positive integers can construct a right "
           "triangle"
           "\n\twith segments of lengths corresponding to triple. "
           "\n\n\tFor example (3,4,5) (5,12,13) (6,8,10)");

    printf("\n\n\tNOTICE: Input 888 to Return to the Main Menu.");

    int sta_num,end_num;
    printf("\n\n\tPlease input the start number:");
    scanf("%d", &sta_num);
    printf("\n\n\tPlease input the end number:");
    scanf("%d", &end_num);

    int m = 0;
    for(int a = sta_num; a <= end_num - 2; a++){
        for(int c = a + 2; c <= end_num; c++){
            int b = (int)sqrt(c * c - a * a);
            if(b * b == c * c - a * a && a + b > c && b > a){
                    if(0 == m % 4) printf("\n\t");
                    printf("%8d %3d %3d",a,b,c);
                    m++;

            }
        }
    }

    printf("\n\n\tThere are %d Pythagorean Triples between %d and %d",
           m, sta_num, end_num);

    // 返回
    printf("\n\n\tPRESS ANY KEY TO RETURN TO THE MENU.");
    fflush(stdin);
    getchar();
    main();
}

void Mantissa(void)
{

    printf("\n\tFind the last n digits of Base to the Exponent power."
           "\n\tFor example, find the last 3 digits of 13^13.");

    printf("\n\n\tNOTICE: Input 888 to Return to the Main Menu.");

    int base, exponent, digits, out, i;
    printf("\n\n\tPlease input a positive integer for the Base:");
    scanf("%d", &base);
    printf("\n\tPlease input a positive integer for the Exponent:");
    scanf("%d", &exponent);
    printf("\n\n\tPlease input a positive integer for the Digits<1-6>:");
    scanf("%d", &digits);

    out = 1;
    for(i = 1; i <= exponent; i++){
        out =  out * base % 1000;
    }

    printf("\n\n\n\tThe last %d digits of %d to the %d power is %d",
           digits, base, exponent,out);

    // 返回
    printf("\n\n\tPRESS ANY KEY TO RETURN TO THE MENU.");
    fflush(stdin);
    getchar();
    main();
}

void LM_GD(void)
{
    printf("\n\nLowest Common Multiple: Lowest Common Multiple:the "
           "smallest common multiple of two or more numbers."
           "\n\nGreatest Common Divisor: The largest integer that is"
           " an exact divisor of each of two or more integers.");

    printf("\n\n\tNOTICE: Input 888 to Return to the Main Menu.");

    int fir_num, sec_num, a, b, c, lcm, gcd;

    printf("\n\n\tPlease input the first number:");
    scanf("%d",&fir_num);
    a = fir_num;
    printf("\n\tPlease input the second number:");
    scanf("%d",&sec_num);
    b = sec_num;

    while(a != b){
        // b = (b = (a > b? a: b) ) - (a = (a < b? a: b) );
        c = (a > b? a: b) - (a < b? a: b);
        a = a < b? a: b;
        b = c;
    }
    gcd = a;
    lcm = fir_num * sec_num / gcd;

    printf("\n\n\n\tThe Lowest Common Multiple of %d and %d is %d",
           fir_num,sec_num,lcm);
    printf("\n\n\n\tThe Greatest Common Divisor of %d and %d is %d",
           fir_num,sec_num,gcd);

    // 返回
    printf("\n\n\tPRESS ANY KEY TO RETURN TO THE MENU.");
    fflush(stdin);
    getchar();
    main();
}

