#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "BP_T.h"

enum DateAttributes
{
    MONTH,
    DAY,
    YEAR,
    DATE_ATTRIBUTES_MAX,
};

enum TAttributes
{
    HIGHEST,
    LOWEST,
    T_ATTRIBUTES_MAX,
};

#define DATAMAXN (365 * 5)
#define DATATRAIN (365 * 4)
#define DATATEST (DATAMAXN - DATATRAIN)
#define IN 3
#define OUT 2
#define NEURON 7
#define EPOCH_MAX 30000
#define W_ALPHA_0 0.01
#define V_ALPHA_0 0.01

double dataAll_in[DATAMAXN][IN];
double dataAll_out[DATAMAXN][OUT];
double maxIn[IN], minIn[IN];
double maxOut[OUT], minOut[OUT];
double train_in[DATATRAIN][IN];
double test_in[DATATEST][IN];
double w[IN][NEURON];
double neuron1[NEURON];
double v[NEURON][OUT];
double pre[OUT];
double train_out[DATATRAIN][OUT];
double test_out[DATATEST][OUT];
double w_alpha;
double v_alpha;

/* 局部函数定义 */

void initDataAll(Database *p, int databaseSize);

void shuffle(void);

void divideData(void);

void normalizate(void);

void InitBPNetwork(void);

void TrainBPNetwork(void);

void TestBPNetwork(void);

void exponentialDecay(int epoch);

/* 接口函数实现 */

void InitTemperatureModel_BP(Database *p, int databaseSize)
{
    initDataAll(p, databaseSize);
    shuffle();
    divideData();
    normalizate();
    InitBPNetwork();
    TrainBPNetwork();
    TestBPNetwork();
}

/* 局部函数实现 */

void initDataAll(Database *p, int databaseSize)
{
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        dataAll_in[t][YEAR] = (double)((*p)[i].date.year);
        dataAll_in[t][MONTH] = (double)((*p)[i].date.month);
        dataAll_in[t][DAY] = (double)((*p)[i].date.day);
        dataAll_out[t][HIGHEST] = (*p)[i].temperature.max;
        dataAll_out[t][LOWEST] = (*p)[i].temperature.min;
    }
}

void shuffle(void)
{
    srand((unsigned int)time(0));
    for (int i = 0; i < DATAMAXN; i++)
    {
        int index1 = rand() % DATAMAXN;
        int index2 = rand() % DATAMAXN;
        while (index2 == index1)
        {
            index2 = rand() % DATAMAXN;
        }
        for (int j = 0; j < IN; j++)
        {
            double temp;
            temp = dataAll_in[index1][j];
            dataAll_in[index1][j] = dataAll_in[index2][j];
            dataAll_in[index2][j] = temp;
        }
        for (int j = 0; j < OUT; j++)
        {
            double temp;
            temp = dataAll_out[index1][j];
            dataAll_out[index1][j] = dataAll_out[index2][j];
            dataAll_out[index2][j] = temp;
        }
    }
}

void divideData(void)
{
    for (int i = 0; i < DATAMAXN; i++)
    {
        if (i < DATATRAIN)
        {
            for (int j = 0; j < IN; j++)
            {
                train_in[i][j] = dataAll_in[i][j];
            }
            for (int j = 0; j < OUT; j++)
            {
                train_out[i][j] = dataAll_out[i][j];
            }
        }
        else
        {
            for (int j = 0; j < IN; j++)
            {
                test_in[i - DATATRAIN][j] = dataAll_in[i][j];
            }
            for (int j = 0; j < OUT; j++)
            {
                test_out[i - DATATRAIN][j] = dataAll_out[i][j];
            }
        }
    }
}

void normalizate(void) // min-max normalizate
{
    for (int i = 0; i < IN; i++)
    {
        maxIn[i] = minIn[i] = train_in[0][i];
        for (int j = 1; j < DATATRAIN; j++)
        {
            maxIn[i] = train_in[j][i] > maxIn[i] ? train_in[j][i] : maxIn[i];
            minIn[i] = train_in[j][i] < minIn[i] ? train_in[j][i] : minIn[i];
        }
        for (int j = 0; j < DATATRAIN; j++)
        {
            train_in[j][i] = (train_in[j][i] - minIn[i]) / (maxIn[i] - minIn[i]);
        }
        for (int j = 0; j < DATATEST; j++)
        {
            test_in[j][i] = (test_in[j][i] - minIn[i]) / (maxIn[i] - minIn[i]);
        }
    }
    for (int i = 0; i < OUT; i++)
    {
        maxOut[i] = minOut[i] = train_out[0][i];
        for (int j = 1; j < DATATRAIN; j++)
        {
            maxOut[i] = train_out[j][i] > maxOut[i] ? train_out[j][i] : maxOut[i];
            minOut[i] = train_out[j][i] < minOut[i] ? train_out[j][i] : minOut[i];
        }
        for (int j = 0; j < DATATRAIN; j++)
        {
            train_out[j][i] = (train_out[j][i] - minOut[i]) / (maxOut[i] - minOut[i]);
        }
    }
}

void InitBPNetwork(void)
{
    srand((unsigned int)time(0));
    for (int i = 0; i < NEURON; i++)
    {
        for (int j = 0; j < IN; j++)
        {
            w[j][i] = rand() % 2 - 1;
        }
        for (int j = 0; j < OUT; j++)
        {
            v[i][j] = rand() % 2 - 1;
        }
    }
    w_alpha = W_ALPHA_0;
    v_alpha = V_ALPHA_0;
}

void TrainBPNetwork(void)
{
    int epoch = 0;
    double mse;
    do
    {
        mse = 0;
        for (int i = 0; i < DATATRAIN; i++)
        {
            /* forward */
            for (int j = 0; j < NEURON; j++)
            {
                neuron1[j] = 0;
                for (int k = 0; k < IN; k++)
                {
                    neuron1[j] += train_in[i][k] * w[k][j];
                }
                neuron1[j] = 1 / (1 + exp(-1 * neuron1[j]));
            }
            for (int j = 0; j < OUT; j++)
            {
                pre[j] = 0;
                for (int k = 0; k < NEURON; k++)
                {
                    pre[j] += neuron1[k] * v[k][j];
                }
                pre[j] = 1 / (1 + exp(-1 * pre[j]));
            }
            /* backward */
            for (int j = 0; j < NEURON; j++)
            {
                double t = 0;
                for (int k = 0; k < OUT; k++)
                {
                    w[j][k] += w_alpha * (train_out[i][k] - pre[k]) * pre[k] * (1 - pre[k]) * neuron1[j];
                    t += (train_out[i][k] - pre[k]) * pre[k] * (1 - pre[k]) * w[j][k];
                }
                for (int k = 0; k < IN; k++)
                {
                    v[k][j] += v_alpha * t * neuron1[j] * (1 - neuron1[j]) * train_in[i][k];
                }
            }
            /* MSE */
            for (int j = 0; j < OUT; j++)
            {
                mse += pow((pre[j] - train_out[i][j]) * (maxOut[j] - minOut[j]), 2);
            }
        }
        mse /= (DATATRAIN * OUT);
        if (epoch % 1000 == 0)
        {
            printf("\nEPOCH: %d,Average MSE: %lf", epoch, mse);
        }
        epoch++;
        exponentialDecay(epoch);
    } while (epoch <= EPOCH_MAX && mse >= 1);
    printf("\nEnd Train Success!");
}

void TestBPNetwork(void)
{
    double rmse = 0;
    for (int i = 0; i < DATATEST; i++)
    {
        for (int j = 0; j < NEURON; j++)
        {
            neuron1[j] = 0;
            for (int k = 0; k < IN; k++)
            {
                neuron1[j] += test_in[i][k] * w[k][j];
            }
            neuron1[j] = 1 / (1 + exp(-1 * neuron1[j]));
        }
        for (int j = 0; j < OUT; j++)
        {
            pre[j] = 0;
            for (int k = 0; k < NEURON; k++)
            {
                pre[j] += neuron1[k] * v[k][j];
            }
            pre[j] = (1 / (1 + exp(-1 * pre[j]))) * (maxOut[j] - minOut[j]) + minOut[j];
            printf("\nTestID: %d, Dimension: %d\n\tprediction: %.2lf VS truth: %.2lf", i + 1, j, pre[j], test_out[i][j]);
            rmse += pow((pre[j] - test_out[i][j]), 2);
        }
    }
    rmse = sqrt(rmse / DATATEST * OUT);
    printf("\nEach RMSE: %lf", rmse);
}

void exponentialDecay(int epoch)
{
    w_alpha = pow(0.95, epoch) * W_ALPHA_0;
    v_alpha = pow(0.95, epoch) * V_ALPHA_0;
}