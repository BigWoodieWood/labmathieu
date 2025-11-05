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

void TPartage::protectTab1(void)
{
    if(protectionEnabled) mutexTab1.take();
}

void TPartage::unProtectTab1(void)
{
    if(protectionEnabled) mutexTab1.release();
}

void TPartage::protectTab2(void)
{
    if(protectionEnabled) mutexTab2.take();
}

void TPartage::unProtectTab2(void)
{
    if(protectionEnabled) mutexTab2.release();
}

void TPartage::setProtectionEnabled(bool en)
{
    protectionEnabled = en;
}

bool TPartage::isProtectionEnabled(void)
{
    return protectionEnabled;
}