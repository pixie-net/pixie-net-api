/// @file TraceInterface.cpp
/// @brief 
/// @author S. V. Paulauskas
/// @date February 29, 2020
#include "TraceInterface.hpp"

#include "PixieNetDefs.hpp"

std::map<unsigned int, std::vector<int> > TraceInterface::get_traces(volatile unsigned int *mapped) {
    // read 8K samples from ADC register
    // at this point, no guarantee that sampling is truly periodic
    mapped[AOUTBLOCK] = OB_EVREG;        // switch reads to event data block of addresses
    
    // dummy reads for sampling update
    mapped[AADC0] & 0xFFFF;
    mapped[AADC1] & 0xFFFF;
    mapped[AADC2] & 0xFFFF;
    mapped[AADC3] & 0xFFFF;
    
    std::map<unsigned int, std::vector<int> > traces;
    for (unsigned int k = 0; k < NTRACE_SAMPLES; k++)
        traces[0].push_back(mapped[AADC0] & 0xFFFF);
    for (unsigned int k = 0; k < NTRACE_SAMPLES; k++)
        traces[1].push_back(mapped[AADC1] & 0xFFFF);
    for (unsigned int k = 0; k < NTRACE_SAMPLES; k++)
        traces[2].push_back(mapped[AADC2] & 0xFFFF);
    for (unsigned int k = 0; k < NTRACE_SAMPLES; k++)
        traces[3].push_back(mapped[AADC3] & 0xFFFF);
    return traces;
}