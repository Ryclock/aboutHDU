#ifndef BP_W_H
#define BP_W_H

#include "data.h"

/* 仅对基本天气进行预测，即晴、阴、雨、雪 */
void InitWeatherModel_BP(Database *p, int databaseSize);

#endif