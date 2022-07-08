#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

#define WIDTH 109        // �п���������ʼ������ֹ��
#define LEFTPOSITION 2   // ���ѡ������
#define RIGHTPOSITION 55 // �Ҳ�ѡ������
#define STARTSIGN '='    // �˵�ͷ�����е�ռλ��
#define ROWSIGN '*'      // �˵������ͷβ�е�ռλ��
#define COLSIGN '$'      // ÿ�е���ʼ������ֹ��
#define OPTIONNUM 10     // ѡ������

/* ȫ�ֱ��� */

char lang = 'C'; // ��ǰ����ʹ�õ�����

/* �ֲ��������� */

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

/* �ӿ�ʵ�� */

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
    printf("\n\t��ӭʹ�ú���������������Ԥ��ϵͳ����ע��������ʾ��");
    printf("\n\t1. �뽫����Դ�ļ�ͬʱ���б��룬���򲿷ֹ��ܿ��ܻ��޷�ִ��");
    printf("\n\t2. ִ�С��������ݡ�����ǰ����ȷ������Դ�ļ���·���Ƿ���ȷ(����ʹ�þ���·��)��");
    printf("\n\t3. ִ���κβ�ѯ�������Ԥ�����ǰ����ȷ���Ѿ�ִ�й����������ݡ�������");
    printf("\n\t4. �����ζ������ݣ�����γ�ʼ�����ݿ��ǷǷ�����");
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

/* �ֲ�����ʵ�� */

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
    char *tail = "Made by Ryclock&SYZ&TYC HDU";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}

void printChineseMenu(void)
{
    char *top = "�˵�";
    char *head = "����������������Ԥ��ϵͳ";
    string options[OPTIONNUM] = {"1-ʹ��˵��", "2-��������", "3-��ѯ��ȥĳһ���������Ϣ",
                                 "4-�������������ĳ����", "5-�������������ĳ����", "6-�����²�����ĳ����",
                                 "7-Ԥ����һ��ĳһ�������", "8-Ԥ����һ��ĳһ����¶�", "9-�˳�ϵͳ", "0-�л���Ӣ�Ĳ˵�"};
    char *tail = "������ @�����&������&������ ���ݵ��ӿƼ���ѧ";
    printMenuHead(top, head);
    printMenuBody(options, OPTIONNUM);
    printMenuTail(tail);
}
