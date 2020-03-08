/// @file RunStatistics.hpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 01, 2020

#ifndef PIXIE_NET_RUNSTATISTICS_HPP
#define PIXIE_NET_RUNSTATISTICS_HPP

#include <map>

class RunStatistics {
public:
    double getRunTime() const;
    
    double getTotalTime() const;
    
    double getEventRate() const;
    
    unsigned int getPsCodeVersion() const;
    
    void setPsCodeVersion(const unsigned int &psCodeVersion);
    
    unsigned int getCsrout() const;
    
    void setCsrout(const unsigned int &csrout);
    
    unsigned int getSystime() const;
    
    void setSystime(const unsigned int &systime);
    
    unsigned int getRunTimeLow() const;
    
    void setRunTimeLow(const unsigned int &RunTimeLow);
    
    unsigned int getRunTimeHigh() const;
    
    void setRunTimeHigh(const unsigned int &RunTimeHigh);
    
    unsigned int getNumEventsLow() const;
    
    void setNumEventsLow(const unsigned int &NumEventsLow);
    
    unsigned int getNumEventsHigh() const;
    
    void setNumEventsHigh(const unsigned int &NumEventsHigh);
    
    unsigned int getBhlEhl() const;
    
    void setBhlEhl(const unsigned int &bhlEhl);
    
    unsigned int getChlFifilength() const;
    
    void setChlFifilength(const unsigned int &chlFifilength);
    
    unsigned int getRevision() const;
    
    void setRevision(const unsigned int &revision);
    
    unsigned int getSnum() const;
    
    void setSnum(const unsigned int &snum);
    
    double getTemperatureAdc() const;
    
    void setTemperatureAdc(const double &temperatureAdc);
    
    double getTemperatureZynq() const;
    
    void setTemperatureZynq(const double &temperatureZynq);
    
    double getCountTime(const unsigned int &channel) const;
    
    double getNtrig(const unsigned int &channel) const;
    
    double getInputCountRate(const unsigned int &channel) const;
    
    double getOutputCountRate(const unsigned int &channel) const;
    
    double getNumEvents() const;
    
    double getNout(const unsigned int &channel) const;
    
    double getFtdt(const unsigned int &channel) const;
    
    double getSfdt(const unsigned int &channel) const;
    
    double getNppi(const unsigned int &channel) const;
    
    double getGcount(const unsigned int &channel) const;
    
    double getGcountRate(const unsigned int &channel) const;
    
    double getPassPileupRate(const unsigned int &channel) const;
    
    double getGdt(const unsigned int &channel) const;
    
    unsigned int getOcr(const unsigned int &channel) const;
    
    void setOcr(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getIcr(const unsigned int &channel) const;
    
    void setIcr(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getCountTimeLow(const unsigned int &channel) const;
    
    void setCountTimeLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getCountTimeHigh(const unsigned int &channel) const;
    
    void setCountTimeHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNtrigLow(const unsigned int &channel) const;
    
    void setNtrigLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNtrigHigh(const unsigned int &channel) const;
    
    void setNtrigHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getFtdtLow(const unsigned int &channel) const;
    
    void setFtdtLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getFtdtHigh(const unsigned int &channel) const;
    
    void setFtdtHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getSfdtLow(const unsigned int &channel) const;
    
    void setSfdtLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getSfdtHigh(const unsigned int &channel) const;
    
    void setSfdtHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getGcountLow(const unsigned int &channel) const;
    
    void setGcountLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getGcountHigh(const unsigned int &channel) const;
    
    void setGcountHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNoutLow(const unsigned int &channel) const;
    
    void setNoutLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNoutHigh(const unsigned int &channel) const;
    
    void setNoutHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getGdtLow(const unsigned int &channel) const;
    
    void setGdtLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getGdtHigh(const unsigned int &channel) const;
    
    void setGdtHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNppiLow(const unsigned int &channel) const;
    
    void setNppiLow(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getNppiHigh(const unsigned int &channel) const;
    
    void setNppiHigh(const unsigned int &channel, const unsigned int &value);
    
    unsigned int getPsaLicensed() const;
    
    void setPsaLicensed(const unsigned int &psaLicensed);
    
    unsigned int getActive() const;
    
    void setActive(const unsigned int &active);
    
    unsigned int getPtpRequired() const;
    
    void setPtpRequired(const unsigned int &ptpRequired);
    
    unsigned int getHwVersion() const;
    
    void setHwVersion(unsigned int hwVersion);

    unsigned int getTotalTimeLow() const;
    
    void setTotalTimeLow(unsigned int totalTimeLow);
    
    unsigned int getTotalTimeHigh() const;
    
    void setTotalTimeHigh(unsigned int totalTimeHigh);
    
private:
    unsigned int total_time_low;
    unsigned int total_time_high;
    unsigned int ps_code_version;
    unsigned int psa_licensed;
    unsigned int csrout;
    unsigned int systime;
    unsigned int run_time_low;
    unsigned int run_time_high;
    
    unsigned int num_events_low;
    unsigned int num_events_high;
    unsigned int bhl_ehl;
    unsigned int active;
    unsigned int ptp_required;
    unsigned int chl_fifilength;
    unsigned int revision;
    unsigned int snum;
    double temperature_adc;
    double temperature_zynq;
    unsigned int hw_version;
    
    std::map<unsigned int, unsigned int> ocr;
    std::map<unsigned int, unsigned int> icr;
    std::map<unsigned int, unsigned int> count_time_low;
    std::map<unsigned int, unsigned int> count_time_high;
    std::map<unsigned int, unsigned int> ntrig_low;
    std::map<unsigned int, unsigned int> ntrig_high;
    std::map<unsigned int, unsigned int> ftdt_low;
    std::map<unsigned int, unsigned int> ftdt_high;
    std::map<unsigned int, unsigned int> sfdt_low;
    std::map<unsigned int, unsigned int> sfdt_high;
    std::map<unsigned int, unsigned int> gcount_low;
    std::map<unsigned int, unsigned int> gcount_high;
    std::map<unsigned int, unsigned int> nout_low;
    std::map<unsigned int, unsigned int> nout_high;
    std::map<unsigned int, unsigned int> gdt_low;
    std::map<unsigned int, unsigned int> gdt_high;
    std::map<unsigned int, unsigned int> nppi_low;
    std::map<unsigned int, unsigned int> nppi_high;
};


#endif //PIXIE_NET_RUNSTATISTICS_HPP
