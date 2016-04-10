#ifndef VIDEODLG_H
#define VIDEODLG_H
#include<reghand.h>
#include <QDialog>
#include <QTimer>
#include<QKeyEvent>
#include <QEvent>
#include<cvxtext.h>
#include<iostream>
namespace Ui {
class videodlg;
}

class videodlg : public QDialog
{
    Q_OBJECT
    reghand rehand;
//    CvxText CvText;
   // CvText text("simsun.ttf");



public:
    explicit videodlg(QWidget *parent = 0);
    ~videodlg();

private slots:
    void timerDone();

    void cvThresholdOtsu(IplImage* src, IplImage* dst);
    void cvSkinYUV(IplImage* src,IplImage* dst);
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void closeCamara();
    void  video(int nnstop);
void timerstart1();


    void on_pushButton_clicked();

private:
    Ui::videodlg *ui;
    QImage *qImage;
    IplImage *iplImage;
    QTimer *timer;
    QTimer *timerControl;
    int Cycle=0,fra;
    CvCapture *capture ;
    int nresult=1;
    int nstop=1;
    int nresult0=0;




};

#endif // VIDEODLG_H
