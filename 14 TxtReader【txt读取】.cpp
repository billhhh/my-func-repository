//读取txt
bool TxtReader(string path,string content)
{
	//文件读取
	//ifstream myfile ("D:\\TESTCASE\\格式1.txt");
	ifstream myfile (path);
	string buf;
	string outStr;

	if(!myfile){
		cout << "Unable to open myfile";
		return false; // terminate with error
	}

	while (myfile)
	{
		if( getline( myfile, buf ) ){  
			outStr.append(buf);
			outStr.append("\n");
		}
	}

	content = outStr;

	return true;
}