/**
 * @file mqtt_task.hpp
 * @brief Thread wrapper for periodic MQTT publishing (if needed) and liveness
 */
#ifndef MQTT_TASK_HPP
#define MQTT_TASK_HPP

#include "thread.hpp"
#include "MQTT.hpp"

class TMqttTask : public TThread
{
public:
    TMqttTask(const char *name, void *shared, int policy, int priority, int32_t cpu = -1);
    ~TMqttTask() = default;
    void task(void) override;
};

#endif // MQTT_TASK_HPP
