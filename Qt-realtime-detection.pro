#-------------------------------------------------
#
# Project created by QtCreator 2018-10-16T10:06:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-realtime-detection
TEMPLATE = app
CONFIG += console c++11



SOURCES += main.cpp\
        mainwindow.cpp \
    global.cpp \
    darknet.c \
    detector.c \
    image.c \
    network.c \
    yolo_layer.c \
    Camerathread.cpp \
    GrabThread.cpp

HEADERS  += mainwindow.h \
    global.h \
    darknet.h \
    Camerathread.h \
    GrabThread.h




 INCLUDEPATH += /usr/include/opencv/
 INCLUDEPATH += /usr/include/opencv2/
 INCLUDEPATH += /usr/local/cuda/include/

 LIBS +=    -L/usr/lib/    \
    -lopencv_core  \
    -lopencv_imgproc   \
    -lopencv_ml \
    -lopencv_photo  \
    -lopencv_tegra  \
    -lopencv_video  \
    -lopencv_vstab  \
    -lopencv_legacy \
    -lopencv_core   \
    -lopencv_flann  \
    -lopencv_calib3d    \
    -lopencv_contrib    \
    -lopencv_gpu    \
    -lopencv_detection_based_tracker    \
    -lopencv_highgui    \
    -lopencv_imgproc    \
    -lopencv_imuvstab   \
    -lopencv_superres   \
    -lopencv_objdetect  \
    -lopencv_facedetect \
    -lopencv_features2d \
    -lopencv_esm_panorama   \
    -lopencv_stitching  \
    -lopencv_videostab  \
    -lopencv_highgui

 LIBS +=    -L/home/ubuntu/darknet/    \
    -ldarknet


 LIBS +=     -L/lib/aarch64-linux-gnu/   \
    -lpthread

 LIBS +=    -L/usr/lib/aarch64-linux-gnu/   \
    -lcudnn

 LIBS +=    -L/usr/local/cuda/lib64/    \
    -lcuda  \
    -lcudart    \
    -lcublas    \
    -lcurand

 LIBS +=    -L/home/ubuntu/Qt/Qt-realtime-detection/  \
    -lblas_kernels

