#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <QString>

class Today
{
public:
    Today()
        : date("2022-10-20"), city("广州"), ganmao("感冒指数"), wendu("0"), shidu("0%"), pm25(0),
          quality("无数据"), type("多云"),  fx("南风"), fl("2级"),high(30), low(18)
    {}

    QString date;   // 日期
    QString city;   // 城市
    QString ganmao; // 感冒指数
    QString wendu;  // 温度
    QString shidu;  // 湿度
    int pm25;       // pm2.5
    QString quality; // 控制质量
    QString type;   // 天气
    QString fx;     // 风向
    QString fl;     // 风力
    int high;       // 高温
    int low;        // 低温
};

class SixDay
{
public:
    SixDay()
        : date("2022-10-20"), week("周五"), type("多云"), high(0), low(0), fx("南风"), fl("2级"), aqi(0)
    {
    }

    QString date;   // 日期
    QString week;   // 星期几
    QString type;   // 天气
    int high;       // 高温
    int low;        // 低温
    QString fx;     // 风向
    QString fl;     // 风力
    int aqi;        // 空气质量
};

#endif // WEATHER_DATA_H
