#include "Camerathread.h"
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


Camerathread::Camerathread()
{

}

void Camerathread::run()

{
    VideoCapture cap("rtsp://admin:12345678xin@172.168.1.64/h264/ch1/main/av_stream");


        for(;;)
        {
            if (!cap.isOpened())
            {
                cerr << "ERROR! Unable to open camera\n";
                cout << "open fail" << endl;
                break;

            }
            cap.read(frame);
            if (frame.empty())
            {
                cerr << "ERROR! blank frame grabbed\n";
                cout << "frame is empty" << endl;
                continue;
            }
            else
            {

                 //writingImg = true;

                 cap >> frame;
                 ifframe=true;
                 //writingImg = false;
                 emit show("show");
            }

            if(flag1==1)
            {
                imwrite("/home/ubuntu/Documents/test.jpg",frame);
                flag=1;
                flag1=0;
            }


        }

}
