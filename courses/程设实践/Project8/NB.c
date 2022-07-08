#include <stdio.h>
#include <string.h>
#include "NB.h"

#define X_DIMENSION 12 * 31 // ����������أ���Ϊ��֤�������Զ����º��պϳ�һ��ά��
#define Y_DIMENSION 4

/* ���� */

/* ���Ի�����������ͳ�ƣ����硢�����ꡢѩ */
const char *BasicWeatherName[Y_DIMENSION] = {
    "��",
    "��",
    "��",
    "ѩ",
};

/* ȫ�ֱ��� */

int truth[X_DIMENSION];                              // ÿ�����ʵ����
double priori_P[Y_DIMENSION] = {0};                  // �������
double marginal_P[X_DIMENSION] = {0};                // �߼ʸ��ʣ�֤�ݣ�
double likelihood_P[Y_DIMENSION][X_DIMENSION] = {0}; // ��Ȼ���ʣ��������ʣ�
double posterior_P[X_DIMENSION][Y_DIMENSION];        // �������
int posterior_P_Best[X_DIMENSION];                   // ������ʵ����Ž�
int Matrix[Y_DIMENSION][Y_DIMENSION] = {0};          // ��������Matrix[predition_out][test_out]
double accuracy = 0;                                 // ׼ȷ��
double recall = 0;                                   // �ٻ���

/* �ֲ��������� */

/* ͳ�������Ϣ���ִ��� */
void initFrequency(Database *p, int databaseSize);

/* �����ĸ����ʺ����Ž� */
void calFourProbability(int dataTrueSize);

/* ����������� */
void calMatrix(Database *p, int databaseSize);

/* ����׼ȷ�ʺ��ٻ��� */
void evaluateModel(int dataTrueSize);

/* �ӿ�ʵ�� */

void FitWeatherModel_NB(Date futureDate, Database *p, int databaseSize, int dataTrueSize)
{
    initFrequency(p, databaseSize);
    calFourProbability(dataTrueSize);
    calMatrix(p, databaseSize);
    evaluateModel(dataTrueSize);
    printf("\n%d-%d-%d�Ļ�������Ԥ�����£�", futureDate.year, futureDate.month, futureDate.day);
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        printf("\n\tP(%s) = %.2lf",
               BasicWeatherName[i],
               posterior_P[(futureDate.month - 1) * 31 + (futureDate.day - 1)][i]);
    }
    printf("\n��ͳ����ģ��Ԥ���׼ȷ��Ϊ %.3lf���ٻ���Ϊ %.3lf", accuracy, recall);
}

/* �ֲ�����ʵ�� */
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
    /* ��Ȼ���� */
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        for (int j = 0; j < X_DIMENSION; j++)
        {
            likelihood_P[i][j] /= priori_P[i];
        }
    }
    /* ������� */
    for (int i = 0; i < Y_DIMENSION; i++)
    {
        priori_P[i] /= dataTrueSize;
    }
    /* �߼ʸ��� */
    for (int i = 0; i < X_DIMENSION; i++)
    {
        marginal_P[i] /= dataTrueSize;
    }
    /* ������� */
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
    /* ���Ž� */
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