#include <stdlib.h>
#include "irisBP.h"

int main(void)
{
    ReadData();
    InitBPNetwork();
    TrainBPNetwork();
    system("pause");
    TestBPNetwork();
    system("pause");
    return 0;
}