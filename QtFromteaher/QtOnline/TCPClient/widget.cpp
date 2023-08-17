#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket = new QTcpSocket;   //创建socket对象
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_cancelButton_clicked()
{
    this->close();
}

void Widget::on_connectButton_clicked()
{
    //获取ip地址和端口号
    QString IP = ui->ipLineEdit->text();
    QString port = ui->portLineEdit->text();

    //连接服务器
    socket->connectToHost(QHostAddress(IP), port.toShort());

    //连接服务器成功，socket对象会发出信号
    connect(socket, &QTcpSocket::connected, [this]()
    {
        QMessageBox::information(this, "连接提示", "连接服务器成功");

        this->hide();
        Chat *c = new Chat(socket);    //堆空间创建
        c->show();
    });

    //连接断开，socket会发出信号
    connect(socket, &QTcpSocket::disconnected, [this]()
    {
        QMessageBox::warning(this, "连接提示", "连接异常 网络断开");
    });
}
