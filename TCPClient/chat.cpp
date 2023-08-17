#include "chat.h"
#include "ui_chat.h"

Chat::Chat(QTcpSocket *s,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
    socket = s;
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_clearBtn_clicked()
{
    ui->sendText->clear();
}

void Chat::on_sendBtn_clicked()
{
    QByteArray ba;
    QString s = ui->sendText->text();
    ba.append(s.toUtf8());

    socket->write(ba);

}
