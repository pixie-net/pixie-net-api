/*----------------------------------------------------------------------
 * Copyright (c) 2017 XIA LLC
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
#include <cstdio>

#include <sys/mman.h>
#include <unistd.h>

#include "PixieNetCommon.hpp"
#include "PixieNetDefs.hpp"
#include "UserspaceIo.hpp"

int main(void) {
    int size = 4096;
    int k;
    unsigned int adc0[NTRACE_SAMPLES], adc1[NTRACE_SAMPLES], adc2[NTRACE_SAMPLES], adc3[NTRACE_SAMPLES];
    
    // *************** PS/PL IO initialization *********************
    UserspaceIo uio;
    int fd = uio.OpenPdFileDescription();
    unsigned int *map_addr = uio.MapMemoryAddress(fd, 4096);
    volatile unsigned int *mapped = map_addr;
    
    // **************** XIA code begins **********************
    // read 8K samples from ADC register
    // at this point, no guarantee that sampling is truly periodic
    mapped[AOUTBLOCK] = OB_EVREG;        // switch reads to event data block of addresses
    
    // dummy reads for sampling update
    k = mapped[AADC0] & 0xFFFF;
    k = mapped[AADC1] & 0xFFFF;
    k = mapped[AADC2] & 0xFFFF;
    k = mapped[AADC3] & 0xFFFF;
    
    for (k = 0; k < NTRACE_SAMPLES; k++)
        adc0[k] = mapped[AADC0] & 0xFFFF;
    for (k = 0; k < NTRACE_SAMPLES; k++)
        adc1[k] = mapped[AADC1] & 0xFFFF;
    for (k = 0; k < NTRACE_SAMPLES; k++)
        adc2[k] = mapped[AADC2] & 0xFFFF;
    for (k = 0; k < NTRACE_SAMPLES; k++)
        adc3[k] = mapped[AADC3] & 0xFFFF;
    
    // open the output file
    FILE *fil = fopen("ADC.csv", "w");
    fprintf(fil, "sample,adc0,adc1,adc2,adc3\n");
    
    //  write to file
    for (k = 0; k < NTRACE_SAMPLES; k++)
        fprintf(fil, "%d,%d,%d,%d,%d\n ", k, adc0[k], adc1[k], adc2[k], adc3[k]);
    
    munmap(map_addr, size);
    close(fd);
    fclose(fil);
    return 0;
}
