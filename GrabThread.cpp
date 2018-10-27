#include "GrabThread.h"
#include <QtDebug>
#include "mainwindow.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <global.h>

using namespace std;
using namespace cv;


GrabThread::GrabThread()
{

}

void GrabThread::run()

{
    CvFont font;
    cvInitFont(&font,CV_FONT_HERSHEY_PLAIN,1.5f,1.5f,0,2,CV_AA);
    char coordinate[256];
    while(1)
    {
        if(ifframe)
        {
            grabframe=frame.clone();
            imwrite("/home/ubuntu/Qt/Qt-realtime-detection/Grab/grabframe.jpg",grabframe);
            grabwrite=1;
            ifframe=false;
            while(1)
            {
                if(ifcoordinate==1)
                {

                    sprintf(coordinate,"grab coor: x11= %i,y11= %i,x12= %i,y12= %i \n",x11,y11,x12,y12);
                    strcat(labelshowstr,coordinate);
                    bzero(coordinate,sizeof(coordinate));
                    rectangle(grabframe,cvPoint(grabx11,graby11),cvPoint(grabx12,graby12),Scalar(255,0,0),3,1,0);
                    IplImage temp = grabframe; //转化为CvMat类型，而不是复制数据
                    IplImage *frame1 = cvCloneImage(&temp);
                    if(graby11-10 > 0)
                    {
                        cvPutText(frame1,grabstr,cvPoint(grabx11,graby11-10),&font,Scalar(255,0,0));
                    }
                    else
                    {
                        cvPutText(frame1,grabstr,cvPoint(grabx11,graby11+10),&font,Scalar(255,0,0));
                    }

                    grabx11=0;graby11=0;grabx12=0;graby12=0;
                    grabframe=Mat(frame1,true);
                    cvReleaseImage(&frame1);
                    memset(grabstr,0,4096);
                    ifcoordinate=0;
                    imwrite("/home/ubuntu/Qt/Qt-realtime-detection/Grab/rectgrabframe.jpg",grabframe);
                    grabframe.release();
                    emit Grab("Grab");
                    break;
                }
            }
            break;
        }

    }

}
