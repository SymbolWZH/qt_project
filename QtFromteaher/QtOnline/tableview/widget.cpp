#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("47.101.128.140");
    db.setDatabaseName("mydatabase");
    db.setUserName("test1");
    db.setPassword("test1");

    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");

        m = new QSqlTableModel;
        m->setTable("student");
        ui->tableView->setModel(m);
    }
    else
    {
        QMessageBox::warning(this, "连接提示", "连接失败");
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    m->select();
}
