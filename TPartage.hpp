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
#include "sem.hpp"
//#include "task3.hpp"
//#include "task4.hpp"
#include "screen.hpp"

class TTask3;
class TTask4;
class SharedState:public TSingleton<SharedState>
{
    friend class TSingleton<SharedState>;
  	private:
 	    SharedState();
 		~SharedState();
 		SharedState(const SharedState&);
 		void operator=(const SharedState&);
        bool taskOneOn;
        bool taskTwoOn;
        bool taskThreeOn;
        bool taskFourOn;
        TSemaphore *sem;
        TTask3 *task3;
        TTask4 *task4;
        TScreen *screen;
    public:
        void setTaskOne(bool val);
        bool isTaskOneOn();
        void setTaskTwo(bool val);
        bool isTaskTwoOn();
        void setTaskThree(bool val);
        bool isTaskThreeOn();
        void setTaskFour(bool val);
        bool isTaskFourOn();
        void acquire();
        void release();
        void initTasksThreeAndFour(void *shared);
        void startTaskThree();
        void startTaskFour();
};
#endif