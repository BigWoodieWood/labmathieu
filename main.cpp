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
#include "com.hpp"
#include "TPartage.hpp"
#include <string.h>
#include <iostream>
using namespace std;
string t1 = "1: trigger task 1";
string t2 = "2: trigger task 2";
int main(int argc, char *argv[])
    {
    char car;

  TThread::initTaskMain(SCHED_FIFO,0);

  // Création Clavier et console
    TClavier *clavier = TClavier::getInstance();
    TScreen *screen  = new TScreen();
    screen->start();

    // Création tâches
    TTask1 *task1 = new TTask1("Task 1",screen,SCHED_FIFO,90,0);
    TTask2 *task2 = new TTask2("Task 2",screen,SCHED_FIFO,89,0);
  SharedState *shared = SharedState::getInstance();
  shared->initTasksThreeAndFour(screen);
   
    // Démarrage tâches

    task1->start();
    task2->start();
  shared->startTaskThree();
  shared->startTaskFour();
    screen->dispStr(0,1,t1);
    screen->dispStr(0,2,t2);
    // Traitement tâche principale
    do
      {
      // Traitement
      
      if(clavier->kbhit())
		    {
		    car = clavier->getch();
		    }
        if(car == '1')
        {
          SharedState *shared = SharedState::getInstance();
          shared->setTaskOne(true);
          car = 0;
        }
        else if(car == '2')
        {
          SharedState *shared = SharedState::getInstance();
          shared->setTaskTwo(true);
          car = 0;
        }
        else if(car == '0')
        {
          SharedState *shared = SharedState::getInstance();
          shared->setTaskOne(false);
          car = 0;
        }
        
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
