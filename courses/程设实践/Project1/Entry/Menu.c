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
    char *top = "�˵�";
    char *head = "˳������������ʾϵͳ";
    string options[OPTIONNUM] = {"1-����˳���", "2-��ʾ˳���", "3-���˳���", "4-˳�������", "5-?ͨ��λ�ò���Ԫ��", "6-?ͨ��ֵ����Ԫ��", "7-?ָ��λ�ò���Ԫ��", "8-ɾ��ָ��λ��Ԫ��", "9-ɾ��ָ��ֵԪ��", "10-ɾ���ظ�Ԫ��", "11-����˳���", "12-����˳���", "13-���ļ��е���", "14-�������ļ�", "15-�����ƽ̨", "16-�˳�<��0��ʾӢ�Ĳ˵�>"};
    char *tail = "���� @����� ���ݵ��ӿƼ���ѧ";
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
