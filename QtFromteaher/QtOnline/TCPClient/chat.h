#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QTcpSocket *s, QWidget *parent = 0);
    ~Chat();

private slots:
    void on_clearButton_clicked();

    void on_sendButton_clicked();

    void recvInfoSlot();

private:
    Ui::Chat *ui;
    QTcpSocket *socket;
};

#endif // CHAT_H
