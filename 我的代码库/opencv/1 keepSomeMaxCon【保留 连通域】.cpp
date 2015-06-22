/**
 * src是传入二值图，n是保留前N大连通域
*/

bool keepSomeMaxCon(Mat &src, int n){
	///////// !!!findcontours不能查找位于图像边缘的点，导致边缘的点没被填充
	for(int i=0;i<src.cols;i++)
		src.at<uchar>(0,i) = src.at<uchar>(src.rows -1,i) = 0;
	for(int j=0;j<src.rows;j++)
		src.at<uchar>(j,0) = src.at<uchar>(j,src.cols -1) = 0;

	//连通域去噪，只剩下n个
	Mat temp = src.clone();
	vector<vector<Point> > contours;
	findContours(temp,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); //轮廓,函数会改变temp

	//原图连通域数量少于所要保留的连通域数量
	if(contours.size() < n)	
		return false;

	Mat srt(Size(contours.size(),1),CV_32SC1);
	for(int c=0;c<(int)contours.size();c++){
		srt.at<int>(0,c) = (int)contourArea(contours[c]);
	}
	cv::sortIdx(srt,srt,CV_SORT_EVERY_ROW + CV_SORT_DESCENDING);
	for(int i=n; i<(int)contours.size(); i++){ //只保留前n大连通域
		int idx = srt.at<int>(i);
		vector<Point> tmp = contours[idx];
		const Point* elementPoints[1] = { &tmp[0] };
		int numberOfPoints = (int)contours[idx].size();	
		fillPoly(src,elementPoints, &numberOfPoints ,1,Scalar(0,0,0));//填充单个连通域		
	}

	return true;
}
