#ifndef IRISBP_H
#define IRISBP_H

#define DATAMAXN 150
#define DATATRAIN 113
#define DATATEST (DATAMAXN - DATATRAIN)
#define EPOCH_MAX 10000
#define IN 4
#define OUT 3
#define NEURON 5
#define W01_ALPHA 0.01
#define W12_ALPHA 0.01

typedef char *String;

void ReadData(void);

void InitBPNetwork(void);

void TrainBPNetwork(void);

void TestBPNetwork(void);

#endif
