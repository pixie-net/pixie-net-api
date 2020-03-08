/// @file RunStatistics.cpp
/// @brief 
/// @author S. V. Paulauskas
/// @date March 01, 2020

#include "RunStatisticsInterface.hpp"

#include "PixieNetDefs.hpp"
#include "PixieNetCommon.hpp"
#include "RunStatistics.hpp"

RunStatisticsInterface::RunStatisticsInterface(volatile unsigned int *mapped) {
    RunStatisticsInterface::mapped = mapped;
}

RunStatistics RunStatisticsInterface::get_statistics() {
    mapped[AOUTBLOCK] = OB_RSREG;
    RunStatistics stats = read_runstats();
    mapped[AOUTBLOCK] = OB_IOREG;
    return stats;
}

RunStatistics RunStatisticsInterface::read_runstats() {
    RunStatistics runstats;
    unsigned int m[N_PL_RS_PAR], c[NCHANNELS][N_PL_RS_PAR];
    
    // read _used_ RS values (32bit) from FPGA
    // at this point, raw binary values; later conversion into count rates etc
    for (unsigned int k = 0; k < N_USED_RS_PAR; k++) {
        m[k] = mapped[ARS0_MOD + k];
        c[0][k] = mapped[ARS0_CH0 + k];
        c[1][k] = mapped[ARS0_CH1 + k];
        c[2][k] = mapped[ARS0_CH2 + k];
        c[3][k] = mapped[ARS0_CH3 + k];
    }
    
    runstats.setCsrout(m[1]);
    runstats.setSystime(m[2]);
    runstats.setRunTimeLow(m[3]);
    runstats.setRunTimeHigh(m[4]);
    runstats.setTotalTimeLow(m[5]);
    runstats.setTotalTimeHigh(m[6]);
    runstats.setNumEventsLow(m[7]);
    runstats.setNumEventsHigh(m[8]);
    runstats.setBhlEhl(m[9]);
    runstats.setChlFifilength(m[10]);
    runstats.setRevision(m[11]);
    runstats.setSnum(m[12]);
    
    runstats.setTemperatureAdc(board_temperature(mapped));
    runstats.setTemperatureZynq(zynq_temperature());
    runstats.setHwVersion((0xFFFF & (hwinfo(mapped) >> 16)));
    
    runstats.setActive((runstats.getCsrout() & 0x00002000) >> 13);
    runstats.setPsaLicensed((runstats.getCsrout() & 0x00000400) >> 10);
    runstats.setPtpRequired( (runstats.getCsrout() & 0x00000020) >> 5);
    
    runstats.setPsCodeVersion(PS_CODE_VERSION);
    
    for(unsigned int chan = 0; chan < NCHANNELS; chan++){
        runstats.getOor(chan, c[chan][1]);
        runstats.setIcr(chan, ICRSCALE * c[chan][2]);
        runstats.setCountTimeLow(chan, c[chan][3]);
        runstats.setCountTimeHigh(chan, c[chan][4]);
        runstats.setNtrigLow(chan, c[chan][5]);
        runstats.setNtrigHigh(chan, c[chan][6]);
        runstats.setFtdtLow(chan, c[chan][7]);
        runstats.setFtdtHigh(chan, c[chan][8]);
        runstats.setSfdtLow(chan, c[chan][9]);
        runstats.setSfdtHigh(chan, c[chan][10]);
        runstats.setGcountLow(chan, c[chan][11]);
        runstats.setGcountHigh(chan, c[chan][12]);
        runstats.setNoutLow(chan, c[chan][13]);
        runstats.setNoutHigh(chan, c[chan][14]);
        runstats.setGdtLow(chan, c[chan][15]);
        runstats.setGdtHigh(chan, c[chan][16]);
        runstats.setNppiLow(chan, c[chan][17]);
        runstats.setNppiHigh(chan, c[chan][18]);
    }
    return runstats;
}