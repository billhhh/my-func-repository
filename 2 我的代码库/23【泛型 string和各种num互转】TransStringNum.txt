/* 
* 
* funtion: stringToNum相互转化模板类
* 
* Date:2015-10-27
* 
*    Author: Bill Wang
*/

#pragma once

#include <iostream>
#include <sstream>	//使用stringstream需要引入这个头文件

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
Type stringToNum(const std::string& str)
{
	std:istringstream iss(str);
	Type num;
	iss >> num;
	return num;    
}

//数值到string转化
template <class Type>
std::string numToString(const Type num)
{
	std::stringstream ss;
	ss<<num;
	std::string s1 = ss.str();
	return s1;
}
