#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer = new QTimer;
    QImage img;
    img.load("E:\\qt\\objectTimer\\img01.jpg");
    ui->label->setPixmap(QPixmap::fromImage(img));
    //定时器时间到发出timerout信号
    connect(timer,&QTimer::timeout,this,&Widget::timeroutSolt);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_label_linkActivated(const QString &link)
{

}

void Widget::on_startBtn_clicked()
{
        timer->start(TIMEOUT);
}

void Widget::on_endBtn_clicked()
{
    timer->stop();
}
void Widget::timeroutSolt()
{
    QString path("E:\\qt\\objectTimer\\img0");
    path += QString::number(picId);
    path += ".jpg";
    QImage img;
    img.load(path);
    ui->label->setPixmap(QPixmap::fromImage(img));
    picId == 1 ? picId++ : picId--;
}

void Widget::on_SingleBtn_clicked()
{
    QTimer::singleShot(TIMEOUT,this,SLOT(timeroutSolt()));
}
