#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPoint>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMap>
#include <QPainter>
#include <QPoint>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "weather_data.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent* event); // 右键菜单事件
    void mousePressEvent(QMouseEvent* event); // 鼠标按下事件
    void mouseMoveEvent(QMouseEvent* event); // 鼠标移动事件
    void keyPressEvent(QKeyEvent *k); // 键盘按下事件
    void getWeatherInfo(QString cityCode); // 获取天气数据
    void parseJson(QByteArray &byteArray); // 解析请求数据
    void InitWidGet(); // 控件初始化
    void UpdateUI(); // 更新UI
    bool eventFilter(QObject* watched, QEvent* event); // 重写父类的eventFilter的方法
    void piant(QString HighOrLow); // 绘制高低温曲线
    void piantHighCurve(); // 绘制高温曲线
    void piantLowCurve(); // 绘制低温曲线

private slots:
    void onReplid(QNetworkReply* reply); // 请求响应槽函数
    void on_btnSearch_clicked(); // 搜索按钮点击槽函数

private:
    Ui::MainWindow* ui;
    QMenu* mExitMenu; // 右键退出的菜单
    QAction* mExitAct; // 退出的行为
    QPoint mOffset; // 窗口移动时，鼠标与窗口左上角的偏移

    QNetworkAccessManager * mNetAccessManager; // 网络请求管理器

    Today today; // 当天天气数据
    SixDay sixday[6]; // 六天天气数据
    QList<QLabel*> WeekList; // 星期列表
    QList<QLabel*> DateList; // 日期列表
    QList<QLabel*> TypeList; // 天气类型列表
    QList<QLabel*> TypeIconList; // 天气图标列表
    QList<QLabel*> AqlList; // 天气污染指数列表
    QList<QLabel*> FxList; // 风向列表
    QList<QLabel*> FlList; // 风力列表
    QMap<QString,QString> todayTypeMap; // 当天天气类型映射表
};
#endif  // MAINWINDOW_H
