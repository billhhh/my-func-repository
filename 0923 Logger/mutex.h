/* 
* 
* function: pthread mutex锁封装
* 
* Date:2015-09-13
* 
*    Author: Bill Wang
*/

#ifndef MUTEX
#define MUTEX

#include <iostream>
#include <stdint.h> 
#include <pthread.h>
#include <errno.h>
#include <stdexcept>
#include <string.h>
using namespace std;

#pragma comment(lib, "pthreadVC2.lib")
#pragma comment(lib, "pthreadVSE2.lib")

class Mutex {
public:
    explicit Mutex(){
	init();
	}
	
    ~Mutex() {
        pthread_mutex_destroy(&m_Mutex);
    }
    
    void init() {
        int32_t error_t;
        error_t = pthread_mutex_init(&m_Mutex, NULL);
        checkError("Mutex::Mutex", error_t);
    }
    
    ///
    /// \brief 直接加锁
    ///
    void Lock() {
        checkError("Mutex::Lock", pthread_mutex_lock(&m_Mutex));
    }
    
    ///
    /// \brief 尝试加锁
    ///
    bool TryLock() {
        int32_t error_t =pthread_mutex_trylock(&m_Mutex);
        if (error_t == EBUSY) {
            return false;
        }else{
            checkError("Mutex::trylock", error_t);
            return true;
        }
    }
    
    ///
    /// \brief 解锁
    ///
    void unLock() {
        checkError("Mutex::Unlock", pthread_mutex_unlock(&m_Mutex));
    }
    
private:
    ///
    /// \brief 检查错误的类型
    ///
    static void checkError(const char *error_msg, int error) {
        if (error != 0) {
            string msg = error_msg;
            msg += " error: ";
            msg += strerror(error);
			std::cout<<"checkError:"<<msg<<std::endl;
            throw runtime_error(msg);
        }
    }
    
    pthread_mutex_t m_Mutex;
    
    //friend class ConditionVariable;
    
private:
    ///
    /// \brief 禁止拷贝构造
    ///
    Mutex(const Mutex& right);
    
    ///
    /// \brief 禁止赋值
    ///
    Mutex& operator = (const Mutex& right);   
};
#endif