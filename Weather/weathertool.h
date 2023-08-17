#ifndef WEATHERTOOL_H
#define WEATHERTOOL_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonArray>

class WeatherTool
{
public:
    static QString getCityCode(QString cityName)
    {
        if (CityMap.isEmpty())
            InitCityMap();

        QMap<QString, QString>::Iterator it = CityMap.find(cityName);
        if (it == CityMap.end())
        {
            it = CityMap.find(cityName + "市");
        }
        if (it != CityMap.end())
            return it.value();
        else
            return "";
    }

private:
    static QMap<QString, QString> CityMap; // 城市名称和城市代码的映射表

    /**
     * @brief InitCityMap 初始化城市映射表
     */
    static void InitCityMap()
    {
        // 1. 读取文件
        QString filePath = "E:\\qt\\Weather\\citycode.json";
        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = file.readAll();

        // 2. 解析并写入到map
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(json, &err);
        if (err.error != QJsonParseError::NoError)
            return;
        if (!doc.isArray())
            return;

        QJsonArray cities = doc.array();
        for (int i = 0; i < cities.size(); ++i)
        {
            QString city = cities[i].toObject().value("city_name").toString();
            QString code = cities[i].toObject().value("city_code").toString();
            if (!code.isEmpty())
                CityMap.insert(city, code);
        }
    }
};

QMap<QString, QString> WeatherTool::CityMap = {};

#endif // WEATHERTOOL_H
