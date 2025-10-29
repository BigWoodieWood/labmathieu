/**
 * @file mutex.hpp
 * @brief Declaration of class TMutex - Wrapper for POSIX mutex
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class encapsulates POSIX mutexes to provide a simple,
 * object-oriented interface for mutual exclusion between threads.
 */

#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>

class TMutex
    {
    private:
	pthread_mutex_t mutex;
    public:
	TMutex(void);
	~TMutex();

	void take(void);
	void release(void);
    };

#endif // MUTEX_HPP
