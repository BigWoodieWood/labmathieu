/**
 * @file task1.hpp
 * @brief Declaration of class TTask1 - Independent Task 1
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements a real-time task that can be enabled/disabled
 * independently via the user interface.
 */

#ifndef TTASK1_HPP
#define TTASK1_HPP

#include "thread.hpp"
#include "screen.hpp"
#include "temps.hpp"
#include <string.h>

class TTask1 : public TThread
    {
    private:
		TScreen *screen;
    public:
	TTask1(const char *name,void *shared,int policy,int priority,int32_t cpu);
	~TTask1();

	void task(void);
    };

#endif //TTASK1_HPP
