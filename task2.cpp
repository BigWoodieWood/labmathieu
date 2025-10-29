// ewood

#include "task2.hpp"
#include "task3.hpp"
#include "TPartage.hpp"
#include "sem.hpp"
#define UNE_SECONDE 1000000

TTask2::TTask2(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                           TThread(name,shared,policy,priority,cpu)
    {
	    screen = (TScreen *)shared;
        screen->dispStr(1,4,name);
    }

TTask2::~TTask2()
    {
    }

void TTask2::task(void)
        {
        signalStart();

        while(1)
        {
            SharedState *shared = SharedState::getInstance();
            // wait until triggered
            while(!shared->isTaskTwoOn())
            {
                screen->dispStr(8,4,"BLOQUER      ");
                usleep(UNE_SECONDE/10);
            }

            // take semaphore, execute for 2s, trigger task3 and release
            shared->acquire();
            screen->dispStr(8,4,"EXECUTION    ");
            usleep(UNE_SECONDE*2);
            shared->setTaskThree(true);
            shared->release();

            // wait until task3 clears its flag before resetting our own
            while(shared->isTaskThreeOn())
                usleep(10);

            shared->acquire();
            usleep(UNE_SECONDE*2);
            shared->setTaskTwo(false);
            shared->release();
        }
    }
