#include "mainwindow.h"

#include <QContextMenuEvent>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QMessageBox>
#include <QNetworkReply>
#include <QPainter>
#include <QTimer>

#include "weathertool.h"
#include "ui_mainwindow.h"
#define INCREMENT 3 //温度每升高/降低 一度  y轴坐标的增量
#define POINT_REDIUS 3 //曲线描点的大小
#define TEXT_OFFSET_X 12 //X轴偏移
#define TEXT_OFFSET_Y 12 //X轴偏移
MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //设置窗口属性
    setWindowFlag(Qt::FramelessWindowHint);  // 无边框
    setFixedSize(width(), height());         // 固定窗口大小

    // 右键菜单：退出程序
    mExitMenu = new QMenu(this);
    mExitAct = new QAction();
    mExitAct->setText(tr("退出"));
    mExitAct->setIcon(QIcon(":/res/close.png"));
    mExitMenu->addAction(mExitAct);
    //信号槽
    connect(mExitAct, &QAction::triggered, this, [=]() { qApp->exit(0); });

    //将控件添加到控件数组
    InitWidGet();

    mNetAccessManager = new QNetworkAccessManager(this);
    connect(mNetAccessManager,&QNetworkAccessManager::finished,this,&MainWindow::onReplid);
    //程序构造就启动就调用请求数据
    //getWeatherInfo("101010100");
    getWeatherInfo("武汉");

    //给标签添加时间过滤器
    //参数指定为this，也就是当前窗口对象 MainWindow
    ui->lblHighCurve->installEventFilter(this);
    ui->lblLowCurve->installEventFilter(this);
}


MainWindow::~MainWindow() { delete ui; }
//重写父类的虚函数
//父类中默认的实现是忽略右键菜单事件
// 重写之后，处理右键菜单事件
void MainWindow::contextMenuEvent(QContextMenuEvent* event) {
    mExitMenu->exec(QCursor::pos());
    event->accept();
}
//获取鼠标按下相对于左上角窗口的距离
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //globalPos获取鼠标或触摸事件发生的位置
    //this->pos this->pos()返回一个QPoint对象，
    //表示该窗口或控件的坐标位置。
    //这个坐标位置是相对于父窗口或父控件的左上角的偏移量。
    mOffset =  event->globalPosition().toPoint() -  this->pos();
}

//当鼠标或触摸事件发生时，窗口或控件将会被移动到事件发生的全局坐标位置。
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPosition().toPoint() - mOffset);
}

//进行网络请求
void MainWindow::onReplid(QNetworkReply *reply)
{
    //判断是否请求成功
   int status_code =  reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(reply->error()!= QNetworkReply::NoError || status_code != 200)
    {
       qDebug() << reply->errorString().toLatin1().data();
        QMessageBox::warning(NULL,"天气","请求数据失败",QMessageBox::Ok);
    }
    else
    {
       QByteArray byteArray = reply->readAll();
       //qDebug() << "read all :\n" << byteArray.data();
       parseJson(byteArray);
       reply->deleteLater();
    }
}
/*获取天气信息*/
void MainWindow::getWeatherInfo(QString cityName)
{
    QString cityCode = WeatherTool::getCityCode(cityName);
    if(cityCode.isEmpty())
    {
       QMessageBox::warning(this,"提示","请检查输入是否正确！",QMessageBox::Ok);
    }
    QUrl url("http://t.weather.itboy.net/api/weather/city/" + cityCode);
    //mNetAccessManager发送请求后会调用connect信号自动调用onReplid
    mNetAccessManager->get(QNetworkRequest(url));

}

//解析请求数据
void MainWindow::parseJson(QByteArray &byteArray)
{
    QJsonParseError err;
    QJsonDocument doc =  QJsonDocument::fromJson(byteArray,&err);
    if(err.error != QJsonParseError::NoError)
    {
       return;
    }
    QJsonObject rootObj =  doc.object();//总数据
    //1 解析日期和城市
    today.date = rootObj.value("date").toString();
    today.city = rootObj.value("cityInfo").toObject().value("city").toString();
    //2 解析yeasterday
    QJsonObject objdata = rootObj.value("data").toObject();

    QJsonObject objyesterday = objdata.value("yesterday").toObject();
    sixday[0].week = objyesterday.value("week").toString();
    sixday[0].date = objyesterday.value("ymd").toString();
    sixday[0].type = objyesterday.value("type").toString();
    //高温
    QString s;
    s = objyesterday.value("high").toString().split(" ").at(1);
    s = s.left(s.length() - 1 );
    sixday[0].high = s.toInt();
    //低温
    s = objyesterday.value("low").toString().split(" ").at(1);
    s = s.left(s.length() - 1 );
    sixday[0].low = s.toInt();
    //风向、风力、污染指数
    sixday[0].fx = objyesterday.value("fx").toString();
    sixday[0].fl = objyesterday.value("fl").toString();
    sixday[0].aqi = objyesterday.value("aqi").toDouble();
    //3 解析 forcast中5天数据
    QJsonArray forecastArr = objdata.value("forecast").toArray();
    for (int i = 0; i < 5; ++i) {
       QJsonObject objForecast = forecastArr[i].toObject();
       sixday[i+1].week = objForecast.value("week").toString();
       sixday[i+1].date = objForecast.value("ymd").toString();
       sixday[i+1].type = objForecast.value("type").toString();
       QString s;
       s = objForecast.value("high").toString().split(" ").at(1);
       s = s.left(s.length() - 1 );
       sixday[i+1].high = s.toInt();
       //低温
       s = objForecast.value("low").toString().split(" ").at(1);
       s = s.left(s.length() - 1 );
       sixday[i+1].low = s.toInt();
       //风向、风力、污染指数
       sixday[i+1].fx = objForecast.value("fx").toString();
       sixday[i+1].fl = objForecast.value("fl").toString();
       sixday[i+1].aqi = objForecast.value("aqi").toDouble();
    }
    //4 解析今天的数据
    today.ganmao = objdata.value("ganmao").toString();
    today.wendu = objdata.value("wendu").toString();
    today.shidu = objdata.value("shidu").toString();
    today.pm25 = objdata.value("pm25").toDouble();
    today.quality = objdata.value("quality").toString();
    //5 forecast 中第一个数组元素是今天的数据
    today.type = sixday[1].type;
    today.fx = sixday[1].fx;
    today.fl = sixday[1].fl;
    today.high = sixday[1].high;
    today.low = sixday[1].low;


    //6 更新UI
    UpdateUI();

    //6.2 绘制温度曲线
    ui->lblHighCurve->update();
    ui->lblLowCurve->update();
}



//更新UI
void MainWindow::UpdateUI()
{
    //1 更新日期和城市
    ui->lblDate->setText(QDateTime::fromString(today.date,"yyyyMMdd").toString("yyyy-MM-dd")+" " + sixday[1].week);
    ui->lblCity->setText(today.city);
    //2 更新今天
    ui->lblTypeIcon->setPixmap(todayTypeMap[today.type]);
    ui->lblTemp->setText(today.wendu + "°");
    ui->lblType->setText(today.type);
    ui->lblLowHigh->setText(QString::number(today.low) + "~" + QString::number(today.high) + "℃" );

    ui->lblGanMao->setText("感冒指数：" + today.ganmao);
    ui->lblWindFx->setText(today.fx);
    ui->lblWindFl->setText(today.fl);
    ui->lblPM25->setText(QString::number(today.pm25));
    ui->lblShiDu->setText(today.shidu);
    ui->lblQuality->setText(today.quality);
    //3 更新六天
    for (int i = 0; i < 6; ++i) {
        //更新日期和时间
        WeekList[i]->setText("周"+sixday[i].week.right(1));
        ui->lblWeek0->setText("昨天");
        ui->lblWeek1->setText("今天");
        ui->lblWeek2->setText("明天");
        QStringList ymdList =  sixday[i].date.split("-");
        DateList[i]->setText(ymdList[1]+"-" + ymdList[2]);

        //更新天气类型
        TypeList[i]->setText(sixday[i].type);
        TypeIconList[i]->setPixmap(todayTypeMap[sixday[i].type]);
        //更新空气质量
        if(sixday[i].aqi >= 0 && sixday[i].aqi <= 50)
        {
            AqlList[i]->setText("优");
            AqlList[i]->setStyleSheet("background-color: rgb(121,184,0);");
        }
        else if(sixday[i].aqi > 50 && sixday[i].aqi <= 100)
        {
            AqlList[i]->setText("良");
            AqlList[i]->setStyleSheet("background-color: rgb(255,178,23);");
        }
        else if(sixday[i].aqi > 100 && sixday[i].aqi <= 150)
        {
            AqlList[i]->setText("轻度");
            AqlList[i]->setStyleSheet("background-color: rgb(255,87,97);");
        }
        else if(sixday[i].aqi > 150 && sixday[i].aqi <= 200)
        {
            AqlList[i]->setText("中度");
            AqlList[i]->setStyleSheet("background-color: rgb(235,17,27);");
        }
        else if(sixday[i].aqi > 200 && sixday[i].aqi <= 250)
        {
            AqlList[i]->setText("重度");
            AqlList[i]->setStyleSheet("background-color: rgb(170,0,0);");
        }
        else
        {
            AqlList[i]->setText("严重");
            AqlList[i]->setStyleSheet("background-color: rgb(110,0,0);");
        }
        //更新风力风向
        FxList[i]->setText(sixday[i].fx);
        FlList[i]->setText(sixday[i].fl);


    }
}
//重写父类的eventFilter的方法
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lblHighCurve && event->type() == QEvent::Paint)
        piantHighCurve();

    if(watched == ui->lblLowCurve && event->type() == QEvent::Paint)
        piantLowCurve();

    //执行完我们的操作后,继续父类的操作
    return QWidget::eventFilter(watched, event);
}

void MainWindow::piant(QString HighOrLow)
{
    QLabel * Now = nullptr; // 当前要绘制的曲线标签
    QColor color; // 曲线的颜色
    if(HighOrLow == "High")
    {
        Now = ui->lblHighCurve; // 获取高温曲线标签
        color = QColor(255,170,0); // 设置高温曲线颜色为橙色
    }
    else if(HighOrLow == "Low")
    {
        Now = ui->lblLowCurve; // 获取低温曲线标签
        color = QColor(0,255,255); // 设置低温曲线颜色为青色
    }
    else
    {
        return; // 如果不是"High"或"Low"，则直接返回
    }

    QPainter painter(Now); // 创建一个绘图对象，绘制在当前曲线标签上
    painter.setRenderHint(QPainter::Antialiasing, true); // 设置抗锯齿

    int pointX[6] = {0}; // 存储X坐标
    int tempSum = 0; // 温度总和
    int tempAverage = 0; // 温度平均值
    int value;

    // 获取X坐标
    for (int i = 0; i < 6; ++i) {
        pointX[i] = WeekList[i]->pos().x() + WeekList[i]->width() / 2;
        value = (HighOrLow == "High") ? sixday[i].high : sixday[i].low;
        tempSum += value;
    }
    tempAverage = tempSum / 6; // 计算温度平均值

    int pointY[6] = {0}; // 存储Y坐标
    int yCenter = Now->height() / 2; // Y轴中心坐标

    // 计算Y轴坐标
    for (int i = 0; i < 6; ++i) {
        value = (HighOrLow == "High") ? sixday[i].high : sixday[i].low;
        pointY[i] = yCenter - ((value - tempAverage) * INCREMENT);
    }

    QPen pen = painter.pen(); // 获取当前画笔
    pen.setWidth(1); // 设置画笔宽度
    pen.setColor(color); // 设置画笔颜色
    painter.setPen(pen); // 设置画笔

    painter.setBrush(color); // 设置画刷颜色

    // 绘制点和温度文本
    for (int i = 0; i < 6; ++i) {
        painter.drawEllipse(QPoint(pointX[i], pointY[i]), POINT_REDIUS, POINT_REDIUS); // 绘制点
        int value = (HighOrLow == "High") ? sixday[i].high : sixday[i].low;
        painter.drawText(pointX[i] - TEXT_OFFSET_X, pointY[i] - TEXT_OFFSET_Y, QString::number(value) + "°"); // 绘制温度文本
    }

    // 绘制连线
    for (int i = 0; i < 5; ++i) {
        pen.setStyle(i == 0 ? Qt::SolidLine : Qt::DotLine); // 设置画笔样式
        painter.setPen(pen); // 设置画笔
        painter.drawLine(pointX[i], pointY[i], pointX[i+1], pointY[i+1]); // 绘制线段
    }
}

//绘制高温曲线
void MainWindow::piantHighCurve()
{
    piant("High");
}
//绘制低温曲线
void MainWindow::piantLowCurve()
{
    piant("Low");
}



void MainWindow::on_btnSearch_clicked()
{
    QString cityName = ui->leCity->text();
    if(!cityName.isEmpty())
        getWeatherInfo(cityName);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        // 执行回车键按下后的操作
        QString cityName = ui->leCity->text();
        if(!cityName.isEmpty())
            getWeatherInfo(cityName);
    }
}

void MainWindow::InitWidGet()
{
    //将控件添加到控件数组
    /*星期几*/
    WeekList << ui->lblWeek0 << ui->lblWeek1 << ui->lblWeek2 << ui->lblWeek3 << ui->lblWeek4 << ui->lblWeek5;
    /*日期*/
    DateList << ui->lblDate0 << ui->lblDate1 << ui->lblDate2 << ui->lblDate3 << ui->lblDate4 << ui->lblDate5;
    /*天气*/
    TypeList << ui->lblType0 << ui->lblType1 << ui->lblType2 << ui->lblType3 << ui->lblType4 << ui->lblType5;
    /*天气图标*/
    TypeIconList << ui->lblTypeIcon0 << ui->lblTypeIcon1 << ui->lblTypeIcon2 << ui->lblTypeIcon3 << ui->lblTypeIcon4 << ui->lblTypeIcon5;

    /*天气污染*/
    AqlList << ui->lblQuality0 << ui->lblQuality1 << ui->lblQuality2 << ui->lblQuality3 << ui->lblQuality4 << ui->lblQuality5;
    /*风向和风力*/
    FxList << ui->lblFx0 << ui->lblFx1 << ui->lblFx2 << ui->lblFx3 << ui->lblFx4 << ui->lblFx5;
    FlList << ui->lblFl0 << ui->lblFl1 << ui->lblFl2 << ui->lblFl3 << ui->lblFl4 << ui->lblFl5;

    //图标
    todayTypeMap.insert("暴雪",":/res/type/BaoXue.png");
    todayTypeMap.insert("暴雨",":/res/type/BaoYu.png");
    todayTypeMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    todayTypeMap.insert("大暴雨",":/res/type/DaBaoYu.png");
    todayTypeMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    todayTypeMap.insert("大到暴雪",":/res/type/DaDaoBaoXue.png");
    todayTypeMap.insert("大到暴雨",":/res/type/DaDaoBaoYu.png");
    todayTypeMap.insert("大雪",":/res/type/DaXue.png");
    todayTypeMap.insert("大雨",":/res/type/DaYu.png");
    todayTypeMap.insert("冻雨",":/res/type/DongYu.png");
    todayTypeMap.insert("多云",":/res/type/DuoYun.png");
    todayTypeMap.insert("浮沉",":/res/type/FuChen.png");
    todayTypeMap.insert("雷阵雨",":/res/type/LeiZhenYu.png");
    todayTypeMap.insert("雷阵雨伴有冰雹",":/res/type/LeiZhenYuBanYouBingBao.png");
    todayTypeMap.insert("霾",":/res/type/Mai.png");
    todayTypeMap.insert("强沙城暴",":/res/type/QiangShaChenBao.png");
    todayTypeMap.insert("晴",":/res/type/Qing.png");
    todayTypeMap.insert("沙城暴",":/res/type/ShaChenBao.png");
    todayTypeMap.insert("特大暴雨",":/res/type/TeDaBaoYu.png");
    todayTypeMap.insert("undefined",":/res/type/undefined.png");
    todayTypeMap.insert("雾",":/res/type/Wu.png");
    todayTypeMap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");
    todayTypeMap.insert("小到中雨",":/res/type/XiaoDaoZhongYu.png");
    todayTypeMap.insert("小雪",":/res/type/XiaoXue.png");
    todayTypeMap.insert("小雨",":/res/type/XiaoYu.png");
    todayTypeMap.insert("雪",":/res/type/Xue.png");
    todayTypeMap.insert("扬沙",":/res/type/YangSha.png");
    todayTypeMap.insert("阴",":/res/type/Yin.png");
    todayTypeMap.insert("雨",":/res/type/Yu.png");
    todayTypeMap.insert("雨夹雪",":/res/type/YuJiaXue.png");
    todayTypeMap.insert("阵雪",":/res/type/ZhenXue.png");
    todayTypeMap.insert("阵雨",":/res/type/ZhenYu.png");
    todayTypeMap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    todayTypeMap.insert("中到大雨",":/res/type/ZhongDaoDaYu.png");
    todayTypeMap.insert("中雪",":/res/type/ZhongXue.png");
    todayTypeMap.insert("中雨",":/res/type/ZhongYu.png");
}
