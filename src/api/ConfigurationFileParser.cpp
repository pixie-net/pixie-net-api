/// @file ConfigurationFileParser.cpp
/// @brief
/// @author S. V. Paulauskas
/// @date February 22, 2020
#include <iostream>

#include "ConfigurationFileParser.hpp"

PixieNetFippiConfig ConfigurationFileParser::parse_config(const char *settings) {
    PixieNetFippiConfig fippiconfig;
    
    // Do not allow any missing entries in defaults.ini.
    const char *defaults_file = settings;
    int rval = init_PixieNetFippiConfig_from_file(defaults_file, 0, &fippiconfig);
    if (rval != 0)
        throw std::invalid_argument("Failed to parse FPGA settings from defaults.ini");
    
    const char *settings_file = settings;
    rval = init_PixieNetFippiConfig_from_file(settings_file, 1, &fippiconfig);
    if (rval != 0)
        throw std::invalid_argument("Failed to parse FPGA settings from settings.ini");
    return fippiconfig;
}