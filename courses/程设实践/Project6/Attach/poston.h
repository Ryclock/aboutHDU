#ifndef POSTON_H
#define POSTON_H

#define DATA_TRAIN 380
#define DATA_TEST 126
#define EPOCH_MAX 40000
#define IN 13
#define OUT 1
#define NEURON 40
#define W_ALPHA 0.1
#define V_ALPHA 0.2

void ReadData(void);

void InitBPNetwork(void);

void TrainBPNetwork(void);

void TestBPNetwork(void);

#endif