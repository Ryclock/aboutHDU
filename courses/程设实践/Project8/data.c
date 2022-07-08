#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "NB.h" // 朴素贝叶斯分类器预测天气
#include "PR.h" // 多项式预测气温

/* 常量 */

const char *Delim = ",";          // 数据文件（.csv）的项分隔符
const char *BlankLine = ",,,,\n"; // 数据文件（.csv）的空行显示形式
const char *WindDirectionName[WINDDIRECTIONMAX] = {
    "无持续风向",
    "东风",
    "西风",
    "北风",
    "南风",
    "东北风",
    "西北风",
    "东南风",
    "西南风",
};

/* 全局变量 */

int databaseSize = 0;                            //数据库最大容量，非真实大小，即包含空行
int invalidRecord = 0;                           //空行量
Date now = {.year = 2022, .month = 5, .day = 8}; // 记录数据库中的最近日期

/* 局部函数定义 */

/* 将数据文件中所有非标题行均视作可能的有效数据记录，并计算可能的数据库大小 */
void getPossibleDatabaseSizeFromFile(FILE *fp);

/* 初始化数据库并返回此数据库 */
Database initDatabase(void);

/* 判断此行是否为空行 */
bool parseValidity(char *record);

/* 解析此行，并使其成为一条数据记录 */
void parseRecord(char *record, DataRecord *p);

/* 判断此字符是否为数字字符 */
bool isDigit(char ch);

/* 检查此日期是否在数据库内 */
void checkDateValidity(Date date, Database *p);

/* 以下函数均为解析日期各部分信息的函数及其子函数，以及反解析函数（目前只有天气的） */
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

/* -------------------------分隔线------------------------- */
/* 为调用qsort函数需要的比较函数，即int cmp(const void *a, const void *b)的变形 */
int cmpMaxTemperature_Ascending(const void *a, const void *b);

int cmpMaxTemperature_Descending(const void *a, const void *b);

int cmpMinTemperature_Ascending(const void *a, const void *b);

int cmpMinTemperature_Descending(const void *a, const void *b);

int cmpDiffTemperature_Ascending(const void *a, const void *b);

int cmpDiffTemperature_Descending(const void *a, const void *b);

/* 接口实现 */

int readData(char *filePathName, Database *p, bool *inited)
{
    if (*inited)
    {
        printf("\n错误代码：%d", NEW_EXCEPTION); // 自定义错误（数据库初始化出错，尝试二次初始化数据库）
        printf("\n报错信息：Database has been initializated");
        return NEW_EXCEPTION;
    }
    errno = 0; // 防止其他程序修改过errno值
    FILE *fp;
    if (fopen_s(&fp, filePathName, "rt")) // 打开文件失败返回非零值
    {
        printf("\n错误代码：%d", errno);
        perror("\n报错信息：");
        return errno;
    }
    getPossibleDatabaseSizeFromFile(fp);
    *p = initDatabase();
    char record[1024];
    fgets(record, sizeof(record), fp);
    printf("\n\n正在初始化数据库...");
    for (int i = 0; i < databaseSize; i++)
    {
        memset(record, -1, sizeof(record));
        if (fgets(record, sizeof(record), fp) == NULL)
        {
            printf("\n错误代码：%d", NEW_EXCEPTION); // 自定义错误（数据库初始化出错，其记录量大于数据文件的非标题行数）
            printf("\n报错信息：File size and database size do not match");
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
    printf("\n数据库初始化完成！");
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
            printf("\n\n查询成功！");
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
    printf("\n\n排序后的结果是：");
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
        printf("\n错误代码：%d", NEW_EXCEPTION); // 自定义错误（非未来日期）
        printf("\n报错信息：This is not a future date");
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
        printf("\n错误代码：%d", NEW_EXCEPTION); // 自定义错误（非未来日期）
        printf("\n报错信息：This is not a future date");
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
    if (!record.validity) // 空行形成的数据记录不打印
    {
        return;
    }
    printf("\n\n日期：%d-%d-%d\n天气：%s\n最高温：%.2lf\n最低温：%.2lf\n风向：%s\n风力等级：%d-%d",
           record.date.year, record.date.month, record.date.day,
           record.weather.name,
           record.temperature.max, record.temperature.min,
           WindDirectionName[record.wind.direction],
           record.wind.average_power_min, record.wind.average_power_max);
}

/* 局部函数实现 */

void getPossibleDatabaseSizeFromFile(FILE *fp)
{
    char line[1024];
    fgets(line, sizeof(line), fp); // 标题行剔除
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        databaseSize++;
    }
    rewind(fp); // 重置位置指针到文件头部
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
    char *item = strtok(record, Delim); // 按Delim划分字符串
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
    printf("\n错误代码：%d", NEW_EXCEPTION); // 自定义错误（提供的数据库中没有此日期）
    printf("\n报错信息：Invalid date");
    system("pause");
    exit(EXIT_FAILURE);
}

Date parseDate(char *str)
{
    Date result;
    /* 某年 */
    while (!isDigit(*str)) // 去除年份前的无效前缀
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
    /* 某月 */
    while (!isDigit(*str)) // 去除月份前的无效前缀
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
    /* 某日 */
    while (!isDigit(*str)) // 去除日份前的无效前缀
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

    if (strstr(str, "晴"))
    {
        return SUNNY;
    }
    else if (strstr(str, "多云"))
    {
        return CLOUDY;
    }
    else if (strstr(str, "阴"))
    {
        return OVERCAST;
    }
    else if (strstr(str, "雨"))
    {
        return RAIN;
    }
    else if (strstr(str, "雪"))
    {
        return SNOW;
    }
}

enum WeatherExtent parseWeatherExtent(char *str)
{
    if (strstr(str, "到") || strstr(str, "转") || strstr(str, "-"))
    {
        if (strstr(str, "小") && strstr(str, "中"))
        {
            return LIGHT_MODERATE;
        }
        else if (strstr(str, "中") && strstr(str, "大"))
        {
            return MODERATE_HEAVY;
        }
        else if (strstr(str, "大") && strstr(str, "暴"))
        {
            return HEAVY_STORM;
        }
    }
    else if (strstr(str, "毛毛") || strstr(str, "细"))
    {
        return MAOMAO;
    }
    else if (strstr(str, "小"))
    {
        return LIGHT;
    }
    else if (strstr(str, "中"))
    {
        return MODERATE;
    }
    else if (strstr(str, "大"))
    {
        return HEAVY;
    }
    else if (strstr(str, "暴"))
    {
        return STORM;
    }
    return NO_EXTENT;
}

enum WeatherIncidental parseWeatherIncidental(char *str)
{
    if (strstr(str, "雷"))
    {
        return WITH_THUNDER;
    }
    else if (strstr(str, "夹雪"))
    {
        return WITH_SNOW;
    }
    return NO_INCIDENTAL;
}

bool parseWeatherSuddenness(char *str)
{
    if (strstr(str, "阵"))
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
            strcat(p->name, "雷阵");
        }
        else
        {
            strcat(p->name, "阵");
        }
    }
    strcat(p->name, getWeatherExtent(p->extent));
    strcat(p->name, getWeatherType(p->type));
    if (p->incidental == WITH_SNOW)
    {
        strcat(p->name, "夹雪");
    }
}

char *getWeatherType(enum WeatherType e)
{
    switch (e)
    {
    case SUNNY:
        return "晴";
    case CLOUDY:
        return "多云";
    case OVERCAST:
        return "阴";
    case RAIN:
        return "雨";
    case SNOW:
        return "雪";
    }
}

char *getWeatherExtent(enum WeatherExtent e)
{
    switch (e)
    {
    case MAOMAO:
        return "毛毛";
    case LIGHT:
        return "小";
    case MODERATE:
        return "中";
    case HEAVY:
        return "大";
    case STORM:
        return "暴";
    case LIGHT_MODERATE:
        return "小到中";
    case MODERATE_HEAVY:
        return "中到大";
    case HEAVY_STORM:
        return "大到暴";
    case NO_EXTENT:
        return "";
    }
}

double parseTemperature(char *str)
{
    int negative = 1;
    if (strstr(str, "-")) // 负数情况率先考虑
    {
        negative = -1;
    }
    while (!isDigit(*str)) // 去除温度前的无效前缀
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
    if (strstr(str, "无持续"))
    {
        return NO_SUSTAINED;
    }
    else if (strstr(str, "东"))
    {
        if (strstr(str, "北"))
        {
            return NORTHEAST;
        }
        if (strstr(str, "南"))
        {
            return SOUTHEAST;
        }
        return EAST;
    }
    else if (strstr(str, "西"))
    {
        if (strstr(str, "北"))
        {
            return NORTHWEST;
        }
        if (strstr(str, "南"))
        {
            return SOUTHWEST;
        }
        return WEST;
    }
    else if (strstr(str, "北"))
    {
        return NORTH;
    }
    else if (strstr(str, "南"))
    {
        return SOUTH;
    }
}

void parseWindAveragePower(Wind *p, char *str)
{
    int attach = 0;
    p->average_power_max = p->average_power_min = 0;
    if (strstr(str, "≤"))
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
