//找出一张图片连通域边界矩形
Rect find_con_bound(Mat img)
{
	vector<vector<Point>> _contours;//储存所有轮廓
	vector<Vec4i>hierarchy;
	cv::findContours( img, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	Point a,c;
	for(size_t i = 0; i< _contours.size(); ++i)
	{
		Rect r = boundingRect(Mat(_contours[i]));

		//r.x还在a.x的左边
		if (r.x < a.x)
			a.x = r.x;
		//r.y 还在 a.y 上面
		if(r.y < a.y)
			a.y = r.y;
		//r.x+r.width 还在c.x的右边
		if ((r.x+r.width) > c.x)
			c.x = r.x+r.width;
		//(r.y+r.height) 还在 c.y 下面
		if((r.y+r.height) > c.y)
			c.y = r.y+r.height;
	}

	return Rect(a,c);
}