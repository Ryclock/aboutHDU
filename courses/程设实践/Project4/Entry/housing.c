#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "housing.h"
#include "unary.h"
#include "multiple.h"

string digitToDimension[BEFOREMEDV] = {
    "CRIM",
    "ZN",
    "INDUS",
    "CHAS",
    "NOX",
    "RM",
    "AGE",
    "DIS",
    "RAD",
    "TAX",
    "PTRATIO",
    "B",
    "LSTAT",
};

int main(void)
{
    if (GetData())
    {
        int dimensionAll[BEFOREMEDV];
        for (int i = 0; i < BEFOREMEDV; i++)
        {
            dimensionAll[i] = i;
        }
        AllUnaryLinearReg(dimensionAll, BEFOREMEDV);
        int best[NBESTDIMENSION];
        GetNBestUnary(best, NBESTDIMENSION);
        system("pause");
        /* 望众知：
            由于接口内部直接操作原有数组，
            以下两个函数调用（即13维度多元线性和4最佳维度多元线性）不能具有任何先后执行关系
         */
        printf("\n\nAll dimension's ending:");
        MultipleLinearReg(dimensionAll, BEFOREMEDV);
        system("pause");
        /* ----------我是二选一的分隔线---------- */
        printf("\n\n%d Best dimension's ending:", NBESTDIMENSION);
        MultipleLinearReg(best, NBESTDIMENSION);
        system("pause");
        return 0;
    }
    else
    {
        fprintf(stdout, "Error no.%d: %s\n", errno, strerror(errno));
        system("pause");
        exit(errno);
    }
}

bool GetData(void)
{
    FILE *fp = fopen("housing.txt", "rb");
    if (fp == NULL)
    {
        fputs("Open error", stderr);
        return false;
    }
    char buffer[256];
    fgets(buffer, 256, fp);
    for (int i = 0; i < DATAMAXN; i++)
    {
        fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
               &dataAll[i][CRIM], &dataAll[i][ZN], &dataAll[i][INDUS], &dataAll[i][CHAS], &dataAll[i][NOX], &dataAll[i][RM], &dataAll[i][AGE],
               &dataAll[i][DIS], &dataAll[i][RAD], &dataAll[i][TAX], &dataAll[i][PTRATIO], &dataAll[i][B], &dataAll[i][LSTAT], &dataAll[i][MEDV]);
    }
    fclose(fp);
    /* 数据读取正确性检验 */
    // printf("\n%s", buffer);
    // for (int i = 0; i < DATAMAXN; i++)
    // {
    //     printf("\n%8.5lf %8.2lf %8.3lf %3d %8.4lf %8.4lf %8.2lf %8.4lf %3d %8.1lf %8.2lf %8.2lf %8.2lf %8.2lf",
    //            dataAll[i][CRIM], dataAll[i][ZN], dataAll[i][INDUS], dataAll[i][CHAS], dataAll[i][NOX], dataAll[i][RM], dataAll[i][AGE],
    //            dataAll[i][DIS], dataAll[i][RAD], dataAll[i][TAX], dataAll[i][PTRATIO], dataAll[i][B], dataAll[i][LSTAT], dataAll[i][MEDV]);
    // }
    return true;
}
void NormalizeData(void) // x = (x - min)/(max - min)
{
    Data_T max[INFOMAXN] = {0};
    Data_T min[INFOMAXN] = {0};
    for (int dimension = 0; dimension < INFOMAXN; dimension++)
    {
        for (int i = 0; i < DATAMAXN; i++)
        {
            if (dataAll[i][dimension] > max[dimension])
            {
                max[dimension] = dataAll[i][dimension];
            }
            if (dataAll[i][dimension] < min[dimension])
            {
                min[dimension] = dataAll[i][dimension];
            }
        }
        for (int i = 0; i < DATAMAXN; i++)
        {
            dataAll[i][dimension] = (dataAll[i][dimension] - min[dimension]) / (max[dimension] - min[dimension]);
        }
    }
}