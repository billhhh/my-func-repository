#include "logger.h"

#include <stdlib.h>
#include <time.h>

#include "../common.h"

std::ofstream Logger::m_error_log_file;
std::ofstream Logger::m_info_log_file;
std::ofstream Logger::m_warn_log_file;
Mutex Logger::loggerLock;

//初始化，友元函数
void initLogger(const std::string &info_log_filename,
				const std::string &warn_log_filename,
				const std::string &error_log_filename)
{
    Logger::m_info_log_file.open(info_log_filename.c_str(),ios::app);
    Logger::m_warn_log_file.open(warn_log_filename.c_str(),ios::app);
    Logger::m_error_log_file.open(error_log_filename.c_str(),ios::app);
}

//获取log文件名称前缀
string logFilePrefix()
{
	 char temp[200]={NULL};
     //sprintf(temp, "%s-%s-%s","SERVER",getHostName().c_str(),getTimeNow().c_str());
     return string(temp);
}

std::ostream& Logger::getStream(log_rank_t log_rank){
    return (_INFO == log_rank) ?
                (m_info_log_file.is_open() ? m_info_log_file : std::cout) :
                (_WARNING == log_rank ?
                    (m_warn_log_file.is_open() ? m_warn_log_file : std::cerr) :
                    (m_error_log_file.is_open() ? m_error_log_file : std::cerr));
}

std::ostream& Logger::whlogger( log_rank_t rank, const std::string& file, const int32 line,
							   const std::string& function)
{
	loggerLock.Lock();
	std::ostream & tmpOstream = start(rank,file,line,function);
	loggerLock.unLock();
	return tmpOstream;
}

std::ostream& Logger::whlogger( log_rank_t rank, const std::string& file, const int32 line,
							const std::string& function, const std::string reason )
{
	loggerLock.Lock();
	std::ostream & tmpOstream = start(rank,file,line,function,reason);
	loggerLock.unLock();
	return tmpOstream;
}

std::ostream& Logger::start(
	log_rank_t rank, 
							   const string& file,
							   const int32 line,
							   const std::string &function
							   ) {
    time_t tm;
    time(&tm);
    char time_string[64];
    //ctime_r(&tm, time_string);
	//strftime(time_string,sizeof(time_string),"%Y/%m/%d %X %A 本年第%j天 %z",localtime(&tm));
	strftime(time_string,sizeof(time_string),"%Y/%m/%d %X %A ",localtime(&tm));
    return getStream(rank)<< time_string<<file<<", function:("<< function<<")"<<", line:"<<line<<" "<<std::flush;
}

std::ostream& Logger::start( log_rank_t rank, const std::string& file, const int32 line,
							const std::string& function, const std::string reason )
{
	time_t tm;
	time(&tm);
	char time_string[64];
	//ctime_r(&tm, time_string);
	//strftime(time_string,sizeof(time_string),"%Y/%m/%d %X %A 本年第%j天 %z",localtime(&tm));
	strftime(time_string,sizeof(time_string),"%Y/%m/%d %X %A ",localtime(&tm));
	return getStream(rank)<< time_string<<file<<", function:("<< function<<")"<<", line:"<<line<<" reason:"<<reason<<std::flush;
}

Logger::~Logger(){
    getStream(m_log_rank) << std::endl << std::flush;
    
    if (_FATAL == m_log_rank) {
        m_info_log_file.close();
        m_info_log_file.close();
        m_info_log_file.close();
        abort();
    }
}



