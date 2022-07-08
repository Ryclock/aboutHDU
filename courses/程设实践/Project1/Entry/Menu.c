#include <stdio.h>
#include <string.h>
#include "Menu.h"

#define WIDTH 70
#define RIGHTPOSITION 40
#define LEFTPOSITION 5
#define STARTSIGN '='
#define ROWSIGN '*'
#define COLSIGN '$'
#define OPTIONNUM 16

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
    char *head = "Sequence List Basic System";
    string options[OPTIONNUM] = {"1-Create List", "2-Display List", "3-Clear List", "4-Sort List", "5-Search by Position",
                                 "6-Search by Value", "7-Insert by Position", "8-Delete by Position", "9-Delete by Value",
                                 "10-Delete Duplicate", "11-Reverse List", "12-Divide List", "13-Import from File",
                                 "14-Export to File", "15-Get Maximum Platform", "16-Exit<0 for Chinese Menu>"};
    char *tail = "Designed By Ryclock HDU";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}

void printChineseMenu(void)
{
    char *top = "菜单";
    char *head = "顺序表基本操作演示系统";
    string options[OPTIONNUM] = {"1-创建顺序表", "2-显示顺序表", "3-清空顺序表", "4-顺序表排序", "5-?通过位置查找元素", "6-?通过值查找元素", "7-?指定位置插入元素", "8-删除指定位置元素", "9-删除指定值元素", "10-删除重复元素", "11-置逆顺序表", "12-划分顺序表", "13-从文件中导入", "14-导出到文件", "15-求最大平台", "16-退出<按0显示英文菜单>"};
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
