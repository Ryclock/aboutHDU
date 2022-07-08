#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <math.h>
#include <time.h>
#include "iris.h"

#define NDIMENSION 4
#define RAW -1

struct iris
{
    double sepalLength;
    double sepalWidth;
    double petalLength;
    double petalWidth;
    int clusterID;
} irisData[150], center[K], newCenter[K];

bool isContinue;
double distanceToCenter[K];
int sizeOfCenter[K];

/* 局部函数定义 */

void DivideAllPoints(void);

void DivideOnePoint(int pointID);

void GetDistanceToAllCenters(int pointID);

void GetDistanceToOneCenter(int pointID, int centerID);

void GetNewCenters(void);

void CompareOldAndNew(void);

bool InitAllPoints(void);

/* 测试函数 */

int main(void)
{
    while (true)
    {
        if (!GetData())
        {
            fprintf(stdout, "Error no.%d: %s\n", errno, strerror(errno));
            system("pause");
            exit(errno);
        }
        InitCenter();
        KMeans();
        system("pause");
    }
    return 0;
}

/* 接口函数实现 */

bool GetData(void)
{
    char irisname[20];
    FILE *fp = fopen("data.txt", "rb"); // First make sure that the path is correct
    if (fp == NULL)
    {
        fputs("Open error", stderr);
        return false;
    }
    for (int i = 0; i < DATATRAIN; i++)
    {
        fscanf(fp, "%lf,%lf,%lf,%lf,%s", &irisData[i].sepalLength, &irisData[i].sepalWidth, &irisData[i].petalLength, &irisData[i].petalWidth, irisname);
    }
    fclose(fp);
    return true;
}

void InitCenter(void)
{
    int centerIndex[K];
    for (int i = 0; i < K; i++)
    {
        srand(time(0));
        int next = rand() % DATATRAIN;
        int j = 0;
        while (j < i)
        {
            if (next == centerIndex[j])
            {
                next = rand() % DATATRAIN;
                j = 0;
            }
            else
            {
                j++;
            }
        }
        center[i].clusterID = irisData[next].clusterID = i;
        center[i].sepalLength = irisData[next].sepalLength;
        center[i].sepalWidth = irisData[next].sepalWidth;
        center[i].petalLength = irisData[next].petalLength;
        center[i].petalWidth = irisData[next].petalWidth;
        centerIndex[i] = next;
    }
}

void KMeans(void)
{
    for (int round = 0; round < MAXROUNDS; round++)
    {
        printf("\n\nRound %d: ", round + 1);
        InitAllPoints();
        DivideAllPoints();
        GetNewCenters();
        if (!isContinue)
        {
            printf("\n\nEnding: All round cost is %d", round + 1);
            break;
        }
    }
}

/* 局部函数实现 */

void DivideAllPoints(void)
{
    for (int pointID = 0; pointID < DATATRAIN; pointID++)
    {
        GetDistanceToAllCenters(pointID);
        DivideOnePoint(pointID);
    }
}

void GetDistanceToAllCenters(int pointID)
{
    for (int centerID = 0; centerID < K; centerID++)
    {
        GetDistanceToOneCenter(pointID, centerID);
    }
}

void GetDistanceToOneCenter(int pointID, int centerID)
{
    double x1 = pow(irisData[pointID].sepalLength - center[centerID].sepalLength, 2);
    double x2 = pow(irisData[pointID].sepalWidth - center[centerID].sepalWidth, 2);
    double x3 = pow(irisData[pointID].petalLength - center[centerID].petalLength, 2);
    double x4 = pow(irisData[pointID].petalWidth - center[centerID].petalWidth, 2);
    distanceToCenter[centerID] = sqrt(x1 + x2 + x3 + x4);
}

void DivideOnePoint(int pointID)
{
    int minOneID = 0;
    for (int centerID = 1; centerID < K; centerID++)
    {
        if (distanceToCenter[centerID] < distanceToCenter[minOneID])
        {
            minOneID = centerID;
        }
    }
    irisData[pointID].clusterID = center[minOneID].clusterID;
}

void GetNewCenters(void)
{
    memset(newCenter, 0, sizeof(newCenter));
    memset(sizeOfCenter, 0, sizeof(sizeOfCenter));
    for (int i = 0; i < DATATRAIN; i++)
    {
        newCenter[irisData[i].clusterID].sepalLength += irisData[i].sepalLength;
        newCenter[irisData[i].clusterID].sepalWidth += irisData[i].sepalWidth;
        newCenter[irisData[i].clusterID].petalLength += irisData[i].petalLength;
        newCenter[irisData[i].clusterID].petalWidth += irisData[i].petalWidth;
        sizeOfCenter[irisData[i].clusterID]++;
    }
    for (int i = 0; i < K; i++)
    {
        if (sizeOfCenter[i] != 0)
        {
            newCenter[i].sepalLength /= sizeOfCenter[i];
            newCenter[i].sepalWidth /= sizeOfCenter[i];
            newCenter[i].petalLength /= sizeOfCenter[i];
            newCenter[i].petalWidth /= sizeOfCenter[i];
            printf("\nThe size of cluster center %d is %d", i + 1, sizeOfCenter[i]);
            printf("\n\tsepalLength:%.2lf\n\tsepalWidth:%.2lf\n\tpetalLength:%.2lf\n\tpetalWidth:%.2lf",
                   newCenter[i].sepalLength, newCenter[i].sepalWidth, newCenter[i].petalLength, newCenter[i].petalWidth);
        }
        else
        {
            printf("\nThe size of cluster center %d is zero!", i);
        }
    }
    CompareOldAndNew();
    for (int i = 0; i < K; i++)
    {
        center[i].sepalLength = newCenter[i].sepalLength;
        center[i].sepalWidth = newCenter[i].sepalWidth;
        center[i].petalLength = newCenter[i].petalLength;
        center[i].petalWidth = newCenter[i].petalWidth;
        center[i].clusterID = i;
    }
}

void CompareOldAndNew(void)
{
    for (int i = 0; i < K; i++)
    {
        if (newCenter[i].sepalLength != center[i].sepalLength ||
            newCenter[i].sepalWidth != center[i].sepalWidth ||
            newCenter[i].petalLength != center[i].petalLength ||
            newCenter[i].petalWidth != center[i].petalWidth)
        {
            isContinue = 1;
            return;
        }
    }
    isContinue = 0;
}

bool InitAllPoints(void)
{
    for (int i = 0; i < DATATRAIN; i++)
    {
        irisData[i].clusterID = RAW;
    }
}