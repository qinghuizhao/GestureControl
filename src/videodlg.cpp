#include "videodlg.h"
#include "ui_videodlg.h"
#include<QDebug>
#include<sys/stat.h>
#include <QThread>

videodlg::videodlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::videodlg)
{
    ui->setupUi(this);
    timer = new QTimer;
    timerControl = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
    connect(timerControl,SIGNAL(timeout()),this,SLOT(timerstart1()));
    timerControl->start(2000);
      // timer->start(2000);
//    QImage image = QImage((const uchar*)backpicture->imageData, backpicture->width, backpicture->height, QImage::Format_RGB888).rgbSwapped();
//    ui->label->setPixmap(QPixmap::fromImage(image));

      //QImage image = QImage((const uchar*)backpicture->imageData, backpicture->width, backpicture->height, QImage::Format_RGB888).rgbSwapped();
      //ui->label->setPixmap(QPixmap::fromImage(image));

}

videodlg::~videodlg()
{
    timer->stop();
    fra=1;
    cvReleaseCapture(&capture);
    delete ui;
}
void videodlg::timerstart1(){
     static int xx = 0;

    if(nresult == 1)
    {
        if (xx == 0)
        timer->start(2000);
        xx = 2;
    }
    else if(nresult == 4)
    {
        xx=0;

        timer->stop();
        IplImage* b6=cvLoadImage("./res/call.jpg");
        QImage imageback6 = QImage((const uchar*)b6->imageData, b6->width, b6->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback6));
        cvReleaseImage(&b6);

    }
}

void videodlg::timerDone()
{
    Cycle++;
    CvFont font;
    int  nframe=Cycle%5;
//    char*[55];
//    IplImage* ii=cvLoadImage("../"+nframe+".jpg");
    int ii=0;
    switch (nframe)
    {

    case 0:
       {
        IplImage* backpicture=cvCreateImage(cvSize(1280,680),IPL_DEPTH_8U,3);//选择背景图
        cvZero(backpicture);//黑色背景


        if(nresult==1){
        //timer->start(2000);
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture,"=====>", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture,"=====>", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==2){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture,"<=====", cvPoint(440, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture,"<=====", cvPoint(440, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==4){
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
            cvPutText(backpicture,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
            cvPutText(backpicture,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
          //timer->stop();
//            QThread::sleep(5000);
        //  connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
        }
        if(nresult==3){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        QImage image = QImage((const uchar*)backpicture->imageData, backpicture->width, backpicture->height, QImage::Format_RGB888).rgbSwapped();
        ui->labelvideo->setPixmap(QPixmap::fromImage(image));

        IplImage* b1=cvLoadImage("./res/b1.png");
         QImage imageback1 = QImage((const uchar*)b1->imageData, b1->width, b1->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback1));
        cvReleaseImage(&backpicture) ;
        cvReleaseImage(&b1);
//        ii++;if(ii>0)timer->stop();
    }
        break;
    case 1:
       {
        IplImage* backpicture1=cvCreateImage(cvSize(1280,680),IPL_DEPTH_8U,3);//选择背景图
        cvZero(backpicture1);//黑色背景
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
//        cvPutText(backpicture1,"外科", cvPoint(420, 180), &font, CV_RGB(255,0,0));
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
//        cvPutText(backpicture1, "外科", cvPoint(420, 180), &font, CV_RGB(0,255,0));
        if(nresult==1){
       // timer->start(2000);
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture1,"=====>", cvPoint(380, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture1,"=====>", cvPoint(380, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==2){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture1,"<=====", cvPoint(420, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture1,"<=====", cvPoint(420, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==4){
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
            cvPutText(backpicture1,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
            cvPutText(backpicture1,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
//          QThread::sleep(5000);
         // connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
        }
        if(nresult==3){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture1,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture1,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        QImage image1 = QImage((const uchar*)backpicture1->imageData, backpicture1->width, backpicture1->height, QImage::Format_RGB888).rgbSwapped();
        ui->labelvideo->setPixmap(QPixmap::fromImage(image1));
        cvReleaseImage(&backpicture1);
        IplImage* b2=cvLoadImage("./res/b2.png");
         QImage imageback2 = QImage((const uchar*)b2->imageData, b2->width, b2->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback2));
        cvReleaseImage(&b2);
       }
        break;
    case 2:
       { IplImage* backpicture2=cvCreateImage(cvSize(1280,680),IPL_DEPTH_8U,3);//选择背景图
        cvZero(backpicture2);//黑色背景
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
//        cvPutText(backpicture2,"内科", cvPoint(420, 180), &font, CV_RGB(255,0,0));
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
//        cvPutText(backpicture2, "内科", cvPoint(420, 180), &font, CV_RGB(0,255,0));
        if(nresult==1){
       // timer->start(2000);
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture2,"=====>", cvPoint(400, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture2,"=====>", cvPoint(400, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==2){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture2,"<=====", cvPoint(400, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture2,"<=====", cvPoint(400, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==4){
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
            cvPutText(backpicture2,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
            cvPutText(backpicture2,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
//          QThread::sleep(5000);
            //timer->stop();
         // connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
        }
        if(nresult==3){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture2,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture2,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        QImage image2 = QImage((const uchar*)backpicture2->imageData, backpicture2->width, backpicture2->height, QImage::Format_RGB888).rgbSwapped();
        ui->labelvideo->setPixmap(QPixmap::fromImage(image2));
        cvReleaseImage(&backpicture2);
        IplImage* b3=cvLoadImage("./res/b3.png");
        QImage imageback3 = QImage((const uchar*)b3->imageData, b3->width, b3->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback3));
        cvReleaseImage(&b3);
        }
        break;
    case 3:
       { IplImage* backpicture3=cvCreateImage(cvSize(1280,680),IPL_DEPTH_8U,3);//选择背景图
        cvZero(backpicture3);//黑色背景
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
//        cvPutText(backpicture3,"传染科", cvPoint(420, 180), &font, CV_RGB(255,0,0));
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
//        cvPutText(backpicture3, "传染科", cvPoint(420, 180), &font, CV_RGB(0,255,0));
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        if(nresult==1){
        //timer->start(2000);
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture3,"=====>", cvPoint(420, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture3,"=====>", cvPoint(420, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==2){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture3,"<=====", cvPoint(380, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture3,"<=====", cvPoint(380, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==4){
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
            cvPutText(backpicture3,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
            cvPutText(backpicture3,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
//          QThread::sleep(5000);
           // timer->stop();
         // connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
        }
        if(nresult==3){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture3,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture3,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        QImage image3 = QImage((const uchar*)backpicture3->imageData, backpicture3->width, backpicture3->height, QImage::Format_RGB888).rgbSwapped();
        ui->labelvideo->setPixmap(QPixmap::fromImage(image3));
        cvReleaseImage(&backpicture3);
        IplImage* b4=cvLoadImage("./res/b4.png");
        QImage imageback4 = QImage((const uchar*)b4->imageData, b4->width, b4->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback4));
        cvReleaseImage(&b4);
       }
        break;
    case 4:
      {  IplImage* backpicture4=cvCreateImage(cvSize(1280,680),IPL_DEPTH_8U,3);//选择背景图
        cvZero(backpicture4);//黑色背景
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
//        cvPutText(backpicture4,"放射科", cvPoint(420, 180), &font, CV_RGB(255,0,0));
//        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
//        cvPutText(backpicture4, "放射科", cvPoint(420, 180), &font, CV_RGB(0,255,0));
        if(nresult==1){
      //  timer->start(2000);
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture4,"=====>", cvPoint(440, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture4,"=====>", cvPoint(440, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==2){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture4,"<=====", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture4,"<=====", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        if(nresult==4){
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
            cvPutText(backpicture4,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
            cvPutText(backpicture4,"**Calling**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
//          QThread::sleep(5000);
        //    timer->stop();
       //   connect(timer,SIGNAL(timeout()),this,SLOT(timerDone()));
        }
        if(nresult==3){
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,5,8);
        cvPutText(backpicture4,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,0,255));
        cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,1.0f,1.0f,0,2,8);
        cvPutText(backpicture4,"**rest**", cvPoint(360, 480), &font, CV_RGB(0,255,0));
        }
        QImage image4 = QImage((const uchar*)backpicture4->imageData, backpicture4->width, backpicture4->height, QImage::Format_RGB888).rgbSwapped();
        ui->labelvideo->setPixmap(QPixmap::fromImage(image4));
        cvReleaseImage(&backpicture4);
        IplImage* b5=cvLoadImage("./res/b5.png");
        QImage imageback5 = QImage((const uchar*)b5->imageData, b5->width, b5->height, QImage::Format_RGB888).rgbSwapped();
        ui->label->setPixmap(QPixmap::fromImage(imageback5));
        cvReleaseImage(&b5);
      }
        break;

    default:
        break;}



}

void  videodlg::video(int nnstop)
{
    while(!nnstop){

        int a=0,contArea = 0,imgArea,contArea1 ;
        int movex=0,movey=0,movex1=0,movey1=0;
        int start=0,end=0,up=0,down=0,right=0,left=0;
        int leight;
        capture=cvCreateCameraCapture(1);
        IplImage* frame;
        CvMemStorage* g_storage0=cvCreateMemStorage(0);
        CvPoint move;
        CvSeq* conturs0=0;
        CvMemStorage* g_storage6=cvCreateMemStorage(0);
        CvSeq* conturs6=0;
        CvSeq* hull =NULL ;
        CvContourScanner scanner;
        while(1)
        {frame=cvQueryFrame (capture);
        if(frame) break;	}
        IplImage* dst_YUV=cvCreateImage(cvGetSize(frame),8,3);
        IplImage* GRAY=cvCreateImage(cvGetSize(frame),8,1);
        IplImage* sample=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
        IplImage* img=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
        IplImage* out=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
        IplImage* out1=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
        IplImage* result= cvCreateImage(cvGetSize(out),8,1);
        IplImage *imageContour=cvCreateImage(cvSize(640,480),8,1);
        CvPoint* corners=new CvPoint[15];
        float rate;
        int ii=0;
            while(1)
            {
                ii++;
                 char * ss=new char;
                sprintf(ss,"%d",ii);
            cvZero(sample);
            cvZero(out1);
            frame=cvQueryFrame (capture);
            if(!frame) break;
            CvFont font;
            cvSmooth(frame,img,CV_MEDIAN,3,0,0);
            cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX,.90f,.90f,0,2,8);
            cvPutText(frame, ss, cvPoint(5, 50), &font, CV_RGB(0,255,0));
            QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped();
            ui->label_2->setPixmap(QPixmap::fromImage(image));
        //           cvNamedWindow("RGB",0);
        //           cvShowImage("RGB",frame);
            cvSkinYUV(img,dst_YUV);
            cvSplit(dst_YUV,GRAY,0,0,0);
            cvThresholdOtsu(GRAY,GRAY);
            cvMorphologyEx(GRAY,GRAY,0,NULL,CV_MOP_OPEN  ,1 );
            cvMorphologyEx(GRAY,GRAY,0,NULL,CV_MOP_CLOSE  ,1 );
            cvCopy(GRAY,out);
            scanner= cvStartFindContours(out,g_storage0,sizeof(CvContour), CV_RETR_EXTERNAL);
            imgArea = out->height * out->width;

        while((conturs0 = cvFindNextContour(scanner)) != NULL)
        {
         contArea = fabs(cvContourArea( conturs0, CV_WHOLE_SEQ ));
         if ( (double)contArea/imgArea < 0.095)continue;
         cvDrawContours(sample,conturs0,CV_RGB(255,0,0),CV_RGB(0,255,0),0);
         cvCheckContourConvexity(conturs0);
         hull = cvConvexHull2(conturs0,0,CV_CLOCKWISE,0);
         CvPoint pt0 = **(CvPoint**)cvGetSeqElem(hull,hull->total - 1);
            for(int i = 0;i<hull->total;++i)
            {
                CvPoint pt1 = **(CvPoint**)cvGetSeqElem(hull,i);
               cvLine(sample,pt0,pt1,CV_RGB(0,0,255));
               cvLine(out1,pt0,pt1,CV_RGB(0,0,255));
               cvLine(out1,pt0,pt1,CV_RGB(0,0,255));
               pt0 = pt1;
            }
            cvFindContours (out1,g_storage6,&conturs6,sizeof(CvContour), CV_RETR_EXTERNAL);
            cvZero(imageContour);
            cvDrawContours(imageContour,conturs0,cvScalar(255),cvScalar(255),0,CV_FILLED);
            nresult=rehand.regnition(conturs0);
            //qDebug()<<"我是"<<nresult;
            contArea1 = fabs(cvContourArea( conturs0, CV_WHOLE_SEQ ));
            rate=(double)contArea1/(double)contArea;
            if(rate>0.95&&rate<1.3)
            {end=1;start=0;}
            if(rate>1.4&&rate<1.6)
            {end=0;start=1;}
            if(rate>1.7&&rate<1.9)
            {end=1;start=1;}
            CvSeq *defect = cvConvexityDefects(conturs0,hull);
            for(int i = 0;i<defect->total;++i)
            {
                CvConvexityDefect df = *(CvConvexityDefect*)cvGetSeqElem(defect,i);
                if(df.depth<50) {continue;}
                cvCircle(sample,*df.start,5,CV_RGB(255,255,0),-1);
                cvCircle(sample,*df.end,5,CV_RGB(255,255,0),-1);
                move =*df.start;
                corners[a]=move;
                movex1+=move.x;
                a++;
                movey1+=move.y;
               cvCircle(sample,*df.depth_point,5,CV_RGB(0,255,255),-1);
            }


        if(a!=0)
        {
            movex1=(int)movex1/a;
            movey1=(int)movey1/a;
            a=0;
            move=cvPoint(320,20);
            cvCircle(sample,move,5,CV_RGB(0,255,0),-1);
            movey1+=50;
            move=cvPoint(movex1,movey1);
            cvCircle(sample,move,5,CV_RGB(0,255,0),-1);
                        }
            leight=(movex1-320)*(movex1-320)+(movey1-240)*(movey1-240);
            leight=sqrt((float)leight);
            if(leight<80){up=0;down=0;right=0;left=0;}
            else
                if(abs(movex1-320)>abs(movey1-240))
                {
                    if(movex1>120&&movex1<240)  {up=0;down=0;right+=1;left=0;}
                    else
                    if(movex1>400&&movex1<520)  {up=0;down=0;right=0;left+=1;}
                }
                else
                {
                    if(movey1>80&&movey1<160)  {up+=1;down=0;right=0;left=0;}
                    else
                    if(movey1>320&&movey1<400)  {up=0;down+=1;right=0;left=0;}
                }
            movex=0;
            movey=0;
            movex1=0;
            movey1=0;
            if(start==1&&end==0)
            {
            if(right==2) {qDebug()<<"��    \n";right=0;}
            if(left==2)  {qDebug()<<"��   \n";left=0;}
            if(up==2)    {qDebug()<<"��   \n";up=0;}
            if(down==2)  {qDebug()<<"��   \n";down=0;}
            }

        }
//        cvNamedWindow("");
//        cvShowImage("",sample);

          cvEndFindContours(&scanner );

         char c=cvWaitKey(33);
         if(c=='s')cvSaveImage("../myhand.jpg",sample);
         if(c=='0') break;
        }

        closeCamara();
        cvReleaseImage(&dst_YUV);
        cvReleaseImage(&GRAY);
        cvReleaseImage(&sample);
        cvReleaseImage(& img);
        cvReleaseImage(& frame);
        cvReleaseImage(& out);
        cvReleaseImage(& out1);
        cvReleaseImage(& result);
        cvReleaseImage(&imageContour);
    }
}
void videodlg::cvThresholdOtsu(IplImage* src, IplImage* dst)
{
 int height=src->height;
 int width=src->width;

 //histogram
 float histogram[256]= {0};
 for(int i=0; i<height; i++)
 {
     unsigned char* p=(unsigned char*)src->imageData+src->widthStep*i;
     for(int j=0; j<width; j++)
     {
         histogram[*p++]++;
     }
 }
 //normalize histogram
 int size=height*width;
 for(int i=0; i<256; i++)
 {
     histogram[i]=histogram[i]/size;
 }

 //average pixel value
 float avgValue=0;
 for(int i=0; i<256; i++)
 {
     avgValue+=i*histogram[i];
 }

 int threshold;
 float maxVariance=0;
 float w=0,u=0;
 for(int i=0; i<256; i++)
 {
     w+=histogram[i];
     u+=i*histogram[i];

     float t=avgValue*w-u;
     float variance=t*t/(w*(1-w));
     if(variance>maxVariance)
     {
         maxVariance=variance;
         threshold=i;
     }
 }

 cvThreshold(src,dst,threshold,255,CV_THRESH_BINARY);
}
void videodlg::cvSkinYUV(IplImage* src,IplImage* dst)
{
    IplImage* ycrcb=cvCreateImage(cvGetSize(src),8,3);
    //IplImage* cr=cvCreateImage(cvGetSize(src),8,1);
    cvCvtColor(src,ycrcb,CV_BGR2YCrCb);

    static const int Cb=2;
    static const int Cr=1;
    static const int Y=0;

    //IplImage* dst=cvCreateImage(cvGetSize(_dst),8,3);
    cvZero(dst);

    for (int h=0; h<src->height; h++)
    {
        unsigned char* pycrcb=(unsigned char*)ycrcb->imageData+h*ycrcb->widthStep;
        unsigned char* psrc=(unsigned char*)src->imageData+h*src->widthStep;
        unsigned char* pdst=(unsigned char*)dst->imageData+h*dst->widthStep;
        for (int w=0; w<src->width; w++)
        {
            if (pycrcb[Cr]>=133&&pycrcb[Cr]<=220&&pycrcb[Cb]>=100&&pycrcb[Cb]<=134)
            {
                memcpy(pdst,psrc,3);
            }
            pycrcb+=3;
            psrc+=3;
            pdst+=3;
        }
    }
}


void videodlg::closeEvent(QCloseEvent *e)

{

close();

}
void videodlg::closeCamara()
{
   timer->stop();

   cvReleaseCapture(&capture);
}
void videodlg::keyPressEvent(QKeyEvent *e)

{

if(e->key()==Qt::Key_Escape)
{

close();

}

}


void videodlg::on_pushButton_clicked()
{
    nstop=0;
    video(nstop);
}
