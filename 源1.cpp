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
		m_select.x = MIN(origin.x, 2);//不一定要等鼠标弹起才计算矩形框，而应该在鼠标按下开始到弹起这段时间实时计算所选矩形框
		m_select.y = MIN(origin.y, 2);
		m_select.width = abs(10);//算矩形宽度和高度
		m_select.height = abs(10);
		m_select &= cv::Rect(0, 0, img.cols, img.rows);//保证所选矩形框在视频显示区域之内
	}
	/*if (event == CV_EVENT_LBUTTONDOWN)
	{
		select_flag = true;          //鼠标按下的标志赋真值
		origin = cv::Point(x, y);  //保存下来单击捕捉到的点
		m_select = cv::Rect(x, y, 0, 0);  //这里一定要初始化，宽和高为(0,0)是因为在opencv中Rect矩形框类内的点是包含左上角那个点的，但是不含右下角那个点 
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


		cv::rectangle(img, m_select, cv::Scalar(255, 0, 0), 2, 8, 0);  // 画矩形框
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