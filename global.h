#ifndef GLOABLE
#define GLOABLE

#ifdef __cplusplus
#include <opencv2/opencv.hpp>
#include "darknet.h"


extern cv::Mat frame,grabframe;
extern bool writingImg,ifgrab,ifframe;
extern int flag,flag1,flag2;
//extern int grabImgnum;
extern int ifsame,grabclick,ifcoordinate,grabwrite,grabdetect;
extern int loading;
extern int x11,y11,x12,y12,diff;
extern int grabx11,graby11,grabx12,graby12;
extern char labstr[4096],grabstr[4096],labelshowstr[4096],Imglabelstr[4096];
//grabImgname[512],rectgrabImgname[512];
extern char **p;

#endif
#endif // GLOABLE

