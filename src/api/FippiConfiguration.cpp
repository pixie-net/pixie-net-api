/// @file FippiConfiguration.hpp
/// @brief Settings for initial values of the Fippi Configuration
/// @author S. V. Paulauskas
/// @date February, 23, 2020

#include "FippiConfiguration.hpp"

FippiConfiguration::FippiConfiguration() {
    NUMBER_CHANNELS = 4;
    C_CONTROL = 768;
    REQ_RUNTIME = 10;
    POLL_TIME = 900000;
    MODULE_CSRA = 1;
    MODULE_CSRB = 0;
    COINCIDENCE_PATTERN = 65534;
    COINCIDENCE_WINDOW = 0.04;
    RUN_TYPE = 0x501;
    FILTER_RANGE = 1;
    ACCEPT_PATTERN = 32;
    SYNC_AT_START = 1;
    HV_DAC = 1.5;
    SERIAL_IO = 14000;
    AUX_CTRL = 1;
    
    for(unsigned int i = 0; i < NUMBER_CHANNELS; i++) {
        CHANNEL_CSRA[i] = 20;
        CHANNEL_CSRB[i] = 0;
        CHANNEL_CSRC[i] = 0;

        ENERGY_RISETIME[i] = 1.32;
        ENERGY_FLATTOP[i] = 0.32;
        TAU[i] = 0.23;

        TRIGGER_FLATTOP[i] = 0.048;
        TRIGGER_RISETIME[i] = 0.048;
        TRIGGER_THRESHOLD[i] = 15.0;

        ANALOG_GAIN[i] = 2.0;
        DIG_GAIN[i] = 1.0;
        VOFFSET[i] = -0.2;

        TRACE_DELAY[i] = 0.612;
        TRACE_LENGTH[i] = 1.304;
        BINFACTOR[i] = 1;

        BLCUT[i] = 30;
        XDT[i] = 0.0667;
        BASELINE_PERCENT[i] = 10;
        PSA_THRESHOLD[i] = 25;
        PSA_NG_THRESHOLD[i] = 1;
        INTEGRATOR[i] = 0;
        GATE_WINDOW[i] = 0.008;
        GATE_DELAY[i] = 0.008;
        COINC_DELAY[i] = 0.008;
        BLAVG[i] = 65534;
        QDC0_DELAY[i] = 0;
        QDC0_LENGTH[i] = 8;
        QDC1_DELAY[i] = 14;
        QDC1_LENGTH[i] = 32;
        QDC_DIV8[i] = 0;
        MCA2D_SCALEX[i] = 200;
        MCA2D_SCALEY[i] = 0;
        ADC_AVG[i] = 2;
        THRESH_ADC_AVG[i] = 2000;
    }
}