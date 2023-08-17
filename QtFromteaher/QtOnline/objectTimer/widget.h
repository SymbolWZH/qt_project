#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#define TIMEOUT    1 * 1000

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    virtual void timerEvent(QTimerEvent *event);
    ~Widget();

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::Widget *ui;
    int myTimerId;
    int picID;
};

#endif // WIDGET_H
