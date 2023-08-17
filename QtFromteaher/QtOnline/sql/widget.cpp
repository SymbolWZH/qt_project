#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("47.101.128.140");
    db.setDatabaseName("mydatabase");
    db.setUserName("test");
    db.setPassword("test");

    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");
        model = new QSqlTableModel;
        model->setTable("student");
        ui->tableView->setModel(model);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_findButton_clicked()
{
    model->select();
}

void Widget::on_addButton_clicked()
{
    QSqlRecord record = model->record();
    int row = model->rowCount();
    qDebug() << row;
    model->insertRecord(row, record);
}
