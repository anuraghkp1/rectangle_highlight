#include<napi.h>
#include <iostream>
#include <opencv2/opencv.hpp>
namespace draw{
    bool draw(std::string path,std::string outpath,double x,double y,double x2,double y2,int r,int g,int b,Napi::Env env);
    Napi::Boolean HocrWrapper(const Napi::CallbackInfo &info);
    Napi::Object Init(Napi::Env env,Napi::Object exports);
    void hough_transform(cv::Mat& im, cv::Mat& orig, double* skew);
}