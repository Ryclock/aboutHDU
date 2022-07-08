#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "menu.h"

/* ȫ�ֱ��� */

Database test = NULL;   // ���ڲ��Ե����ݿ����
bool flag_init = false; // ���ڱ�ʶ�Ƿ��Ѿ��������ݿ⣬��ֹ���ζ���
char dateStr[20];       // ���ڴ洢����������ַ�������
bool flag_AorD = false; // ���ڱ�ʶ�Ƿ�����ı���

/* �ֲ��������� */

void getChoice(void);

void selectSortOrder(void);

/* ���Ժ��� */

int main(void)
{
    while (1)
    {
        showMenu();
        getChoice();
        printf("\n���践�ز˵���");
        system("pause");
        system("cls");
    }
    return 0;
}

/* �ֲ�����ʵ�� */

void getChoice(void)
{
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    char ch = getchar();
    switch (ch)
    {
    case '0':
        switchLanguage();
        break;
    case '1':
        printHelp();
        break;
    case '2':
        readData("D:\\VScode\\Program\\C\\Program_latter\\Project8\\hangzhou_weather.csv", &test, &flag_init);
        break;
    case '3':
        printf("\n������������ѯ�����ڣ����ա���+��+�ա�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        printRecord(getDataRecord(dateStr, &test));
        break;
    case '4':
        printf("\n����������Ҫ��������ڣ����ա���+�¡�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByMaxTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '5':
        printf("\n����������Ҫ��������ڣ����ա���+�¡�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByMinTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '6':
        printf("\n����������Ҫ��������ڣ����ա���+�¡�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByDiffTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '7':
        printf("\n��ܰ��ʾ�����ѡ��δ��һ���ڵ�ĳһ����ΪԤ�����ڣ�");
        printf("\n��������ҪԤ�����µ����ڣ����ա���+��+�ա�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        predictWeather(dateStr, &test);
        break;
    case '8':
        printf("\n��ܰ��ʾ�����ѡ��δ��һ���ڵ�ĳһ����ΪԤ�����ڣ�");
        printf("\n��������ҪԤ�����µ����ڣ����ա���+��+�ա�˳�����룩��");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        predictTemperature(dateStr, &test);
        break;
    case '9':
        exit(EXIT_SUCCESS);
        break;
    default:
        printf("\nWrong! Please choose another true number!\n\n");
        getChoice();
    }
}

void selectSortOrder(void)
{
    printf("\n��ѡ������˳��Ϊ��0-����1-���򣩣�");
    fflush(stdin);
    char ch = getchar();
    while (ch != '1' && ch != '0')
    {
        printf("\n��Ч��ѡ�����������룺");
        fflush(stdin);
        ch = getchar();
    }
    if (ch == '1')
    {
        flag_AorD = true;
    }
    else if (ch == '0')
    {
        flag_AorD = false;
    }
}
