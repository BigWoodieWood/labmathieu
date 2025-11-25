/**
 * @file MQTT.hpp
 * @brief MQTT client wrapper using mosquittopp (singleton)
 */
#ifndef MQTT_HPP
#define MQTT_HPP

#include <mosquittopp.h>
#include <string>
#include <stdint.h>
#include "singleton.hpp"

class TMqttClient : public mosqpp::mosquittopp, public TSingleton<TMqttClient>
{
    friend class TSingleton<TMqttClient>;
private:
    std::string host;
    int port;
    bool connectedFlag;
    TMqttClient(); // private default; use init()
    ~TMqttClient();
    TMqttClient(const TMqttClient&) = delete;
    TMqttClient& operator=(const TMqttClient&) = delete;
public:
    void init(const std::string &serverHost, int serverPort = 1883);
    bool isConnected() const { return connectedFlag; }
    void loopOnce(int timeoutMs = 1000); // non-blocking loop segment
    void publishModule(uint8_t moduleIdx1Based, bool state);

protected:
    void on_connect(int rc) override;
    void on_disconnect(int rc) override;
    void on_message(const mosquitto_message *message) override;
};

#endif // MQTT_HPP
