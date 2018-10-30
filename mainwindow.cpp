#include "mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QWidget>
#include <QSizePolicy>
#include <iostream>
#include <QDesktopWidget>
#include <QScreen>
#include <QApplication>
#include <QTimer>
#include <qdatetime.h>
#include <Camerathread.h>
#include <GrabThread.h>
#include <unistd.h>
#include <global.h>
#include <opencv2/opencv.hpp>
#include <QPixmap>
#include <qfont.h>

using namespace std;
using namespace cv;


Mat Imgframe;
char coordinatestr[256]={0};
char infostr[4096]={0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int g_nActScreenW = screenRect.width();
    int g_nActScreenH = screenRect.height();

    cout <<"width="<<g_nActScreenW<<endl;
    cout <<"height="<<g_nActScreenH<<endl;


    TimeLabel = new QLabel;
    int h0=g_nActScreenH*0.035;
    int w0=g_nActScreenW*0.98;

    TimeLabel->setFixedHeight(h0);
    TimeLabel->setFixedWidth(w0);
    TimeLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    TimeLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    TimeLabel->setAlignment(Qt::AlignRight);

    TopLayout = new QHBoxLayout;
    TopLayout->addWidget(TimeLabel);
    int M_w0=g_nActScreenW*0.005;
    int M_h0=g_nActScreenH*0.02125;
    TopLayout->setContentsMargins(M_w0,M_h0,M_w0,M_h0);



    CameraLabel = new QLabel;
    CameraLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    int w1=g_nActScreenW*0.48;
    int h1=(w1/16)*9;
    CameraLabel->setFixedHeight(h1);
    CameraLabel->setFixedWidth(w1);

    CameraLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    CameraLabel->setScaledContents(true);

    ImgLabel = new QLabel;
    ImgLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    ImgLabel->setFixedHeight(h1);
    ImgLabel->setFixedWidth(w1);
    ImgLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ImgLabel->setScaledContents(true);


    MiddleLayout1 = new QHBoxLayout;


    MiddleLayout1->addWidget(ImgLabel);
    MiddleLayout1->addWidget(CameraLabel);

    MiddleLayout1->setContentsMargins(M_w0,M_h0,M_w0,M_h0);
    int Space=g_nActScreenW*0.02;
    MiddleLayout1->setSpacing(Space);

    DataLabel = new QLabel;
    DataLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    int w2=g_nActScreenW*0.48;
    //int h2=g_nActScreenH*0.035;
    int h2=g_nActScreenH*0.075;
    DataLabel->setFixedHeight(h2);
    DataLabel->setFixedWidth(w2);
    DataLabel->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    DataLabel1 = new QLabel;
    DataLabel1->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    int w3=g_nActScreenW*0.48;
    int h3=g_nActScreenH*0.035;
    //int h3=g_nActScreenH*0.075;
    DataLabel1->setFixedHeight(h3);
    DataLabel1->setFixedWidth(w3);
    DataLabel1->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    MiddleLayout2 = new QHBoxLayout;
    MiddleLayout2->addWidget(DataLabel);
    MiddleLayout2->addWidget(DataLabel1);
    MiddleLayout2->setContentsMargins(M_w0,M_h0,M_w0,M_h0);
    int Space1=g_nActScreenW*0.02;
    MiddleLayout2->setSpacing(Space1);



    int w4=g_nActScreenW*0.2;
    //int h4=g_nActScreenH*0.2;
    int h4=g_nActScreenH*0.16;
    CameraBtn = new QPushButton("Camera");
    CameraBtn->setFixedHeight(h4);
    CameraBtn->setFixedWidth(w4);
    CameraBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    CameraBtn->setFont(QFont("Times",20,QFont::Bold));
    //CameraBtn->setStyleSheet("background-color:rgb(255,10,10)");

    GrabBtn = new QPushButton("Grab");
    GrabBtn->setFixedHeight(h4);
    GrabBtn->setFixedWidth(w4);
    GrabBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    GrabBtn->setFont(QFont("Times",20,QFont::Bold));

    ReImgshowBtn = new QPushButton("ReImgshow");
    ReImgshowBtn->setFixedHeight(h4);
    ReImgshowBtn->setFixedWidth(w4);
    ReImgshowBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ReImgshowBtn->setFont(QFont("Times",20,QFont::Bold));

    ShutdownBtn = new QPushButton("Shutdown");
    ShutdownBtn->setFixedHeight(h4);
    ShutdownBtn->setFixedWidth(w4);
    ShutdownBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ShutdownBtn->setFont(QFont("Times",20,QFont::Bold));



    BottomLayout= new QHBoxLayout;
    BottomLayout->addWidget(CameraBtn);
    BottomLayout->addWidget(GrabBtn);
    BottomLayout->addWidget(ReImgshowBtn);
    BottomLayout->addWidget(ShutdownBtn);
    BottomLayout->setContentsMargins(M_w0,M_h0,M_w0,M_h0);
    int Space2=g_nActScreenW*0.06;
    BottomLayout->setSpacing(Space2);


    QWidget *centerWindow = new QWidget;
    this->setCentralWidget(centerWindow);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    centerWindow->setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(MiddleLayout1);
    mainLayout->addLayout(MiddleLayout2);
    mainLayout->addLayout(BottomLayout);
    mainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);


    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
    connect(CameraBtn,SIGNAL(clicked()),this,SLOT(slotCamera()));
    connect(GrabBtn,SIGNAL(clicked()),this,SLOT(slotGrabthread()));
    connect(ReImgshowBtn,SIGNAL(clicked()),this,SLOT(slotReImgshow()));
    connect(ShutdownBtn,SIGNAL(clicked()),this,SLOT(on_ShutdownBtn_clicked()));


}

MainWindow::~MainWindow()
{

}


void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    TimeLabel->setText(str);
}

void MainWindow::on_ShutdownBtn_clicked()
{
    system("shutdown -h now");
}


void MainWindow::slotCamera()
{
    if(loading == 0)
    {
        QPixmap pixmap("/home/ubuntu/Qt/Qt-realtime-detection/Camera/Camera.jpg");
        CameraLabel->setPixmap(pixmap);
        CameraLabel->show();
    }
    Camerath=new Camerathread();
    connect(Camerath,SIGNAL(show(const QString)),this,SLOT(slotVideo()));
    Camerath ->start();
    CameraBtn ->setEnabled(false);
}

void MainWindow::slotVideo()
{

    if(loading == 0)
    {
        while(1)
        {
            if(loading == 1)
                break;
        }
    }

    Mat Rgb,showframe;
    QImage Img;
    CvFont font;
    cvInitFont(&font,CV_FONT_HERSHEY_PLAIN,1.5f,1.5f,0,2,CV_AA);


    showframe=frame.clone();

    rectangle(showframe,cvPoint(x11,y11),cvPoint(x12,y12),Scalar(255,0,0),3,1,0);
    sprintf(coordinatestr,"     x11=%i,y11=%i,x12=%i,y12=%i",x11,y11,x12,y12);
    IplImage temp = showframe; //转化为CvMat类型，而不是复制数据
    IplImage *frame1 = cvCloneImage(&temp);
    cvPutText(frame1,labstr,cvPoint(x11,y11-10),&font,Scalar(255,0,0));
    showframe=Mat(frame1,true);
    cvReleaseImage(&frame1);
    writingImg=false;
    cv::cvtColor(showframe, Rgb, CV_BGR2RGB);//颜色空间转换
    showframe.release();
    strcat(infostr,labstr);
    strcat(infostr,coordinatestr);
    //bzero(labstr,sizeof(labstr));
    bzero(coordinatestr,sizeof(coordinatestr));

    if(!ifgrab)
    {
        if(diff == 4)
        {            
            diff=0;
            if(ifsame==0)
            {               
                Imgframe=Rgb;
                emit Imgshow("Imgshow");                
                connect(this,SIGNAL(Imgshow(QString)),this,SLOT(slotImgshow()),Qt::UniqueConnection);

            }
        }
    }

    Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);

    CameraLabel->setPixmap(QPixmap::fromImage(Img));
    CameraLabel->show();
    QString infoshowstr=infostr;
    DataLabel1->setText(infoshowstr);
    bzero(infostr,sizeof(infostr));

}

void MainWindow::slotGrabthread()
{
    GrabBtn ->setEnabled(false);
    grabclick=1;
    ifgrab=true;
    Grabth=new GrabThread();

    connect(Grabth,SIGNAL(Grab(const QString)),this,SLOT(slotGrab()));
    Grabth -> start();
    connect(Grabth,&QThread::finished,Grabth,&QObject::deleteLater);


}

void MainWindow::slotGrab()
{      
        QPixmap pixmap("/home/ubuntu/Qt/Qt-realtime-detection/Grab/rectgrabframe.jpg");
        ImgLabel->setPixmap(pixmap);
        ImgLabel->show();
        char ds[256]={0};
        strcat(ds,"12345");
        //DataLabel->setText(str);
        strcat(labelshowstr,ds);
        QString showstr=labelshowstr;
        //strcat(showstr,str);
        DataLabel->setText(showstr);
        //bzero(str,sizeof(str));
        bzero(labelshowstr,sizeof(labelshowstr));
        GrabBtn ->setEnabled(true);



}

void MainWindow::slotImgshow()
{
    QImage showImg;
    showImg = QImage((const uchar*)(Imgframe.data), Imgframe.cols, Imgframe.rows, Imgframe.cols * Imgframe.channels(), QImage::Format_RGB888);
    ImgLabel->setPixmap(QPixmap::fromImage(showImg));
    ImgLabel->show();
    QString showstr=Imglabelstr;
    DataLabel->setText(showstr);
    bzero(labelshowstr,sizeof(Imglabelstr));
    ifsame=1;


}


void MainWindow::slotReImgshow()
{
    diff=0;
    ifgrab=false;
}

