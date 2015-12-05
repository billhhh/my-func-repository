#include "stdafx.h"
#include "TraversingFile.h"
#include <algorithm>
#include <iterator>
using namespace std;

TraversingFile::TraversingFile(void)
{
	FindData;
	hError;
	fileCount = 0;
}


TraversingFile::~TraversingFile(void)
{
}
//含有特殊字符
bool IsNumOrChar(char ch)
{
	if ((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return true;
	}else
		return false;
}
//含有特殊字符
bool IsNotNumOrChar(char ch)
{
	if ((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return false;
	}else
		return true;
}
// 初始化，传入要遍历的目录
int TraversingFile::Init(string path,string suffix)
{
	fileCount = 0;
	//后缀名合法性判断
	string::iterator first;
	first = std::find_if(suffix.begin(),suffix.end(),IsNotNumOrChar);
	if (first != suffix.end())
	{
		//后缀名中含有非法字符
		return -1;
	}
	//构造文件名
	strcpy_s(FilePathName, path.c_str());
	if (path[path.length()-1] != '\\'&&path[path.length()-1] != '/')
	{
		strcat_s(FilePathName, "\\*.");
	}else
	{
		strcat_s(FilePathName, "*.");
		path = path.substr(0,path.length()-1);
	}
	strcat_s(FilePathName, suffix.c_str());
	this->path = path;
	this->suffix = suffix;
	return 0;
}


// 获得要遍历路径下的一个文件名
int TraversingFile::GetFileName(string& filename)
{
	//未初始化？
	if (suffix.length() == 0)
	{
		return -1;
	}
	//第一个文件?
	if (fileCount == 0)
	{
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE)
		{
			return -2;
		}
	}else{
		if (::FindNextFile(hError, &FindData))
		{
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0 )
			{
				return GetFileName(filename);
			}
		}else
		{
			//遍历完毕
			return 1;
		}
	}
	// 构造完整路径
	wsprintf(FullPathName, "%s\\%s", path.c_str(),FindData.cFileName);
	filename = FullPathName;
	fileCount++;
	return 0;
}
int TraversingFile::GetFileLsit(vector<string> &filelist)
{
	string filename;
	int rt_val;
	while (1)
	{
		rt_val = GetFileName(filename);
		if(rt_val == 0)
			filelist.push_back(filename);
		else if(rt_val ==1)
			return 0;
		else
			return -1;
	}
}
int TraversingFile::GetFileLsitForMultisuffix(string path,const string suffixWithComma,vector<string> &filelist){
	int start = 0,end = 0;
	while(1){
		end = suffixWithComma.find_first_of(',',start);
		if(end<0)
			end = suffixWithComma.length();
		suffix = suffixWithComma.substr(start,end-start);
		start = end+1;
		Init(path,suffix);
		vector<string> filelistTmp;

		GetFileLsit(filelistTmp);
		for(int i=0;i<filelistTmp.size(); ++i)
		{
			filelist.push_back(filelistTmp[i]);
		}
		if(start>suffixWithComma.length())
			break;
	}
	return 0;
}