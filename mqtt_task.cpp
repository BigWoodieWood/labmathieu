#include "mqtt_task.hpp"
#include "TConfiguration.hpp"
#include <mosquittopp.h>
#include <unistd.h>
#include <iostream>

TMqttTask::TMqttTask(const char *name, void *shared, int policy, int priority, int32_t cpu) :
    TThread(name, shared, policy, priority, cpu)
{
    mosqpp::lib_init();
    // Initialize client with configuration
    const std::string &host = TConfiguration::getInstance()->getServerAddress();
    TMqttClient::getInstance()->init(host, 1883);
}

void TMqttTask::task(void)
{
    signalStart();
    // We rely on loop_start() thread inside mosquittopp so just monitor
    while(1){
        // Could implement keep-alive logic or republish states on reconnect
        if(TMqttClient::getInstance()->isConnected()){
            // optional: nothing for now
        }
        usleep(200000); // 200 ms
    }
}
