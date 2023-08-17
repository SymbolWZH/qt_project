#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //连接信号与槽
    //谁发出信号         发出什么信号              谁处理
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));

    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::on_pushButton_2_clicked);

    connect(ui->pushButton_3,&QPushButton::clicked,[this]()
    {
        QMessageBox::information(this,"信息","点击浏览");

    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    //获取lineedit数据
    QString program =  ui->lineEdit->text();

    //创建一个process对象
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program);
}

void Widget::on_pushButton_2_clicked()
{
    this->close();
}
