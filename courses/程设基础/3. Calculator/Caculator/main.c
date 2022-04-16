/* caculation.c --  C Project 3 - Calculator. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : Ryclcok
 * Date : 2021-11-22-11.48.55
 * Description : Basic functions of a calcualtor for children.
 */

#define WIDTH 40
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '*'

void Menu(void);
void top_line(char ch, char *pch);
void every_line(char *left, char *right);
void show_n_char(char ch, int num);
int Max(int a, int b);
void Add(void);
void Minus(void);
void Multiply(void);
void Divide(void);
void Mixed(void);

void main(void)
{
    int choice;

    Menu();
    printf("\n\n\tPlease choose one number : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        Add();
        break;
    case 2:
        Minus();
        break;
    case 3:
        Multiply();
        break;
    case 4:
        Divide();
        break;
    case 5:
        Mixed();
        break;
    case 6:
        return 0;
    default:
    {
        printf("\n\t"),
            printf("Wrong! Please choose another true \
                       number!!\n"),
            printf("\n"), main();
    };
    }

    return 0;
}

void Menu(void)
{
    int spaces;
    int middle;

    char *top = "THE MENU";
    char *start = "Caculation";
    char *end = "Made@Ryclcok";
    char *choice1 = "1.add(+)";
    char *choice2 = "2.minus(-)";
    char *choice3 = "3.multiply(*)";
    char *choice4 = "4.divide(/)";
    char *choice5 = "5.mixed ";
    char *choice6 = "6.Exit";

    top_line('=', top);
    printf("\n\n");

    top_line('*', start);

    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);
    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);

    every_line(choice1, choice2);
    every_line(choice3, choice4);
    every_line(choice5, choice6);

    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);
    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);

    top_line('*', end);
}

void top_line(char ch, char *pch) //头尾行输出
{
    int m, i;

    m = (WIDTH - strlen(pch)) / 2;

    printf("\n\t%c", ch);
    show_n_char(ch, m);
    // printf("%s", pch);
    for (i = 0; i < strlen(pch); i++)
    {
        printf("%c", *(pch + i));
    }
    show_n_char(ch, WIDTH + 1 - strlen(pch) - m);
}

void every_line(char *left, char *right) //控制每行的left和right分别对齐
{
    int middle, spaces;

    printf("\n\t");
    middle = MIDDLE - strlen(left) - LEFT;
    spaces = WIDTH - strlen(left) - strlen(right) - LEFT - middle;
    putchar(SIGN);
    show_n_char(SPACE, LEFT);
    printf("%s", left);
    show_n_char(SPACE, middle);
    printf("%s", right);
    show_n_char(SPACE, spaces);
    putchar(SIGN);
}

void show_n_char(char ch, int num) //输出num个ch字符
{
    int count;

    for (count = 1; count <= num; count++)
    {
        putchar(ch);
    }
}

int Max(int a, int b)
{
    int c;
    c = a + b;
    if (a < b)
    {
        a = b;
    }
    return a;
}

void Add(void) //同理注释函数Minus,Multiply,Divide
{
    int x, y, z;
    int answer = 0;

    printf("\n\tInput number 888 to return Menu!!!");
    printf("\n");

    srand((unsigned)time(NULL));
    x = rand() % 100 + 1;
    y = rand() % 100 + 1;
    z = x + y; //随机生成下，一百以内的自然数x和y，并计算他们的和z

    printf("\n\t%d + %d = ", x, y);
    scanf("%d", &answer);

    while (answer != 888)
    {
        if (z == answer)
        {
            x = rand() % 100 + 1;
            y = rand() % 100 + 1;
            z = x + y;
            printf("\n\t%d + %d = ", x, y);
        }
        else
        {
            printf("\n");
            printf("\n\tWrong!!! Please try again!\n");
            printf("\n\t%d + %d = ", x, y);
        }
        scanf("%d", &answer);
    }; //利用while循环满足多次不相同的计算练习

    printf("\n");
    main();
}

void Minus(void)
{
    int x, y, z;
    int answer = 0;

    printf("\n\tInput number 888 to return Menu!!!");
    printf("\n");

    srand((unsigned)time(NULL));
    x = rand() % 100 + 1;
    y = rand() % 100 + 1;
    z = x + y;
    x = Max(x, y);
    y = z - x;
    z = x - y;

    printf("\n\t%d - %d = ", x, y);
    scanf("%d", &answer);

    while (answer != 888)
    {
        if (z == answer)
        {
            x = rand() % 100 + 1;
            y = rand() % 100 + 1;
            z = x - y;
            printf("\n\t%d - %d = ", x, y);
        }
        else
        {
            printf("\n");
            printf("\n\tWrong!!! Please try again!\n");
            printf("\n\t%d - %d = ", x, y);
        }
        scanf("%d", &answer);
    };

    printf("\n");
    main();
}

void Multiply(void)
{
    int x, y, z;
    int answer = 0;

    printf("\n\tInput number 888 to return Menu!!!");
    printf("\n");

    srand((unsigned)time(NULL));
    x = rand() % 10 + 1;
    y = rand() % 10 + 1;
    z = x * y;

    printf("\n\t%d * %d = ", x, y);
    scanf("%d", &answer);

    while (answer != 888)
    {
        if (z == answer)
        {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            z = x * y;
            printf("\n\t%d * %d = ", x, y);
        }
        else
        {
            printf("\n");
            printf("\n\tWrong!!! Please try again!\n");
            printf("\n\t%d * %d = ", x, y);
        }
        scanf("%d", &answer);
    };

    printf("\n");
    main();
}

void Divide(void)
{
    int x, y, z;
    int answer = 0;

    printf("\n\tInput number 888 to return Menu!!!");
    printf("\n");

    srand((unsigned)time(NULL));
    x = rand() % 10 + 1;
    y = rand() % 10 + 1;
    z = x * y;
    x = z;
    z = x / y;

    printf("\n\t%d / %d = ", x, y);
    scanf("%d", &answer);

    while (answer != 888)
    {
        if (z == answer)
        {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            z = x * y;
            x = z;
            z = x / y;
            printf("\n\t%d / %d = ", x, y);
        }
        else
        {
            printf("\n");
            printf("\n\tWrong!!! Please try again!\n");
            printf("\n\t%d / %d = ", x, y);
        }
        scanf("%d", &answer);
    };

    printf("\n");
    main();
}

void Mixed(void)
{
    int x, y, z;
    int i;
    char c;
    int answer = 0;

    printf("\n\tInput number 888 to return Menu!!!");
    printf("\n");

    srand((unsigned)time(NULL));
    i = rand() % 4 + 1;
    switch (i)
    {
    case 1:
        c = '+';
        break;
    case 2:
        c = '-';
        break;
    case 3:
        c = '*';
        break;
    case 4:
        c = '/';
        break;
    } //随机产生四则运算的符号

    switch (c)
    {
    case '+':
        x = rand() % 100 + 1;
        y = rand() % 100 + 1;
        z = x + y;
        break;
    case '-':
        x = rand() % 100 + 1;
        y = rand() % 100 + 1;
        z = x + y;
        x = Max(x, y);
        y = z - x;
        z = x - y;
        break;
    case '*':
        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        z = x * y;
        break;
    case '/':
        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        z = x * y;
        x = z;
        z = x / y;
        break;
    }

    printf("\n\t%d %c %d = ", x, c, y);
    scanf("%d", &answer);

    while (answer != 888)
    {
        if (z == answer)
        {
            i = rand() % 4 + 1;
            switch (i)
            {
            case 1:
                c = '+';
                break;
            case 2:
                c = '-';
                break;
            case 3:
                c = '*';
                break;
            case 4:
                c = '/';
                break;
            }
            switch (c)
            {
            case '+':
                x = rand() % 100 + 1;
                y = rand() % 100 + 1;
                z = x + y;
                break;
            case '-':
                x = rand() % 100 + 1;
                y = rand() % 100 + 1;
                z = x + y;
                x = Max(x, y);
                y = z - x;
                z = x - y;
                break;
            case '*':
                x = rand() % 10 + 1;
                y = rand() % 10 + 1;
                z = x * y;
                break;
            case '/':
                x = rand() % 10 + 1;
                y = rand() % 10 + 1;
                z = x * y;
                x = z;
                z = x / y;
                break;
            }
            printf("\n\t%d %c %d = ", x, c, y);
        }
        else
        {
            printf("\n");
            printf("\n\tWrong!!! Please try again!\n");
            printf("\n\t%d %c %d = ", x, c, y);
        }
        scanf("%d", &answer);
    }; //同样利用while循环满足多次不相同的计算练习

    printf("\n");
    main();
}
