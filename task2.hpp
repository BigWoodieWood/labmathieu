/**
 * @file task2.hpp
 * @brief Declaration of class TTask2 - Sequential Task 2
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements a task that starts a chained execution sequence
 * with tasks 3 and 4. It uses a semaphore for mutual exclusion and waits
 * for downstream tasks to finish.
 */

#ifndef TTASK2_HPP
#define TTASK2_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"


class TTask2 : public TThread
    {
    private:
		TScreen *screen;
    public:
	TTask2(const char *name,void *shared,int policy,int priority,int32_t cpu);
	~TTask2();

	void task(void);
    };

#endif //TTASK3_HPP
