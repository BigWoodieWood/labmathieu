// Simple implementation of TPartage singleton for the mutex lab
#include "TPartage.hpp"
#include <string.h>

TPartage::TPartage()
{
    controleOk = 0;
    controleBad = 0;
    memset(tab1,0,sizeof(tab1));
    memset(tab2,0,sizeof(tab2));
    protectionEnabled = true;
    for(int i=0;i<6;i++) modules[i] = false; // all OFF initially
}

TPartage::~TPartage()
{
}

void TPartage::getTab1(uint8_t *pTab, copy_t type)
{
    if(type == FULL) memcpy(pTab, tab1, 100);
    else if(type == FIRST_HALF) memcpy(pTab, tab1, 50);
    else memcpy(pTab, tab1+50, 50);
}

void TPartage::setTab1(uint8_t *pTab)
{
    memcpy(tab1, pTab, 100);
}

void TPartage::setTab1(uint8_t *pTab, copy_t type)
{
    if (type == FIRST_HALF) memcpy(tab1, pTab, 50);
    else if (type == SECOND_HALF) memcpy(tab1 + 50, pTab, 50);
    else memcpy(tab1, pTab, 100);
}

void TPartage::getTab2(uint8_t *pTab, copy_t type)
{
    if(type == FULL) memcpy(pTab, tab2, 100);
    else if(type == FIRST_HALF) memcpy(pTab, tab2, 50);
    else memcpy(pTab, tab2+50, 50);
}

void TPartage::setTab2(uint8_t *pTab)
{
    memcpy(tab2, pTab, 100);
}

void TPartage::setTab2(uint8_t *pTab, copy_t type)
{
    if (type == FIRST_HALF) memcpy(tab2, pTab, 50);
    else if (type == SECOND_HALF) memcpy(tab2 + 50, pTab, 50);
    else memcpy(tab2, pTab, 100);
}

void TPartage::incControleOk(void)
{
    mutexCtrl.take();
    controleOk++;
    mutexCtrl.release();
}

void TPartage::incControleBad(void)
{
    mutexCtrl.take();
    controleBad++;
    mutexCtrl.release();
}

uint32_t TPartage::getControleOk(void)
{
    uint32_t v;
    mutexCtrl.take();
    v = controleOk;
    mutexCtrl.release();
    return v;
}

uint32_t TPartage::getControleBad(void)
{
    uint32_t v;
    mutexCtrl.take();
    v = controleBad;
    mutexCtrl.release();
    return v;
}

// Try to acquire protection for tab1. Returns true if the mutex was acquired.
bool TPartage::protectTab1(void)
{
    bool prot;
    mutexCtrl.take();
    prot = protectionEnabled;
    mutexCtrl.release();

    if (prot) {
        mutexTab1.take();
        return true;
    }
    return false;
}

void TPartage::unProtectTab1(bool locked)
{
    if (locked) mutexTab1.release();
}

// Try to acquire protection for tab2. Returns true if the mutex was acquired.
bool TPartage::protectTab2(void)
{
    bool prot;
    mutexCtrl.take();
    prot = protectionEnabled;
    mutexCtrl.release();

    if (prot) {
        mutexTab2.take();
        return true;
    }
    return false;
}

void TPartage::unProtectTab2(bool locked)
{
    if (locked) mutexTab2.release();
}

void TPartage::setProtectionEnabled(bool en)
{
    mutexCtrl.take();
    protectionEnabled = en;
    mutexCtrl.release();
}

bool TPartage::isProtectionEnabled(void)
{
    bool v;
    mutexCtrl.take();
    v = protectionEnabled;
    mutexCtrl.release();
    return v;
}

bool TPartage::getModule(uint8_t idx)
{
    if(idx >= 6) return false;
    mutexModules.take();
    bool v = modules[idx];
    mutexModules.release();
    return v;
}

void TPartage::setModule(uint8_t idx, bool state)
{
    if(idx >= 6) return;
    mutexModules.take();
    modules[idx] = state;
    mutexModules.release();
}

bool TPartage::toggleModule(uint8_t idx)
{
    if(idx >= 6) return false;
    mutexModules.take();
    modules[idx] = !modules[idx];
    bool v = modules[idx];
    mutexModules.release();
    return v;
}

void TPartage::getModules(bool *dest6)
{
    if(!dest6) return;
    mutexModules.take();
    for(int i=0;i<6;i++) dest6[i] = modules[i];
    mutexModules.release();
}