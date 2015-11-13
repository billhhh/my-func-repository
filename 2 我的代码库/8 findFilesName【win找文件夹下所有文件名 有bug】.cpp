#include <afx.h>

void findFilesName(CString path)
{
	CFileFind finder;
	bool bResult =finder.FindFile(path+"\\*.*");
	while(bResult ){
		bResult =finder.FindNextFile();//读取下一个文件
		cout<<(LPCTSTR)finder.GetFileName()<<"\n";
	}
	finder.Close();
}