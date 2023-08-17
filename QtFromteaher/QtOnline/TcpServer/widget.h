#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <mythread.h>

#define PORT    8000

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void newClientHandler();
    //void clientInfoSlot();
    void threadSlot(QByteArray b);

private:
    Ui::Widget *ui;
    QTcpServer *server;
};

#endif // WIDGET_H
