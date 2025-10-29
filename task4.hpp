/**
 * @file task4.hpp
 * @brief Declaration of class TTask4 - Final Task 4 of the sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements the final task of the execution sequence.
 * It is triggered by task 3 and terminates the execution chain.
 */

#ifndef TTASK4_HPP
#define TTASK4_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"


class TTask4 : public TThread
    {
    private:
		TScreen *screen;
    public:
	TTask4(const char *name,void *shared,int policy,int priority,int32_t cpu);
	~TTask4();

	void task(void);
    };

#endif //TTASK3_HPP
