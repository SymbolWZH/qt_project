#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>
#include<string.h>
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
    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_0_clicked();

    void on_button_mul_clicked();

    void on_button_div_clicked();

    void on_button_left_clicked();

    void on_button_right_clicked();

    void on_button_add_clicked();

    void on_button_sub_clicked();

    void on_button_empty_clicked();

    void on_button_del_clicked();

    void on_button_equal_clicked();

private:
    Ui::Widget *ui;
    QString expression;
    int Priority(char ch);
};

#endif // WIDGET_H
