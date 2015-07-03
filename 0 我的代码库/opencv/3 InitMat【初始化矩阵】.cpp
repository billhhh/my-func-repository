//用一个常数来初始化矩阵
void InitMat(Mat& m,float t)
{
    for(int i=0;i<m.rows;i++)
	for(int j=0;j<m.cols;j++)
	   m.at<float>(i,j)=t;
}


int _tmain(int argc, _TCHAR* argv[])
{
   //Mat矩阵中的初始化，可以利用Mat：：at()来完成
   Mat M0(3,3,CV_32F);
   InitMat(M0,3);
}