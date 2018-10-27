#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <iostream>
#include <QDesktopWidget>
#include <QScreen>
#include <QApplication>
#include <global.h>
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <fstream>
#include <cstdio>
#include <string>
#include "darknet.h"
#include "image.h"
#include <pthread.h>
#include <thread>
#include "global.h"

using namespace std;

int t1()
{
    char *p[]={"/home/ubuntu/Qt/build-Qt-realtime-detection-TX1-Debug/Qt-realtime-detection","detector","test","/home/ubuntu/darknet/cfg/meter01.data","/home/ubuntu/Documents/yolov3-voccopy.cfg","/home/ubuntu/darknet/yolov3-voc_final.weights","/home/ubuntu/Documents/test.jpg"};
    //char *p[]={"/home/ubuntu/Qt/build-Qt-realtime-detection-TX1-Debug/Qt-realtime-detection","detector","test","/home/ubuntu/darknet/cfg/meter01.data","/home/ubuntu/Documents/yolov3-voccopy.cfg","/home/ubuntu/darknet/yolov3-voc_final.weights","/home/ubuntu/Qt/Qt-realtime-detection/Grab/grabframe.jpg"};
    darknet(7,p);
    free(p);
    return 0;
}



int main(int argc,char *argv[])
{
    QApplication a(argc, argv);
    cout << "argc=" << argc << endl;

    for(int l=0;l<argc;l++)
    {
        cout << argv[l] << endl;
    }
    MainWindow w;
    w.show();
    w.showFullScreen();

    thread th1(t1);
    th1.detach();

//    thread th2(t2);
//    th2.detach();


    //darknet(argc,argv);

    return a.exec();
}
