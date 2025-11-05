/**
 * @file main.cpp
 * @brief Program entry: creates tasks and the shared object, then handles user input
 * @author elliot wood
 * @date 26 October 2025
 * @version 1.0
 */

#include "clavier.hpp"
#include "screen.hpp"
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"
#include "TPartage.hpp"
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

    // Création tâches
    TTask1 *task1 = new TTask1("Task 1",screen,SCHED_FIFO,90,0);
    TTask2 *task2 = new TTask2("Task 2",screen,SCHED_FIFO,89,0);
  // start consumer tasks (Task3 and Task4)
  TTask3 *task3 = new TTask3("Task 3",screen,SCHED_FIFO,88,0);
  TTask4 *task4 = new TTask4("Task 4",screen,SCHED_FIFO,87,0);
   
    // Démarrage tâches

    task1->start();
    task2->start();
  task3->start();
  task4->start();
    // Traitement tâche principale
    do
      {
      // check keyboard
      if(clavier->kbhit())
        {
        car = clavier->getch();
        }

      TPartage *shared = TPartage::getInstance();
      // toggle protection
      if(car == 'p' || car == 'P'){
        shared->setProtectionEnabled(!shared->isProtectionEnabled());
        car = 0;
      }
      // explicit OFF/ON
      if(car == 'o' || car == 'O'){ shared->setProtectionEnabled(false); car = 0; }
      if(car == 'i' || car == 'I'){ shared->setProtectionEnabled(true);  car = 0; }

  // show counters and protection state
  uint32_t ok = shared->getControleOk();
  uint32_t bad = shared->getControleBad();
  /* Moved counters up since top trigger lines were removed */
  screen->dispStr(0,1,"Controle OK:");
  screen->dispStr(15,1,ok);
  screen->dispStr(0,2,"Controle BAD:");
  screen->dispStr(15,2,bad);
  screen->dispStr(0,3,"Protection:");
  screen->dispStr(15,3, shared->isProtectionEnabled() ? "ON " : "OFF");

      usleep(200000);

      }
    while( (car != 'q') && (car != 'Q') );

    // Destruction tâches
    if(task1)
    	delete task1;
    if(task2)
		  delete task2;

    // Destruction console
    if(screen)
    	delete screen;


    return 0;
    }
