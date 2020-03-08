/// @file RunStatisticsInterface.hpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 01, 2020

#ifndef PIXIE_NET_RUNSTATISTICSINTERFACE_HPP
#define PIXIE_NET_RUNSTATISTICSINTERFACE_HPP


#include "RunStatistics.hpp"

class RunStatisticsInterface {
public:
    RunStatisticsInterface(volatile unsigned int *mapped);
    
    RunStatistics get_statistics();
    
    RunStatistics read_runstats();

private:
    volatile unsigned int *mapped;
};


#endif //PIXIE_NET_RUNSTATISTICS_HPP
