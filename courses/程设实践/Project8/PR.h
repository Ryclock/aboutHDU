#ifndef PR_H
#define PR_H

#include "data.h"

/*
    �������ܣ�ͨ������ʽ��ϣ���δ��ĳ�������º�����½���Ԥ�⣬
                ����ӡ��Ԥ������¼��������
    ��ν��ͣ�
        futureDate Date���� ����Ԥ�����һ��
        p ָ���Ѿ��������ݵ����ݿ��ָ��
        databaseSize ���ݿ��������������ݿ��ļ���������
        dataTrueSize ���ݿ��ʵ������
    ����ֵ�� ��
 */
void FitTemperatureModel_PR(Date futureDate, Database *p, int databaseSize, int dataTrueSize);

#endif