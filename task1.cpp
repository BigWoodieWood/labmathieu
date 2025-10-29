/**
 * @file task1.cpp
 * @brief Implementation of class TTask1 - Task 1 in the execution sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

#include "task1.hpp"
#include "TPartage.hpp"
#define delay 1000000
TTask1::TTask1(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                            TThread(name,shared,policy,priority,cpu)
    {
	screen = (TScreen *)shared;
        screen->dispStr(1,3,name);
    }

TTask1::~TTask1()
    {
    }

void TTask1::task(void)
        {
        signalStart();

        while(1)
        {
                SharedState *shared = SharedState::getInstance();

            // show blocked next to name and wait until triggered
                while(!shared->isTaskOneOn())
            {
                screen->dispStr(8,3,"BLOQUER      ");
                usleep(delay/10);
            }

            // when triggered, show execution, sleep 1s, then clear trigger
            screen->dispStr(8,3,"EXECUTION    ");
            usleep(delay);
                shared->setTaskOne(false);
        }
    }
