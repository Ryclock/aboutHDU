#ifndef PR_H
#define PR_H

#include "data.h"

/*
    函数功能：通过多项式拟合，对未来某天的最高温和最低温进行预测，
                并打印出预测的气温及可能误差
    输参解释：
        futureDate Date类型 代表预测的那一天
        p 指向已经导入数据的数据库的指针
        databaseSize 数据库的最大容量（数据库文件的行数）
        dataTrueSize 数据库的实际容量
    返回值： 无
 */
void FitTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize);

#endif