#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qt_data");
    db.setUserName("root");
    db.setPassword("root");

    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");
        qm = new QSqlTableModel;
        qm->setTable("qt_data");
        ui->tableView->setModel(qm);
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


void Widget::on_SearchBtn_clicked()
{
    qm->select();
}

