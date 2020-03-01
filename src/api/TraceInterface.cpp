/// @file TraceInterface.cpp
/// @brief 
/// @author S. V. Paulauskas
/// @date February 29, 2020
#include "TraceInterface.hpp"

#include <exception>

#include <cmath>

#include <unistd.h>

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

std::map<unsigned int, std::vector<int> >
TraceInterface::get_averaged_traces(const FippiConfiguration &fippiConfiguration, volatile unsigned int *mapped) {
    std::map<unsigned int, std::vector<int> > ave_traces;
    unsigned int mval;
    unsigned int maxwait;
    double scale[NCHANNELS];
    int k;
    
    // compute max. wait time  and scaling factor
    maxwait = 0;
    // get maximum sampling interval
    for (k = 0; k < NCHANNELS; k++) {
        if (maxwait < fippiConfiguration.ADC_AVG[k])
            maxwait = fippiConfiguration.ADC_AVG[k];
        
        scale[k] = (double) fippiConfiguration.ADC_AVG[k];
        if (fippiConfiguration.ADC_AVG[k] > 2048)
            scale[k] = scale[k] / 16384.0;
        else if (fippiConfiguration.ADC_AVG[k] > 64)
            scale[k] = scale[k] / 128.0;
    }
    maxwait = maxwait * NAVG_TRACE_SAMPLES * 10;            // ten times  max total sampling time   (in clock cycles)
    maxwait = (int) floor(maxwait * 8 / 100000);             // scale in 100 us wait cycles
    
    // 1. arm trigger
    mapped[AOUTBLOCK] = OB_IOREG;
    mapped[ACOUNTER_CLR] = 1;          // any write to COUNTER_CLR arms the trigger for capturing averaged samples
    
    // 2. poll for capture to be finished
    mapped[AOUTBLOCK] = OB_EVREG;        // switch reads to event data block of addresses
    k = 0;
    do {
        usleep(1000);
        k = k + 1;
        mval = mapped[AADCTRIG];
        printf("ADCTRIG = 0x%x \n", mval);
    } while (((mval & 0x00F0) == 0) & (k < maxwait));      // any of the 4 channels triggered and is done
    
    if (k >= maxwait)
        throw std::overflow_error("Error: Timed out while waiting for channels to trigger.");
    
    // 3. read 4K samples from ADC register
    // dummy reads for sampling update
    k = mapped[AAVGADC0] & 0xFFFF;
    k = mapped[AAVGADC1] & 0xFFFF;
    k = mapped[AAVGADC2] & 0xFFFF;
    k = mapped[AAVGADC3] & 0xFFFF;
    
    if ((mval & 0x0010) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[0][k] = (int)round(mapped[AAVGADC0] / scale[0]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[0][k] = (k & 0x0003) + 0;
    
    if ((mval & 0x0020) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[1][k] = (int) (int)round(mapped[AAVGADC1] / scale[1]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[1][k] = (k & 0x0003) + 1;
    
    if ((mval & 0x0040) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[2][k] = (int)round(mapped[AAVGADC2] / scale[2]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[2][k] = (k & 0x0003) + 2;
    
    if ((mval & 0x0080) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[3][k] = (int)round(mapped[AAVGADC3] / scale[3]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            ave_traces[3][k] = (k & 0x0003) + 3;
        
    return ave_traces;
}