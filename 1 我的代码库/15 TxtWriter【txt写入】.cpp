//写入txt
bool TxtWriter(string path,string content)
{
	//ofstream myfile("D:\\TESTCASE\\testout.txt",ios::out);

	ofstream myfile(path,ios::out);
	if(!myfile)
	{
		cout << "Unable to open TXT\n";
		return false;
	}

	else
	{
		myfile<<content;
		myfile.close();
	}

	return true;
}