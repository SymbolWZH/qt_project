#include "mythread.h"

myThread::myThread(QTcpSocket *s)
{
    socket = s;
}
void myThread::run()
{
    //连接信号与槽
    connect(socket,&QTcpSocket::readyRead,this,&myThread::clientInfoSlot);
}
//不能在其他类里面操作界面 自定义信号可以
void myThread::clientInfoSlot()
{
    //接收
    //qDebug() << socket->readAll();
    QByteArray ba = socket ->readAll();
    emit sendToWidget(ba); //发送信号
}
