//辅助函数，求一个数组中数据的最大位数
int maxbit(int data[], int n)
{
	int d = 1; //保存最大的位数
	int p = 10;
	for(int i = 0; i < n; ++i)
	{
		while(data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}