// simple pthread mutex wrapper
#include "mutex.hpp"
#include <pthread.h>

TMutex::TMutex(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
    pthread_mutex_init(&mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

TMutex::~TMutex()
{
    pthread_mutex_destroy(&mutex);
}

void TMutex::take(void)
{
    pthread_mutex_lock(&mutex);
}

void TMutex::release(void)
{
    pthread_mutex_unlock(&mutex);
}
