#include <stdlib.h>
#include "poston.h"

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