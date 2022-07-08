#ifndef BAYES_H
#define BAYES_H

#include "data.h"

/*
    函数功能：通过朴素贝叶斯分类器，统计已有的数据，尝试对未来某天的天气进行预测，
                并打印出四种基本天气（阴、晴、雨、雪）的出现概率及模型的准确率和召回率
    输参解释：
        futureDate Date类型 代表预测的那一天
        p 指向已经导入数据的数据库的指针
        databaseSize 数据库的最大容量（数据库文件的行数）
        dataTrueSize 数据库的实际容量
    返回值： 无
 */
void FitWeatherModel_NB(Date futureDate, Database *p, int databaseSize, int dataTrueSize);

#endif