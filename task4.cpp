/**
 * @file task4.cpp
 * @brief Implementation of class TTask4 - Final task in the sequence
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

// Consumer 2
#include "task4.hpp"
#include "TPartage.hpp"
#define CONSUMER_SLEEP_MID 50000 // 50 ms
#define BETWEEN_TAB_SLEEP 25000 // 25 ms

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
    uint8_t buf[100];
    while(true)
    {
        TPartage *shared = TPartage::getInstance();
        {
            char lbl[64];
            const char *txt = shared->isProtectionEnabled() ? "CONSUMER 2" : "CONSUMER 2 [UNPROT]";
            /* Use a wide fixed field to fully clear previous longer labels */
            snprintf(lbl, sizeof(lbl), "%-32s", txt);
            screen->dispStr(8,6,lbl);
        }

        if (shared->isProtectionEnabled()) {
            bool locked = shared->protectTab1();
            shared->getTab1(buf, TPartage::FULL);
            usleep(100000);
            shared->unProtectTab1(locked);
        } else {
            shared->getTab1(buf, TPartage::FIRST_HALF);
            usleep(CONSUMER_SLEEP_MID);
            shared->getTab1(buf + 50, TPartage::SECOND_HALF);
        }

        uint8_t sum = 0;
        for(int i=0;i<99;i++) sum += buf[i];
        uint8_t chk = buf[99];
        if((uint8_t)(~sum + 1) == chk) shared->incControleOk();
        else shared->incControleBad();

        usleep(BETWEEN_TAB_SLEEP);

        if (shared->isProtectionEnabled()) {
            bool locked2 = shared->protectTab2();
            shared->getTab2(buf, TPartage::FULL);
            usleep(CONSUMER_SLEEP_MID);
            shared->unProtectTab2(locked2);
        } else {
            shared->getTab2(buf, TPartage::FIRST_HALF);
            usleep(CONSUMER_SLEEP_MID);
            shared->getTab2(buf + 50, TPartage::SECOND_HALF);
        }

        sum = 0;
        for(int i=0;i<99;i++) sum += buf[i];
        chk = buf[99];
        if((uint8_t)(~sum + 1) == chk) shared->incControleOk();
        else shared->incControleBad();
    }
}