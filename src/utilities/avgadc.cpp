/*----------------------------------------------------------------------
 * Copyright (c) 2018 XIA LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, 
 * with or without modification, are permitted provided 
 * that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above 
 *     copyright notice, this list of conditions and the 
 *     following disclaimer.
 *   * Redistributions in binary form must reproduce the 
 *     above copyright notice, this list of conditions and the 
 *     following disclaimer in the documentation and/or other 
 *     materials provided with the distribution.
 *   * Neither the name of XIA LLC
 *     nor the names of its contributors may be used to endorse 
 *     or promote products derived from this software without 
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE.
 *----------------------------------------------------------------------*/
#include <iostream>

#include <cmath>
#include <cstdio>

#include <sys/mman.h>
#include <unistd.h>

#include "ConfigurationFileParser.hpp"
#include "PixieNetDefs.hpp"
#include "PixieNetCommon.hpp"
#include "ProgramFippi.hpp"
#include "UserspaceIo.hpp"

int main(int argc, char *argv[]) {
    FippiConfiguration fippiConfiguration;
    if (argc == 2)
        fippiConfiguration = ConfigurationFileParser().parse_config(argv[1]);
    ProgramFippi().program_fippi(fippiConfiguration);
    
    int size = 4096;
    int k;
    FILE *fil;
    unsigned int adc0[NAVG_TRACE_SAMPLES], adc1[NAVG_TRACE_SAMPLES], adc2[NAVG_TRACE_SAMPLES], adc3[NAVG_TRACE_SAMPLES];
    unsigned int mval;
    unsigned int maxwait;
    double scale[NCHANNELS];
    
    // compute max. wait time  and scaling factor
    maxwait = 0;
    for (k = 0; k < NCHANNELS; k++)          // get maximum sampling interval
    {
        if (maxwait < fippiConfiguration.ADC_AVG[k])
            maxwait = fippiConfiguration.ADC_AVG[k];
        
        scale[k] = (double) fippiConfiguration.ADC_AVG[k];
        if (fippiConfiguration.ADC_AVG[k] > 2048)
            scale[k] = scale[k] / 16384.0;
        else if (fippiConfiguration.ADC_AVG[k] > 64)
            scale[k] = scale[k] / 128.0;
        // scale[k] =1; // debug
        
    }
    maxwait = maxwait * NAVG_TRACE_SAMPLES * 10;            // ten times  max total sampling time   (in clock cycles)
    maxwait = (int) floor(maxwait * 8 / 100000);             // scale in 100 us wait cycles
    printf("maxwait for timeout: %d \n", maxwait);
    printf("scale factors %f %f %f %f \n", scale[0], scale[1], scale[2], scale[3]);
    
    // *************** PS/PL IO initialization *********************
    UserspaceIo uio;
    int fd = uio.OpenPdFileDescription();
    unsigned int *map_addr = uio.MapMemoryAddress(fd, size);
    volatile unsigned int *mapped = map_addr;
    
    // **************** XIA code begins **********************
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
    if (k >= maxwait) {
        printf("Error: Waiting for trigger timed out \n");
        return -1;
    }
    
    // 3. read 4K samples from ADC register 
    
    // dummy reads for sampling update
    k = mapped[AAVGADC0] & 0xFFFF;
    k = mapped[AAVGADC1] & 0xFFFF;
    k = mapped[AAVGADC2] & 0xFFFF;
    k = mapped[AAVGADC3] & 0xFFFF;
    
    if ((mval & 0x0010) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc0[k] = (int) floor((double) mapped[AAVGADC0] / scale[0]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc0[k] = (k & 0x0003) + 0;
    
    if ((mval & 0x0020) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc1[k] = (int) floor((double) mapped[AAVGADC1] / scale[1]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc1[k] = (k & 0x0003) + 1;
    
    if ((mval & 0x0040) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc2[k] = (int) floor((double) mapped[AAVGADC2] / scale[2]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc2[k] = (k & 0x0003) + 2;
    
    if ((mval & 0x0080) > 0)    // read only traces that triggered
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc3[k] = (int) floor((double) mapped[AAVGADC3] / scale[3]);
    else
        for (k = 0; k < NAVG_TRACE_SAMPLES; k++)
            adc3[k] = (k & 0x0003) + 3;
    
    // 4. open the output file
    fil = fopen("ADCAVG.csv", "w");
    fprintf(fil, "sample,adc0,adc1,adc2,adc3\n");
    
    //  write to file
    for (k = 0; k < NAVG_TRACE_SAMPLES; k++) {
        fprintf(fil, "%d,%d,%d,%d,%d\n ", k, adc0[k], adc1[k], adc2[k], adc3[k]);
    }
    
    // clean up
    fclose(fil);
    munmap(map_addr, size);
    close(fd);
    return 0;
}