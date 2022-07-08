#include <stdio.h>
#include <stdlib.h>
#include "SimpleHousePrediction.h"

typedef struct data
{
    double x; // area
    double y; // price
} Data;

Data data[DATAMAXN];
int dataN;
double a; // Y = a + bX
double b; // Y = a + bX
double sumx;
double sumy;
double sumxx;
double sumxy;

/* 测试函数 */

int main(void)
{
    if (GetData() == false)
    {
        printf("Error:can't get Data!!");
        system("pause");
        exit(0);
    }
    InitProblem();
    LineReg();
    OutputResult();
    system("pause");
    return 0;
}

/* 函数实现 */

bool GetData(void)
{
    char filename[256];
    printf("\nPlease input data file name: ");
    scanf("%s", filename);
    printf("\nPlease input the number of data: ");
    scanf("%d", &dataN);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error:can't open file %s", filename);
        return false;
    }
    for (int i = 0; i < dataN; i++)
    {
        fscanf(fp, "%lf,%lf", &data[i].x, &data[i].y);
    }
    // /* 测试输入 */
    // for (int i = 0; i < dataN; i++)
    // {
    //     printf("%lf,%lf", data[i].x, data[i].y);
    // }
    return true;
}

void InitProblem(void)
{
    a = b = sumx = sumy = sumxx = sumxy = 0;
}

void LineReg(void)
{
    for (int i = 0; i < dataN; i++)
    {
        sumx += data[i].x;
        sumy += data[i].y;
        sumxx += data[i].x * data[i].x;
        sumxy += data[i].x * data[i].y;
    }
    b = (sumxy * dataN - sumx * sumy) / (sumxx * dataN - sumx * sumx);
    a = sumy / dataN - b * sumx / dataN;
    printf("\nThe prediction line is:\n\tY = %.2lfX + %.2lf", b, a);
}

void OutputResult(void)
{
    double newArea = -1;
    double newPrice = -1;
    printf("\nPlease input the area of house (Unit: square meter): ");
    scanf("%lf", &newArea);
    newPrice = a + b * newArea;
    printf("\nThe house price predicted is: %.2lf", newPrice);
}