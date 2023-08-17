#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *k);
    void mousePressEvent(QMouseEvent *m);

private slots:
    void newActionSlot();
    void openActionSlot();
    void saveActionSlot();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
