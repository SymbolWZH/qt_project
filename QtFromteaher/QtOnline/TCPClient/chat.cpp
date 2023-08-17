#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *s, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    socket = s;

    connect(socket, &QTcpSocket::readyRead, this, &Chat::recvInfoSlot);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}

void Chat::on_sendButton_clicked()
{
    QByteArray ba;
    ba.append(ui->lineEdit->text());
    socket->write(ba);
}

void Chat::recvInfoSlot()
{
    ui->recvLineEdit->setText(QString(socket->readAll()));
}
