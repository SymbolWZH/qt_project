#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    picId = 2;
    ui->setupUi(this);
    QPixmap pix("E:\\qt\\objectTimer\\img01.jpg");
    ui->ban->setPixmap(pix);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_startBtn_clicked()
{
    //定时器 毫秒单位 开启定时器返回定时器编号
   timerId = this->startTimer(TIME_OUT);
}

void Widget::on_ban_linkActivated(const QString &link)
{

}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId() != timerId)
        return;

    QString path("E:\\qt\\objectTimer\\img0");
    path+=QString::number(picId);
    path+=".jpg";

    QPixmap pix(path);
    ui->ban->setPixmap(pix);
    picId == 1?picId++ : picId--;
}

void Widget::on_endBtn_clicked()
{
    this->killTimer(timerId);
}
