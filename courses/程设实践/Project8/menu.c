#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define WIDTH 109        // 行宽，不包括起始符和终止符
#define LEFTPOSITION 2   // 左侧选项的瞄点
#define RIGHTPOSITION 55 // 右侧选项的瞄点
#define STARTSIGN '='    // 菜单头部首行的占位符
#define ROWSIGN '*'      // 菜单主体的头尾行的占位符
#define COLSIGN '$'      // 每行的起始符和终止符
#define OPTIONNUM 10     // 选项总数

/* 全局变量 */

char lang = 'C'; // 当前正在使用的语言

/* 局部函数定义 */

typedef char *string;

void printNChar(char ch, int num);

void printNSpace(int num);

void printBodyOfOptionsLine(char *leftOption, char *rightOption);

void printBodyOfBlankLine(void);

void printBodyOfInfoLine(char ch, char *pch);

void printEndOfLine(char ch);

void printHeadOfLine(char ch);

void printOptionLine(char ch, char *leftOption, char *rightOption);

void printBlankLine(char ch);

void printInfoLine(char ch, char *pch);

void printMenuTail(char *tail);

void printMenuBody(string options[], int num);

void printMenuHead(char *top, char *head);

void printEnglishMenu(void);

void printChineseMenu(void);

/* 接口实现 */

void showMenu(void)
{
    if (lang == 'C')
    {
        printChineseMenu();
    }
    else if (lang == 'E')
    {
        printEnglishMenu();
    }
    else
    {
        printf("\nNew error: Language is wrong!");
        system("pause");
        exit(EXIT_FAILURE);
    }
}

void printHelp(void)
{
    printf("\n\t欢迎使用杭州天气情况管理和预测系统，请注意以下提示：");
    printf("\n\t1. 请将所有源文件同时进行编译，否则部分功能可能会无法执行");
    printf("\n\t2. 执行“导入数据”操作前，请确保数据源文件的路径是否正确(建议使用绝对路径)；");
    printf("\n\t3. 执行任何查询或排序或预测操作前，请确保已经执行过“导入数据”操作；");
    printf("\n\t4. 请勿多次读入数据，即多次初始化数据库是非法操作");
}

void switchLanguage(void)
{
    if (lang == 'C')
    {
        lang = 'E';
    }
    else
    {
        lang = 'C';
    }
}

/* 局部函数实现 */

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
    char *head = "Hangzhou Weather Management and Forecasting System";
    string options[OPTIONNUM] = {"1-Instructions for use", "2-Read data",
                                 "3-Inquiry past weather information of one day",
                                 "4-Sort the dates of one month by highest temperature",
                                 "5-Sort the dates of one month by lowest temperature",
                                 "6-Sort the dates of one month by temperature diff",
                                 "7-Predict the weather for one day in the next year",
                                 "8-Predict the temperature for one day in the next year",
                                 "9-Exit", "0- Change to Chinese Menu"};
    char *tail = "Made by Ryclock HDU";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}

void printChineseMenu(void)
{
    char *top = "菜单";
    char *head = "杭州天气情况管理和预测系统";
    string options[OPTIONNUM] = {"1-使用说明", "2-导入数据", "3-查询过去某一天的天气信息",
                                 "4-按日最高温排序某个月", "5-按日最低温排序某个月", "6-按日温差排序某个月",
                                 "7-预测下一年某一天的天气", "8-预测下一年某一天的温度", "9-退出系统", "0-切换成英文菜单"};
    char *tail = "制作者 @姜曜楠 杭州电子科技大学";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}
