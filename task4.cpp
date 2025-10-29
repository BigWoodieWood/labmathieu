/**
 * @file task4.cpp
 * @brief Implementation of class TTask4 - Final task in the sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

#include "task4.hpp"
#include "TPartage.hpp"
#define UNE_SECONDE 1000000
TTask4::TTask4(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                           TThread(name,shared,policy,priority,cpu)
    {
	    screen = (TScreen *)shared;
        screen->dispStr(1,6,name);
    }

TTask4::~TTask4()
    {
    }

void TTask4::task()
{
    signalStart();
    
    while(true)
	{
    SharedState *shared = SharedState::getInstance();
    // wait until triggered
    while(!shared->isTaskFourOn())
        {
            screen->dispStr(8,6,"BLOQUER      ");
            usleep(UNE_SECONDE/10);
        }

    // execute for 4s then clear flag
    screen->dispStr(8,6,"EXECUTION    ");
    usleep(UNE_SECONDE*4);
    shared->setTaskFour(false);
    }
}