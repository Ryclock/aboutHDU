#ifndef IRISKNN_H
#define IRISKNN_H

#include <stdbool.h>

#define DATAMAXN 150
#define DATATRAIN (int)(DATAMAXN * 3 / 5)
#define EPCHO 10000
#define K 5

enum property
{
    sepalLength,
    sepalWidth,
    petalLength,
    petalWidth,
    dimensionN,
};

/* º¯Êý¶¨Òå */

bool GetData(void);

void Preprocess(void);

void KNN(void);

double GetAccuracy(void);

#endif