/*
 * tsi.c
 *
 *  Created on: Nov 29, 2016
 *      Author: rakes
 */

#include "main.h"

// input channel
int touch_data(int channel)
{
    return raw_counts[channel] - base_counts[channel];
}

// Initiate a touch scan on the given channel
void scan_start(int channel)
{
    TSI0_DATA = TSI_DATA_TSICH(channel) | TSI_DATA_SWTS_MASK;
}

// Return scan data for most recent scan
uint16_t scan_data(void)
{
    TSI0_GENCS |= TSI_GENCS_EOSF_MASK;
    return TSI0_DATA & TSI_DATA_TSICNT_MASK;
}

// Initialize touch input
void touch_init(uint32_t channel_mask)
{
    // Turn on clock gating for TSI and configure touch input
    SIM_SCGC5 |= SIM_SCGC5_TSI_MASK;
    TSI0_GENCS |= (TSI_GENCS_ESOR_MASK          // Enable end of scan interrupt
                   | TSI_GENCS_MODE(0)          // Capactive sensing
                   | TSI_GENCS_REFCHRG(4)       // Reference charge 4 uA
                   | TSI_GENCS_DVOLT(0)         // Voltage rails
                   | TSI_GENCS_EXTCHRG(7)       // External osc charge
                   | TSI_GENCS_PS(4)            // Prescalar divide by 4
                   | TSI_GENCS_NSCN(11)         // Scans per electrode
                   | TSI_GENCS_TSIIEN_MASK      // Input interrupt enable
                   | TSI_GENCS_STPE_MASK        // Enable in STOP mode
                   );

    TSI0_GENCS |= TSI_GENCS_TSIEN_MASK;

    // Read initial (baseline) values for each enabled channel
    int i, first_channel = 0;
    enable_mask = channel_mask;
    for(i=15; i>=0; i--) {
        if((1 << i) & enable_mask) {
            scan_start(i);
            while(!(TSI0_GENCS & TSI_GENCS_EOSF_MASK));      // Wait until done
            	base_counts[i] = scan_data();
            	first_channel = i;
        }
    }

    // Enable TSI interrupts and start the first scan
    NVIC_EnableIRQ(TSI0_IRQn);
    scan_start(first_channel);
}





