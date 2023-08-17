#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>

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
    void on_commitButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
