#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H

#include <stdbool.h>

#define NEW_EXCEPTION -1
#define WEATHER_NAME_MAX 20 // ����������Ϊ20��char�ַ�����10��������

enum WeatherType
{
    SUNNY,
    CLOUDY,
    OVERCAST,
    RAIN,
    SNOW,
    WEATHERTYPEMAX, //��ö�����͵���Чֵ����
};

enum WeatherExtent
{
    NO_EXTENT, // �޽�ˮ�̶ȣ����ǡ��ꡱ��ѩ��������
    MAOMAO,
    LIGHT,
    MODERATE,
    HEAVY,
    STORM,
    LIGHT_MODERATE,
    MODERATE_HEAVY,
    HEAVY_STORM,
    WEATHEREXTENTMAX, //��ö�����͵���Чֵ����
};

enum WeatherIncidental
{
    NO_INCIDENTAL, // �޸�����
    WITH_THUNDER,
    WITH_SNOW,
    WEATHERINCIDENTALMAX, //��ö�����͵���Чֵ����
};

enum WindDirection
{
    NO_SUSTAINED, //�޳�������
    EAST,
    WEST,
    NORTH,
    SOUTH,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST,
    WINDDIRECTIONMAX, //��ö�����͵���Чֵ����
};

/* �������� */

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char name[WEATHER_NAME_MAX];       // ����������
    enum WeatherType type;             // �������ͣ���Ҫ��
    enum WeatherExtent extent;         // ��ˮ�̶ȣ���Ҫ�������ݡ��ꡱ��ѩ����������
    enum WeatherIncidental incidental; // �������ͣ������������ס�������ѩ��
    bool suddenness;                   // ��ˮ�Ƿ����ͻȻ�ԣ����Ƿ�Ϊ�����ꡱ����ѩ��
} Weather;

typedef struct
{
    double max; // �����
    double min; // �����
} Temperature;

typedef struct
{
    enum WindDirection direction; // ����
    int average_power_max;        // ��߷����ȼ�
    int average_power_min;        // ��ͷ����ȼ�
} Wind;

typedef struct
{
    bool validity; // ����Ƿ�Ϊ��Ч�У�false����Ϊ���У�
    Date date;
    Weather weather;
    Temperature temperature;
    Wind wind;
} DataRecord, *Database;

/* �ӿڶ��� */

/*
    �������ܣ��������ݲ���ʼ�����ݿ�
    ���ν��ͣ�
        filePathName�������ļ�����·����
        p��ָ����Ҫ����ʼ�������ݿ��ָ��
        inited: ��ʶpָ������ݿ��Ƿ��Ѿ�����ʼ��
    ����ֵ��
        0������һ������
        NEW_EXCEPTION���������Զ������
        �����errnoֵ�����������Զ������
 */
int readData(char *filePathName, Database *p, bool *inited);

/*
    �������ܣ��������ڲ�ѯ�õ���Ӧ��һ�����ݼ�¼
    ���ν��ͣ�
        dateStr���������ڵ��ַ���
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
    ����ֵ��
        ��Ӧ�����ݼ�¼������һ������ʱ
        **ע�⣺��������ᱻǿ���˳�ϵͳ**
        ���κη���ֵ���������Զ������
 */
DataRecord getDataRecord(char *dateStr, Database *p);

/*
    �������ܣ��������������ĳ����Ϣ
    ���ν��ͣ�
        month_year_str������ĳ��ĳ�µ��ַ���
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
        ascending�������������Ƿ�Ϊ�������У���ascendingΪtrue�������򣻵�ascendingΪfalse������
    ����ֵ���޷���ֵ
 */
void sortByMaxTemperature(char *month_year_str, Database *p, bool ascending);

/*
    �������ܣ��������������ĳ����Ϣ
    ���ν��ͣ�
        month_year_str������ĳ��ĳ�µ��ַ���
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
        ascending�������������Ƿ�Ϊ�������У���ascendingΪtrue�������򣻵�ascendingΪfalse������
    ����ֵ���޷���ֵ
 */
void sortByMinTemperature(char *month_year_str, Database *p, bool ascending);

/*
    �������ܣ�����ÿ���²�����ĳ����Ϣ
    ���ν��ͣ�
        month_year_str������ĳ��ĳ�µ��ַ���
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
        ascending�������������Ƿ�Ϊ�������У���ascendingΪtrue�������򣻵�ascendingΪfalse������
    ����ֵ���޷���ֵ
 */
void sortByDiffTemperature(char *month_year_str, Database *p, bool ascending);

/*
    �������ܣ���ӡ�������
    ���ν��ͣ�
        month_year_str������ĳ��ĳ�µ��ַ���
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
    ����ֵ���޷���ֵ
 */
void printResultAfterSorted(char *month_year_str, Database *p);

/*
    �������ܣ�Ԥ������
    ���ν��ͣ�
        futureDateStr������δ��һ����ĳ��ʱ����ַ�������С�̶�Ϊ�գ�
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
    ����ֵ��
         0������һ������
        NEW_EXCEPTION���������Զ������
        �����errnoֵ�����������Զ������
 */
int predictWeather(char *futureDateStr, Database *p);

/*
    �������ܣ�ʹ�ö���ʽ�ع�Ԥ������
    ���ν��ͣ�
        futureDateStr������δ��һ����ĳ��ʱ����ַ�������С�̶�Ϊ�գ�
        p��ָ����Ҫ����ѯ�����ݿ��ָ�룬Ҫ�����ݿ��ѱ���ʼ��
    ����ֵ��
        0������һ������
        NEW_EXCEPTION���������Զ������
        �����errnoֵ�����������Զ������
 */
int predictTemperature(char *futureDateStr, Database *p);

/*
    �������ܣ��õ����ݿ����Ч��С��ȥ�������ļ��Ŀ��м������к����µ�������
    ���ν��ͣ�����Ҫ����
    ����ֵ�����ݿ����Ч��С��ȥ�������ļ��Ŀ��У�
    **�ر�˵�����������޸�Ϊ������ݿ�ʱ���б�Ҫ�޸Ĵ˺����Ĵ�����������ڲ�ʵ��**
 */
int getDatabaseSize(void);

/*
    �������ܣ���ӡһ�����ݼ�¼
    ���ν��ͣ���Ӧ�����ݼ�¼����
    ����ֵ���޷���ֵ
 */
void printRecord(DataRecord record);

#endif