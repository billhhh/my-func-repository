vector<string> img_list_path;

void batFindImgName(string path)
{
	string buf;
	//读入检测样本  
	ifstream img_stream( path );  
	while( img_stream ) 
		if( getline( img_stream, buf ) ) 
			img_list_path.push_back( buf );
	img_stream.close();
}