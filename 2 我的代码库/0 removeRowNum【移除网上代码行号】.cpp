//移除网页上下载的代码，换行后前面的行号数字
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s,tmp;
	//输入
	getline(cin,s);
	while(1)
	{
		getline(cin,tmp);
		if (tmp.size()==0) //连续输入两个回车结束
			break;

		s.append("\n");
		s.append(tmp);
	}

	for (int i=0;i<s.length();i++)
	{
		if (s.at(i) == '\n')//如果某一位是回车，则后两位去掉
			s.erase(i+1,2);
	}

	cout<<"处理后的结果为：\n";
	cout<<s<<"\n";

	system("pause");
	return 0;
}
