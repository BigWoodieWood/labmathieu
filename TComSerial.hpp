/**
 * @file TComSerial.hpp
 * @brief Serial communication task built on top of TCom
 */
#ifndef TCOMSERIAL_HPP
#define TCOMSERIAL_HPP

#include "com.hpp"
#include "screen.hpp"
#include "TConfiguration.hpp"
#include <string>
#include <chrono>

class TComSerial : public TCom
    {
    private:
        TScreen *screen;
        std::string rxBuffer;
        // time point of last received character
        std::chrono::steady_clock::time_point lastRxTime;
        bool errorDisplayed;
        int32_t dispX;
        int32_t dispY;

    public:
        TComSerial(const char *name, TScreen *screenPtr, int priority,
                   baudrate_t baudRate = b9600,
                   parity_t parite = pNONE, dimData_t dimData = dS8,
                   int32_t timeoutRxMs = 10000);
        virtual ~TComSerial();


        virtual void rxCar(unsigned char car);
        virtual void rxTimeout(void);
    };

#endif // TCOMSERIAL_HPP
