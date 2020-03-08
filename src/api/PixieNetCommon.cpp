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
#include <fstream>
#include <string>

#include <cstdio>

#include <unistd.h>

#include "PixieNetDefs.hpp"
#include "PixieNetCommon.hpp"


void I2Cstart(volatile unsigned int *mapped) {
    unsigned int mval;
    // I2C start
    mval = 7;   // SDA = 1; SCL = 1; CTRL = 1
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 6;   // SDA = 0; SCL = 1; CTRL = 1
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
}


void I2Cstop(volatile unsigned int *mapped) {
    unsigned int mval;
    // I2C stop
    mval = 4;   // SDA = 0; SCL = 0; CTRL = 1
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    
    mval = 6;   // SDA = 0; SCL = 1; CTRL = 1
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 7;   // SDA = 1; SCL = 1; CTRL = 1
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
}

void I2Cslaveack(volatile unsigned int *mapped) {
    unsigned int mval;
    // I2C acknowledge
    mval = 0x0000;   // clear SCL and CTRL to give slave control of SDA     
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 2;   // set SCL     
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 0x0000;   // clear SCL and CTRL to give slave control of SDA   
    // for PLL
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    // now can read SDA bit for ACK
}

void I2Cmasterack(volatile unsigned int *mapped) {
    unsigned int mval;
    // I2C acknowledge
    mval = 0x0004;   // clear SCL and SDA but not CTRL to keep control of SDA     
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 2;   // set SCL     
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
}

void I2Cmasternoack(volatile unsigned int *mapped) {
    unsigned int mval;
    // I2C acknowledge
    mval = 0x0004;   // clear SCL and SDA but not CTRL to keep control of SDA     
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
    mval = 3;   // set SCL  and SDA   
    mapped[AI2CREG] = mval;
    usleep(I2CWAIT);
}


void I2Cbytesend(volatile unsigned int *mapped, unsigned int *data) {
    unsigned int mval, k;
    // I2C byte send
    // SDA is captured during the low to high transition of SCL
    mval = 4;   // SDA = 0; SCL = 0; CTRL = 1
    for (k = 0; k < 8; k++) {
        //  printf("Sending a bit\n");
        mval = mval & 0x0005;   // clear SCL
        mapped[AI2CREG] = mval;
        usleep(I2CWAIT);
        if (data[7 - k])
            mval = 5;            // SDA = 1; SCL = 0; CTRL = 1
        else
            mval = 4;            // SDA = 0; SCL = 0; CTRL = 1
        mapped[AI2CREG] = mval;
        usleep(I2CWAIT);
        mval = mval | 0x0002;   // set SCL
        mapped[AI2CREG] = mval;
        usleep(I2CWAIT);
    }
    // for PLL
    mval = mval & 0x0005;   // clear SCL
    mapped[AI2CREG] = mval;
}

void I2Cbytereceive(volatile unsigned int *mapped, unsigned int *data) {
    // I2C byte send
    unsigned int mval, k;
    // SDA is captured during the low to high transition of SCL
    mval = 0;   // SDA = 0; SCL = 0; CTRL = 0
    for (k = 0; k < 8; k++) {
        mval = 0;   // SDA = 0; SCL = 0; CTRL = 0
        mapped[AI2CREG] = mval;
        usleep(I2CWAIT);
        mval = 2;   // set SCL
        mapped[AI2CREG] = mval;
        usleep(I2CWAIT);
        mapped[AOUTBLOCK] = OB_EVREG;
        mval = mapped[ACSROUT];
        //   printf("CSRout %x I2Cwait %d \n",mval,I2CWAIT);
        if (mval & 0x4)          // test for SDA out bit
            data[7 - k] = 1;
        else
            data[7 - k] = 0;
        //   mapped[AI2CREG] = mval;   not for PLL
        usleep(I2CWAIT);
    }
}


int hwinfo(volatile unsigned int *mapped)
// returns 32bit hwrev_sn, or 0 on error
{
    unsigned int mval, i2cdata[8];
    unsigned int revsn;
    int k;
    
    // ---------------- read EEPROM ---------------------------
    mapped[AOUTBLOCK] = OB_EVREG;     // read from event registers
    mval = mapped[ABRDINFO];
    //printf("ABRDINGFO 0x%04X\n",mval);
    mapped[AOUTBLOCK] = OB_IOREG;     // read from i/o registers
    
    unsigned int ctrl[8];
    ctrl[7] = (mval & 0x800000) >> 23;
    ctrl[6] = (mval & 0x400000) >> 22;
    ctrl[5] = (mval & 0x200000) >> 21;
    ctrl[4] = (mval & 0x100000) >> 20;
    ctrl[3] = (mval & 0x080000) >> 19;
    ctrl[2] = (mval & 0x040000) >> 18;
    ctrl[1] = (mval & 0x020000) >> 17;
    ctrl[0] = (mval & 0x010000) >> 16;
    
    I2Cstart(mapped);
    ctrl[0] = 0;   // R/W*
    I2Cbytesend(mapped, ctrl);     // I2C control byte: write
    I2Cslaveack(mapped);
    
    i2cdata[7] = (mval & 0x8000) >> 15;
    i2cdata[6] = (mval & 0x4000) >> 14;
    i2cdata[5] = (mval & 0x2000) >> 13;
    i2cdata[4] = (mval & 0x1000) >> 12;
    i2cdata[3] = (mval & 0x0800) >> 11;
    i2cdata[2] = (mval & 0x0400) >> 10;
    i2cdata[1] = (mval & 0x0200) >> 9;
    i2cdata[0] = (mval & 0x0100) >> 8;
    I2Cbytesend(mapped, i2cdata);
    I2Cslaveack(mapped);
    
    i2cdata[7] = (mval & 0x0080) >> 7;
    i2cdata[6] = (mval & 0x0040) >> 6;
    i2cdata[5] = (mval & 0x0020) >> 5;
    i2cdata[4] = (mval & 0x0010) >> 4;
    i2cdata[3] = (mval & 0x0008) >> 3;
    i2cdata[2] = (mval & 0x0004) >> 2;
    i2cdata[1] = (mval & 0x0002) >> 1;
    i2cdata[0] = (mval & 0x0001);
    I2Cbytesend(mapped, i2cdata);
    I2Cslaveack(mapped);
    
    // read data byte 0..1
    mval = 0;
    ctrl[0] = 1;   // R/W*         // now read
    
    usleep(100);
    I2Cstart(mapped);               //restart
    I2Cbytesend(mapped, ctrl);
    I2Cslaveack(mapped);
    I2Cbytereceive(mapped, i2cdata);
    for (k = 0; k < 8; k++)
        if (i2cdata[k])
            mval = mval + (1 << (k + 0));
    I2Cmasterack(mapped);
    
    usleep(100);
    I2Cstart(mapped);               //restart
    I2Cbytesend(mapped, ctrl);
    I2Cslaveack(mapped);
    I2Cbytereceive(mapped, i2cdata);
    for (k = 0; k < 8; k++)
        if (i2cdata[k])
            mval = mval + (1 << (k + 8));
    I2Cmasterack(mapped);
    
    //printf("I2C read Revision 0x%04X\n",mval);
    if ((mval == PN_BOARD_VERSION_12_250_A) ||
        (mval == PN_BOARD_VERSION_12_250_B) ||
        (mval == PN_BOARD_VERSION_12_250_B_PTP) ||
        (mval == 0))
        //printf("HW Revision 0x%04X\n",mval);
        revsn = mval << 16;
    else {
        printf("Unsupported HW Revision 0x%04X\n", mval);
        return (0);
    }
    
    // read data byte 1..2
    mval = 0;
    ctrl[0] = 1;   // R/W*         // now read
    
    usleep(100);
    I2Cstart(mapped);               //restart
    I2Cbytesend(mapped, ctrl);
    I2Cslaveack(mapped);
    I2Cbytereceive(mapped, i2cdata);
    for (k = 0; k < 8; k++)
        if (i2cdata[k])
            mval = mval + (1 << (k + 0));
    I2Cmasterack(mapped);
    
    usleep(100);
    I2Cstart(mapped);               //restart
    I2Cbytesend(mapped, ctrl);
    I2Cslaveack(mapped);
    I2Cbytereceive(mapped, i2cdata);
    for (k = 0; k < 8; k++)
        if (i2cdata[k])
            mval = mval + (1 << (k + 8));
    I2Cmasterack(mapped);
    
    //printf("I2C read Serial number %d \n",mval);
    
    mapped[ABVAL] = mval;
    revsn = revsn + (mval & 0xFFFF);
    //printf("Revision %04X, Serial Number %d \n",(revsn>>16), revsn&0xFFFF);
    
    //  I2Cmasternoack(mapped);
    I2Cstop(mapped);
    return (revsn);
}


float board_temperature(volatile unsigned int *mapped) {
    unsigned int i2cdata[8];
    
    I2Cstart(mapped);
    
    // I2C addr byte
    i2cdata[7] = 1;
    i2cdata[6] = 0;
    i2cdata[5] = 0;
    i2cdata[4] = 1;
    i2cdata[3] = 1;   // A2
    i2cdata[2] = 0;   // A1
    i2cdata[1] = 0;   // A0
    i2cdata[0] = 1;   // R/W*
    I2Cbytesend(mapped, i2cdata);
    
    I2Cslaveack(mapped);
    
    I2Cbytereceive(mapped, i2cdata);
    unsigned int temperature_val = 0;
    for (int k = 0; k < 7; k++)
        if (i2cdata[k])
            temperature_val = temperature_val + (1 << (k + 8));
    
    unsigned int Tsign = i2cdata[7];
    //printf("Temperature: bits 0x%x \n",mval >> 8);
    
    I2Cmasterack(mapped);
    I2Cbytereceive(mapped, i2cdata);     // second byte has fractional portion, no use
    I2Cmasternoack(mapped);
    I2Cstop(mapped);
    
    return (Tsign ? -1.0 : 1.0) * temperature_val / 256.0f;
}//float board_temperature( volatile unsigned int *mapped )

/// Calculates the ADC temperature
/// See https://forums.xilinx.com/t5/Processor-System-Design/Zynq-zc706-XADC-Reading-External-Voltages/m-p/593620/highlight/true#M7052
/// and https://forums.xilinx.com/t5/Embedded-Linux/Zynq-Linux-XADC-Temperature-Sensor/td-p/323677
/// for the equation to calculate the temperature.
float zynq_temperature() {
    float raw_temperature = -999., offset = 0., scale = 1.;
    
    std::ifstream file("/sys/devices/soc0/amba/f8007100.adc/iio:device0/in_temp0_raw");
    file >> raw_temperature;
    file.close();
    
    std::ifstream offset_file("/sys/devices/soc0/amba/f8007100.adc/iio:device0/in_temp0_offset");
    offset_file >> offset;
    offset_file.close();
    
    std::ifstream scale_file("/sys/devices/soc0/amba/f8007100.adc/iio:device0/in_temp0_scale");
    scale_file >> scale;
    scale_file.close();

    return (raw_temperature + offset) * scale / 1000;
}
