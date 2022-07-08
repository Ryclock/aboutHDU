#ifndef SIMPLEHOUSEPREDICTION_H
#define SIMPLEHOUSEPREDICTION_H

#include <stdbool.h>

#define DATAMAXN 100

/* º¯Êý¶¨Òå */

bool GetData(void);

void InitProblem(void);

void LineReg(void);

void OutputResult(void);

#endif