//按百分比截取图片
void cut_image_percent(Mat &img,double left,double upper,double right,double bottom)
{
	Point a,c;
	a.x = img.cols * left;
	a.y = img.rows * upper;
	c.x = img.cols * right;
	c.y = img.rows * bottom;
	Rect r = Rect(a,c);
	img = img(r);
}