/// @file ProgramFippi.hpp
/// @brief Uses the provided configuration file to program the FPGA.
/// @author S. V. Paulauskas
/// @date February 22, 2020

#ifndef PIXIE_NET_PROGRAMFIPPI_HPP
#define PIXIE_NET_PROGRAMFIPPI_HPP

#include "FippiConfiguration.hpp"

class ProgramFippi {
public:
    int program_fippi(const FippiConfiguration &fippiconfig);
};


#endif //PIXIE_NET_PROGRAMFIPPI_HPP
