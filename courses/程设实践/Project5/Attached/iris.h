#ifndef IRIS_H
#define IRIS_H

#include <stdbool.h>

#define K 3
#define MAXROUNDS 100
#define DATATRAIN 150

/* º¯Êý¶¨Òå */

bool GetData(void);

void InitCenter(void);

void KMeans(void);

#endif