#ifndef BAYES_H
#define BAYES_H

#include "data.h"

/*
    �������ܣ�ͨ�����ر�Ҷ˹��������ͳ�����е����ݣ����Զ�δ��ĳ�����������Ԥ�⣬
                ����ӡ�����ֻ��������������硢�ꡢѩ���ĳ��ָ��ʼ�ģ�͵�׼ȷ�ʺ��ٻ���
    ��ν��ͣ�
        futureDate Date���� ����Ԥ�����һ��
        p ָ���Ѿ��������ݵ����ݿ��ָ��
        databaseSize ���ݿ��������������ݿ��ļ���������
        dataTrueSize ���ݿ��ʵ������
    ����ֵ�� ��
 */
void FitWeatherModel_NB(Date futureDate, Database *p, int databaseSize, int dataTrueSize);

#endif