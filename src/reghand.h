#ifndef REGHAND
#define REGHAND
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#define PI 3.1415926;
using namespace std;
using namespace cv;

class reghand
{
public:
    reghand();
    ~reghand();
public :
    int regnition(CvSeq *hangcontour);
    CvPoint handcenter;float handradis;CvBox2D minrect;float fingerTh=0;
    CvSeq * elimNeighborHulls(CvSeq *hullseq);
    CvSeq * filthull2(CvSeq *filted_elimhull);
    CvSeq *filthull(CvSeq *hullseq);
};
#endif // REGHAND

