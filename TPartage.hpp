/**
 * @file TPartage.hpp
 * @brief Declaration of class TPartage - Singleton sharing class
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 *
 * This class implements a singleton for sharing information
 * between tasks. It manages task states, synchronization semaphores,
 * and access to shared resources.
 */

#ifndef TPARTAGE_HPP
#define TPARTAGE_HPP

#include "singleton.hpp"
#include "mutex.hpp"
#include <stdint.h>

class TPartage : public TSingleton<TPartage>
{
    friend class TSingleton<TPartage>;
private:
    TPartage();
    ~TPartage();
    TPartage(const TPartage&) = delete;
    TPartage &operator=(const TPartage&) = delete;

    uint8_t tab1[100];
    uint8_t tab2[100];
    uint32_t controleOk;
    uint32_t controleBad;
    TMutex mutexTab1;
    TMutex mutexTab2;
    TMutex mutexCtrl;
    bool protectionEnabled;

public:
    enum copy_t { FULL, FIRST_HALF, SECOND_HALF };

    void getTab1(uint8_t *pTab, copy_t type);
    void setTab1(uint8_t *pTab);
    void getTab2(uint8_t *pTab, copy_t type);
    void setTab2(uint8_t *pTab);

    void incControleOk(void);
    void incControleBad(void);
    uint32_t getControleOk(void);
    uint32_t getControleBad(void);

    void protectTab1(void);
    void unProtectTab1(void);
    void protectTab2(void);
    void unProtectTab2(void);
    void setProtectionEnabled(bool en);
    bool isProtectionEnabled(void);
};

#endif // TPARTAGE_HPP