#include "reghand.h"

reghand::reghand()
{

}

reghand::~reghand()
{

}
CvSeq *reghand::elimNeighborHulls(CvSeq *hullseq)
{
    int disthreshold=handradis/3;
    CvSeq *filtedhullseq=cvCloneSeq(hullseq);
    if(hullseq->total<=1) return filtedhullseq;
    cvClearSeq(filtedhullseq);
    CvPoint **curdata;CvPoint currpt,nextpt;
    for(int i=0;i<hullseq->total-1;i++)
    {
        curdata=CV_GET_SEQ_ELEM(CvPoint*,hullseq,i);
        currpt=**curdata;
        nextpt=**CV_GET_SEQ_ELEM(CvPoint*,hullseq,i+1);
        double distance=sqrt(pow(double(currpt.x-nextpt.x),2)+pow(double(currpt.y-nextpt.y),2));
        if(distance>disthreshold) cvSeqPush(filtedhullseq,curdata);

    }
    //	if(hullseq->total==2)return filtedhullseq;
    curdata=CV_GET_SEQ_ELEM(CvPoint*,hullseq,hullseq->total-1);
    currpt=**curdata;
    nextpt=**CV_GET_SEQ_ELEM(CvPoint*,hullseq,0);
    double distance=sqrt(pow(double(currpt.x-nextpt.x),2)+pow(double(currpt.y-nextpt.y),2));
    if(distance>disthreshold) cvSeqPush(filtedhullseq,curdata);
    return filtedhullseq;
}
CvSeq *reghand::filthull(CvSeq *hullseq)
{
    int thresh=handcenter.y;
    CvSeq *filtedhullseq=cvCloneSeq(hullseq);
    cvClearSeq(filtedhullseq);
    for (int i=0;i<hullseq->total;i++)
    {
        CvPoint** data=CV_GET_SEQ_ELEM(CvPoint*,hullseq,i);
        CvPoint currpt=**data;
        if(currpt.y<thresh)
            cvSeqPush(filtedhullseq,data);

        ;
    }
    return filtedhullseq;
}
CvSeq *reghand::filthull2(CvSeq *filted_elimhull)
{
    //CvSeq *filtedhullseq=cvCloneSeq(filted_elimhull);
    float maxdis=0;CvPoint **fingpt;CvScalar mean,std=cvScalarAll(0);
    CvMat *dismat=cvCreateMat(1,filted_elimhull->total,CV_32FC1);
    CvPoint2D32f center=minrect.center;
    for (int i=0;i<filted_elimhull->total;i++)
    {
        CvPoint **data=CV_GET_SEQ_ELEM(CvPoint*,filted_elimhull,i);
        CvPoint pt=**data;
        float dis=sqrt(pow(pt.x-center.x,2)+pow(pt.y-center.y,2));
        dismat->data.fl[i]=dis;
        if(dis>maxdis){maxdis=dis;fingpt=data;}
    }
    cvAvgSdv(dismat,&mean,&std);
    if(filted_elimhull->total==1&&maxdis>fingerTh*0.5) return filted_elimhull;
    if(filted_elimhull->total==2&&maxdis>fingerTh*0.5&&std.val[0]<10)
    {
        CvPoint startpt=**CV_GET_SEQ_ELEM(CvPoint*,filted_elimhull,0);
        CvPoint endpt=**CV_GET_SEQ_ELEM(CvPoint*,filted_elimhull,1);;
        double bfang=atan(double(startpt.y-handcenter.y)/(startpt.x-handcenter.x))*180/PI;
        if(bfang<0)bfang+=180;
        double afang=atan(double(endpt.y-handcenter.y)/(endpt.x-handcenter.x))*180/PI;
        if(afang<0)afang+=180;
        if(fabs(bfang-afang)>60)
        {cvClearSeq(filted_elimhull);cvSeqPush(filted_elimhull,fingpt);return filted_elimhull;}
        else	return filted_elimhull;
    }
    cvClearSeq(filted_elimhull);
    if(maxdis>fingerTh*0.5&&std.val[0]>13)
        cvSeqPush(filted_elimhull,fingpt);
    return filted_elimhull;

}
int reghand::regnition(CvSeq *hangcontour)
{
    //	cvDrawContours(imageContour,bigcontour,cvScalar(255),cvScalar(255),0);
    IplImage *imageContour=cvCreateImage(cvSize(640,480),8,1);
    cvZero(imageContour);
    CvSeq *bigcontour=hangcontour;
    CvMemStorage *storage1 = cvCreateMemStorage(0);
    CvSeq *approxContour=cvApproxPoly(bigcontour,sizeof(CvContour),storage1, CV_POLY_APPROX_DP,10);
    bigcontour=approxContour;
    /// draw polygon
    cvDrawContours(imageContour,bigcontour,cvScalar(255),cvScalar(255),0);
    minrect=cvMinAreaRect2(bigcontour);
    if (minrect.size.height<minrect.size.width)
    {handradis=cvRound(minrect.size.height/2);fingerTh=minrect.size.width;}
    else
    {handradis=cvRound(minrect.size.width/2);fingerTh=minrect.size.height;}
    handcenter.x=minrect.center.x;
    handcenter.y=minrect.center.y+handradis*2/3;
    CvSeq *hullseq=cvConvexHull2(bigcontour,0,CV_CLOCKWISE,0);
    CvSeq *filtedhull=filthull(hullseq);// filt operation
    CvSeq *filted_elimhull=elimNeighborHulls(filtedhull);
    CvMemStorage *storage2= cvCreateMemStorage(0);
    CvSeq *defects = cvConvexityDefects(bigcontour,filted_elimhull, storage2);
    CvConvexityDefect *defectArray= (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*defects->total);
    cvCvtSeqToArray(defects, defectArray, CV_WHOLE_SEQ);
    // store defects points in the convexDefects parameter.
    CvMemStorage *storage3= cvCreateMemStorage(0);
    CvSeq * defectseq=cvCreateSeq(CV_32SC2,sizeof(CvSeq),sizeof(CvPoint),storage3);
    float maxdepth=0;
    int onlydefect=0;int nn=0;
    for(int i = 0; i<defects->total; i++)
    {
        CvPoint ptf;
        ptf.x = defectArray[i].depth_point->x;
        ptf.y = defectArray[i].depth_point->y;
        if(ptf.y>handcenter.y){ defectArray[i].depth=0;nn++;}
        if(defectArray[i].depth>maxdepth)maxdepth=defectArray[i].depth;

    }
    float angth;
    if(defects->total-nn>2)angth=80;
    else angth=50;
    for(int i = 0; i<defects->total; i++)
    {
        if(defectArray[i].depth<=max<float>(maxdepth*2/3,handradis*0.6)) continue;

        CvPoint startpt=*defectArray[i].start;
        CvPoint endpt=*defectArray[i].end;
        double bfang=atan(double(startpt.y-handcenter.y)/(startpt.x-handcenter.x))*180/PI;
        if(bfang<0)bfang+=180;
        double afang=atan(double(endpt.y-handcenter.y)/(endpt.x-handcenter.x))*180/PI;
        if(afang<0)afang+=180;
        if(fabs(bfang-afang)>angth) continue;
        CvPoint ptf;
        ptf.x = defectArray[i].depth_point->x;
        ptf.y = defectArray[i].depth_point->y;
        onlydefect=i;
        cvSeqPush(defectseq,&ptf);
    }
    cvCircle(imageContour, handcenter, 2, cvScalarAll(255), 5, 8,0);

    if(!defectseq->total&&filted_elimhull->total)
        filted_elimhull=filthull2(filted_elimhull);

    for ( int i=0; i <defectseq->total; i++)
        cvCircle(imageContour, *((CvPoint*)(cvGetSeqElem(defectseq,i))),2, cvScalarAll(255), 2, 8, 0);
    //   cvCircle(imageContour, *((CvPoint*)(cvGetSeqElem(resultdefect,i))),2, color, 2, 8, 0);
    for ( int i=0; i<filted_elimhull->total; i++)
    {
        CvPoint pt=**CV_GET_SEQ_ELEM(CvPoint*,filted_elimhull,i);
        //CvPoint pt=*((CvPoint*)(cvGetSeqElem(resulthull,i)));
        cvCircle(imageContour,  pt, 4, cvScalarAll(255), 1, 8, 0);
    }

    //get result
    int result;
    if(defectseq->total) result=defectseq->total+1;
    else result=filted_elimhull->total;
    cvReleaseMemStorage(&storage1);
    cvReleaseMemStorage(&storage2);
    cvReleaseMemStorage(&storage3);
    while(cvWaitKey(0)==27) break;
    return result;
}


