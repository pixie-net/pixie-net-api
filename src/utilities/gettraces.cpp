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
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <getopt.h>
#include <sys/mman.h>
#include <unistd.h>

#include "ConfigurationFileParser.hpp"
#include "FippiConfiguration.hpp"
#include "PixieNetCommon.hpp"
#include "PixieNetDefs.hpp"
#include "TraceInterface.hpp"
#include "UserspaceIo.hpp"


int main(int argc, char *argv[]) {
    std::string filename = "traces", fileformat = ".csv", cfg_file = "default";
    bool doAverage = false;
    
    int opt;
    while ((opt = getopt(argc, argv, "ac:f:")) != EOF)
        switch (opt) {
            case 'a':
                doAverage = true;
                break;
            case 'c':
                cfg_file = optarg;
                break;
            case 'f':
                filename = optarg;
                break;
            case '?':
                std::cout << "Usage: ./gettraces.cpp -f <filename> -a -c <config file>" << std::endl;
                break;
            default:
                std::cout << std::endl;
                abort();
        }
    
    // *************** PS/PL IO initialization *********************
    UserspaceIo uio;
    int fd = uio.OpenPdFileDescription();
    int size = 4096;
    unsigned int *map_addr = uio.MapMemoryAddress(fd, size);
    volatile unsigned int *mapped = map_addr;
    
    std::map<unsigned int, std::vector<int> > result;
    
    if (!doAverage)
        result = TraceInterface().get_traces(mapped);
    else {
        try {
            if (cfg_file == "default")
                result = TraceInterface().get_averaged_traces(FippiConfiguration(), mapped);
            else
                result = TraceInterface().get_averaged_traces(ConfigurationFileParser().parse_config(cfg_file.c_str()),
                                                              mapped);
        } catch (std::overflow_error &err) {
            std::cout << err.what() << std::endl;
        }
    }
    
    std::stringstream output_name;
    output_name << filename << '-' << std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count() << fileformat;
    
    std::ofstream output(output_name.str().c_str());
    output << "sample,adc0,adc1,adc2,adc3" << std::endl;
    for (int k = 0; k < NTRACE_SAMPLES; k++)
        output << k << "," << result[0][k] << "," << result[1][k] << "," << result[2][k] << "," << result[3][k]
               << std::endl;
    output.close();
    
    munmap(map_addr, size);
    close(fd);
}
