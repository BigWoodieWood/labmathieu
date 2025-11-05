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

// Consumer 1
#include "task3.hpp"
#include "TPartage.hpp"
#define CONSUMER_SLEEP_MID 50000 // 50 ms
#define BETWEEN_TAB_SLEEP 25000 // 25 ms

TTask3::TTask3(const char *name,void *shared,int policy,int priority,int32_t cpu) :
                                                           TThread(name,shared,policy,priority,cpu)
    {
    screen = (TScreen *)shared;
    screen->dispStr(1,5,name);
    }

TTask3::~TTask3()
    {
    }

void TTask3::task()
{
    signalStart();
    uint8_t buf[100];
    while(true)
    {
        TPartage *shared = TPartage::getInstance();
        screen->dispStr(8,5,"CONSUMER 1   ");

        // read tab1
        shared->protectTab1();
        shared->getTab1(buf, TPartage::FULL);
        // emulate mid-read delay to increase race window
        usleep(CONSUMER_SLEEP_MID);
        shared->unProtectTab1();

        // validate checksum
        uint8_t sum = 0;
        for(int i=0;i<99;i++) sum += buf[i];
        uint8_t chk = buf[99];
        if((uint8_t)(~sum + 1) == chk) shared->incControleOk();
        else shared->incControleBad();

        usleep(BETWEEN_TAB_SLEEP);

        // read tab2 same way
        shared->protectTab2();
        shared->getTab2(buf, TPartage::FULL);
        usleep(CONSUMER_SLEEP_MID);
        shared->unProtectTab2();

        sum = 0;
        for(int i=0;i<99;i++) sum += buf[i];
        chk = buf[99];
        if((uint8_t)(~sum + 1) == chk) shared->incControleOk();
        else shared->incControleBad();

    }
}