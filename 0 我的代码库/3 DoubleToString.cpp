string DoubleToString(double d)
{
	char buffer[1024];
	sprintf(buffer,"%f\0",d);
	string str(buffer);
	return str;
}