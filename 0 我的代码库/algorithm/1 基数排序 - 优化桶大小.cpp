#include <iostream>
#include <time.h>
#include <algorithm>

#define MAXN 1<<27
#define MIN 0
#define MAX 100000
#define BUCKET_SIZE 1024
using namespace std;

int wh_array[MAXN];

void generate();
int maxbit(int data[], int n); //辅助函数，求数据的最大位数
void radixsort(int data[], int n);

int main()
{
	int N = MAXN;
	srand((unsigned) time(NULL));
	generate();

	clock_t start, end;
	start = clock();

	radixsort(wh_array,N);

	end = clock();
	cout<<"Run time: "<<(double)(end - start)<<"ms"<<endl;
	system("pause");
	return 0;
}

void generate()
{
	for (int i=0;i<MAXN;i++)
		wh_array[i] = rand()% (MAX + 1 - MIN) + MIN;
}

int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
	int d = 1; //保存最大的位数
	int p = BUCKET_SIZE;
	for(int i = 0; i < n; ++i)
	{
		while(data[i] >= p)
		{
			p *= BUCKET_SIZE;
			++d;
		}
	}
	return d;
}

void radixsort(int data[], int n) //基数排序
{
	int d = maxbit(data, n);
	int *tmp = new int[n];
	int *count = new int[BUCKET_SIZE]; //计数器
	int i, j, k;
	int radix = 1;
	for(i = 1; i <= d; i++) //进行d次排序
	{
		for(j = 0; j < BUCKET_SIZE; j++)
			count[j] = 0; //init 计数器

		for(j = 0; j < n; j++)
		{
			k = (data[j] / radix) % BUCKET_SIZE; //统计每个桶中的记录数
			count[k]++;
		}

		for(j = 1; j < BUCKET_SIZE; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶

		for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % BUCKET_SIZE;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}

		for(j = 0; j < n; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];

		radix = radix * BUCKET_SIZE;
	}
	delete[]tmp;
	delete[]count;
}
