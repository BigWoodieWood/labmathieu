/**
 * @file TConfiguration.hpp
 * @brief Simple configuration reader for MQTT server address (singleton)
 *
 * The file com.def must sit beside the executable. If missing it's created
 * with default content "/dev/ttyS0". Only the first line is used.
 */
#ifndef TCONFIGURATION_HPP
#define TCONFIGURATION_HPP

#include "singleton.hpp"
#include <string>

class TConfiguration : public TSingleton<TConfiguration>
{
    friend class TSingleton<TConfiguration>;
private:
    std::string serverAddress;
    TConfiguration();
    ~TConfiguration() = default;
    TConfiguration(const TConfiguration&) = delete;
    TConfiguration& operator=(const TConfiguration&) = delete;

    void load();
public:
    const std::string& getServerAddress() const { return serverAddress; }
};

#endif // TCONFIGURATION_HPP
