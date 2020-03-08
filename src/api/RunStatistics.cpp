/// @file RunStatistics.cpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 01, 2020

#include "RunStatistics.hpp"

#include <cmath>

unsigned int RunStatistics::getPsCodeVersion() const {
    return ps_code_version;
}

void RunStatistics::setPsCodeVersion(const unsigned int &psCodeVersion) {
    ps_code_version = psCodeVersion;
}

unsigned int RunStatistics::getCsrout() const {
    return csrout;
}

void RunStatistics::setCsrout(const unsigned int &csrout) {
    RunStatistics::csrout = csrout;
}

unsigned int RunStatistics::getSystime() const {
    return systime;
}

void RunStatistics::setSystime(const unsigned int &value) {
    RunStatistics::systime = value;
}

unsigned int RunStatistics::getRunTimeLow() const {
    return run_time_low;
}

void RunStatistics::setRunTimeLow(const unsigned int &RunTimeLow) {
    run_time_low = RunTimeLow;
}

unsigned int RunStatistics::getRunTimeHigh() const {
    return run_time_high;
}

void RunStatistics::setRunTimeHigh(const unsigned int &RunTimeHigh) {
    run_time_high = RunTimeHigh;
}

unsigned int RunStatistics::getNumEventsLow() const {
    return num_events_low;
}

void RunStatistics::setNumEventsLow(const unsigned int &NumEventsLow) {
    num_events_low = NumEventsLow;
}

unsigned int RunStatistics::getNumEventsHigh() const {
    return num_events_high;
}

void RunStatistics::setNumEventsHigh(const unsigned int &NumEventsHigh) {
    num_events_high = NumEventsHigh;
}

unsigned int RunStatistics::getBhlEhl() const {
    return bhl_ehl;
}

void RunStatistics::setBhlEhl(const unsigned int &bhlEhl) {
    bhl_ehl = bhlEhl;
}

unsigned int RunStatistics::getChlFifilength() const {
    return chl_fifilength;
}

void RunStatistics::setChlFifilength(const unsigned int &chlFifilength) {
    chl_fifilength = chlFifilength;
}

unsigned int RunStatistics::getRevision() const {
    return revision;
}

void RunStatistics::setRevision(const unsigned int &revision) {
    RunStatistics::revision = revision;
}

unsigned int RunStatistics::getSnum() const {
    return snum;
}

void RunStatistics::setSnum(const unsigned int &snum) {
    RunStatistics::snum = snum;
}

double RunStatistics::getTemperatureAdc() const {
    return temperature_adc;
}

void RunStatistics::setTemperatureAdc(const double &temperatureAdc) {
    temperature_adc = temperatureAdc;
}

double RunStatistics::getTemperatureZynq() const {
    return temperature_zynq;
}

void RunStatistics::setTemperatureZynq(const double &temperatureZynq) {
    temperature_zynq = temperatureZynq;
}

double RunStatistics::getRunTime() const {
    if (run_time_low == 0)
        return 0;
    return (run_time_low + run_time_high * std::pow(2, 32)) * 1.e-9;
}

double RunStatistics::getNumEvents() const {
    return num_events_low + num_events_high * std::pow(2, 32);
}

double RunStatistics::getEventRate() const {
    if (getRunTime() == 0)
        return 0;
    return getNumEvents() / getRunTime();
}

double RunStatistics::getCountTime(const unsigned int &channel) const {
    return (getCountTimeLow(channel) + getCountTimeHigh(channel) * std::pow(2, 32)) * 1.e-9;
}

double RunStatistics::getNtrig(const unsigned int &channel) const {
    return getNtrigLow(channel) + getNtrigHigh(channel) * std::pow(2, 32);
}

double RunStatistics::getInputCountRate(const unsigned int &channel) const {
    if (getCountTime(channel) - getFtdt(channel) == 0)
        return 0;
    return getNtrig(channel) / (getCountTime(channel) - getFtdt(channel));
}

double RunStatistics::getNout(const unsigned int &channel) const {
    return getNoutLow(channel) + getNoutHigh(channel) * std::pow(2, 32);
}

double RunStatistics::getOutputCountRate(const unsigned int &channel) const {
    if (getCountTime(channel) == 0)
        return 0;
    return getNout(channel) / getCountTime(channel);
}

double RunStatistics::getFtdt(const unsigned int &channel) const {
    return getFtdtLow(channel) + getFtdtHigh(channel) * std::pow(2, 32);
}

double RunStatistics::getSfdt(const unsigned int &channel) const {
    return (getSfdtLow(channel) + getSfdtHigh(channel) * std::pow(2, 32)) * 1.e-9;
}

double RunStatistics::getNppi(const unsigned int &channel) const {
    return getNppiLow(channel) + getNppiHigh(channel) * std::pow(2, 32);
}

double RunStatistics::getPassPileupRate(const unsigned int &channel) const {
    if (getCountTime(channel) == 0)
        return 0;
    return getNppi(channel) / getCountTime(channel);
}

double RunStatistics::getGcount(const unsigned int &channel) const {
    return getGcountLow(channel) + getGcountHigh(channel) * std::pow(2, 32);
}

/// AKA gate rate
double RunStatistics::getGcountRate(const unsigned int &channel) const {
    if (getCountTime(channel) == 0)
        return 0;
    return getGcount(channel) / getCountTime(channel);
}

/// AKA gate time
double RunStatistics::getGdt(const unsigned int &channel) const {
    return (getGdtLow(channel) + getGdtHigh(channel) * std::pow(2, 32)) * 1.e-9;
}

unsigned int RunStatistics::getOor(const unsigned int &channel) const {
    return oor.at(channel);
}

void RunStatistics::getOor(const unsigned int &channel, const unsigned int &value) {
    RunStatistics::oor[channel] = value;
}

unsigned int RunStatistics::getIcr(const unsigned int &channel) const {
    return icr.at(channel);
}

void RunStatistics::setIcr(const unsigned int &channel, const unsigned int &value) {
    RunStatistics::icr[channel] = value;
}

unsigned int RunStatistics::getCountTimeLow(const unsigned int &channel) const {
    return count_time_low.at(channel);
}

void RunStatistics::setCountTimeLow(const unsigned int &channel, const unsigned int &value) {
    count_time_low[channel] = value;
}

unsigned int RunStatistics::getCountTimeHigh(const unsigned int &channel) const {
    return count_time_high.at(channel);
}

void RunStatistics::setCountTimeHigh(const unsigned int &channel, const unsigned int &value) {
    count_time_high[channel] = value;
}

unsigned int RunStatistics::getNtrigLow(const unsigned int &channel) const {
    return ntrig_low.at(channel);
}

void RunStatistics::setNtrigLow(const unsigned int &channel, const unsigned int &value) {
    ntrig_low[channel] = value;
}

unsigned int RunStatistics::getNtrigHigh(const unsigned int &channel) const {
    return ntrig_high.at(channel);
}

void RunStatistics::setNtrigHigh(const unsigned int &channel, const unsigned int &value) {
    ntrig_high[channel] = value;
}

unsigned int RunStatistics::getFtdtLow(const unsigned int &channel) const {
    return ftdt_low.at(channel);
}

void RunStatistics::setFtdtLow(const unsigned int &channel, const unsigned int &value) {
    ftdt_low[channel] = value;
}

unsigned int RunStatistics::getFtdtHigh(const unsigned int &channel) const {
    return ftdt_high.at(channel);
}

void RunStatistics::setFtdtHigh(const unsigned int &channel, const unsigned int &value) {
    ftdt_high[channel] = value;
}

unsigned int RunStatistics::getSfdtLow(const unsigned int &channel) const {
    return sfdt_low.at(channel);
}

void RunStatistics::setSfdtLow(const unsigned int &channel, const unsigned int &value) {
    sfdt_low[channel] = value;
}

unsigned int RunStatistics::getSfdtHigh(const unsigned int &channel) const {
    return sfdt_high.at(channel);
}

void RunStatistics::setSfdtHigh(const unsigned int &channel, const unsigned int &value) {
    sfdt_high[channel] = value;
}

unsigned int RunStatistics::getGcountLow(const unsigned int &channel) const {
    return gcount_low.at(channel);
}

void RunStatistics::setGcountLow(const unsigned int &channel, const unsigned int &value) {
    gcount_low[channel] = value;
}

unsigned int RunStatistics::getGcountHigh(const unsigned int &channel) const {
    return gcount_high.at(channel);
}

void RunStatistics::setGcountHigh(const unsigned int &channel, const unsigned int &value) {
    gcount_high[channel] = value;
}

unsigned int RunStatistics::getNoutLow(const unsigned int &channel) const {
    return nout_low.at(channel);
}

void RunStatistics::setNoutLow(const unsigned int &channel, const unsigned int &value) {
    nout_low[channel] = value;
}

unsigned int RunStatistics::getNoutHigh(const unsigned int &channel) const {
    return nout_high.at(channel);
}

void RunStatistics::setNoutHigh(const unsigned int &channel, const unsigned int &value) {
    nout_high[channel] = value;
}

unsigned int RunStatistics::getGdtLow(const unsigned int &channel) const {
    return gdt_low.at(channel);
}

void RunStatistics::setGdtLow(const unsigned int &channel, const unsigned int &value) {
    gdt_low[channel] = value;
}

unsigned int RunStatistics::getGdtHigh(const unsigned int &channel) const {
    return gdt_high.at(channel);
}

void RunStatistics::setGdtHigh(const unsigned int &channel, const unsigned int &value) {
    gdt_high[channel] = value;
}

unsigned int RunStatistics::getNppiLow(const unsigned int &channel) const {
    return nppi_low.at(channel);
}

void RunStatistics::setNppiLow(const unsigned int &channel, const unsigned int &value) {
    nppi_low[channel] = value;
}

unsigned int RunStatistics::getNppiHigh(const unsigned int &channel) const {
    return nppi_high.at(channel);
}

void RunStatistics::setNppiHigh(const unsigned int &channel, const unsigned int &value) {
    nppi_high[channel] = value;
}

unsigned int RunStatistics::getPsaLicensed() const {
    return psa_licensed;
}

void RunStatistics::setPsaLicensed(const unsigned int &psaLicensed) {
    psa_licensed = psaLicensed;
}

unsigned int RunStatistics::getActive() const {
    return active;
}

void RunStatistics::setActive(const unsigned int &active) {
    RunStatistics::active = active;
}

unsigned int RunStatistics::getPtpRequired() const {
    return ptp_required;
}

void RunStatistics::setPtpRequired(const unsigned int &ptpRequired) {
    ptp_required = ptpRequired;
}

unsigned int RunStatistics::getHwVersion() const {
    return hw_version;
}

void RunStatistics::setHwVersion(unsigned int hwVersion) {
    hw_version = hwVersion;
}

unsigned int RunStatistics::getTotalTimeLow() const {
    return total_time_low;
}

void RunStatistics::setTotalTimeLow(unsigned int totalTimeLow) {
    total_time_low = totalTimeLow;
}

unsigned int RunStatistics::getTotalTimeHigh() const {
    return total_time_high;
}

void RunStatistics::setTotalTimeHigh(unsigned int totalTimeHigh) {
    total_time_high = totalTimeHigh;
}

double RunStatistics::getTotalTime() const {
    return (total_time_low + total_time_high * std::pow(2., 32)) * 1.e-9;
}