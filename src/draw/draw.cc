#include "draw.h"
#include<stdio.h>
using namespace cv;
bool draw::draw(std::string path,std::string outpath,double x,double y,double x2,double y2,int r,int g,int b,Napi::Env env)
{

try{

	// char y[100];
	char *path_char = new char[path.length() + 1]; 
	std::strcpy(path_char, path.c_str());
	Mat rotated=imread(path_char);
	Rect RectangleToDraw(x, y,x2-x, y2-y);
	rectangle(rotated, RectangleToDraw.tl(), RectangleToDraw.br(), Scalar(b, g, r), 2, 8, 0);
	//cvtColor(rotated,rotated,COLOR_GRAY2RGB);
	imwrite(outpath,rotated);
	rotated.release();
	return 1;
		}
		catch(cv::Exception& e){
		  const char* err_msg = e.what();
    	std::cout << "exception caught: " << err_msg << std::endl;
		Napi::Error::New(env,e.what()).ThrowAsJavaScriptException();
		return 0;
	}
}
Napi::Boolean draw::HocrWrapper(const Napi::CallbackInfo &info)
{
	try
	{
    Napi::Env env=info.Env();
    if(info.Length() < 1)
    {
        Napi::TypeError::New(env, "Path Expected").ThrowAsJavaScriptException();
    }
    Napi::String path=info[0].As<Napi::String>();
	Napi::String outpath=info[1].As<Napi::String>();
	Napi::Number x=info[2].As<Napi::Number>();
	Napi::Number y=info[3].As<Napi::Number>();
	Napi::Number x2=info[4].As<Napi::Number>();
	Napi::Number y2=info[5].As<Napi::Number>();
	Napi::Number r=info[6].As<Napi::Number>();
	Napi::Number g=info[7].As<Napi::Number>();
	Napi::Number b=info[8].As<Napi::Number>();
    return Napi::Boolean::New(env,draw::draw(path.ToString(),outpath.ToString(),x.DoubleValue(),y.DoubleValue(),x2.DoubleValue(),y2.DoubleValue(),r.Int32Value(),g.Int32Value(),b.Int32Value(),env));
		}
		catch(cv::Exception& e){
		  const char* err_msg = e.what();
    	std::cout << "exception caught: " << err_msg << std::endl;
		Napi::Error::New(info.Env(),e.what()).ThrowAsJavaScriptException();
		
	}
}
Napi::Object draw::Init(Napi::Env env,Napi::Object exports)
{
     exports.Set("draw",Napi::Function::New(env,draw::HocrWrapper));
     return exports;
}