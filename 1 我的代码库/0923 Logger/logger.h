/* 
* 
* function: 日志模块
* 
* Date:2015-09-13
* 
*    Author: Bill Wang
*/

#ifndef LOGGER
#define LOGGER

#include "common.h"
#include "mutex.h"
#include <iostream>
//#include <iomanip>
#include <fstream>
#include <string>
//#include <cstdlib>
//using namespace std;

///
/// \brief 日志文件的类型
///
typedef enum log_rank {
    _INFO,
    _WARNING,
    _ERROR,
    _FATAL
}log_rank_t;


void initLogger(const std::string& info_log_filename,
                const std::string& warn_log_filename,
                const std::string& error_log_filename);

//获取日志文件名称前缀
 string logFilePrefix();

///
/// \brief 日志系统类
///
class Logger {
    friend void initLogger(const std::string& info_log_filename,
                           const std::string& warn_log_filename,
                           const std::string& erro_log_filename);
    
public:
	static Mutex loggerLock;

    Logger(log_rank_t log_rank) : m_log_rank(log_rank) {}
    
    ~Logger();

    static std::ostream& whlogger(
		log_rank_t,
		const std::string& file, 
		const int32 line, 
		const std::string& function
		);

	static std::ostream& whlogger(
		log_rank_t,
		const std::string& file, 
		const int32 line, 
		const std::string& function,
		const std::string reason
		);
    
private:
    ///
    /// \brief 根据等级获取相应的日志输出流
    ///
    static std::ostream& getStream(log_rank_t log_rank);
    
    static std::ofstream m_info_log_file;                   ///< 信息日子的输出流
    static std::ofstream m_warn_log_file;                   ///< 警告信息的输出流
    static std::ofstream m_error_log_file;                  ///< 错误信息的输出流
    log_rank_t m_log_rank;                                  ///< 日志的信息的等级

	static std::ostream& start(
		log_rank_t,
		const std::string& file, 
		const int32 line, 
		const std::string& function
		);

	static std::ostream& start(
		log_rank_t,
		const std::string& file, 
		const int32 line, 
		const std::string& function,
		const std::string reason
		);
};


///
/// \brief 根据不同等级进行用不同的输出流进行读写
///
#define LOG(log_rank)   \
Logger(log_rank).whlogger(log_rank, __FILE__, __LINE__, __FUNCTION__)\

#define LOG2(log_rank,res)   \
Logger(log_rank).whlogger(log_rank, __FILE__, __LINE__, __FUNCTION__,res)\


///
/// \brief 利用日记进行检查的各种宏
///
#define CHECK(a)                                            \
    if(!(a)) {                                              \
        LOG(_ERROR) << " CHECK failed " << endl              \
                   << #a << " = " << (a) << endl;           \
        abort();                                            \
    }                                                       \



#define CHECK_NOTNULL(a)                                    \
    if( NULL == (a)) {                                      \
        LOG(_ERROR) << " CHECK_NOTNULL failed "              \
                   << #a << " == NULL " << endl;            \
        abort();                                            \
    }



#define CHECK_NULL(a)                                       \
    if( NULL != (a)) {                                      \
        LOG(_ERROR) << " CHECK_NULL failed " << endl         \
                   << #a << " != NULL " << endl;            \
        abort();                                            \
    }


#define CHECK_EQ(a, b)                                      \
    if(!((a) == (b))) {                                     \
        LOG(_ERROR) << " CHECK_EQ failed "  << endl          \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
    }



#define CHECK_NE(a, b)                                      \
    if(!((a) != (b))) {                                     \
        LOG(_ERROR) << " CHECK_NE failed " << endl           \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
    }



#define CHECK_LT(a, b)                                      \
    if(!((a) < (b))) {                                      \
        LOG(_ERROR) << " CHECK_LT failed "                   \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
    }



#define CHECK_GT(a, b)                                      \
    if(!((a) > (b))) {                                      \
        LOG(_ERROR) << " CHECK_GT failed "  << endl          \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
    }



#define CHECK_LE(a, b)                                      \
    if(!((a) <= (b))) {                                     \
        LOG(_ERROR) << " CHECK_LE failed "  << endl          \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
    }



#define CHECK_GE(a, b)                                      \
    if(!((a) >= (b))) {                                     \
        LOG(_ERROR) << " CHECK_GE failed "  << endl          \
                   << #a << " = " << (a) << endl            \
                   << #b << " = " << (b) << endl;           \
        abort();                                            \
     }



#define CHECK_DOUBLE_EQ(a, b)                               \
    do {                                                    \
        CHECK_LE((a), (b)+0.000000000000001L);              \
        CHECK_GE((a), (b)-0.000000000000001L);              \
    } while (0)



#endif
