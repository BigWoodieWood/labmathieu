/**
 * @file task1.cpp
 * @brief Implementation of class TTask1 - Task 1 in the execution sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

#include "task1.hpp"
#include "TPartage.hpp"
#define DELAY 1000000
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
            // Producer: fills tab1 (99 random bytes + checksum), sleeps 100ms, then tab2
            TPartage *shared = TPartage::getInstance();

            screen->dispStr(8,3,"PRODUCER 1   ");
            uint8_t buf[100];
            uint8_t sum = 0;
            for(int i=0;i<99;i++){
                buf[i] = (uint8_t)(rand() & 0xFF);
                sum += buf[i];
            }
            buf[99] = (uint8_t)(~sum + 1);

            // protected write
            shared->protectTab1();
            shared->setTab1(buf);
            shared->unProtectTab1();

            usleep(100000); // 100 ms

            // produce second buffer
            sum = 0;
            for(int i=0;i<99;i++){
                buf[i] = (uint8_t)(rand() & 0xFF);
                sum += buf[i];
            }
            buf[99] = (uint8_t)(~sum + 1);

            shared->protectTab2();
            shared->setTab2(buf);
            shared->unProtectTab2();

            usleep(100000); // 100 ms then repeat
        }
    }
