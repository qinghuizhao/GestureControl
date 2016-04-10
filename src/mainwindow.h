#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<videodlg.h>
#include<reghand.h>
//#include<QDebug>
//#include<QPen>
//#include<QPainter>
//#include<QFont>
//#include<QTimer>
//#include<stdlib.h>
//#include<QKeyEvent>
//#include <QEvent>

#define PI 3.1415926;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    videodlg regvideo;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
