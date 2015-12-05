#pragma once
#include <windows.h>
#include <string>
#include <vector>
using namespace std;
#define PATH_MAX_LENGTH 1024
class TraversingFile
{
protected:
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	int fileCount;
	char FilePathName[PATH_MAX_LENGTH];
	// 构造路径
	char FullPathName[PATH_MAX_LENGTH];
	//遍历路径
	string path;
	//后缀名
	string suffix;
public:
	TraversingFile(void);
	~TraversingFile(void);
	// 初始化，传入要遍历的目录
	int Init(string path,string suffix);
	// 获得要遍历路径下的一个文件名
	int GetFileName(string& filename);
	// 获得文件列表
	int GetFileLsit(vector<string> &filelist);
	// 获得多种后缀的文件列表
	int GetFileLsitForMultisuffix(string path,const string suffixWithComma,vector<string> &filelist);
};

