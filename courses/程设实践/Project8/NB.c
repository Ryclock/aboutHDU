#include <stdio.h>
#include <string.h>
#include "NB.h"

#define X_DIMENSION 12 * 31 // 忽略年份因素，且为保证其朴素性而将月和日合成一个维度
#define Y_DIMENSION 4

/* 常量 */

/* 仅对基本天气进行统计，即晴、阴、雨、雪 */
const char *BasicWeatherName[Y_DIMENSION] = {
    "阴",
    "晴",
    "雨",
    "雪",
};

/* 全局变量 */

int truth[X_DIMENSION];                              // 每天的真实天气
double priori_P[Y_DIMENSION] = {0};                  // 先验概率
double marginal_P[X_DIMENSION] = {0};                // 边际概率（证据）
double likelihood_P[Y_DIMENSION][X_DIMENSION] = {0}; // 似然概率（条件概率）
double posterior_P[X_DIMENSION][Y_DIMENSION];        // 后验概率
int posterior_P_Best[X_DIMENSION];                   // 后验概率的最优解
int Matrix[Y_DIMENSION][Y_DIMENSION] = {0};          // 混淆矩阵Matrix[predition_out][test_out]
double accuracy = 0;                                 // 准确率
double recall = 0;                                   // 召回率

/* 局部函数定义 */

/* 统计相关信息出现次数 */
void initFrequency(Database *p, int databaseSize);

/* 计算四个概率和最优解 */
void calFourProbability(int dataTrueSize);

/* 计算混淆矩阵 */
void calMatrix(Database *p, int databaseSize);

/* 计算准确率和召回率 */
void evaluateModel(int dataTrueSize);

/* 接口实现 */

void FitWeatherModel_NB(Date futureDate, Database *p, int databaseSize, int dataTrueSize)
{
    initFrequency(p, databaseSize);
    calFourProbability(dataTrueSize);
    calMatrix(p, databaseSize);
    evaluateModel(dataTrueSize);
    printf("\n%d-%d-%d的基本天气预测如下：", futureDate.year, futureDate.month, futureDate.day);
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        printf("\n\tP(%s) = %.2lf",
               BasicWeatherName[i],
               posterior_P[(futureDate.month - 1) * 31 + (futureDate.day - 1)][i]);
    }
    printf("\n此统计型模型预测的准确率为 %.3lf，召回率为 %.3lf", accuracy, recall);
}

/* 局部函数实现 */
void initFrequency(Database *p, int databaseSize)
{
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        int x = ((*p)[i].date.month - 1) * 31 + ((*p)[i].date.day - 1);
        int y = 0;
        for (int j = 1; j < Y_DIMENSION; j++)
        {
            if (strstr((*p)[i].weather.name, BasicWeatherName[j]))
            {
                y = j;
                break;
            }
        }
        truth[x] = y;
        priori_P[y]++;
        marginal_P[x]++;
        likelihood_P[y][x]++;
    }
}

void calFourProbability(int dataTrueSize)
{
    /* 似然概率 */
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        for (int j = 0; j < X_DIMENSION; j++)
        {
            likelihood_P[i][j] /= priori_P[i];
        }
    }
    /* 先验概率 */
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        priori_P[i] /= dataTrueSize;
    }
    /* 边际概率 */
    for (int i = 0; i < X_DIMENSION; i++)
    {
        marginal_P[i] /= dataTrueSize;
    }
    /* 后验概率 */
    for (int i = 0; i < X_DIMENSION; i++)
    {
        if (marginal_P[i] == 0)
        {
            continue;
        }
        for (int j = 0; j < Y_DIMENSION; j++)
        {
            posterior_P[i][j] = priori_P[j] * likelihood_P[j][i] / marginal_P[i];
        }
    }
    /* 最优解 */
    for (int i = 0; i < X_DIMENSION; i++)
    {
        if (marginal_P[i] == 0)
        {
            continue;
        }
        posterior_P_Best[i] = 0;
        for (int j = 1; j < Y_DIMENSION; j++)
        {
            posterior_P_Best[i] = posterior_P[i][j] > posterior_P[i][posterior_P_Best[i]] ? j : posterior_P_Best[i];
        }
    }
}

void calMatrix(Database *p, int databaseSize)
{
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        int date = ((*p)[i].date.month - 1) * 31 + ((*p)[i].date.day - 1);
        Matrix[posterior_P_Best[date]][truth[date]]++;
    }
}

void evaluateModel(int dataTrueSize)
{
    for (int tru = 0; tru < Y_DIMENSION; tru++)
    {
        accuracy += (double)Matrix[tru][tru] / dataTrueSize;
        double sum_tru = 0;
        for (int pred = 0; pred < Y_DIMENSION; pred++)
        {
            sum_tru += (double)Matrix[pred][tru];
        }
        recall += (Matrix[tru][tru] / sum_tru) / Y_DIMENSION;
    }
}