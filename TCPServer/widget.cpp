#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    server = new QTcpServer;
    server->listen(QHostAddress::AnyIPv4,PORT);
    //客户端发起连接 server 发出连接信号
    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::newClientHandler()
{
    //建立tcp连接
    QTcpSocket *clientSocket = server->nextPendingConnection();
    QHostAddress ip = clientSocket->peerAddress();
    qint16 port = clientSocket->peerPort();

    ui->ip->setText(ip.toString());
    ui->port->setText(QString::number(port));

    //服务器收到发送的信息，socket发出的readyread的信号
    //connect(clientSocket,&QTcpSocket::readyRead,this,&Widget::clientInfoSlot);

    //启动线程
    myThread *t = new myThread(clientSocket);//创建线程对象
    t->start();//开始线程

    connect(t,&myThread::sendToWidget,this,&Widget::ThreadSlot);
}
//void Widget::clientInfoSlot()
//{
//    //获取信号的发出者
//   QTcpSocket *s =(QTcpSocket *)sender();
//   ui->mylineedit->setText(QString(s->readAll()));
//}
void Widget::ThreadSlot(QByteArray b)
{
    ui->mylineedit->setText(QString(b));
}
