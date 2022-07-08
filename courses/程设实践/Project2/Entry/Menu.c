#include <stdio.h>
#include <string.h>
#include "Menu.h"

#define WIDTH 70
#define RIGHTPOSITION 40
#define LEFTPOSITION 5
#define STARTSIGN '='
#define ROWSIGN '*'
#define COLSIGN '$'
#define OPTIONNUM 6

void printNChar(char ch, int num)
{
    for (int count = 1; count <= num; count++)
    {
        putchar(ch);
    }
}

void printNSpace(int num)
{
    printNChar(' ', num);
}

void printBodyOfOptionsLine(char *leftOption, char *rightOption)
{
    printNSpace(LEFTPOSITION);
    printf("%s", leftOption);
    printNSpace(RIGHTPOSITION - LEFTPOSITION - strlen(leftOption));
    printf("%s", rightOption);
    printNSpace(WIDTH - RIGHTPOSITION - strlen(rightOption));
}

void printBodyOfBlankLine(void)
{
    printNSpace(WIDTH);
}

void printBodyOfInfoLine(char ch, char *pch)
{
    printNChar(ch, (WIDTH - strlen(pch)) / 2);
    printf("%s", pch);
    printNChar(ch, WIDTH - strlen(pch) - (WIDTH - strlen(pch)) / 2);
}

void printEndOfLine(char ch)
{
    printf("%c", ch);
}

void printHeadOfLine(char ch)
{
    printf("\n\t%c", ch);
}

void printOptionLine(char ch, char *leftOption, char *rightOption)
{
    printHeadOfLine(ch);
    printBodyOfOptionsLine(leftOption, rightOption);
    printEndOfLine(ch);
}

void printBlankLine(char ch)
{
    printHeadOfLine(ch);
    printBodyOfBlankLine();
    printEndOfLine(ch);
}

void printInfoLine(char ch, char *pch)
{
    printHeadOfLine(ch);
    printBodyOfInfoLine(ch, pch);
    printEndOfLine(ch);
}

void printMenuTail(char *tail)
{
    printBlankLine(COLSIGN);
    printInfoLine(ROWSIGN, tail);
    printf("\n\t");
}

void printMenuBody(string options[], int num)
{
    for (int i = 0; i < num; i += 2)
    {
        printBlankLine(COLSIGN);
        printOptionLine(COLSIGN, options[i], options[i + 1]);
    }
}

void printMenuHead(char *top, char *head)
{
    printInfoLine(STARTSIGN, top);
    printf("\n\n");
    printInfoLine(ROWSIGN, head);
}

void printEnglishMenu(void)
{
    char *top = "THE MENU";
    char *head = "Sequence Stack Basic System";
    string options[OPTIONNUM] = {"11-Hannuota Problem", "13-Backpack Problem", "14-N-queen Problem", "15-Maze Problem", "16-Exit", "<0 for Chinese Menu>"};
    char *tail = "Designed By Ryclock HDU";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}

void printChineseMenu(void)
{
    char *top = "菜单";
    char *head = "顺序栈基本操作演示系统";
    string options[OPTIONNUM] = {"11-汉诺塔问题", "13-背包问题", "14-N-皇后问题", "15-迷宫问题", "16-退出", "<按0显示英文菜单>"};
    char *tail = "作者 @姜曜楠 杭州电子科技大学";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}

void Menu(char lang)
{
    if ('C' == lang)
    {
        printChineseMenu();
    }
    else if ('E' == lang)
    {
        printEnglishMenu();
    }
}

int inputChoice(void)
{
    int choice;
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    scanf("%d", &choice);
    printf("\n");
    return choice;
}

void switchlanguage(char *pLanguage)
{
    if ('C' == *pLanguage)
    {
        *pLanguage = 'E';
    }
    else
    {
        *pLanguage = 'C';
    }
}
