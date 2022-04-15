/* Tickets_System.c -- C Program 8 - Tickets System. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<�����> 2102115 <ѧ��> HDU
 * Date : 2021-11-22-11.42.29
 * Description : Tickets Management Information System(MIS).
 */

#define WIDTH 46
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '*'

void Menu(void);
void top_line(char ch, char *pch);
void every_line(char *left, char *right);
void show_n_char(char ch, int num);
void create(void);
void status(void);
void back(void);
void sell(void);
void refund(void);
void booking(void);
void cancellation(void);
void search(void);

int available = 0, sold = 0, reserved = 0;
int rows, cols;
char **tickets;

int main(void)
{
    int choice;

    Menu();
    printf("\n\n\tPlease choose one number : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        create();
        break;
    case 2:
        status();
        back();
        break;
    case 3:
        status();
        sell();
        break;
    case 4:
        status();
        refund();
        break;
    case 5:
        status();
        booking();
        break;
    case 6:
        status();
        cancellation();
        break;
    case 7:
        search();
        break;
    case 8:
        return 0;
    default:
    {
        printf("\n\t"),
            printf("Wrong! Please choose another true \
                       number!!\n"),
            printf("\n"), main();
    };
    }

    for (int i = 0; i < rows; i++)
    {
        free(tickets[i]);
    }
    free(tickets);
    return 0;
}

void Menu(void)
{
    int spaces;
    int middle;

    char *top = "THE MENU";
    char *start = "Tickets System";
    char *end = "CopyRight@JIANG YAONAN<�����> HDU";
    char *choice1 = "1.Create Theater";
    char *choice2 = "2.Show Status";
    char *choice3 = "3.Sell Ticket";
    char *choice4 = "4.Refund";
    char *choice5 = "5.Book Ticket";
    char *choice6 = "6.Cancellation";
    char *choice7 = "7.Search";
    char *choice8 = "8.Exit";

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
    every_line(choice7, choice8);

    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);
    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);

    top_line('*', end);
}

void top_line(char ch, char *pch) //ͷβ�����
{
    int m, i;

    m = (WIDTH - strlen(pch)) / 2;

    printf("\n\t%c", ch);
    show_n_char(ch, m);
    //printf("%s", pch);
    for (i = 0; i < strlen(pch); i++)
    {
        printf("%c", *(pch + i));
    }
    show_n_char(ch, WIDTH + 1 - strlen(pch) - m);
}

void every_line(char *left, char *right) //����ÿ�е�left��right�ֱ����
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

void show_n_char(char ch, int num) //���num��ch�ַ�
{
    int count;

    for (count = 1; count <= num; count++)
    {
        putchar(ch);
    }
}

void create(void)
{
    available = sold = reserved = 0;

    printf("\nPlease input the Rows of the theater:");
    scanf("%d", &rows);
    printf("\nPlease input the Columns of the theater:");
    scanf("%d", &cols);
    available = rows * cols;
    tickets = (char **)malloc(rows * sizeof(int *));

    top_line('=', "Theater Tickets Create Success");
    printf("\n\t a: %d available     b: %d sold      "
           "c: %d reserved",
           available, sold, reserved);

    printf("\n   ");
    for (int i = 1; i <= cols; i++)
    {
        printf("%4d", i);
    }
    for (int m = 0; m < rows; m++)
    {
        printf("\n%3d", m + 1);
        tickets[m] = (char *)malloc(cols * sizeof(int));
        for (int n = 0; n < cols; n++)
        {
            tickets[m][n] = 'a';
            printf("   %c", tickets[m][n]);
        }
    }

    back();
}

void status(void)
{
    printf("\n\t a: %d available     b: %d sold      "
           "c: %d reserved",
           available, sold, reserved);

    printf("\n   ");
    for (int i = 1; i <= cols; i++)
    {
        printf("%4d", i);
    }
    for (int m = 0; m < rows; m++)
    {
        printf("\n%3d", m + 1);
        for (int n = 0; n < cols; n++)
        {
            printf("   %c", tickets[m][n]);
        }
    }
}

void back(void)
{
    puts("\nPress any key to return to the MENU.");
    fflush(stdin);
    getchar();
    main();
}

void sell(void)
{
    // ��ʼ��Ʊ
    int change_row, change_col;

    printf("\nPlease input the row:");
    scanf("%d", &change_row);
    printf("\nPlease input the column:");
    scanf("%d", &change_col);

    if (change_row > rows || change_row < 1 ||
        change_col > cols || change_col < 1)
    {
        printf("\n\nThe seat number <%d,%d> doesn't exist!",
               change_row, change_col);
        puts("\nPlease change the seat number.");
        sell(); // different
    }
    else
    { // different
        if ('a' == tickets[change_row - 1][change_col - 1])
        {
            tickets[change_row - 1][change_col - 1] = 'b';
            available--;
            sold++;
            printf("\n\tTicket:<%d,%d> sold success.\n",
                   change_row, change_col);
        }
        else
        {
            printf("\n\nYou can't buy <%d,%d>!",
                   change_row, change_col);
            puts("\nPlease change the seat number.");
            sell();
        }
    }

    status();
    back();
}

void refund(void)
{
    // ��ʼ��Ʊ
    int change_row, change_col;

    printf("\nPlease input the row:");
    scanf("%d", &change_row);
    printf("\nPlease input the column:");
    scanf("%d", &change_col);

    if (change_row > rows || change_row < 1 ||
        change_col > cols || change_col < 1)
    {
        printf("\n\nThe seat number <%d,%d> doesn't exist!",
               change_row, change_col);
        puts("\nPlease change the seat number.");
        refund(); // different
    }
    else
    { // different
        if ('b' == tickets[change_row - 1][change_col - 1])
        {
            tickets[change_row - 1][change_col - 1] = 'a';
            available++;
            sold--;
            printf("\n\tTicket:<%d,%d> refund success.\n",
                   change_row, change_col);
        }
        else
        {
            printf("\n\nYou can't refund <%d,%d>!\n",
                   change_row, change_col);
            puts("\nPlease change the seat number.");
            refund();
        }
    }

    status();
    back();
}

void booking(void)
{
    // ��ʼ��Ʊ
    int change_row, change_col;

    printf("\nPlease input the row:");
    scanf("%d", &change_row);
    printf("\nPlease input the column:");
    scanf("%d", &change_col);

    if (change_row > rows || change_row < 1 ||
        change_col > cols || change_col < 1)
    {
        printf("\n\nThe seat number <%d,%d> doesn't exist!",
               change_row, change_col);
        puts("\nPlease change the seat number.");
        booking(); // different
    }
    else
    { // different
        if ('a' == tickets[change_row - 1][change_col - 1])
        {
            tickets[change_row - 1][change_col - 1] = 'c';
            available--;
            reserved++;
            printf("\n\tTicket:<%d,%d> book success.\n",
                   change_row, change_col);
        }
        else
        {
            printf("\n\nYou can't book <%d,%d>!\n",
                   change_row, change_col);
            puts("\nPlease change the seat number.");
            booking();
        }
    }

    status();
    back();
}

void cancellation(void)
{
    // ��ʼ�˶�Ʊ
    int change_row, change_col;

    printf("\nPlease input the row:");
    scanf("%d", &change_row);
    printf("\nPlease input the column:");
    scanf("%d", &change_col);

    if (change_row > rows || change_row < 1 ||
        change_col > cols || change_col < 1)
    {
        printf("\n\nThe seat number <%d,%d> doesn't exist!",
               change_row, change_col);
        puts("\nPlease change the seat number.");
        cancellation(); // different
    }
    else
    { // different
        if ('c' == tickets[change_row - 1][change_col - 1])
        {
            tickets[change_row - 1][change_col - 1] = 'a';
            available++;
            reserved--;
            printf("\n\tTicket:<%d,%d> cancel success.\n",
                   change_row, change_col);
        }
        else
        {
            printf("\n\nYou can't cancel <%d,%d>!\n",
                   change_row, change_col);
            puts("\nPlease change the seat number.");
            cancellation();
        }
    }

    status();
    back();
}

void search(void)
{
    // ��ʼ��Ʊ
    int c_row, c_col;
    char *result;

    result = (char *)malloc(sizeof(char));

    printf("\nPlease input the row:");
    scanf("%d", &c_row);
    printf("\nPlease input the column:");
    scanf("%d", &c_col);

    if (c_row > rows || c_row < 1 || c_col > cols || c_col < 1)
    {
        printf("\n\nThe seat number <%d,%d> doesn't exist!",
               c_row, c_col);
        puts("\nPlease change the seat number.");
        search(); // different
    }
    else
    { // different
        printf("\n\tTicket: <%d,%d> is", c_row, c_col);
        switch (tickets[c_row - 1][c_col - 1])
        {
        case 'a':
            puts("available.\n");
            break;
        case 'b':
            puts("sold.\n");
            break;
        case 'c':
            puts("reserved.\n");
            break;
        }
    }

    status();
    back();
}
