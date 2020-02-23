/// @file ParseConfigurationFiles.hpp
/// @brief Parses configuation files for the Pixie-net
/// @author S. V. Paulauskas
/// @date February 22, 2020

#ifndef PIXIE_NET_PARSECONFIGURATIONFILES_HPP
#define PIXIE_NET_PARSECONFIGURATIONFILES_HPP

#include "PixieNetConfig.hpp"

class ParseConfigurationFiles {
public:
    ///Parses the provided configuration file for parameters.
    ///@return The configuration parsed out of the file
    PixieNetFippiConfig parse_config(const char *settings);
};


#endif //PIXIE_NET_PARSECONFIGURATIONFILES_HPP
