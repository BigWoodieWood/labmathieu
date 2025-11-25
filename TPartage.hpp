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
    bool modules[6]; // state of 6 modules (false=OFF, true=ON)
    TMutex mutexModules;

public:
    enum copy_t { FULL, FIRST_HALF, SECOND_HALF };

    void getTab1(uint8_t *pTab, copy_t type);
    void setTab1(uint8_t *pTab);
    void setTab1(uint8_t *pTab, copy_t type);
    void getTab2(uint8_t *pTab, copy_t type);
    void setTab2(uint8_t *pTab);
    void setTab2(uint8_t *pTab, copy_t type);

    void incControleOk(void);
    void incControleBad(void);
    uint32_t getControleOk(void);
    uint32_t getControleBad(void);

    // protectTabX returns true if it actually acquired the mutex
    bool protectTab1(void);
    void unProtectTab1(bool locked);
    bool protectTab2(void);
    void unProtectTab2(bool locked);
    void setProtectionEnabled(bool en);
    bool isProtectionEnabled(void);
    // Module state management
    bool getModule(uint8_t idx); // idx 0..5
    void setModule(uint8_t idx, bool state);
    bool toggleModule(uint8_t idx); // returns new state
    void getModules(bool *dest6); // bulk copy
};

#endif // TPARTAGE_HPP