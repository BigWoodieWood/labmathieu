/**
 * @file TComSerial.cpp
 * @brief Implementation of TComSerial
 */

#include "TComSerial.hpp"
#include "clavier.hpp"
#include <cstdio>
#include <cstring>

TComSerial::TComSerial(const char *name, TScreen *screenPtr, int priority,
                       baudrate_t baudRate, parity_t parite, dimData_t dimData,
                       int32_t timeoutRxMs)
    : TCom(name, (void *)screenPtr, priority, baudRate, parite, dimData, timeoutRxMs)
    {
      
    // Display the configured port name on startup
    const std::string &port = TConfiguration::getInstance()->getServerAddress();
    if(screen)
        screen->dispStr(0, 9, (std::string("Port serie: ") + port));
    else
        printf("Port serie: %s\n", port.c_str());
}

TComSerial::~TComSerial()
{
}

void TComSerial::rxCar(unsigned char car)
{
    // Clear timeout error if shown
    if(errorDisplayed){
        if(screen)
            screen->dispStr(0, 11, "               ");
        else
            printf("(timeout cleared)\n");
        errorDisplayed = false;
    }

    // Append character to buffer and display
    if(car == '\r') return; // ignore CR, let LF handle line breaks
    if(car == '\n'){
        // show current buffer then newline
        if(screen)
            screen->dispStr(dispX, dispY, rxBuffer);
        else
            printf("%s\n", rxBuffer.c_str());
        rxBuffer.clear();
        // move display line down
        dispY++;
        if(dispY > 22) dispY = 12; // wrap
    } else {
        rxBuffer.push_back((char)car);
        // Keep last 80 chars
        if(rxBuffer.size() > 80) rxBuffer.erase(0, rxBuffer.size()-80);
        if(screen)
            screen->dispStr(dispX, dispY, rxBuffer);
        else
            printf("%c", car);
    }
}

void TComSerial::rxTimeout(void)
{
    // Display timeout error
    const char *err = "Erreur: >10s depuis dernier caractere reçu";
    if(screen)
        screen->dispStr(0, 11, (char *)err);
    else
        fprintf(stderr, "%s\n", err);
    errorDisplayed = true;
}
