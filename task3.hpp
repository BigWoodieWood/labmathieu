/**
 * @file task3.hpp
 * @brief Declaration of class TTask3 - Task 3 in the sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements task 3 of the execution sequence.
 * It is triggered by task 2 and in turn triggers task 4.
 */

#ifndef TTASK3_HPP
#define TTASK3_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"


class TTask3 : public TThread
    {
    private:
		TScreen *screen;
    public:
	TTask3(const char *name,void *shared,int policy,int priority,int32_t cpu);
	~TTask3();

	void task(void);
    };

#endif //TTASK3_HPP
