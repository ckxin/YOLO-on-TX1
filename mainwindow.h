#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <Camerathread.h>
#include <GrabThread.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QLabel *TimeLabel;
    QLabel *CameraLabel;
    QLabel *ImgLabel;
    QLabel *DataLabel;
    QLabel *DataLabel1;

    QPushButton *CameraBtn;
    QPushButton *GrabBtn;
    QPushButton *ReImgshowBtn;
    QPushButton *ShutdownBtn;


    QHBoxLayout *TopLayout;
    QHBoxLayout *CameraLayout;
    QHBoxLayout *ImgLayout;
    QHBoxLayout *MiddleLayout1;
    QHBoxLayout *MiddleLayout2;
    QHBoxLayout *BottomLayout;

    Camerathread *Camerath;
    GrabThread *Grabth;


signals:
    void Imgshow(const QString &name);


public slots:
    void timerUpdate(void);
    void slotCamera();
    void slotGrab();
    void slotVideo();
    void slotImgshow();
    void slotGrabthread();
    void slotReImgshow();
private slots:
    void on_ShutdownBtn_clicked();



};

#endif // MAINWINDOW_H
