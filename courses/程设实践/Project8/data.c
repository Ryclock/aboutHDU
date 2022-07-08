#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "NB.h" // ���ر�Ҷ˹������Ԥ������
#include "PR.h" // ����ʽԤ������

/* ���� */

const char *Delim = ",";          // �����ļ���.csv������ָ���
const char *BlankLine = ",,,,\n"; // �����ļ���.csv���Ŀ�����ʾ��ʽ
const char *WindDirectionName[WINDDIRECTIONMAX] = {
    "�޳�������",
    "����",
    "����",
    "����",
    "�Ϸ�",
    "������",
    "������",
    "���Ϸ�",
    "���Ϸ�",
};

/* ȫ�ֱ��� */

int databaseSize = 0;                            //���ݿ��������������ʵ��С������������
int invalidRecord = 0;                           //������
Date now = {.year = 2022, .month = 5, .day = 8}; // ��¼���ݿ��е��������

/* �ֲ��������� */

/* �������ļ������зǱ����о��������ܵ���Ч���ݼ�¼����������ܵ����ݿ��С */
void getPossibleDatabaseSizeFromFile(FILE *fp);

/* ��ʼ�����ݿⲢ���ش����ݿ� */
Database initDatabase(void);

/* �жϴ����Ƿ�Ϊ���� */
bool parseValidity(char *record);

/* �������У���ʹ���Ϊһ�����ݼ�¼ */
void parseRecord(char *record, DataRecord *p);

/* �жϴ��ַ��Ƿ�Ϊ�����ַ� */
bool isDigit(char ch);

/* ���������Ƿ������ݿ��� */
void checkDateValidity(Date date, Database *p);

/* ���º�����Ϊ�������ڸ�������Ϣ�ĺ��������Ӻ������Լ�������������Ŀǰֻ�������ģ� */
Date parseDate(char *str);

Weather parseWeather(char *str);

enum WeatherType parseWeatherType(char *str);

enum WeatherExtent parseWeatherExtent(char *str);

enum WeatherIncidental parseWeatherIncidental(char *str);

bool parseWeatherSuddenness(char *str);

void getWeatherName(Weather *p);

char *getWeatherType(enum WeatherType e);

char *getWeatherExtent(enum WeatherExtent e);

double parseTemperature(char *str);

Wind parseWind(char *str);

enum WindDirection parseWindDirection(char *str);

void parseWindAveragePower(Wind *p, char *str);

/* -------------------------�ָ���------------------------- */
/* Ϊ����qsort������Ҫ�ıȽϺ�������int cmp(const void *a, const void *b)�ı��� */
int cmpMaxTemperature_Ascending(const void *a, const void *b);

int cmpMaxTemperature_Descending(const void *a, const void *b);

int cmpMinTemperature_Ascending(const void *a, const void *b);

int cmpMinTemperature_Descending(const void *a, const void *b);

int cmpDiffTemperature_Ascending(const void *a, const void *b);

int cmpDiffTemperature_Descending(const void *a, const void *b);

/* �ӿ�ʵ�� */

int readData(char *filePathName, Database *p, bool *inited)
{
    if (*inited)
    {
        printf("\n������룺%d", NEW_EXCEPTION); // �Զ���������ݿ��ʼ���������Զ��γ�ʼ�����ݿ⣩
        printf("\n������Ϣ��Database has been initializated");
        return NEW_EXCEPTION;
    }
    errno = 0; // ��ֹ���������޸Ĺ�errnoֵ
    FILE *fp;
    if (fopen_s(&fp, filePathName, "rt")) // ���ļ�ʧ�ܷ��ط���ֵ
    {
        printf("\n������룺%d", errno);
        perror("\n������Ϣ��");
        return errno;
    }
    getPossibleDatabaseSizeFromFile(fp);
    *p = initDatabase();
    char record[1024];
    fgets(record, sizeof(record), fp);
    printf("\n\n���ڳ�ʼ�����ݿ�...");
    for (int i = 0; i < databaseSize; i++)
    {
        memset(record, -1, sizeof(record));
        if (fgets(record, sizeof(record), fp) == NULL)
        {
            printf("\n������룺%d", NEW_EXCEPTION); // �Զ���������ݿ��ʼ���������¼�����������ļ��ķǱ���������
            printf("\n������Ϣ��File size and database size do not match");
            return NEW_EXCEPTION;
        }
        (*p)[i].validity = parseValidity(record);
        if (!(*p)[i].validity)
        {
            invalidRecord++;
            continue;
        }
        parseRecord(record, &(*p)[i]);
    }
    printf("\n���ݿ��ʼ����ɣ�");
    *inited = true;
    fclose(fp);
    return 0;
}

DataRecord getDataRecord(char *dateStr, Database *p)
{
    Date date = parseDate(dateStr);
    checkDateValidity(date, p);
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if ((*p)[i].date.year == date.year && (*p)[i].date.month == date.month && (*p)[i].date.day == date.day)
        {
            printf("\n\n��ѯ�ɹ���");
            return (*p)[i];
        }
    }
}

void sortByMaxTemperature(char *month_year_str, Database *p, bool ascending)
{
    Date date = parseDate(month_year_str);
    checkDateValidity(date, p);
    int count = 0, endPos;
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if (date.year == (*p)[i].date.year && date.month == (*p)[i].date.month)
        {
            count++;
            endPos = i;
        }
    }
    if (ascending)
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpMaxTemperature_Ascending);
    }
    else
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpMaxTemperature_Descending);
    }
}

void sortByMinTemperature(char *month_year_str, Database *p, bool ascending)
{
    Date date = parseDate(month_year_str);
    checkDateValidity(date, p);
    int count = 0, endPos;
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if (date.year == (*p)[i].date.year && date.month == (*p)[i].date.month)
        {
            count++;
            endPos = i;
        }
    }
    if (ascending)
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpMinTemperature_Ascending);
    }
    else
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpMinTemperature_Descending);
    }
}

void sortByDiffTemperature(char *month_year_str, Database *p, bool ascending)
{
    Date date = parseDate(month_year_str);
    checkDateValidity(date, p);
    int count = 0, endPos;
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if (date.year == (*p)[i].date.year && date.month == (*p)[i].date.month)
        {
            count++;
            endPos = i;
        }
    }
    if (ascending)
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpDiffTemperature_Ascending);
    }
    else
    {
        qsort(&(*p)[endPos - count + 1], count, sizeof(DataRecord), cmpDiffTemperature_Descending);
    }
}

void printResultAfterSorted(char *month_year_str, Database *p)
{
    Date date = parseDate(month_year_str);
    checkDateValidity(date, p);
    int startPos = -1, endPos;
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if (date.year == (*p)[i].date.year && date.month == (*p)[i].date.month)
        {
            endPos = i;
            if (startPos == -1)
            {
                startPos = i;
            }
        }
    }
    printf("\n\n�����Ľ���ǣ�");
    for (int i = startPos; i <= endPos; i++)
    {
        printRecord((*p)[i]);
    }
}

int predictWeather(char *futureDateStr, Database *p)
{
    Date futureDate = parseDate(futureDateStr);
    if ((futureDate.year < now.year) ||
        (futureDate.year == now.year && futureDate.month < now.month) ||
        (futureDate.year == now.year && futureDate.month == now.month && futureDate.day < now.day))
    {
        printf("\n������룺%d", NEW_EXCEPTION); // �Զ�����󣨷�δ�����ڣ�
        printf("\n������Ϣ��This is not a future date");
        return NEW_EXCEPTION;
    }
    FitWeatherModel_NB(futureDate, p, databaseSize, getDatabaseSize());
}

int predictTemperature(char *futureDateStr, Database *p)
{
    Date futureDate = parseDate(futureDateStr);
    if ((futureDate.year < now.year) ||
        (futureDate.year == now.year && futureDate.month < now.month) ||
        (futureDate.year == now.year && futureDate.month == now.month && futureDate.day < now.day))
    {
        printf("\n������룺%d", NEW_EXCEPTION); // �Զ�����󣨷�δ�����ڣ�
        printf("\n������Ϣ��This is not a future date");
        return NEW_EXCEPTION;
    }
    FitTemperatureModel_PR(futureDate, p, databaseSize, getDatabaseSize());
    return 0;
}

int getDatabaseSize(void)
{
    return (databaseSize - invalidRecord);
}

void printRecord(DataRecord record)
{
    if (!record.validity) // �����γɵ����ݼ�¼����ӡ
    {
        return;
    }
    printf("\n\n���ڣ�%d-%d-%d\n������%s\n����£�%.2lf\n����£�%.2lf\n����%s\n�����ȼ���%d-%d",
           record.date.year, record.date.month, record.date.day,
           record.weather.name,
           record.temperature.max, record.temperature.min,
           WindDirectionName[record.wind.direction],
           record.wind.average_power_min, record.wind.average_power_max);
}

/* �ֲ�����ʵ�� */

void getPossibleDatabaseSizeFromFile(FILE *fp)
{
    char line[1024];
    fgets(line, sizeof(line), fp); // �������޳�
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        databaseSize++;
    }
    rewind(fp); // ����λ��ָ�뵽�ļ�ͷ��
}

Database initDatabase(void)
{
    return (Database)malloc(sizeof(DataRecord) * databaseSize);
}

bool parseValidity(char *record)
{
    return strcmp(record, BlankLine);
}

void parseRecord(char *record, DataRecord *p)
{
    char *item = strtok(record, Delim); // ��Delim�����ַ���
    p->date = parseDate(item);
    item = strtok(NULL, Delim);
    p->weather = parseWeather(item);
    item = strtok(NULL, Delim);
    p->temperature.max = parseTemperature(item);
    item = strtok(NULL, Delim);
    p->temperature.min = parseTemperature(item);
    item = strtok(NULL, Delim);
    p->wind = parseWind(item);
}

bool isDigit(char ch)
{
    return (ch >= '0') && (ch <= '9');
}

void checkDateValidity(Date date, Database *p)
{
    for (int i = 0; i < databaseSize; i++)
    {
        if (!(*p)[i].validity)
        {
            continue;
        }
        if ((*p)[i].date.year == date.year && (*p)[i].date.month == date.month && (*p)[i].date.day == date.day)
        {
            return;
        }
    }
    printf("\n������룺%d", NEW_EXCEPTION); // �Զ�������ṩ�����ݿ���û�д����ڣ�
    printf("\n������Ϣ��Invalid date");
    system("pause");
    exit(EXIT_FAILURE);
}

Date parseDate(char *str)
{
    Date result;
    /* ĳ�� */
    while (!isDigit(*str)) // ȥ�����ǰ����Чǰ׺
    {
        str++;
    }
    int temp = 0, count = 0;
    while (isDigit(*str) && count < 4)
    {
        temp = temp * 10 + (*str - '0');
        str++;
        count++;
    }
    result.year = temp;
    /* ĳ�� */
    while (!isDigit(*str)) // ȥ���·�ǰ����Чǰ׺
    {
        str++;
    }
    temp = count = 0;
    while (isDigit(*str) && count < 2)
    {
        temp = temp * 10 + (*str - '0');
        str++;
        count++;
    }
    result.month = temp;
    /* ĳ�� */
    while (!isDigit(*str)) // ȥ���շ�ǰ����Чǰ׺
    {
        str++;
    }
    temp = count = 0;
    while (isDigit(*str) && count < 2)
    {
        temp = temp * 10 + (*str - '0');
        str++;
        count++;
    }
    result.day = temp;
    return result;
}

Weather parseWeather(char *str)
{
    Weather result = {
        .type = parseWeatherType(str),
        .extent = parseWeatherExtent(str),
        .incidental = parseWeatherIncidental(str),
        .suddenness = parseWeatherSuddenness(str),
    };
    getWeatherName(&result);
    return result;
}

enum WeatherType parseWeatherType(char *str)
{

    if (strstr(str, "��"))
    {
        return SUNNY;
    }
    else if (strstr(str, "����"))
    {
        return CLOUDY;
    }
    else if (strstr(str, "��"))
    {
        return OVERCAST;
    }
    else if (strstr(str, "��"))
    {
        return RAIN;
    }
    else if (strstr(str, "ѩ"))
    {
        return SNOW;
    }
}

enum WeatherExtent parseWeatherExtent(char *str)
{
    if (strstr(str, "��") || strstr(str, "ת") || strstr(str, "-"))
    {
        if (strstr(str, "С") && strstr(str, "��"))
        {
            return LIGHT_MODERATE;
        }
        else if (strstr(str, "��") && strstr(str, "��"))
        {
            return MODERATE_HEAVY;
        }
        else if (strstr(str, "��") && strstr(str, "��"))
        {
            return HEAVY_STORM;
        }
    }
    else if (strstr(str, "ëë") || strstr(str, "ϸ"))
    {
        return MAOMAO;
    }
    else if (strstr(str, "С"))
    {
        return LIGHT;
    }
    else if (strstr(str, "��"))
    {
        return MODERATE;
    }
    else if (strstr(str, "��"))
    {
        return HEAVY;
    }
    else if (strstr(str, "��"))
    {
        return STORM;
    }
    return NO_EXTENT;
}

enum WeatherIncidental parseWeatherIncidental(char *str)
{
    if (strstr(str, "��"))
    {
        return WITH_THUNDER;
    }
    else if (strstr(str, "��ѩ"))
    {
        return WITH_SNOW;
    }
    return NO_INCIDENTAL;
}

bool parseWeatherSuddenness(char *str)
{
    if (strstr(str, "��"))
    {
        return true;
    }
    return false;
}

void getWeatherName(Weather *p)
{
    memset(p->name, 0, sizeof(p->name));
    if (p->suddenness)
    {
        if (p->incidental == WITH_THUNDER)
        {
            strcat(p->name, "����");
        }
        else
        {
            strcat(p->name, "��");
        }
    }
    strcat(p->name, getWeatherExtent(p->extent));
    strcat(p->name, getWeatherType(p->type));
    if (p->incidental == WITH_SNOW)
    {
        strcat(p->name, "��ѩ");
    }
}

char *getWeatherType(enum WeatherType e)
{
    switch (e)
    {
    case SUNNY:
        return "��";
    case CLOUDY:
        return "����";
    case OVERCAST:
        return "��";
    case RAIN:
        return "��";
    case SNOW:
        return "ѩ";
    }
}

char *getWeatherExtent(enum WeatherExtent e)
{
    switch (e)
    {
    case MAOMAO:
        return "ëë";
    case LIGHT:
        return "С";
    case MODERATE:
        return "��";
    case HEAVY:
        return "��";
    case STORM:
        return "��";
    case LIGHT_MODERATE:
        return "С����";
    case MODERATE_HEAVY:
        return "�е���";
    case HEAVY_STORM:
        return "�󵽱�";
    case NO_EXTENT:
        return "";
    }
}

double parseTemperature(char *str)
{
    int negative = 1;
    if (strstr(str, "-")) // ����������ȿ���
    {
        negative = -1;
    }
    while (!isDigit(*str)) // ȥ���¶�ǰ����Чǰ׺
    {
        str++;
    }
    double result = 0;
    while (isDigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * negative;
}

Wind parseWind(char *str)
{
    Wind result;
    result.direction = parseWindDirection(strtok(str, " "));
    parseWindAveragePower(&result, strtok(NULL, " "));
    return result;
}

enum WindDirection parseWindDirection(char *str)
{
    if (strstr(str, "�޳���"))
    {
        return NO_SUSTAINED;
    }
    else if (strstr(str, "��"))
    {
        if (strstr(str, "��"))
        {
            return NORTHEAST;
        }
        if (strstr(str, "��"))
        {
            return SOUTHEAST;
        }
        return EAST;
    }
    else if (strstr(str, "��"))
    {
        if (strstr(str, "��"))
        {
            return NORTHWEST;
        }
        if (strstr(str, "��"))
        {
            return SOUTHWEST;
        }
        return WEST;
    }
    else if (strstr(str, "��"))
    {
        return NORTH;
    }
    else if (strstr(str, "��"))
    {
        return SOUTH;
    }
}

void parseWindAveragePower(Wind *p, char *str)
{
    int attach = 0;
    p->average_power_max = p->average_power_min = 0;
    if (strstr(str, "��"))
    {
        while (!isDigit(*str))
        {
            str++;
        }
    }
    else if (strstr(str, "<"))
    {
        attach = -1;
        while (!isDigit(*str))
        {
            str++;
        }
    }
    else
    {
        while (!isDigit(*str))
        {
            str++;
        }
        while (isDigit(*str))
        {
            p->average_power_min = p->average_power_min * 10 + (*str - '0');
            str++;
        }
    }
    while (!isDigit(*str))
    {
        str++;
    }
    while (isDigit(*str))
    {
        p->average_power_max = p->average_power_max * 10 + (*str - '0');
        str++;
    }
    p->average_power_max += attach;
}

int cmpMaxTemperature_Ascending(const void *a, const void *b)
{
    double max1 = (*(DataRecord *)a).temperature.max;
    double max2 = (*(DataRecord *)b).temperature.max;
    if (max1 > max2)
    {
        return 1;
    }
    else if (max1 < max2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int cmpMaxTemperature_Descending(const void *a, const void *b)
{
    double max1 = (*(DataRecord *)a).temperature.max;
    double max2 = (*(DataRecord *)b).temperature.max;
    if (max1 < max2)
    {
        return 1;
    }
    else if (max1 > max2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int cmpMinTemperature_Ascending(const void *a, const void *b)
{
    double min1 = (*(DataRecord *)a).temperature.min;
    double min2 = (*(DataRecord *)b).temperature.min;
    if (min1 > min2)
    {
        return 1;
    }
    else if (min1 < min2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int cmpMinTemperature_Descending(const void *a, const void *b)
{
    double min1 = (*(DataRecord *)a).temperature.min;
    double min2 = (*(DataRecord *)b).temperature.min;
    if (min1 < min2)
    {
        return 1;
    }
    else if (min1 > min2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int cmpDiffTemperature_Ascending(const void *a, const void *b)
{
    double diff1 = (*(DataRecord *)a).temperature.max - (*(DataRecord *)a).temperature.min;
    double diff2 = (*(DataRecord *)b).temperature.max - (*(DataRecord *)b).temperature.min;
    if (diff1 > diff2)
    {
        return 1;
    }
    else if (diff1 < diff2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int cmpDiffTemperature_Descending(const void *a, const void *b)
{
    double diff1 = (*(DataRecord *)a).temperature.max - (*(DataRecord *)a).temperature.min;
    double diff2 = (*(DataRecord *)b).temperature.max - (*(DataRecord *)b).temperature.min;
    if (diff1 < diff2)
    {
        return 1;
    }
    else if (diff1 > diff2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
