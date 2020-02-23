/// @file ParseConfigurationFiles.hpp
/// @brief Parses configuation files for the Pixie-net
/// @author S. V. Paulauskas
/// @date February 22, 2020
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

#ifndef PIXIE_NET_CONFIGURATIONFILEPARSER_HPP
#define PIXIE_NET_CONFIGURATIONFILEPARSER_HPP

#include <map>
#include <string>
#include <vector>

#include "FippiConfiguration.hpp"
#include "PixieNetDefs.hpp"


class ConfigurationFileParser {
public:
    ///Parses the provided configuration file for parameters.
    ///@return The configuration parsed out of the file
    FippiConfiguration parse_config(const char *settings);

private:
    /// Parses the provided ini file into the provided PixieNetFipiConfig struct.
    ///Note that current requires that for each member variable of
    ///PixieNetFipiConfig, the configuration file must have a line starting with
    ///that identifier string, and followed by the expected number of numeric
    ///values.
    ///
    ///Blank lines, or lines starting with a '#' character are skipped, as are
    ///any lines with unrecognized identifiers.
    ///
    ///Integer numeric values that start with a '0x' prefix are assumed to be
    ///hexidecimal.
    ///
    ///Currently does not due any range checking!  This is left to progfippi.
    ///@returns 0 upon success.
    int init_FippiConfiguration_from_file(const char *const filename, int ignore_missing,
                                           struct FippiConfiguration *config);
    
    void split(std::vector<std::string> &resutls, const std::string &input, const char *delims);
    
    bool starts_with(const std::string &line, const std::string &label);
    
    bool split_label_values(const std::string &line, std::string &label, std::string &values);
    
    int get_single_value_str(const std::map<std::string, std::string> &label_to_values,
                             const std::string &label, std::string &value, int ignore_missing);
    
    int get_multiple_value_str(const std::map<std::string, std::string> &label_to_values,
                               const std::string &label, std::string values[NCHANNELS], int ignore_missing);
    
    int parse_single_bool_val(const std::map<std::string, std::string> &label_to_values, const std::string &label,
                              bool &value, int ignore_missing);
    
    int parse_multiple_bool_val(const std::map<std::string, std::string> &label_to_values,
                                const std::string &label, bool values[NCHANNELS], int ignore_missing);
    
    int parse_single_int_val(const std::map<std::string, std::string> &label_to_values, const std::string &label,
                             unsigned int &value, int ignore_missing);
    
    int parse_single_dbl_val(const std::map<std::string, std::string> &label_to_values, const std::string &label,
                             double &value, int ignore_missing);
    
    int parse_multiple_int_val(const std::map<std::string, std::string> &label_to_values,
                               const std::string &label, unsigned int values[NCHANNELS],
                               int ignore_missing);
    
    int parse_multiple_dbl_val(const std::map<std::string, std::string> &label_to_values,
                               const std::string &label, double values[NCHANNELS], int ignore_missing);
    
    bool read_config_file_lines(const char* const filename,
                                std::map<std::string, std::string> &label_to_values);
    
    int SetBit(int bit, int value);
    
    int ClrBit(int bit, int value);
    
    int SetOrClrBit(int bit, int value, int set);
};


#endif //PIXIE_NET_CONFIGURATIONFILEPARSER_HPP
