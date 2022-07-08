#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "irisBP.h"

String iris_kinds[OUT] = {
    "Iris-setosa",
    "Iris-versicolor",
    "Iris-virginica",
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
double softmax_out[OUT];
int train_out[DATATRAIN][OUT];
int test_out[DATATEST][OUT];

int Matrix[OUT][OUT]; // Matrix[predition_out][test_out]

/* 局部函数定义 */

void shuffle(void);

void divideData(void);

void normalizate(void);

/* 接口函数实现 */

void ReadData(void)
{
    FILE *fp = fopen("data.txt", "rb"); // First make sure that the path is correct
    if (fp != NULL)
    {
        char ch;
        for (int i = 0; i < DATAMAXN; i++)
        {
            for (int j = 0; j < IN; j++)
            {
                if (j != 0)
                {
                    fscanf(fp, "%c", &ch);
                }
                fscanf(fp, "%lf", &dataAll_in[i][j]);
            }
            char buffer[256];
            fscanf(fp, "%c%s", &ch, buffer);
            for (int j = 0; j < OUT; j++)
            {
                if (strcmp(buffer, iris_kinds[j]) == 0)
                {
                    dataAll_out[i][j] = 1;
                }
                else
                {
                    dataAll_out[i][j] = 0;
                }
            }
        }
    }
    else
    {
        fputs("Open Error!", stderr);
        system("pause");
        exit(1);
    }
    fclose(fp);
}

void InitBPNetwork(void)
{
    shuffle();
    divideData();
    normalizate();

    srand((unsigned int)time(0));
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
    double accuracy, recall;
    do
    {
        memset(Matrix, 0, sizeof(Matrix));
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
            /* backward */
            for (int j = 0; j < NEURON; j++)
            {
                double loss_w01 = 0;
                for (int k = 0; k < OUT; k++)
                {
                    double loss = (pred_out[k] - train_out[i][k]) * pred_out[k] * (1 - pred_out[k]);
                    w12[j][k] -= W12_ALPHA * loss * neuron1[j];
                    loss_w01 += w12[j][k] * loss;
                }
                for (int k = 0; k < IN; k++)
                {
                    double loss = loss_w01 * neuron1[j] * (1 - neuron1[j]);
                    w01[k][j] -= W01_ALPHA * loss * train_in[i][k];
                }
            }
            /* Matrix[prediction][truth] */
            int truth = 0, prediction = 0;
            for (int j = 1; j < OUT; j++)
            {
                prediction = pred_out[j] > pred_out[prediction] ? j : prediction;
                if (train_out[i][j] == 1)
                {
                    truth = j;
                }
            }
            Matrix[prediction][truth]++;
        }
        /* Accuracy */
        accuracy = recall = 0;
        for (int tru = 0; tru < OUT; tru++)
        {
            accuracy += (Matrix[tru][tru] / (double)DATATRAIN);
            double sum_tru = 0;
            for (int pred = 0; pred < OUT; pred++)
            {
                sum_tru += (double)Matrix[pred][tru];
            }
            recall += (Matrix[tru][tru] / sum_tru) / OUT;
        }
        if (epoch % 1000 == 0)
        {
            printf("\nEPOCH: %d\tAccurary: %.3lf\tRecall: %.3lf", epoch, accuracy, recall);
        }
        epoch++;
    } while (epoch <= EPOCH_MAX);
    printf("\nEnd Train Success");
}

void TestBPNetwork(void)
{
    double accuracy, recall;
    memset(Matrix, 0, sizeof(Matrix));
    for (int i = 0; i < DATATEST; i++)
    {
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
        /* Test Data */
        printf("\nPrediction:");
        for (int j = 0; j < OUT; j++)
        {
            printf("%6.3lf", softmax_out[j]);
        }
        printf("\nTruth Data:");
        for (int j = 0; j < OUT; j++)
        {
            printf("%6d", test_out[i][j]);
        }
        /* Matrix[prediction][truth] */
        int truth = 0, prediction = 0;
        for (int j = 1; j < OUT; j++)
        {
            prediction = softmax_out[j] > softmax_out[prediction] ? j : prediction;
            if (test_out[i][j] == 1)
            {
                truth = j;
            }
        }
        Matrix[prediction][truth]++;
    }
    /* Accuracy */
    accuracy = recall = 0;
    for (int tru = 0; tru < OUT; tru++)
    {
        accuracy += (Matrix[tru][tru] / (double)DATATEST);
        double sum_tru = 0;
        for (int pred = 0; pred < OUT; pred++)
        {
            sum_tru += (double)Matrix[pred][tru];
        }
        recall += (Matrix[tru][tru] / sum_tru) / OUT;
    }
    printf("\nAccurary: %.3lf\tRecall: %.3lf", accuracy, recall);
}

/* 局部函数实现 */

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
}
