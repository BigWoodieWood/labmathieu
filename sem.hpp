/**
 * @file sem.hpp
 * @brief Declaration of class TSemaphore - Wrapper for POSIX semaphores
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class encapsulates POSIX semaphores to provide a simple,
 * object-oriented interface for synchronization between tasks.
 */

#ifndef SEM_HPP
#define SEM_HPP

#include <stdint.h>
#include <semaphore.h>

class TSemaphore
    {
    private:
	sem_t sem;
    public:
	TSemaphore(uint32_t valeur = 1);
	~TSemaphore();

	void take(void);
	void release(void);
    };

#endif // SEM_HPP
