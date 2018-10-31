#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat img1, img;
bool select_flag = false;
cv::Rect m_select;
cv::Point origin;
int ROI_count;

void onMouseRectPicking(int event, int x, int y, int, void*)
{
	if (select_flag)
	{
		m_select.x = MIN(origin.x, 2);//��һ��Ҫ����굯��ż�����ο򣬶�Ӧ������갴�¿�ʼ���������ʱ��ʵʱ������ѡ���ο�
		m_select.y = MIN(origin.y, 2);
		m_select.width = abs(10);//����ο�Ⱥ͸߶�
		m_select.height = abs(10);
		m_select &= cv::Rect(0, 0, img.cols, img.rows);//��֤��ѡ���ο�����Ƶ��ʾ����֮��
	}
	/*if (event == CV_EVENT_LBUTTONDOWN)
	{
		select_flag = true;          //��갴�µı�־����ֵ
		origin = cv::Point(x, y);  //��������������׽���ĵ�
		m_select = cv::Rect(x, y, 0, 0);  //����һ��Ҫ��ʼ������͸�Ϊ(0,0)����Ϊ��opencv��Rect���ο����ڵĵ��ǰ������Ͻ��Ǹ���ģ����ǲ������½��Ǹ��� 
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		select_flag = false;
		ROI_count++;
	}*/
}

int main(int argc, char* argv[])
{

	img1 = imread("DSC_0966.JPG", 0);
	img = img1.clone();
	threshold(img1, img, 127, 255.0, CV_THRESH_BINARY);
	bool stop = false;

	cv::namedWindow("capframe", CV_WINDOW_AUTOSIZE);
	cv::setMouseCallback("capframe", onMouseRectPicking, 0);

	char pic_name[40];
	ROI_count = 0;

	while (!stop)
	{
		img1 = imread("DSC_0966.JPG", 0);
		img = img1.clone();
		threshold(img1, img, 127, 255.0, CV_THRESH_BINARY);


		cv::rectangle(img, m_select, cv::Scalar(255, 0, 0), 2, 8, 0);  // �����ο�
		cv::imshow("capframe", img);



		if ((m_select.x != 0) && (m_select.y != 0) && (m_select.width != 0) && (m_select.height != 0))
		{
			sprintf_s(pic_name, "ROI_%d.jpg", ROI_count);
			Mat ROI = img(m_select);
			imshow("ROI_WIN", ROI);
			imwrite(pic_name, ROI);
		}


		char key = cv::waitKey(30);
		if (key == 27)
			stop = true;
	}
	waitKey(0);
	return 0;
}