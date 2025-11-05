// Producer 2: similar behaviour to task1
#include "task2.hpp"
#include "TPartage.hpp"
#define DELAY2 1000000

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
        TPartage *shared = TPartage::getInstance();
        screen->dispStr(8,4,"PRODUCER 2   ");
        uint8_t buf[100];
        uint8_t sum = 0;
        for(int i=0;i<99;i++){
            buf[i] = (uint8_t)(rand() & 0xFF);
            sum += buf[i];
        }
        buf[99] = (uint8_t)(~sum + 1);

        shared->protectTab1();
        shared->setTab1(buf);
        shared->unProtectTab1();

        usleep(100000);

        sum = 0;
        for(int i=0;i<99;i++){
            buf[i] = (uint8_t)(rand() & 0xFF);
            sum += buf[i];
        }
        buf[99] = (uint8_t)(~sum + 1);
        shared->protectTab2();
        shared->setTab2(buf);
        shared->unProtectTab2();

        usleep(100000);
    }
    }
