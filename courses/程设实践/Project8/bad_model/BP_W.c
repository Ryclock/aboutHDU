#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "BP_W.h"

#define DATAMAXN (365 * 5)
#define DATATRAIN DATAMAXN
#define DATATEST (DATAMAXN - DATATRAIN)
#define IN 3
#define OUT 4
#define NEURON 5
#define EPOCH_MAX 100000
#define W01_ALPHA 0.3
#define W12_ALPHA 0.02

char *basicWeatherName[OUT] = {
    "雪",
    "雨",
    "阴",
    "晴",
};

double dataAll_in[DATAMAXN][IN];
int dataAll_out[DATAMAXN][OUT];
double maxIn[IN], minIn[IN];
double train_in[DATATRAIN][IN];
double test_in[DATATEST][IN];
double w01[IN][NEURON];
double neuron1[NEURON];
double w12[NEURON][OUT];
double pred_out[OUT];
int train_out[DATATRAIN][OUT];
int test_out[DATATEST][OUT];

/* 局部函数定义 */

void softmax(double *src, double *dst, int length);

void initDataAll(Database *p, int databaseSize);

void parseWeatherName(char *str, int *dst);

void shuffle(void);

void divideData(void);

void normalizate(void);

void InitBPNetwork(void);

void TrainBPNetwork(void);

void TestBPNetwork(void);

/* 接口函数实现 */

void InitWeatherModel_BP(Database *p, int databaseSize)
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

void softmax(double *src, double *dst, int length)
{
    double sum = 0.0;
    for (int i = 0; i < length; i++)
    {
        sum += exp(src[i]);
    }
    for (int i = 0; i < length; i++)
    {
        dst[i] = exp(src[i]) / sum;
    }
}

void initDataAll(Database *p, int databaseSize)
{
    for (int i = 0, t = 0; i < databaseSize; i++, t++)
    {
        if (!(*p)[i].validity)
        {
            t--;
            continue;
        }
        dataAll_in[t][0] = (double)((*p)[i].date.year);
        dataAll_in[t][1] = (double)((*p)[i].date.month);
        dataAll_in[t][2] = (double)((*p)[i].date.day);
        parseWeatherName((*p)[i].weather.name, dataAll_out[t]);
    }
}

void parseWeatherName(char *str, int *dst)
{
    int basic = 0;
    for (int i = 1; i < OUT; i++)
    {
        if (strstr(str, basicWeatherName[i]))
        {
            basic = i;
            break;
        }
    }
    memset(dst, 0, sizeof(dst));
    dst[basic] = 1;
}

void shuffle(void)
{
    srand((unsigned int)time(NULL));
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
            int temp;
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
        if (i < DATATEST)
        {
            for (int j = 0; j < IN; j++)
            {
                test_in[i][j] = dataAll_in[i][j];
            }
            for (int j = 0; j < OUT; j++)
            {
                test_out[i][j] = dataAll_out[i][j];
            }
        }
        else
        {
            for (int j = 0; j < IN; j++)
            {
                train_in[i - DATATEST][j] = dataAll_in[i][j];
            }
            for (int j = 0; j < OUT; j++)
            {
                train_out[i - DATATEST][j] = dataAll_out[i][j];
            }
        }
    }
}

void normalizate(void)
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
}

void InitBPNetwork(void)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < NEURON; i++)
    {
        for (int j = 0; j < IN; j++)
        {
            w01[j][i] = rand() % 2 - 1;
        }
        for (int j = 0; j < OUT; j++)
        {
            w12[i][j] = rand() % 2 - 1;
        }
    }
}

void TrainBPNetwork(void)
{
    int epoch = 0;
    double accuracy;
    do
    {
        accuracy = 0;
        double softmax_out[OUT];
        for (int i = 0; i < DATATRAIN; i++)
        {
            /* forward */
            for (int j = 0; j < NEURON; j++)
            {
                neuron1[j] = 0;
                for (int k = 0; k < IN; k++)
                {
                    neuron1[j] += train_in[i][k] * w01[k][j];
                }
                neuron1[j] = 1 / (1 + exp(-1 * neuron1[j]));
            }
            for (int j = 0; j < OUT; j++)
            {
                pred_out[j] = 0;
                for (int k = 0; k < NEURON; k++)
                {
                    pred_out[j] += neuron1[k] * w12[k][j];
                }
                pred_out[j] = 1 / (1 + exp(-1 * pred_out[j]));
            }
            softmax(pred_out, softmax_out, OUT);
            /* backward */
            for (int j = 0; j < NEURON; j++)
            {
                double loss_w01 = 0;
                for (int k = 0; k < OUT; k++)
                {
                    double loss = (pred_out[k] - train_out[i][k]);
                    w12[j][k] -= W12_ALPHA * loss * neuron1[j];
                    loss_w01 += w12[j][k] * loss;
                }
                for (int k = 0; k < IN; k++)
                {
                    double loss = loss_w01 * neuron1[j] * (1 - neuron1[j]);
                    w01[k][j] -= W01_ALPHA * loss * train_in[i][k];
                }
            }
            /* Accuracy */
            int prediction = 0;
            for (int j = 1; j < OUT; j++)
            {
                prediction = pred_out[j] > pred_out[prediction] ? j : prediction;
            }
            if (train_out[i][prediction] == 1)
            {
                accuracy++;
            }
            // printf("\nPredict: %s", basicWeatherName[prediction]);
            // for (int j = 0; j < OUT; j++)
            // {
            //     if (train_out[i][j] == 1)
            //     {
            //         printf("\tTruth: %s", basicWeatherName[j]);
            //         break;
            //     }
            // }
        }
        accuracy /= DATATRAIN;
        if (epoch % 1000 == 0)
        {
            printf("\nEPOCH: %d\tAccurary: %.3lf", epoch, accuracy);
            // system("pause");
        }
        epoch++;
    } while (epoch <= EPOCH_MAX);
    printf("\nEnd Train Success");
}

void TestBPNetwork(void)
{
    double accuracy;
    for (int i = 0; i < DATATEST; i++)
    {
        double softmax_out[OUT];
        /* forward */
        for (int j = 0; j < NEURON; j++)
        {
            neuron1[j] = 0;
            for (int k = 0; k < IN; k++)
            {
                neuron1[j] += test_in[i][k] * w01[k][j];
            }
            neuron1[j] = 1 / (1 + exp(-1 * neuron1[j]));
        }
        double lnC = 0;
        for (int j = 0; j < OUT; j++)
        {
            pred_out[j] = 0;
            for (int k = 0; k < NEURON; k++)
            {
                pred_out[j] += neuron1[k] * w12[k][j];
            }
            pred_out[j] = 1 / (1 + exp(-1 * pred_out[j]));
            lnC = pred_out[j] > lnC ? pred_out[j] : lnC;
        }
        double sum_ex = 0;
        for (int j = 0; j < OUT; j++)
        {
            sum_ex += exp(pred_out[j] - lnC);
        }
        for (int j = 0; j < OUT; j++)
        {
            softmax_out[j] = exp(pred_out[j] - lnC) / sum_ex;
        }
        /* Accuracy */
        int truth = 0, prediction = 0;
        for (int j = 1; j < OUT; j++)
        {
            prediction = softmax_out[j] > softmax_out[prediction] ? j : prediction;
            if (test_out[i][j] == 1)
            {
                truth = j;
            }
        }
        printf("\nPrediction: %s", basicWeatherName[prediction]);
        printf("\nTruth: %s", basicWeatherName[truth]);
    }
    /* Accuracy */
    printf("\nAccurary: %.3lf", accuracy);
}