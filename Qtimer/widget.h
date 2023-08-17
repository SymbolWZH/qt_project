#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#define TIMEOUT 1000
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
    void timeroutSolt();
    void on_label_linkActivated(const QString &link);

    void on_startBtn_clicked();

    void on_endBtn_clicked();

    void on_SingleBtn_clicked();

private:
    Ui::Widget *ui;
    QTimer *timer;
    int picId = 2;
};

#endif // WIDGET_H
