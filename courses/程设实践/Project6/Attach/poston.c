#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "poston.h"

double train_in[DATA_TRAIN][IN];
double train_out[DATA_TRAIN][OUT];
double test_in[DATA_TEST][IN];
double test_out[DATA_TEST][OUT];
double v[IN][NEURON];
double w[NEURON][OUT];
double neuron[NEURON];
double pre[OUT];
double maxIn[IN], minIn[IN];
double maxOut[OUT], minOut[OUT];

void ReadData(void)
{
    char ch;
    FILE *fp1 = fopen("in.txt", "rb"); // First make sure that the path is correct
    if (fp1 != NULL)
    {
        for (int i = 0; i < DATA_TRAIN; i++)
        {
            for (int j = 0; j < IN; j++)
            {
                if (j != 0)
                {
                    fscanf(fp1, "%c", &ch);
                }
                fscanf(fp1, "%lf", &train_in[i][j]);
            }
        }
    }
    else
    {
        fputs("Open Error", stderr);
    }
    fclose(fp1);

    FILE *fp2 = fopen("out.txt", "rb"); // First make sure that the path is correct
    if (fp2 != NULL)
    {
        for (int i = 0; i < DATA_TRAIN; i++)
        {
            for (int j = 0; j < OUT; j++)
            {
                if (j != 0)
                {
                    fscanf(fp2, "%c", &ch);
                }
                fscanf(fp2, "%lf", &train_out[i][j]);
            }
        }
    }
    else
    {
        fputs("Open Error", stderr);
    }
    fclose(fp2);
}

void InitBPNetwork(void)
{
    /* 输入层Max—Min归一化 */
    for (int i = 0; i < IN; i++)
    {
        maxIn[i] = minIn[i] = train_in[0][i];
        for (int j = 1; j < DATA_TRAIN; j++)
        {
            maxIn[i] = train_in[j][i] > maxIn[i] ? train_in[j][i] : maxIn[i];
            minIn[i] = train_in[j][i] < minIn[i] ? train_in[j][i] : minIn[i];
        }
    }
    for (int i = 0; i < DATA_TRAIN; i++)
    {
        for (int j = 0; j < IN; j++)
        {
            train_in[i][j] = (train_in[i][j] - minIn[j]) / (maxIn[j] - minIn[j]);
        }
    }
    /* 输出层Max—Min归一化 */
    for (int i = 0; i < OUT; i++)
    {
        maxOut[i] = minOut[i] = train_out[0][i];
        for (int j = 1; j < DATA_TRAIN; j++)
        {
            maxOut[i] = train_out[j][i] > maxOut[i] ? train_out[j][i] : maxOut[i];
            minOut[i] = train_out[j][i] < minOut[i] ? train_out[j][i] : minOut[i];
        }
    }
    for (int i = 0; i < DATA_TRAIN; i++)
    {
        for (int j = 0; j < OUT; j++)
        {
            train_out[i][j] = (train_out[i][j] - minOut[j]) / (maxOut[j] - minOut[j]);
        }
    }
    /* 权重初始化 */
    srand((unsigned int)time(0));
    for (int i = 0; i < NEURON; i++)
    {
        for (int j = 0; j < IN; j++)
        {
            v[j][i] = rand() % 2 - 1;
        }
        for (int j = 0; j < OUT; j++)
        {
            w[i][j] = rand() % 2 - 1;
        }
    }
}

void TrainBPNetwork(void)
{
    int epoch = 0;
    double mse;
    do
    {
        mse = 0;
        for (int i = 0; i < DATA_TRAIN; i++)
        {
            /* forward */
            for (int j = 0; j < NEURON; j++)
            {
                neuron[j] = 0;
                for (int k = 0; k < IN; k++)
                {
                    neuron[j] += train_in[i][k] * v[k][j];
                }
                neuron[j] = 1 / (1 + exp(-1 * neuron[j]));
            }
            for (int j = 0; j < OUT; j++)
            {
                pre[j] = 0;
                for (int k = 0; k < NEURON; k++)
                {
                    pre[j] += neuron[k] * w[k][j];
                }
                pre[j] = 1 / (1 + exp(-1 * pre[j]));
            }
            /* backward */
            for (int j = 0; j < NEURON; j++)
            {
                double t = 0;
                for (int k = 0; k < OUT; k++)
                {
                    w[j][k] += W_ALPHA * (train_out[i][k] - pre[k]) * pre[k] * (1 - pre[k]) * neuron[j];
                    t += (train_out[i][k] - pre[k]) * pre[k] * (1 - pre[k]) * w[j][k];
                }
                for (int k = 0; k < IN; k++)
                {
                    v[k][j] += V_ALPHA * t * neuron[j] * (1 - neuron[j]) * train_in[i][k];
                }
            }
            /* MSE */
            for (int j = 0; j < OUT; j++)
            {
                mse += pow((pre[j] - train_out[i][j]) * (maxOut[j] - minOut[j]), 2);
            }
        }
        mse /= (DATA_TRAIN * OUT);
        if (epoch % 1000 == 0)
        {
            printf("\nEPOCH: %d, MSE: %.2lf", epoch, mse);
        }
        epoch++;
    } while (epoch <= EPOCH_MAX && mse >= 1);
    printf("\nEnd Train Success!");
}

void TestBPNetwork(void)
{
    FILE *fp = fopen("test.txt", "rb"); // First make sure that the path is correct
    if (fp != NULL)
    {
        char ch;
        for (int i = 0; i < DATA_TEST; i++)
        {
            for (int j = 0; j < IN; j++)
            {
                if (j != 0)
                {
                    fscanf(fp, "%c", &ch);
                }
                fscanf(fp, "%lf", &test_in[i][j]);
            }
            for (int j = 0; j < OUT; j++)
            {
                fscanf(fp, "%c%lf", &ch, &test_out[i][j]);
            }
        }
    }
    else
    {
        fputs("Open Error", stderr);
    }

    /* test_in -> Max-Min归一化 */
    for (int i = 1; i < DATA_TEST; i++)
    {
        for (int j = 0; j < IN; j++)
        {
            test_in[i][j] = (test_in[i][j] - minIn[j]) / (maxIn[j] - minIn[j]);
        }
    }
    /* get pre[OUT] && RMSE*/
    double rmse = 0;
    for (int i = 0; i < DATA_TEST; i++)
    {
        for (int j = 0; j < NEURON; j++)
        {
            neuron[j] = 0;
            for (int k = 0; k < IN; k++)
            {
                neuron[j] += test_in[i][k] * v[k][j];
            }
            neuron[j] = 1 / (1 + exp(-1 * neuron[j]));
        }
        for (int j = 0; j < OUT; j++)
        {
            pre[j] = 0;
            for (int k = 0; k < NEURON; k++)
            {
                pre[j] += neuron[k] * w[k][j];
            }
            pre[j] = (1 / (1 + exp(-1 * pre[j]))) * (maxOut[j] - minOut[j]) + minOut[j];
            printf("\n TestID: %d, prediction: %.2lf, truth: %.2lf", i + 1, pre[j], test_out[i][j]);
            rmse += pow((pre[j] - test_out[i][j]), 2);
        }
    }
    rmse = sqrt(rmse / DATA_TEST * OUT);
    printf("\nRMSE: %.2lf", rmse);
}