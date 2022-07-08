#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "PR.h"

/* 部分高阶存在更小的MSE误差（平均后），如18阶为38.26，但还是在(38,39)范围内 */
/* 超过20阶后，会因超过double数值范围而导致非法运算 */
#define RANK_MAX 5

/* 全局变量 */
time_t maxIn, minIn;
double b_Matrix[RANK_MAX + 1] = {0}; // 系数矩阵

/* 局部函数定义 */

/* 拟合最高温的多项式模型，并进行预测 */
double highTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse);

/* 拟合最低温的多项式模型，并进行预测 */
double lowTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse);

/* 预测函数 */
double predict(Date futureDate);

/* 将Date结构体转成时间戳格式 */
time_t toDatetime(Date date);

/* 对原数据进行平移化处理，并将处理后数据存储在tar_x和tar_y中 */
void Normalize(time_t *src_x, double *src_y, int dataTrueSize, double *tar_x, double *tar_y);

/* 多项式回归的矩阵求解：XB = Y */
void solveMatrix_PR(double *x, double *y, int dataTrueSize);

/* 计算MSE误差 */
double getMse(double *x, double *attach, double *y, int dataTrueSize);

/* 最高温的每月浮动偏差 */
double maxFloatByMonth(Date date);

/* 最低温的每月浮动偏差 */
double minFloatByMonth(Date date);

/* 接口实现 */

void FitTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize)
{
    Temperature averageMse;
    Temperature result = {
        .max = highTemperatureModel_PR(futureDate, p, databaseSize, dataTrueSize, &averageMse.max),
        .min = lowTemperatureModel_PR(futureDate, p, databaseSize, dataTrueSize, &averageMse.min),
    };
    printf("\n%d-%d-%d的气温预测如下："
           "\n最高温：%.2lf\t可能存在的误差范围（正负）：%lf"
           "\n最低温：%.2lf\t可能存在的误差范围（正负）：%lf",
           futureDate.year, futureDate.month, futureDate.day,
           result.max, sqrt(averageMse.max),
           result.min, sqrt(averageMse.min));
}

/* 局部函数实现 */

double highTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse)
{
    time_t in[dataTrueSize];
    double out[dataTrueSize];
    double x[dataTrueSize];
    double attach[dataTrueSize];
    double y[dataTrueSize];
    /* 读入数据库 */
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        in[t] = toDatetime((*p)[i].date);
        out[t] = (*p)[i].temperature.max;
        attach[t] = maxFloatByMonth((*p)[i].date);
    }
    Normalize(in, out, dataTrueSize, x, y);
    solveMatrix_PR(x, y, dataTrueSize);
    *averageMse = getMse(x, attach, y, dataTrueSize) / dataTrueSize;
    return predict(futureDate) + maxFloatByMonth(futureDate);
}

double lowTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse)
{
    time_t in[dataTrueSize];
    double out[dataTrueSize];
    double x[dataTrueSize];
    double attach[dataTrueSize];
    double y[dataTrueSize];
    /* 读入数据库 */
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        in[t] = toDatetime((*p)[i].date);
        out[t] = (*p)[i].temperature.min;
        attach[t] = minFloatByMonth((*p)[i].date);
    }
    Normalize(in, out, dataTrueSize, x, y);
    solveMatrix_PR(x, y, dataTrueSize);
    *averageMse = getMse(x, attach, y, dataTrueSize) / dataTrueSize;
    return predict(futureDate) + minFloatByMonth(futureDate);
}

double predict(Date futureDate)
{
    double predict_x = (double)toDatetime(futureDate) - (maxIn + minIn) / 2.0;
    double result = 0;
    for (int k = 0; k < RANK_MAX + 1; k++)
    {
        result += b_Matrix[k] * pow(predict_x, k);
    }
    return result;
}

time_t toDatetime(Date date)
{
    struct tm tm_;
    tm_.tm_year = 2023 - 1900;   // 年，丢弃年份因素。
    tm_.tm_mon = date.month - 1; // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
    tm_.tm_mday = date.day;      // 日。
    tm_.tm_hour = 0;             // 时。
    tm_.tm_min = 0;              // 分。
    tm_.tm_sec = 0;              // 秒。
    tm_.tm_isdst = 0;            // 非夏令时。
    time_t t_ = mktime(&tm_);    // 将tm结构体转换成time_t格式。
    return t_;
}

void Normalize(time_t *src_x, double *src_y, int dataTrueSize, double *tar_x, double *tar_y)
{
    maxIn = minIn = src_x[0];
    for (int i = 1; i < dataTrueSize; i++)
    {
        maxIn = src_x[i] > maxIn ? src_x[i] : maxIn;
        minIn = src_x[i] < minIn ? src_x[i] : minIn;
    }
    for (int i = 0; i < dataTrueSize; i++)
    {
        tar_x[i] = (double)src_x[i] - (maxIn + minIn) / 2.0;
        tar_y[i] = src_y[i];
    }
}

void solveMatrix_PR(double *x, double *y, int dataTrueSize)
{
    double xMatrix[RANK_MAX + 1][RANK_MAX + 1] = {0};
    double yMatrix[RANK_MAX + 1] = {0};
    double xPower_sum[2 * RANK_MAX + 1] = {0};
    for (int i = 0; i < dataTrueSize; i++)
    {
        for (int j = 0; j < 2 * RANK_MAX + 1; j++)
        {
            xPower_sum[j] += pow(x[i], j);
        }
        for (int j = 0; j < RANK_MAX + 1; j++)
        {
            yMatrix[j] += y[i] * pow(x[i], j);
        }
    }
    for (int i = 0; i < RANK_MAX + 1; i++)
    {
        for (int j = 0, k = i; j < RANK_MAX + 1; j++, k++)
            xMatrix[i][j] = xPower_sum[k];
    }
    /* 高斯消元法 */
    for (int j = 0; j < RANK_MAX + 1; j++) // 保证主对角线元素不为零
    {
        if (xMatrix[j][j] != 0)
        {
            continue;
        }
        for (int i = 0; i < RANK_MAX + 1; i++) // 若为零，则寻找此列一个非零元素所在行并叠加到原来行，Y矩阵同步操作
        {
            if (xMatrix[i][j] != 0)
            {
                for (int k = 0; k < RANK_MAX + 1; k++)
                {
                    xMatrix[j][k] += xMatrix[i][k];
                }
                yMatrix[j] += yMatrix[i];
                break;
            }
        }
    }
    for (int j = 0; j < RANK_MAX + 1; j++) // 消元，主要是Y矩阵的对应操作操作
    {
        for (int i = 0; i < RANK_MAX + 1; i++)
        {
            if (i == j)
            {
                continue;
            }
            yMatrix[i] -= (xMatrix[i][j] / xMatrix[j][j]) * yMatrix[j];
        }
    }
    for (int i = 0; i < RANK_MAX + 1; i++) // 化成单位阵映射到Y矩阵的对应操作，得到需要的系数矩阵
    {
        b_Matrix[i] = yMatrix[i] / xMatrix[i][i];
    }
}

double getMse(double *x, double *attach, double *y, int dataTrueSize)
{
    double mse = 0;
    for (int i = 0; i < dataTrueSize; i++)
    {
        double forcast = 0;
        for (int k = 0; k < RANK_MAX + 1; k++)
        {
            forcast += b_Matrix[k] * pow(x[i], k);
        }
        forcast += attach[i];
        // printf("\nforcast: %lf \ttruth: %lf \terror: %lf", forcast, y[i], forcast - y[i]);
        mse += pow(forcast - y[i], 2);
    }
    return mse;
}

double maxFloatByMonth(Date date)
{
    switch (date.month)
    {
    case 1:
        return -5.0;
    case 2:
        return -6.0;
    case 3:
        return -0.5;
    case 4:
        return +0.5;
    case 5:
        return +2.5;
    case 6:
        return +4.5;
    case 7:
        return +9.0;
    case 8:
        return +7.0;
    case 9:
        return +3.5;
    case 10:
        return -2.0;
    case 11:
        return -6.0;
    case 12:
        return -7.5;
    }
}

double minFloatByMonth(Date date)
{
    switch (date.month)
    {
    case 1:
        return -4.0;
    case 2:
        return -5.0;
    case 3:
        return -2.0;
    case 4:
        return -1.5;
    case 5:
        return +1.5;
    case 6:
        return +3.5;
    case 7:
        return +6.5;
    case 8:
        return +5.0;
    case 9:
        return +3.0;
    case 10:
        return -2.0;
    case 11:
        return -5.0;
    case 12:
        return -8.0;
    }
}