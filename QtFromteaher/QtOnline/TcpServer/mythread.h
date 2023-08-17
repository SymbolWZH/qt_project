#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket *s);
    void run();     //线程处理函数

signals:
    void sendToWidget(QByteArray b);

public slots:
    void clientInfoSlot();

private:
    QTcpSocket *socket;
};

#endif // MYTHREAD_H
