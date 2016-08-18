#include <iostream> 
#include "opencv2/opencv.hpp"
using namespace std; 
using namespace cv;
int main(int argc, char* argv[])
{
	//读入图像，并将之转为单通道图像 
	Mat im = imread("girl1.jpg", CV_LOAD_IMAGE_COLOR);
	
	//请一定检查是否成功读图 
	if( im.empty() ) {
	cout << "Can not load image." << endl; 
	return -1;
	}
	//进行Canny 操作，并将结果存于 result 
	Mat result; 
	//Canny(im, result,40,80);
	//保存结果 
	Mat gray_img;
	cvtColor(im,gray_img, CV_BGR2GRAY);
	Canny(gray_img, result, 50, 150);
	imwrite("whitebg-canny.jpg", result);
	Mat img = imread("whitebg-canny.jpg");
	Mat B = img.clone();
	
	imwrite("whitebg-gray.jpg", gray_img);
	
	Mat C = imread("whitebg-gray.jpg",0);
	//imshow("whitebg", C);
	//imshow("whitebg-origin", im);
	imshow("whitebg-canny", img);
	//waitKey(10);
	Mat M(10, 10, CV_8UC3, Scalar(0, 0, 255));
	Mat k(3, 3, CV_8UC3, Scalar(0, 0, 255));
	/*imwrite("test.jpg", M);
	imshow("test", M);
	waitKey(5000);*/

	Mat bg = imread("stage2.jpg", CV_LOAD_IMAGE_COLOR);
	uchar* p = gray_img.data;
	uchar* q = im.data;
	uchar* p_bg = bg.data;
	for (unsigned int i = 0; i < gray_img.rows*gray_img.cols; ++i)
	{
		if (*p > 230){
			*p = 255;
			*q = *p_bg;
			*(q + 1) = *(p_bg + 1);
			*(q + 2) = *(p_bg + 2);
			q += 3;
			p_bg += 3;
		}
		else {
			q += 3;
			p_bg += 3;
		}
		p++;
	}

	imshow("gray", gray_img);
	Canny(gray_img, result, 50, 150);
	imshow("canny", result);
	imshow("origin", im);
	waitKey(0);


	//cout << gray_img << endl;
	//cout << img;
	return 0;
}