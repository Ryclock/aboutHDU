#ifndef HOUSING_H
#define HOUSING_H

#include <stdbool.h>

#define DATAMAXN 506
#define DATATRAIN (int)(DATAMAXN * 3 / 5)
#define BEFOREMEDV 13
#define NBESTDIMENSION 4

enum dimensionToDigit
{
    CRIM,
    ZN,
    INDUS,
    CHAS,
    NOX,
    RM,
    AGE,
    DIS,
    RAD,
    TAX,
    PTRATIO,
    B,
    LSTAT,
    MEDV,
    INFOMAXN
};
typedef char *string;
extern string digitToDimension[BEFOREMEDV];
typedef double Data_T;
Data_T dataAll[DATAMAXN][INFOMAXN];

/* º¯Êý¶¨Òå */

bool GetData(void);

void NormalizeData(void);

#endif