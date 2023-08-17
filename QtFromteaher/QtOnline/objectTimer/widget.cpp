#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    picID = 2;

    QPixmap pix("D:\\QTProject\\1.jpg");
    ui->label->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startButton_clicked()
{
    //开启定时器，返回定时器编号
    myTimerId = this->startTimer(TIMEOUT);
}

void Widget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() != myTimerId)
        return;

    QString path("D:\\QTProject\\");
    path += QString::number(picID);
    path += ".jpg";

    QPixmap pix(path);
    ui->label->setPixmap(pix);

    picID++;
    if (5 == picID)
        picID = 1;
}

void Widget::on_stopButton_clicked()
{
    this->killTimer(myTimerId);
}
