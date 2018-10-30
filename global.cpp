#include <global.h>
#include <opencv2/opencv.hpp>

cv::Mat frame,grabframe;
bool writingImg=true,ifgrab=false,ifframe=false;
extern int flag=0,flag1=1,flag2=0;
extern int ifsame=0,grabclick=0,ifcoordinate=0,grabwrite=0,grabdetect=0;
extern int loading=0;
extern int x11=0,y11=0,x12=0,y12=0,diff=0;
extern int grabx11=0,graby11=0,grabx12=0,graby12=0;
//extern int grabImgnum=0;
extern char labstr[4096]={0},grabstr[4096]={0},labelshowstr[4096]={0},Imglabelstr[4096]={0};
//grabImgname[512]={0},rectgrabImgname[512]={0};
extern char **p;


