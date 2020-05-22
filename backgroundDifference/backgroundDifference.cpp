#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	VideoCapture cap(0);

	//如果摄像头打开失败
	if (!cap.isOpened())
	{
		std::cout << "Fail to open camera" << std::endl;
		return -1;
	}

	int cnt = 0;

	cv::Mat frame;
	cv::Mat bgMat;
	cv::Mat subMat;
	cv::Mat bny_subMat;


	while (1)
	{
		cap >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0)
		{
			//第一帧，获得背景图像
			frame.copyTo(bgMat);
		}
		else
		{
			//第二帧开始背景差分
			absdiff(frame, bgMat, subMat);
			//差分结果二值化
			threshold(subMat, bny_subMat, 20, 255, CV_THRESH_BINARY);

			cv::imshow("b_subMat", bny_subMat);
			cv::imshow("frame", frame);
			waitKey(30);
		}
		cnt++;
	}
	return 0;
}


