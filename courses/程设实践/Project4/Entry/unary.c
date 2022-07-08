#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "unary.h"

struct data
{
    double x; // one dimension from[CRIM, ZN, INDUS, CHAS, NOX, RM, AGE, DIS, RAD, TAX, PTRATIO, B, LSTAT]
    double y; // MEDV
} data[DATAMAXN], max, min;
double a; // Y = a + bX
double b; // Y = a + bX
double sumx;
double sumy;
double sumxx;
double sumxy;
double sumyy;
double r[BEFOREMEDV];
bool flag[BEFOREMEDV];
int bestDimension;
string correlateStrength[5] = {
    "Extremely weak",   // |r| < 0.2    -> 0
    "Weak",             // |r| < 0.4    -> 1
    "Medium level",     // |r| < 0.6    -> 2
    "Strong",           // |r| < 0.8    -> 3
    "Extremely strong", // |r| < 1.0    -> 4
};

/* 局部函数定义 */

void initUnary(int dimension);

void processUnary(int dimension);

void deviationUnary(int dimension);

void assessUnary(int dimension);

void bestUnary(void);

/* 接口实现 */

void UnaryLinearReg(int dimension)
{
    initUnary(dimension);
    processUnary(dimension);
    deviationUnary(dimension);
    assessUnary(dimension);
}

void AllUnaryLinearReg(int *dimension, int N)
{
    for (int i = 0; i < N; i++)
    {
        UnaryLinearReg(dimension[i]);
    }
    bestUnary();
}

void GetNBestUnary(int *best, int number)
{
    for (int i = 0; i < number; i++)
    {
        best[i] = 0;
    }
    for (int i = 0; i < BEFOREMEDV; i++)
    {
        flag[i] = false;
    }
    for (int i = 0; i < number; i++)
    {
        bestDimension = 0;
        for (int dimension = 1; dimension < BEFOREMEDV; dimension++)
        {
            if (flag[dimension] == true)
            {
                continue;
            }
            double tempR = r[dimension] > 0 ? r[dimension] : -r[dimension];
            double BestR = r[bestDimension] > 0 ? r[bestDimension] : -r[bestDimension];
            if ((tempR - BestR) > 0.001)
            {
                bestDimension = dimension;
            }
        }
        best[i] = bestDimension;
        flag[bestDimension] = true;
        printf("\nBest[%d]: %s", i + 1, digitToDimension[best[i]]);
    }
}

/* 局部函数实现 */

void initUnary(int dimension)
{
    max.x = min.x = dataAll[0][dimension];
    max.y = min.y = dataAll[0][MEDV];
    for (int i = 1; i < DATATRAIN; i++)
    {
        if (dataAll[i][dimension] > max.x)
        {
            max.x = dataAll[i][dimension];
        }
        else if (dataAll[i][dimension] < min.x)
        {
            min.x = dataAll[i][dimension];
        }
        if (dataAll[i][MEDV] > max.y)
        {
            max.y = dataAll[i][MEDV];
        }
        else if (dataAll[i][MEDV] < min.y)
        {
            min.y = dataAll[i][MEDV];
        }
    }
    for (int i = 0; i < DATAMAXN; i++)
    {
        data[i].x = (dataAll[i][dimension] - min.x) / (max.x - min.x);
        data[i].y = (dataAll[i][MEDV] - min.y) / (max.y - min.y);
    }
    a = b = sumx = sumy = sumxx = sumxy = sumyy = 0;
}

void processUnary(int dimension)
{
    for (int i = 0; i < DATATRAIN; i++)
    {
        sumx += data[i].x;
        sumy += data[i].y;
        sumxx += data[i].x * data[i].x;
        sumxy += data[i].x * data[i].y;
        sumyy += data[i].y * data[i].y;
    }
    b = (sumxy * DATATRAIN - sumx * sumy) / (sumxx * DATATRAIN - sumx * sumx);
    a = sumy / DATATRAIN - b * sumx / DATATRAIN;
    printf("\nPrediction(%7s And MENV):\tY = %+4.2lfX %+4.2lf", digitToDimension[dimension], b, a);
}

void deviationUnary(int dimension)
{
    /*
        RMSE = sqrt(E[(obs-model)^2]) = sqrt(sum((obs - model)^2) / n)
     */
    double sum_ObsAndModel = 0;
    for (int i = DATATRAIN + 1; i < DATAMAXN; i++)
    {
        double model = a + b * data[i].x;
        double modelReal = model * (max.y - min.y) + min.y;
        sum_ObsAndModel += pow((dataAll[i][MEDV] - modelReal), 2);
    }
    double rmse = sqrt(sum_ObsAndModel / (DATAMAXN - DATATRAIN - 1)); // 分母确保方差估计量的无偏性
    printf("\nRMSE:\t%.4lf", rmse);
}

void assessUnary(int dimension) // using the Pearson correlation coefficient
{
    /*
        r = Cov(X,Y)/ sqrt(Var[X]*Var[Y])
        Cov(X,Y) = E[XY] - E[X]E[Y] = sumxy/n - (sumx/n)*(sumy/n)
        Var[X] = E[X^2] - (E[X])^2 = sumxx/n - (sumx/n)^2
    */
    double covxy = sumxy / DATATRAIN - sumx * sumy / pow(DATATRAIN, 2);
    double varx = sumxx / DATATRAIN - sumx * sumx / pow(DATATRAIN, 2);
    double vary = sumyy / DATATRAIN - sumy * sumy / pow(DATATRAIN, 2);
    r[dimension] = covxy / sqrt(varx * vary);
    printf("\nPerson:\t%+4.2lf\nExtent:\t%s", r[dimension], correlateStrength[abs((int)(r[dimension] * 100)) / 20]);
}

void bestUnary(void)
{
    bestDimension = 0;
    for (int dimension = 1; dimension < BEFOREMEDV; dimension++)
    {
        double tempR = r[dimension] > 0 ? r[dimension] : -r[dimension];
        double BestR = r[bestDimension] > 0 ? r[bestDimension] : -r[bestDimension];
        if ((tempR - BestR) > 0.0001)
        {
            bestDimension = dimension;
        }
    }
    printf("\n\n\nBest prediction:(%s And MENV): Y = %+.2lfX%+.2lf", digitToDimension[bestDimension], b, a);
    printf("\nPerson:\t%+.2lf\nExtent:\t%s", r[bestDimension], correlateStrength[abs((int)(r[bestDimension] * 100)) / 20]);
}
