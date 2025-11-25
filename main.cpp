/**
 * @file main.cpp
 * @brief Program entry: creates tasks and the shared object, then handles user input
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

#include "clavier.hpp"
#include "screen.hpp"
#include "TComSerial.hpp"
#include "TConfiguration.hpp"
#include <string.h>
int main(int argc, char *argv[])
    {
  (void)argc; (void)argv; // parameters unused in this program
  char car = 0;

  TThread::initTaskMain(SCHED_FIFO,0);

  // Création Clavier et console
    TClavier *clavier = TClavier::getInstance();
    TScreen *screen  = new TScreen();
    screen->start();


  // Serial communication task (uses TConfiguration to read com.def)
  TComSerial *serial = new TComSerial(TConfiguration::getInstance()->getServerAddress().c_str(), screen, 90);
  // start serial task
  serial->start();
    // Traitement tâche principale: lecture clavier et envoi sur la liaison série
    screen->dispStr(0,0,"Tapez des caracteres: q pour quitter");

      do
        {
        // check keyboard
        if(clavier->kbhit())
          {
          car = clavier->getch();
          }

        // if quit requested, exit loop
        if( (car == 'q') || (car == 'Q') ) break;

        // send any typed character to the serial port
        if((car != 0) && (serial != nullptr)){
            serial->sendTx(&car, 1);
        // debug: print to stdout that we attempted to send
        printf("[DEBUG] sent char: %c\n", car);
        fflush(stdout);
        car = 0; // avoid re-sending same char
        }

        usleep(200000);

        }
      while(1);


  if(serial) delete serial;

    // Destruction console
    if(screen)
        delete screen;


    return 0;
    }
