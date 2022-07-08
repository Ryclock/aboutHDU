#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "PR.h"

/* ���ָ߽״��ڸ�С��MSE��ƽ���󣩣���18��Ϊ38.26����������(38,39)��Χ�� */
/* ����20�׺󣬻��򳬹�double��ֵ��Χ�����·Ƿ����� */
#define RANK_MAX 5

/* ȫ�ֱ��� */
time_t maxIn, minIn;
double b_Matrix[RANK_MAX + 1] = {0}; // ϵ������

/* �ֲ��������� */

/* �������µĶ���ʽģ�ͣ�������Ԥ�� */
double highTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse);

/* �������µĶ���ʽģ�ͣ�������Ԥ�� */
double lowTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse);

/* Ԥ�⺯�� */
double predict(Date futureDate);

/* ��Date�ṹ��ת��ʱ�����ʽ */
time_t toDatetime(Date date);

/* ��ԭ���ݽ���ƽ�ƻ�����������������ݴ洢��tar_x��tar_y�� */
void Normalize(time_t *src_x, double *src_y, int dataTrueSize, double *tar_x, double *tar_y);

/* ����ʽ�ع�ľ�����⣺XB = Y */
void solveMatrix_PR(double *x, double *y, int dataTrueSize);

/* ����MSE��� */
double getMse(double *x, double *attach, double *y, int dataTrueSize);

/* ����µ�ÿ�¸���ƫ�� */
double maxFloatByMonth(Date date);

/* ����µ�ÿ�¸���ƫ�� */
double minFloatByMonth(Date date);

/* �ӿ�ʵ�� */

void FitTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize)
{
    Temperature averageMse;
    Temperature result = {
        .max = highTemperatureModel_PR(futureDate, p, databaseSize, dataTrueSize, &averageMse.max),
        .min = lowTemperatureModel_PR(futureDate, p, databaseSize, dataTrueSize, &averageMse.min),
    };
    printf("\n%d-%d-%d������Ԥ�����£�"
           "\n����£�%.2lf\t���ܴ��ڵ���Χ����������%lf"
           "\n����£�%.2lf\t���ܴ��ڵ���Χ����������%lf",
           futureDate.year, futureDate.month, futureDate.day,
           result.max, sqrt(averageMse.max),
           result.min, sqrt(averageMse.min));
}

/* �ֲ�����ʵ�� */

double highTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize, double *averageMse)
{
    time_t in[dataTrueSize];
    double out[dataTrueSize];
    double x[dataTrueSize];
    double attach[dataTrueSize];
    double y[dataTrueSize];
    /* �������ݿ� */
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
    /* �������ݿ� */
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
    tm_.tm_year = 2023 - 1900;   // �꣬����������ء�
    tm_.tm_mon = date.month - 1; // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
    tm_.tm_mday = date.day;      // �ա�
    tm_.tm_hour = 0;             // ʱ��
    tm_.tm_min = 0;              // �֡�
    tm_.tm_sec = 0;              // �롣
    tm_.tm_isdst = 0;            // ������ʱ��
    time_t t_ = mktime(&tm_);    // ��tm�ṹ��ת����time_t��ʽ��
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
    /* ��˹��Ԫ�� */
    for (int j = 0; j < RANK_MAX + 1; j++) // ��֤���Խ���Ԫ�ز�Ϊ��
    {
        if (xMatrix[j][j] != 0)
        {
            continue;
        }
        for (int i = 0; i < RANK_MAX + 1; i++) // ��Ϊ�㣬��Ѱ�Ҵ���һ������Ԫ�������в����ӵ�ԭ���У�Y����ͬ������
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
    for (int j = 0; j < RANK_MAX + 1; j++) // ��Ԫ����Ҫ��Y����Ķ�Ӧ��������
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
    for (int i = 0; i < RANK_MAX + 1; i++) // ���ɵ�λ��ӳ�䵽Y����Ķ�Ӧ�������õ���Ҫ��ϵ������
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