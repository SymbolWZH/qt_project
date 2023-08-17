#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    timer = new QTimer;
    picID = 2;

    QImage img;
    img.load("D:\\QTProject\\1.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));

    //定时器时间到，发出timeout信号
    connect(timer, &QTimer::timeout, this, &Widget::timeoutSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    timer->start(TIMEOUT);
}

void Widget::timeoutSlot()
{
    QString path("D:\\QTProject\\");
    path += QString::number(picID);
    path += ".jpg";

    QImage img;
    img.load(path);
    ui->label->setPixmap(QPixmap::fromImage(img));

    picID++;
    if (5 == picID)
        picID = 1;
}

void Widget::on_stopButton_clicked()
{
    timer->stop();
}

void Widget::on_singleButton_clicked()
{
    QTimer::singleShot(1000, this, SLOT(timeoutSlot()));
}
