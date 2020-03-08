/// @file RunStatisticsPrinter.cpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 07, 2020

#include "RunStatisticsPrinter.hpp"

#include <iostream>
#include <sstream>

#include "PixieNetDefs.hpp"

std::string RunStatisticsPrinter::format_channel_for_json(const unsigned int &channel,
                                                          const RunStatistics &stats) const {
    std::stringstream stream;
    stream << "'" << channel << "': {"
           << "'count_time': " << stats.getCountTime(channel) << ","
           << "'input_count_rate': " << stats.getInputCountRate(channel) << ","
           << "'output_count_rate': " << stats.getOutputCountRate(channel) << ","
           << "'ftdt': " << stats.getFtdt(channel) << ","
           << "'sfdt': " << stats.getSfdt(channel) << ","
           << "'pass_pileup_rate': " << stats.getPassPileupRate(channel) << ","
           << "'gate_rate': " << stats.getGcountRate(channel) << ","
           << "'gdt': " << stats.getGdt(channel) << ","
           << "'oor': " << stats.getOcr(channel) << ","
           << "'icr': " << stats.getIcr(channel) << ","
           << "'count_time_low': " << stats.getCountTimeLow(channel) << ","
           << "'count_time_high': " << stats.getCountTimeHigh(channel) << ","
           << "'ntrig_low': " << stats.getNtrigLow(channel) << ","
           << "'ntrig_high': " << stats.getNtrigHigh(channel) << ","
           << "'ftdt_low': " << stats.getFtdtLow(channel) << ","
           << "'ftdt_high': " << stats.getFtdtHigh(channel) << ","
           << "'sfdt_low': " << stats.getSfdtLow(channel) << ","
           << "'sfdt_high': " << stats.getSfdtHigh(channel) << ","
           << "'gcount_low': " << stats.getGcountLow(channel) << ","
           << "'gcount_high': " << stats.getGcountHigh(channel) << ","
           << "'nout_low': " << stats.getNoutLow(channel) << ","
           << "'nout_high': " << stats.getNoutHigh(channel) << ","
           << "'gdt_low': " << stats.getGdtLow(channel) << ","
           << "'gdt_high': " << stats.getGdtHigh(channel) << ","
           << "'nppi_low': " << stats.getNppiLow(channel) << ","
           << "'nppi_high': " << stats.getNppiHigh(channel) << ","
           << "}";
    return stream.str();
}

void RunStatisticsPrinter::print_statistics(const RunStatistics &stats) {
    std::stringstream stream;
    stream << "{" << "'module': {"
           << "'run_time': " << stats.getRunTime() << ","
           << "'total_time': " << stats.getTotalTime() << ","
           << "'event_rate': " << stats.getEventRate() << ","
           << "'ps_code_version': " << stats.getPsCodeVersion() << ","
           << "'active': " << stats.getActive() << ","
           << "'psa_licensed': " << stats.getPsaLicensed() << ","
           << "'ptp_req': " << stats.getPtpRequired() << ","
           << "'csrout': " << stats.getCsrout() << ","
           << "'systime': " << stats.getSystime() << ","
           << "'runtime_low': " << stats.getRunTimeLow() << ","
           << "'runtime_high': " << stats.getRunTimeHigh() << ","
           << "'total_time_low': " << stats.getTotalTimeLow() << ","
           << "'total_time_high': " << stats.getTotalTimeHigh() << ","
           << "'numevents_low': " << stats.getNumEventsLow() << ","
           << "'numevents_high': " << stats.getNumEventsHigh() << ","
           << "'bhl_ehl': " << stats.getBhlEhl() << ","
           << "'chl_fifilength': " << stats.getChlFifilength() << ","
           << "'revision': " << stats.getRevision() << ","
           << "'snum': " << stats.getSnum() << ","
           << "'adc_temp': " << stats.getTemperatureAdc() << ","
           << "'zynq_temp': " << stats.getTemperatureZynq() << ","
           << "}, 'channel': {";
    
    for (unsigned int chan = 0; chan < NCHANNELS; chan++)
        stream << format_channel_for_json(chan, stats) << ",";
    
    stream << "}}";
    std::cout << stream.str() << std::endl;
}