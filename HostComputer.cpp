#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>

using namespace cv;
using namespace std;



int main(void)
{

	HANDLE hCom;//全局变量，串口句柄
	hCom = CreateFile(_T("COM3"),//COM3口
		GENERIC_READ | GENERIC_WRITE,//允许读和写
		0,//独占方式
		NULL,
		OPEN_EXISTING,//打开而不是创建
		0,//同步方式
		//FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERAPPLE,//重叠方式
		NULL);
	if (hCom == (HANDLE)-1)
	{
		printf("打开COM失败！");
		return 0;
	}
	SetupComm(hCom, 20480, 20480);//输入缓冲区和输出缓冲区的大小都是20480
	COMMTIMEOUTS TimeOuts;
	//设定读超时
	TimeOuts.ReadIntervalTimeout = 1000;
	TimeOuts.ReadTotalTimeoutMultiplier = 500;
	TimeOuts.ReadTotalTimeoutConstant = 5000;
	//设定写超时
	TimeOuts.WriteTotalTimeoutMultiplier = 500;
	TimeOuts.WriteTotalTimeoutConstant = 2000;
	SetCommTimeouts(hCom, &TimeOuts);//设置超时
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 115200;//波特率为115200
	dcb.ByteSize = 8;//每个字节有8位
	dcb.Parity = NOPARITY;//无奇偶校验位
	dcb.StopBits = TWOSTOPBITS;//两个停止位
	dcb.fParity = FALSE;
	dcb.fNull = FALSE;
	SetCommState(hCom, &dcb);
	PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//在读写串口之前清空缓冲区
	short int MessageLen = 20;//数据头：数据长度，不包括数据头和校验位
	unsigned char result[1] = { 5 };//写入串口缓存区的数组
	DWORD dwwrittenLen = 0;


	//配置摄像头
	VideoCapture capture(1);//打开摄像头  
	if (!capture.isOpened())//没有打开摄像头的话，就返回。
		return 0;
	Mat edges, edges1; //定义一个Mat变量，用于存储每一帧的图像
//【2】循环显示每一帧  
	cv::Rect m_select;

	m_select.width = abs(130);//算矩形宽度和高度
	m_select.height = abs(70);
	//m_select &= cv::Rect(0, 0, img.cols, img.rows);//保证所选矩形框在视频显示区域之内
	bool stop = false;
	long sum = 0, avr = 0;
	int r, c;
	while (!stop)
	{
		                        
		if (frame.empty())
		{
			break;
		}
		else
		{
			/*result[0] = { 5 };
			WriteFile(hCom, result, 24, &dwwrittenLen, NULL);*/
			Mat frame; //定义一个Mat变量，用于存储每一帧的图像  
		        
			// col 4:
			capture >> frame;  //读取当前帧  
			cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
			threshold(edges, edges, 150, 255.0, CV_THRESH_BINARY);
			m_select.x = 165;//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
			m_select.y = 50;
			

			cv::rectangle(edges, m_select, cv::Scalar(255, 128, 128), 2, 8, 0);  // 画矩形框
			imshow("Video", edges); //显示当前帧
			for (r = 50; r < 120; r++)
			{
				for (c = 165; c < 295; c++)
				{
					sum += edges.at<uchar>(r, c);
				}
			}
			avr = sum / 9100;
			if (avr < 50)
			{
			result[0] = { 5 };
			WriteFile(hCom, result, 24, &dwwrittenLen, NULL);
                        waitKey(100);
			}
			avr = 0;
			sum = 0;




			//col 3:
                        capture >> frame;  //读取当前帧  
			cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
			threshold(edges, edges, 150, 255.0, CV_THRESH_BINARY);
			m_select.x = 165;//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
			m_select.y = 140;
			cv::rectangle(edges, m_select, cv::Scalar(255, 128, 128), 2, 8, 0);  // 画矩形框
			imshow("Video", edges); //显示当前帧
			for (r = 140; r < 210; r++)
			{
				for (c = 165; c < 295; c++)
				{
					sum += edges.at<uchar>(r, c);
				}
			}
			avr = sum / 9100;
			if (avr < 50)
			{
				result[0] = { 4 };
				WriteFile(hCom, result, 24, &dwwrittenLen, NULL);

			}
				avr = 0;
				sum = 0;
			//col 2:
                        capture >> frame;  //读取当前帧  
			cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
			threshold(edges, edges, 150, 255.0, CV_THRESH_BINARY);
			m_select.x = 165;//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
			m_select.y = 230;
			cv::rectangle(edges, m_select, cv::Scalar(255, 128, 128), 2, 8, 0);  // 画矩形框
			imshow("Video", edges); //显示当前帧
			for (r = 230; r < 300; r++)
			{
				for (c = 165; c < 295; c++)
				{
					sum += edges.at<uchar>(r, c);
				}
			}
			avr = sum / 9100;
			printf("%d\n",avr);
			if(avr < 50)
			{
				result[0] = { 3 };
				WriteFile(hCom, result, 24, &dwwrittenLen, NULL);
                                waitKey(100);
			}
				avr = 0;
				sum = 0;
			//col 1:
                        capture >> frame;  //读取当前帧  
			cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
			threshold(edges, edges, 150, 255.0, CV_THRESH_BINARY);
			m_select.x = 165;//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
			m_select.y = 320;
			cv::rectangle(edges, m_select, cv::Scalar(255, 128, 128), 2, 8, 0);  // 画矩形框
			imshow("Video", edges); //显示当前帧
			for (r = 320; r < 390; r++)
			{
				for (c = 165; c < 295; c++)
				{
					sum += edges.at<uchar>(r, c);
				}
			}
			avr = sum / 9100;
			if(avr < 50)
			{
				result[0] = { 2 };
				WriteFile(hCom, result, 24, &dwwrittenLen, NULL);
                                waitKey(100);
			}
			avr = 0;
			sum = 0;
		}
		
			waitKey(10); //延时30ms  
		}




		// result[0] = { 5 };
		 //WriteFile(hCom, result, 24, &dwwrittenLen, NULL);
		 //printf("Main Baseline往串口发送数据成功\n");





		CloseHandle(hCom);

	}
