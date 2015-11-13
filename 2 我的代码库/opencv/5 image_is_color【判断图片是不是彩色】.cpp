//判断一幅图像是否是彩色图像
bool image_is_color(Mat image,bool& is_color)
{
	if(!image.data)
		return false;

	int row = image.rows;
	int col = image.cols;
	isColor = false;
	for(int i = 0; i < row;i++)
		for(int j = 0; j< col;j++)
			if (  ((int)(image.at<Vec3b>(i,j)[0]) != (int)(image.at<Vec3b>(i,j)[1]))
				||((int)(image.at<Vec3b>(i,j)[1]) != (int)(image.at<Vec3b>(i,j)[2]))
				||((int)(image.at<Vec3b>(i,j)[2]) != (int)(image.at<Vec3b>(i,j)[0]))
			   )
			{
				//是彩色视频
				is_color=true;
				return true;
			}

	return true;
}