#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //连接数据库
    db = QSqlDatabase::addDatabase("QODBC");     //加载MySQL数据库驱动

    db.setDatabaseName("qt_data");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");

    if (db.open())
    {
        QMessageBox::information(this, "连接提示", "连接成功");
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

void Widget::on_insertPushButton_clicked()
{
    QString id = ui->idLineEdit->text();
    QString name = ui->nameLineEdit->text();
    QString birth = ui->birLineEdit->text();

    QString sql = QString("insert into qt_data values (%1, '%2', '%3');").arg(id).arg(name).arg(birth);
    QSqlQuery query;
    if(query.exec(sql))
    {
        QMessageBox::information(this,"插入提示","插入成功");
    }
    else
    {
        QMessageBox::information(this,"插入提示","插入失败");
    }
}

void Widget::on_findPushButton_clicked()
{
    QSqlQuery query;
    query.exec("select * from qt_data;");
    while (query.next()) {
        qDebug() << query.value(0);
        qDebug() << query.value(1);
        qDebug() << query.value(2);
        qDebug() << "\n";
    }
}
