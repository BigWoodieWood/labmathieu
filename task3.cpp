/**
 * @file task3.cpp
 * @brief Implementation of class TTask3 - Task 3 in the execution sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements task 3 of the execution sequence.
 * It is triggered by task 2, runs for 2 seconds,
 * triggers task 4 and waits for it to finish before terminating.
 */

#include "task3.hpp"
#include "task4.hpp"
#include "TPartage.hpp"
#define UNE_SECONDE 1000000
// ewood
TTask3::TTask3(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                           TThread(name,shared,policy,priority,cpu)
    {
	    screen = (TScreen *)shared;
        screen->dispStr(1,5,name);
    }
// ewood

TTask3::~TTask3()
    {
    }

void TTask3::task()
{
    signalStart();

    while(true)
    {
        SharedState *shared = SharedState::getInstance();

        // wait until triggered
        while(!shared->isTaskThreeOn())
        {
            screen->dispStr(8,5,"BLOQUER      ");
            usleep(UNE_SECONDE/10);
        }

        // when triggered, execute 2s, trigger task4 and clear own flag
        screen->dispStr(8,5,"EXECUTION    ");
        usleep(UNE_SECONDE*2);
        shared->setTaskFour(true);

        // wait for task4 to finish
        while(shared->isTaskFourOn())
            usleep(10);

        // sleep 2s after task4 finishes
        usleep(UNE_SECONDE*2);
        shared->setTaskThree(false);
    }
}