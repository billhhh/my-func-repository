#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
using namespace std;

int main()
{
	/** 打开输入视频文件 */
	cv::VideoCapture vc;
	vc.open( "./4.mp4" );

	if ( vc.isOpened() )
	{
		/** 打开输出视频文件 */
		cv::VideoWriter vw;
		vw.open( "./output.avi", // 输出视频文件名
			-1, // 也可设为CV_FOURCC_PROMPT，在运行时选取
			25.0, // 视频帧率
			cv::Size( (int)vc.get( CV_CAP_PROP_FRAME_WIDTH ), (int)vc.get( CV_CAP_PROP_FRAME_HEIGHT ) ), // 视频大小
			true ); // 是否输出彩色视频

		/** 如果成功打开输出视频文件 */
		if ( vw.isOpened() )
		{
			while ( true )
			{
				/** 读取当前视频帧 */
				cv::Mat frame;
				vc >> frame;

				/** 若视频读取完毕，跳出循环 */
				if ( frame.empty() )
				{
					break;
				}

				/** 将视频写入文件 */
				vw << frame;
			}
		}
	}

	/** 手动释放视频捕获资源 */
	vc.release();

	return 0;
}
