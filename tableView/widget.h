#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_SearchBtn_clicked();

private:
    Ui::Widget *ui;
    QSqlTableModel * qm;
    QSqlDatabase  db;
};
#endif // WIDGET_H
