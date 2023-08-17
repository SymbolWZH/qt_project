#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#define TIME_OUT 1 * 1000
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    virtual void timerEvent(QTimerEvent * event);
    ~Widget();

private slots:
    void on_startBtn_clicked();

    void on_ban_linkActivated(const QString &link);

    void on_endBtn_clicked();

private:
    Ui::Widget *ui;
    int timerId;
    int picId;
};

#endif // WIDGET_H
