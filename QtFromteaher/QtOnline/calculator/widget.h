#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>
#include <string.h>

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
    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_zeroButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

    void on_addButton_clicked();

    void on_subButton_clicked();

    void on_divButton_clicked();

    void on_mulButton_clicked();

    void on_clearButton_clicked();

    void on_delButton_clicked();

    void on_equalButton_clicked();

private:
    Ui::Widget *ui;
    QString expression;

    int Priority(char ch);
};

#endif // WIDGET_H
