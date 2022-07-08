#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "multiple.h"

#define MAXECHO 10000

Data_T max[INFOMAXN];
Data_T min[INFOMAXN];
Data_T W[BEFOREMEDV + 1];
Data_T prediction[DATAMAXN];
double alpha = 0.0008;

/* 局部函数定义 */

void initMultiple(void);

void processMultiple(int *dimension, int N);

void deviationMultiple(int *dimension, int N);

/* 接口实现 */

void MultipleLinearReg(int *dimension, int N)
{
    initMultiple();
    processMultiple(dimension, N);
    deviationMultiple(dimension, N);
}

/* 局部函数实现 */

void initMultiple(void)
{
    memset(W, 0, sizeof(W));
    for (int dimension = 0; dimension < INFOMAXN; dimension++)
    {
        max[dimension] = min[dimension] = dataAll[0][dimension];
        for (int i = 1; i < DATATRAIN; i++)
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

void processMultiple(int *dimension, int N)
{
    double grad[BEFOREMEDV + 1];
    double loss;
    for (int echo = 0; echo < MAXECHO; echo++)
    {
        loss = 0;
        for (int i = 0; i < DATATRAIN; i++)
        {
            prediction[i] = W[0] * 1;
            for (int j = 0; j < N; j++)
            {
                prediction[i] += W[dimension[j] + 1] * dataAll[i][dimension[j]];
            }
            loss += pow((prediction[i] - dataAll[i][MEDV]) * (max[MEDV] - min[MEDV]), 2);
        }
        loss = loss / (DATATRAIN - 1);
        printf("\nTrain loss: %.3lf", loss);
        if (loss < 0.001)
        {
            break;
        }
        for (int i = 0; i < BEFOREMEDV + 1; i++)
        {
            grad[i] = 0;
        }
        for (int i = 0; i < DATATRAIN; i++)
        {
            grad[0] += (prediction[i] - dataAll[i][MEDV]) * 1;
            for (int j = 0; j < N; j++)
            {
                grad[dimension[j] + 1] += (prediction[i] - dataAll[i][MEDV]) * dataAll[i][dimension[j]];
            }
        }
        for (int i = 0; i < BEFOREMEDV + 1; i++)
        {
            W[i] -= alpha * grad[i];
        }
    }
    printf("\nTrain loss: %.3lf", loss);
}

void deviationMultiple(int *dimension, int N)
{
    /*
        RMSE = sqrt(E[(obs-model)^2]) = sqrt(sum((obs - model)^2) / n)
     */
    double sum_ObsAndModel = 0;
    for (int i = DATATRAIN + 1; i < DATAMAXN; i++)
    {
        prediction[i] = W[0] * 1;
        for (int j = 0; j < N; j++)
        {
            prediction[i] += W[dimension[j] + 1] * dataAll[i][dimension[j]];
        }
        sum_ObsAndModel += pow((dataAll[i][MEDV] - prediction[i]) * (max[MEDV] - min[MEDV]), 2);
    }
    double rmse = sqrt(sum_ObsAndModel / (DATAMAXN - DATATRAIN - 1)); // 分母确保方差估计量的无偏性
    printf("\nRMSE: %.3lf", rmse);
}
