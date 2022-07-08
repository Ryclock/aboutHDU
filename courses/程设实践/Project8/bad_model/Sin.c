#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sin.h"

/* Ϊʲôֻ��С��������ڲ��� => Ϊʲôa0��a4��a2����һ�������� */
#define COEF_NUM 4
#define EPOCH 500000
#define PRECISION (pow(0.0001, 2))
#define LOSS 0.00005
#define LAMBDA 0.5

/* ȫ�ֱ��� */

/* �ֲ��������� */

time_t toDatetime(Date date);

/* �ӿ�ʵ�� */

void InitHighTemperatureModel_Sin(Database *p, int databaseSize, int dataTrueSize)
{
    time_t in[dataTrueSize];
    double out[dataTrueSize];
    double x[dataTrueSize];
    double y[dataTrueSize];
    time_t maxIn, minIn;
    double maxOut, minOut;
    /* ���� */
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        in[t] = toDatetime((*p)[i].date);
        out[t] = (*p)[i].temperature.max;
    }
    /* ƽ�� */
    maxIn = minIn = in[0];
    maxOut = minOut = out[0];
    for (int i = 1; i < dataTrueSize; i++)
    {
        maxIn = in[i] > maxIn ? in[i] : maxIn;
        minIn = in[i] < minIn ? in[i] : minIn;
        maxOut = out[i] > maxOut ? out[i] : maxOut;
        minOut = out[i] < minOut ? out[i] : minOut;
    }
    for (int i = 0; i < dataTrueSize; i++)
    {
        x[i] = (in[i] - (double)minIn) / (maxIn - minIn);
        y[i] = (out[i] - minOut) / (maxOut - minOut);
    }
    /* ��˹ţ�ٷ�����Ĳ������Һ�����https://max.book118.com/html/2019/0531/5313231031002042.shtm#:~:text=%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E6%8B%9F%E5%90%88%E8%AE%A1%E7%AE%97%20%E4%B8%80%E3%80%81%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E7%9A%84%E4%B8%80%E8%88%AC%E8%A1%A8%E8%BE%BE%E5%BC%8F%E7%9A%84%E5%BB%BA%E7%AB%8B%20%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E7%9A%84%E4%B8%80%E8%88%AC%E8%A1%A8%E8%BE%BE%E5%BC%8F%E4%B8%BA%EF%BC%9A%20%EF%BC%881%EF%BC%89,%E5%AF%B9%E4%BA%8E%E4%B8%80%E7%B3%BB%E5%88%97%E7%9A%84n%E4%B8%AA%E7%82%B9%EF%BC%9A%20%EF%BC%882%EF%BC%89%20%E8%A6%81%E7%94%A8%E7%82%B9%E6%8B%9F%E5%90%88%E8%AE%A1%E7%AE%97%E4%B8%8A%E8%BF%B0%E6%96%B9%E7%A8%8B%EF%BC%8C%E5%88%99%E4%BD%BF%EF%BC%9A%20%E6%9C%80%E5%B0%8F%E3%80%82 */
    double A_Matrix[COEF_NUM];
    double diffA_Matrix[COEF_NUM] = {0};
    int epoch = 0;
    double precision = 0;
    /* ��ʼ��ϵ������A */
    A_Matrix[0] = (maxOut - minOut) / 2;
    A_Matrix[3] = (maxOut + minOut) / 2;
    A_Matrix[1] = asin((y[0] - A_Matrix[3]) / A_Matrix[0]) / x[0];
    A_Matrix[2] = 1;
    /* ���� */
    do
    {
        /* ����ϵ������ */
        for (int i = 0; i < COEF_NUM; i++)
        {
            A_Matrix[i] += LAMBDA * diffA_Matrix[i];
            diffA_Matrix[i] = 0;
        }
        // srand(time(NULL));
        // for (int i = 0; i < COEF_NUM; i++)
        // {
        //     A_Matrix[i] = A_Matrix[i] * (1 + rand() % 1);
        // }
        /* ������⣺J*diffX = -F */
        /* f = a0 * sin(a1*xi + a2) + a3 */
        double J_Matrix[COEF_NUM][COEF_NUM] = {0};
        double _F_Matrix[COEF_NUM] = {0};
        /* �������-F��loss��ϵ����ƫ��������ʽ����ƫ��Ҫ������ʱ������С  */
        /* loss = ((f-y)^2)/2 */
        for (int i = 0; i < dataTrueSize; i++)
        {
            double f = A_Matrix[0] * sin(A_Matrix[1] * x[i] + A_Matrix[2]) + A_Matrix[3];
            _F_Matrix[0] += (-1) * (f - y[i]) * sin(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[1] += (-1) * (f - y[i]) * x[i] * cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[2] += (-1) * (f - y[i]) * cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[3] += (-1) * (f - y[i]);
        }
        /* �����ſɱȾ���J */
        for (int i = 0; i < dataTrueSize; i++)
        {
            double sinx = sin(A_Matrix[1] * x[i] + A_Matrix[2]);
            double sin2x = sin(2 * (A_Matrix[1] * x[i] + A_Matrix[2]));
            double cosx = cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            double cos2x = cos(2 * (A_Matrix[1] * x[i] + A_Matrix[2]));

            J_Matrix[0][0] += pow(sinx, 2);
            J_Matrix[0][1] += A_Matrix[0] * x[i] * sin2x + (A_Matrix[3] - y[i]) * x[i] * cosx;
            J_Matrix[0][2] += A_Matrix[0] * sinx + (A_Matrix[3] - y[i]) * cosx;
            J_Matrix[0][3] += sinx;

            J_Matrix[1][0] += x[i] * sin2x / 2;
            J_Matrix[1][1] += A_Matrix[0] * x[i] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * x[i] * sinx;
            J_Matrix[1][2] += A_Matrix[0] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * sinx;
            J_Matrix[1][3] += x[i] * cosx;

            J_Matrix[2][0] += sin2x / 2;
            J_Matrix[2][1] += A_Matrix[0] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * sinx;
            J_Matrix[2][2] += A_Matrix[0] * cos2x - (A_Matrix[3] - y[i]) * sinx;
            J_Matrix[2][3] += cosx;

            J_Matrix[3][0] += sinx;
            J_Matrix[3][1] += A_Matrix[0] * x[i] * cosx;
            J_Matrix[3][2] += A_Matrix[0] * cosx;
            J_Matrix[3][3] += 1;
        }
        /* ��˹��Ԫ�� */
        for (int j = 0; j < COEF_NUM; j++) // ��֤���Խ���Ԫ�ز�Ϊ��
        {
            if (J_Matrix[j][j] != 0)
            {
                continue;
            }
            for (int i = 0; i < COEF_NUM; i++) // ��Ϊ�㣬��Ѱ�Ҵ���һ������Ԫ�������в����ӵ�ԭ���У�-F����ͬ������
            {
                if (J_Matrix[i][j] != 0)
                {
                    for (int k = 0; k < COEF_NUM; k++)
                    {
                        J_Matrix[j][k] += J_Matrix[i][k];
                    }
                    _F_Matrix[j] += _F_Matrix[i];
                    break;
                }
            }
        }
        for (int j = 0; j < COEF_NUM; j++) // ��Ԫ����Ҫ��-F����Ķ�Ӧ��������
        {
            for (int i = 0; i < COEF_NUM; i++)
            {
                if (i == j)
                {
                    continue;
                }
                _F_Matrix[i] -= (J_Matrix[i][j] / J_Matrix[j][j]) * _F_Matrix[j];
            }
        }
        for (int i = 0; i < COEF_NUM; i++) // ���ɵ�λ��ӳ�䵽-F����Ķ�Ӧ�������õ���Ҫ��ϵ������
        {
            diffA_Matrix[i] = _F_Matrix[i] / J_Matrix[i][i];
        }
        /* ���㾫�� */
        precision = 0;
        for (int i = 0; i < COEF_NUM; i++)
        {
            precision += pow(diffA_Matrix[i], 2);
        }
        if (epoch % 1000 == 0)
        {
            printf("\nPrecision: %lf", precision);
        }
        epoch++;
    } while (epoch < EPOCH && precision > PRECISION);
    /* ��� */
    double mse = 0;
    for (int i = 0; i < dataTrueSize; i++)
    {
        double forcast = A_Matrix[0] * sin(A_Matrix[1] * x[i] + A_Matrix[2]) + A_Matrix[3];
        printf("\nforcast: %lf \ttruth: %lf \terror: %f",
               forcast * (maxOut - minOut) + minOut, y[i] * (maxOut - minOut) + minOut, (forcast - y[i]) * (maxOut - minOut));
        mse += pow((forcast - y[i]) * (maxOut - minOut), 2);
    }
    printf("\nY = %lf sin(%lf x + %lf) + %lf", A_Matrix[0], A_Matrix[1], A_Matrix[2], A_Matrix[3]);
    printf("\n\tAverage MSE is %lf", mse / dataTrueSize);
}

/* �ֲ�����ʵ�� */

void InitLowTemperatureModel_Sin(Database *p, int databaseSize, int dataTrueSize)
{
    time_t in[dataTrueSize];
    double out[dataTrueSize];
    double x[dataTrueSize];
    double y[dataTrueSize];
    time_t maxIn, minIn;
    double maxOut, minOut;
    /* ���� */
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        in[t] = toDatetime((*p)[i].date);
        out[t] = (*p)[i].temperature.min;
    }
    /* ƽ�� */
    maxIn = minIn = in[0];
    maxOut = minOut = out[0];
    for (int i = 1; i < dataTrueSize; i++)
    {
        maxIn = in[i] > maxIn ? in[i] : maxIn;
        minIn = in[i] < minIn ? in[i] : minIn;
        maxOut = out[i] > maxOut ? out[i] : maxOut;
        minOut = out[i] < minOut ? out[i] : minOut;
    }
    for (int i = 0; i < dataTrueSize; i++)
    {
        x[i] = (in[i] - (double)minIn) / (maxIn - minIn);
        y[i] = (out[i] - minOut) / (maxOut - minOut);
    }
    /* ��˹ţ�ٷ�����Ĳ������Һ�����https://max.book118.com/html/2019/0531/5313231031002042.shtm#:~:text=%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E6%8B%9F%E5%90%88%E8%AE%A1%E7%AE%97%20%E4%B8%80%E3%80%81%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E7%9A%84%E4%B8%80%E8%88%AC%E8%A1%A8%E8%BE%BE%E5%BC%8F%E7%9A%84%E5%BB%BA%E7%AB%8B%20%E6%AD%A3%E5%BC%A6%E5%87%BD%E6%95%B0%E7%9A%84%E4%B8%80%E8%88%AC%E8%A1%A8%E8%BE%BE%E5%BC%8F%E4%B8%BA%EF%BC%9A%20%EF%BC%881%EF%BC%89,%E5%AF%B9%E4%BA%8E%E4%B8%80%E7%B3%BB%E5%88%97%E7%9A%84n%E4%B8%AA%E7%82%B9%EF%BC%9A%20%EF%BC%882%EF%BC%89%20%E8%A6%81%E7%94%A8%E7%82%B9%E6%8B%9F%E5%90%88%E8%AE%A1%E7%AE%97%E4%B8%8A%E8%BF%B0%E6%96%B9%E7%A8%8B%EF%BC%8C%E5%88%99%E4%BD%BF%EF%BC%9A%20%E6%9C%80%E5%B0%8F%E3%80%82 */
    double A_Matrix[COEF_NUM];
    double diffA_Matrix[COEF_NUM] = {0};
    int epoch = 0;
    double precision = 0;
    /* ��ʼ��ϵ������A */
    A_Matrix[0] = (maxOut - minOut) / 2;
    A_Matrix[3] = (maxOut + minOut) / 2;
    A_Matrix[1] = asin((y[0] - A_Matrix[3]) / A_Matrix[0]) / x[0];
    A_Matrix[2] = 1;
    /* ���� */
    do
    {
        /* ����ϵ������ */
        for (int i = 0; i < COEF_NUM; i++)
        {
            A_Matrix[i] += LAMBDA * diffA_Matrix[i];
            diffA_Matrix[i] = 0;
        }
        srand(time(NULL));
        for (int i = 0; i < COEF_NUM; i++)
        {
            A_Matrix[i] = A_Matrix[i] * (1 + rand() % 1);
        }
        /* ������⣺J*diffX = -F */
        /* f = a0 * sin(a1*xi + a2) + a3 */
        double J_Matrix[COEF_NUM][COEF_NUM] = {0};
        double _F_Matrix[COEF_NUM] = {0};
        /* �������-F��loss��ϵ����ƫ��������ʽ����ƫ��Ҫ������ʱ������С  */
        /* loss = ((f-y)^2)/2 */
        for (int i = 0; i < dataTrueSize; i++)
        {
            double f = A_Matrix[0] * sin(A_Matrix[1] * x[i] + A_Matrix[2]) + A_Matrix[3];
            _F_Matrix[0] += (-1) * (f - y[i]) * sin(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[1] += (-1) * (f - y[i]) * x[i] * cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[2] += (-1) * (f - y[i]) * cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            _F_Matrix[3] += (-1) * (f - y[i]);
        }
        /* �����ſɱȾ���J */
        for (int i = 0; i < dataTrueSize; i++)
        {
            double sinx = sin(A_Matrix[1] * x[i] + A_Matrix[2]);
            double sin2x = sin(2 * (A_Matrix[1] * x[i] + A_Matrix[2]));
            double cosx = cos(A_Matrix[1] * x[i] + A_Matrix[2]);
            double cos2x = cos(2 * (A_Matrix[1] * x[i] + A_Matrix[2]));

            J_Matrix[0][0] += pow(sinx, 2);
            J_Matrix[0][1] += A_Matrix[0] * x[i] * sin2x + (A_Matrix[3] - y[i]) * x[i] * cosx;
            J_Matrix[0][2] += A_Matrix[0] * sinx + (A_Matrix[3] - y[i]) * cosx;
            J_Matrix[0][3] += sinx;

            J_Matrix[1][0] += x[i] * sin2x / 2;
            J_Matrix[1][1] += A_Matrix[0] * x[i] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * x[i] * sinx;
            J_Matrix[1][2] += A_Matrix[0] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * sinx;
            J_Matrix[1][3] += x[i] * cosx;

            J_Matrix[2][0] += sin2x / 2;
            J_Matrix[2][1] += A_Matrix[0] * x[i] * cos2x - (A_Matrix[3] - y[i]) * x[i] * sinx;
            J_Matrix[2][2] += A_Matrix[0] * cos2x - (A_Matrix[3] - y[i]) * sinx;
            J_Matrix[2][3] += cosx;

            J_Matrix[3][0] += sinx;
            J_Matrix[3][1] += A_Matrix[0] * x[i] * cosx;
            J_Matrix[3][2] += A_Matrix[0] * cosx;
            J_Matrix[3][3] += 1;
        }
        /* ��˹��Ԫ�� */
        for (int j = 0; j < COEF_NUM; j++) // ��֤���Խ���Ԫ�ز�Ϊ��
        {
            if (J_Matrix[j][j] != 0)
            {
                continue;
            }
            for (int i = 0; i < COEF_NUM; i++) // ��Ϊ�㣬��Ѱ�Ҵ���һ������Ԫ�������в����ӵ�ԭ���У�-F����ͬ������
            {
                if (J_Matrix[i][j] != 0)
                {
                    for (int k = 0; k < COEF_NUM; k++)
                    {
                        J_Matrix[j][k] += J_Matrix[i][k];
                    }
                    _F_Matrix[j] += _F_Matrix[i];
                    break;
                }
            }
        }
        for (int j = 0; j < COEF_NUM; j++) // ��Ԫ����Ҫ��-F����Ķ�Ӧ��������
        {
            for (int i = 0; i < COEF_NUM; i++)
            {
                if (i == j)
                {
                    continue;
                }
                _F_Matrix[i] -= (J_Matrix[i][j] / J_Matrix[j][j]) * _F_Matrix[j];
            }
        }
        for (int i = 0; i < COEF_NUM; i++) // ���ɵ�λ��ӳ�䵽-F����Ķ�Ӧ�������õ���Ҫ��ϵ������
        {
            diffA_Matrix[i] = _F_Matrix[i] / J_Matrix[i][i];
        }
        /* ���㾫�� */
        precision = 0;
        for (int i = 0; i < COEF_NUM; i++)
        {
            precision += pow(diffA_Matrix[i], 2);
        }
        if (epoch % 1000 == 0)
        {
            printf("\nPrecision: %lf", precision);
        }
        epoch++;
    } while (epoch < EPOCH && precision > PRECISION);
    /* ��� */
    double mse = 0;
    for (int i = 0; i < dataTrueSize; i++)
    {
        double forcast = A_Matrix[0] * sin(A_Matrix[1] * x[i] + A_Matrix[2]) + A_Matrix[3];
        printf("\nforcast: %lf \ttruth: %lf \terror: %f",
               forcast * (maxOut - minOut) + minOut, y[i] * (maxOut - minOut) + minOut, (forcast - y[i]) * (maxOut - minOut));
        mse += pow((forcast - y[i]) * (maxOut - minOut), 2);
    }
    printf("\nY = %lf sin(%lf x + %lf) + %lf", A_Matrix[0], A_Matrix[1], A_Matrix[2], A_Matrix[3]);
    printf("\n\tAverage MSE is %lf", mse / dataTrueSize);
}

time_t toDatetime(Date date)
{
    struct tm tm_;
    tm_.tm_year = date.year - 1900; // �꣬����������ء�
    tm_.tm_mon = date.month - 1;    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
    tm_.tm_mday = date.day;         // �ա�
    tm_.tm_hour = 0;                // ʱ��
    tm_.tm_min = 0;                 // �֡�
    tm_.tm_sec = 0;                 // �롣
    tm_.tm_isdst = 0;               // ������ʱ��
    time_t t_ = mktime(&tm_);       // ��tm�ṹ��ת����time_t��ʽ��
    return t_;
}
