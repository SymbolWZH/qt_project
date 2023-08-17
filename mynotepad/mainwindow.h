#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <qDebug>
#include<QFile>
#include<QIODevice>
#include<QKeyEvent>
#include<QMouseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *MouseEvent);
private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
