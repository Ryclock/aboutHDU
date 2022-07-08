#ifndef PROJECT_DATA_H
#define PROJECT_DATA_H

#include <stdbool.h>

#define NEW_EXCEPTION -1
#define WEATHER_NAME_MAX 20 // 天气中文名为20个char字符，即10个中文字

enum WeatherType
{
    SUNNY,
    CLOUDY,
    OVERCAST,
    RAIN,
    SNOW,
    WEATHERTYPEMAX, //此枚举类型的有效值个数
};

enum WeatherExtent
{
    NO_EXTENT, // 无降水程度，即非“雨”“雪”类天气
    MAOMAO,
    LIGHT,
    MODERATE,
    HEAVY,
    STORM,
    LIGHT_MODERATE,
    MODERATE_HEAVY,
    HEAVY_STORM,
    WEATHEREXTENTMAX, //此枚举类型的有效值个数
};

enum WeatherIncidental
{
    NO_INCIDENTAL, // 无附带物
    WITH_THUNDER,
    WITH_SNOW,
    WEATHERINCIDENTALMAX, //此枚举类型的有效值个数
};

enum WindDirection
{
    NO_SUSTAINED, //无持续风向
    EAST,
    WEST,
    NORTH,
    SOUTH,
    NORTHEAST,
    NORTHWEST,
    SOUTHEAST,
    SOUTHWEST,
    WINDDIRECTIONMAX, //此枚举类型的有效值个数
};

/* 数据类型 */

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char name[WEATHER_NAME_MAX];       // 天气中文名
    enum WeatherType type;             // 天气类型（主要）
    enum WeatherExtent extent;         // 降水程度（主要用于形容“雨”“雪”类天气）
    enum WeatherIncidental incidental; // 天气类型（附带）：“雷”、“夹雪”
    bool suddenness;                   // 降水是否具有突然性：即是否为“阵雨”“阵雪”
} Weather;

typedef struct
{
    double max; // 最高温
    double min; // 最低温
} Temperature;

typedef struct
{
    enum WindDirection direction; // 风向
    int average_power_max;        // 最高风力等级
    int average_power_min;        // 最低风力等级
} Wind;

typedef struct
{
    bool validity; // 标记是否为有效行（false代表为空行）
    Date date;
    Weather weather;
    Temperature temperature;
    Wind wind;
} DataRecord, *Database;

/* 接口定义 */

/*
    函数功能：读入数据并初始化数据库
    传参解释：
        filePathName：数据文件绝对路径名
        p：指向需要被初始化的数据库的指针
        inited: 标识p指向的数据库是否已经被初始化
    返回值：
        0，代表一切正常
        NEW_EXCEPTION，代表发生自定义错误
        非零的errno值，代表发生非自定义错误
 */
int readData(char *filePathName, Database *p, bool *inited);

/*
    函数功能：按照日期查询得到对应的一条数据记录
    传参解释：
        dateStr：代表日期的字符串
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
    返回值：
        对应的数据记录，仅在一切正常时
        **注意：以下情况会被强制退出系统**
        无任何返回值，即发生自定义错误
 */
DataRecord getDataRecord(char *dateStr, Database *p);

/*
    函数功能：根据最高温排序某月信息
    传参解释：
        month_year_str，代表某年某月的字符串
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
        ascending：代表排序结果是否为升序排列（当ascending为true代表升序；当ascending为false代表降序）
    返回值：无返回值
 */
void sortByMaxTemperature(char *month_year_str, Database *p, bool ascending);

/*
    函数功能：根据最低温排序某月信息
    传参解释：
        month_year_str，代表某年某月的字符串
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
        ascending：代表排序结果是否为升序排列（当ascending为true代表升序；当ascending为false代表降序）
    返回值：无返回值
 */
void sortByMinTemperature(char *month_year_str, Database *p, bool ascending);

/*
    函数功能：根据每日温差排序某月信息
    传参解释：
        month_year_str，代表某年某月的字符串
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
        ascending：代表排序结果是否为升序排列（当ascending为true代表升序；当ascending为false代表降序）
    返回值：无返回值
 */
void sortByDiffTemperature(char *month_year_str, Database *p, bool ascending);

/*
    函数功能：打印排序后结果
    传参解释：
        month_year_str，代表某年某月的字符串
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
    返回值：无返回值
 */
void printResultAfterSorted(char *month_year_str, Database *p);

/*
    函数功能：预测天气
    传参解释：
        futureDateStr，代表未来一年内某个时间的字符串（最小刻度为日）
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
    返回值：
         0，代表一切正常
        NEW_EXCEPTION，代表发生自定义错误
        非零的errno值，代表发生非自定义错误
 */
int predictWeather(char *futureDateStr, Database *p);

/*
    函数功能：使用多项式回归预测气温
    传参解释：
        futureDateStr，代表未来一年内某个时间的字符串（最小刻度为日）
        p：指向需要被查询的数据库的指针，要求数据库已被初始化
    返回值：
        0，代表一切正常
        NEW_EXCEPTION，代表发生自定义错误
        非零的errno值，代表发生非自定义错误
 */
int predictTemperature(char *futureDateStr, Database *p);

/*
    函数功能：得到数据库的有效大小（去除数据文件的空行及标题行后余下的行数）
    传参解释：不需要传参
    返回值：数据库的有效大小（去除数据文件的空行）
    **特别说明：若后续修改为多个数据库时，有必要修改此函数的传入参数及其内部实现**
 */
int getDatabaseSize(void);

/*
    函数功能：打印一条数据记录
    传参解释：对应的数据记录变量
    返回值：无返回值
 */
void printRecord(DataRecord record);

#endif