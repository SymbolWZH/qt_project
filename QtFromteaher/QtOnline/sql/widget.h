#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>

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
    void on_findButton_clicked();

    void on_addButton_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // WIDGET_H
