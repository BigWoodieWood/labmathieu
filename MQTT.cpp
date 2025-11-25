// Implementation of TMqttClient
#include "MQTT.hpp"
#include "TPartage.hpp"
#include <iostream>
#include <sstream>
#include <cstring>

TMqttClient::TMqttClient() : mosqpp::mosquittopp("lab5_client"), port(1883), connectedFlag(false)
{
    // lib_init done automatically outside (first usage). Caller should ensure mosqpp::lib_init() called.
}

TMqttClient::~TMqttClient()
{
    if(connectedFlag) disconnect();
    loop_stop(true);
}

void TMqttClient::init(const std::string &serverHost, int serverPort)
{
    host = serverHost;
    port = serverPort;
    connect_async(host.c_str(), port, 60);
    loop_start(); // start internal thread for network handling
}

void TMqttClient::on_connect(int rc)
{
    if(rc == 0){
        connectedFlag = true;
        subscribe(nullptr, "MODULE/#", 1);
        std::cout << "[MQTT] Connected to " << host << ':' << port << std::endl;
    } else {
        std::cerr << "[MQTT] Connection failed rc=" << rc << std::endl;
    }
}

void TMqttClient::on_disconnect(int rc)
{
    connectedFlag = false;
    std::cout << "[MQTT] Disconnected rc=" << rc << std::endl;
}

void TMqttClient::loopOnce(int timeoutMs)
{
    // Not used when loop_start() called, kept for potential future change.
    loop(timeoutMs, 1);
}

void TMqttClient::publishModule(uint8_t moduleIdx1Based, bool state)
{
    if(moduleIdx1Based < 1 || moduleIdx1Based > 6) return;
    if(!connectedFlag) return;
    std::ostringstream topic;
    topic << "MODULE/" << (int)moduleIdx1Based;
    const char *payload = state ? "ON" : "OFF";
    publish(nullptr, topic.str().c_str(), (int)strlen(payload), payload, 1, false);
}

void TMqttClient::on_message(const mosquitto_message *message)
{
    if(!message || !message->topic) return;
    std::string topic(message->topic);
    if(topic.rfind("MODULE/", 0) == 0){
        std::string rest = topic.substr(7); // after MODULE/
        int moduleNumber = atoi(rest.c_str());
        if(moduleNumber >= 1 && moduleNumber <= 6){
            std::string payload;
            if(message->payload && message->payloadlen > 0){
                payload.assign(static_cast<char*>(message->payload), message->payloadlen);
            }
            bool newState = false;
            if(payload == "ON" || payload == "on" || payload == "On") newState = true;
            else if(payload == "OFF" || payload == "off" || payload == "Off") newState = false;
            else return; // ignore unknown payload
            TPartage *shared = TPartage::getInstance();
            shared->setModule((uint8_t)(moduleNumber-1), newState);
        }
    }
}
