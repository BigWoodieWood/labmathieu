// ewood

#include "TPartage.hpp"
#include "task3.hpp"
#include "task4.hpp"
SharedState::SharedState()
{
    taskOneOn = false;
    taskTwoOn = false;
    taskThreeOn = false;
    taskFourOn = false;
    sem = nullptr;  
    task3 = nullptr;
    task4 = nullptr;
    screen = nullptr;
}
void SharedState::initTasksThreeAndFour(void *shared)
{
    screen = (TScreen *)shared;
    task3 = new TTask3("Task 3",screen,SCHED_FIFO,88,0);
    task4 = new TTask4("Task 4",screen,SCHED_FIFO,87,0);
    sem = new TSemaphore(1);
}
bool SharedState::isTaskOneOn()
{
    return taskOneOn;
}

void SharedState::setTaskOne(bool val)
{
    taskOneOn = val;
}
void SharedState::setTaskTwo(bool val)
{
    taskTwoOn = val;
}
bool SharedState::isTaskTwoOn()
{
    return taskTwoOn;
}
void SharedState::setTaskThree(bool val)
{
    taskThreeOn = val;
}
bool SharedState::isTaskThreeOn()
{
    return taskThreeOn;
}
void SharedState::setTaskFour(bool val)
{
    taskFourOn = val;
}
bool SharedState::isTaskFourOn()
{
    return taskFourOn;
}
void SharedState::acquire()
{
    sem->take();
}
void SharedState::release()
{
    sem->release();
}
void SharedState::startTaskThree()
{
    task3->start();
}
void SharedState::startTaskFour()
{
    task4->start();
}
SharedState::~SharedState()
{
    delete task3;
    delete task4;
    if(sem)
        delete sem;
}