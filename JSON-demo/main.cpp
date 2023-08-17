#include <QCoreApplication>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QFile>
#include<QDebug>
void writeJson()
{
    QJsonObject rootObj;
    //1. 插入name字段("name","China")
    rootObj.insert("name","China");
    //2. 插入info字段
    QJsonObject infoObj;
    infoObj.insert("capital","beijing");
    infoObj.insert("anian",true);
    infoObj.insert("founded",1949);
    rootObj.insert("info",infoObj);
    //3. 插入provinces字段
    QJsonArray provinceArray;

    QJsonObject provinceSdObj;
    provinceSdObj.insert("name","shandong");
    provinceSdObj.insert("capital","jinan");

    QJsonObject provinceZjObj;
    provinceZjObj.insert("name","zhejiang");
    provinceZjObj.insert("capital","hengzhou");

    provinceArray.append(provinceSdObj);
    provinceArray.append(provinceZjObj);

    rootObj.insert("provinces",provinceArray);

    //4. 将rootObj转换成json字符串
    QJsonDocument doc(rootObj);
    QByteArray jsons = doc.toJson();

    //5.1 打印输出
    qDebug() << QString(jsons).toUtf8().data();

    //5.2 将jsons字符串写入到文件
    QFile file("C:\\Users\\Administrator\\Desktop\\C++\\QT\\china.json");
    file.open(QFile::WriteOnly);
    file.write(jsons);
    file.close();
}
void fromJson()
{
    // 1. 读取文件
    QFile file("C:\\Users\\Administrator\\Desktop\\C++\\QT\\china.json");
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    if(!doc.isObject())
    {
        qDebug() << "Not an object";
        return;
    }
    QJsonObject obj = doc.object();
    QStringList keys =  obj.keys();
    for(int i =0;i<keys.size();i++)
    {
        //获取 key-value;
        QString key = keys[i];
        QJsonValue value = obj.value(key);

        //开始解析
        if(value.isBool())
        {
            qDebug()  <<":isBool" << value.toBool();
        }
        else if(value.isString())
        {
            qDebug()  <<":isString" << value.toString();
        }
        else if(value.isDouble())
        {
              qDebug()  <<":isDouble" << value.toInt();
        }
        else if(value.isObject())
        {
            QJsonObject infoObj = value.toObject();
            QString capital =  infoObj["capital"].toString();
            int  founded =  infoObj["founded"].toInt();
            bool anian =  infoObj["anian"].toBool();

            qDebug() << ":capital :" <<capital;
            qDebug() << ":founded :" << founded;
            qDebug() << ":anian :" << anian;
        }
        else if(value.isArray())
        {
              QJsonArray provinceArray = value.toArray();

              for(int i =0;i< provinceArray.size();i++)
              {
                  QJsonObject provinceObj = provinceArray[i].toObject();

                  QString name = provinceObj["name"].toString();
                  QString capital = provinceObj["capital"].toString();

                  qDebug() << ":name :" <<name;
                  qDebug() << ":capital :" << capital;
              }
        }
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //writeJson();
    fromJson();
    return a.exec();
}
