// Implementation of TConfiguration
#include "TConfiguration.hpp"
#include <fstream>
#include <sstream>
#include <unistd.h>

static const char *CFG_FILENAME = "com.def";

TConfiguration::TConfiguration()
{
    load();
}

void TConfiguration::load()
{
    // File expected in current working directory (same as executable)
    std::ifstream in(CFG_FILENAME);
    if(!in.good()){
        // Create with default serial port
        std::ofstream out(CFG_FILENAME, std::ios::out | std::ios::trunc);
        out << "/dev/ttyS0" << std::endl;
        out.close();
        serverAddress = "/dev/ttyS0";
        return;
    }
    std::string line;
    if(std::getline(in, line)){
        // trim whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        size_t end   = line.find_last_not_of(" \t\r\n");
        if(start == std::string::npos) serverAddress = "localhost"; else serverAddress = line.substr(start, end-start+1);
    } else {
        serverAddress = "/dev/ttyS0"; // fallback
    }
}
