#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "menu.h"

/* 全局变量 */

Database test = NULL;   // 用于测试的数据库变量
bool flag_init = false; // 用于标识是否已经读入数据库，防止二次读入
char dateStr[20];       // 用于存储输入的日期字符串变量
bool flag_AorD = false; // 用于标识是否升序的变量

/* 局部函数定义 */

void getChoice(void);

void selectSortOrder(void);

/* 测试函数 */

int main(void)
{
    while (1)
    {
        showMenu();
        getChoice();
        printf("\n如需返回菜单，");
        system("pause");
        system("cls");
    }
    return 0;
}

/* 局部函数实现 */

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
        printf("\n请输入你打算查询的日期（按照“年+月+日”顺序输入）：");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        printRecord(getDataRecord(dateStr, &test));
        break;
    case '4':
        printf("\n请输入你想要排序的日期（按照“年+月”顺序输入）：");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByMaxTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '5':
        printf("\n请输入你想要排序的日期（按照“年+月”顺序输入）：");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByMinTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '6':
        printf("\n请输入你想要排序的日期（按照“年+月”顺序输入）：");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        selectSortOrder();
        sortByDiffTemperature(dateStr, &test, flag_AorD);
        printResultAfterSorted(dateStr, &test);
        break;
    case '7':
        printf("\n温馨提示：最好选择未来一年内的某一天作为预测日期；");
        printf("\n请输入需要预测气温的日期（按照“年+月+日”顺序输入）：");
        memset(dateStr, 0, sizeof(dateStr));
        scanf("%s", dateStr);
        predictWeather(dateStr, &test);
        break;
    case '8':
        printf("\n温馨提示：最好选择未来一年内的某一天作为预测日期；");
        printf("\n请输入需要预测气温的日期（按照“年+月+日”顺序输入）：");
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
    printf("\n请选择排序顺序为（0-降序；1-升序）：");
    fflush(stdin);
    char ch = getchar();
    while (ch != '1' && ch != '0')
    {
        printf("\n无效的选择，请重新输入：");
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
