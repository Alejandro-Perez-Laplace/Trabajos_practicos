//Bibliotecas incluidas
#include <SPI.h> //Comunicacion SPI
// Definiciones de registros
#define ext_ctrl            0x100 // R/W External LNA/PA and internal PA control configuration bits
#define fsk_preamble        0x102 // R/W GFSK/FSK preamble length configuration
#define cca1                0x105 // R/W RSSI threshold for CCA
#define cca2                0x106 // R/W CCA mode configuration
#define buffercfg           0x107 // R/W RX and TX Buffer configuration
#define pkt_cfg             0x108 // R/W Firmware download module enable/FCS/CRC control
#define delaycfg0           0x109 // R/W RC_RX command to SFD or SWD search delay
#define delaycfg1           0x10A // R/W RC_TX command to TX state delay
#define delaycfg2           0x10B // R/W MAC delay extension
#define sync_word0          0x10C // R/W Sync Word Bits[7:0] of [23:0]
#define sync_word1          0x10D // R/W Sync Word Bits[15:8] of [23:0]
#define sync_word2          0x10E // R/W Sync Word Bits[23:16] of [23:0]
#define sync_config         0x10F // R/W Sync word configuration
#define fsk_preamble_config 0x111 // R/W GFSK/FSK preamble configuration
#define rc_cfg              0x13E // R/W Packet/SPORT mode configuration
#define ch_freq0            0x300 // R/W Channel frequency settings—low byte
#define ch_freq1            0x301 // R/W Channel frequency settings—middle byte
#define ch_freq2            0x302 // R/W Channel frequency settings—two MSBs
#define tx_fd               0x304 // R/W Transmit frequency deviation register
#define dm_cfg0             0x305 // R/W Receive discriminator bandwidth register
#define tx_m                0x306 // R/W Gaussian and preemphasis filter configuration
#define rrb                 0x30C // R RSSI readback register
#define lrb                 0x30D // R Signal quality indicator quality readback register
#define dr0                 0x30E // R/W Data rate [bps/100], Bits[15:8] of [15:0]
#define dr1                 0x30F // R/W Data rate [bps/100], Bits[7:0] of [15:0]
#define prampg              0x313 // R/W PRAM page
#define txpb                0x314 // R/W Transmit packet storage base address
#define rxpb                0x315 // R/W Receive packet storage base address
#define tmr_cfg0            0x316 // R/W Wake-up timer configuration register—high byte
#define tmr_cfg1            0x317 // R/W Wake-up timer configuration register—low byte
#define tmr_rld0            0x318 // R/W Wake-up timer value register—high byte
#define tmr_rld1            0x319 // R/W Wake-up timer value register—low byte
#define tmr_ctrl            0x31A // R/W Wake-up timer timeout flag configuration register
#define wuc_32khzosc_status 0x31B // R 32 kHz oscillator/WUC status
#define pd_aux              0x31E // R/W Battery monitor and external PA bias enable
#define gp_cfg              0x32C // R/W GPIO configuration
#define gp_out              0x32D // R/W GPIO configuration
#define synt                0x335 // R/W Synthesizer lock time
#define rc_cal_cfg          0x33D // R/W RC calibration setting
#define vco_band_ovrw       0x353 // R/W Overwrite value for the VCO frequency band.
#define vco_idac_ovrw       0x354 // R/W Overwrite value for the VCO bias current DAC.
#define vco_ovwr_cfg        0x355 // R/W VCO calibration settings overwrite enable
#define pa_bias             0x36E // R/W PA bias control
#define vco_cal_cfg         0x36F // R/W VCO calibration parameters
#define xto26_trim_cal      0x371 // R/W 26 MHz crystal oscillator configuration
#define vco_band_rb         0x380 // R Readback VCO band after calibration
#define vco_idac_rb         0x381 // R Readback of the VCO bias current DAC after calibration
#define iirf_cfg            0x389 // R/W BB filter decimation rate
#define dm_cfg1             0x38B // R/W Postdemodulator filter bandwidth
#define rxcal0              0x395 // R/W Receiver baseband filter calibration word, LSB
#define rxcal1              0x396 // R/W Receiver baseband filter calibration word, MSB
#define rxfe_cfg            0x39B // R/W Receive baseband filter bandwidth and LNA selection
#define pa_rr               0x3A7 // R/W PA ramp rate
#define pa_cfg              0x3A8 // R/W PA output stage current control
#define extpa_cfg           0x3A9 // R/W External PA bias DAC configuration
#define extpa_msc           0x3AA // R/W External PA interface circuit configuration
#define adc_rbk             0x3AE // R ADC readback
#define agc_cfg1            0x3B2 // R/W AGC configuration parameters
#define agc_max             0x3B4 // R/W AGC configuration parameters
#define agc_cfg2            0x3B6 // R/W AGC configuration parameters
#define agc_cfg3            0x3B7 // R/W AGC configuration parameters
#define agc_cfg4            0x3B8 // R/W AGC configuration parameters
#define agc_cfg5            0x3B9 // R/W AGC configuration parameters
#define agc_cfg6            0x3BA // R/W AGC configuration parameters
#define agc_cfg7            0x3BC // R/W AGC configuration parameters
#define ocl_cfg0            0x3BF // R/W OCL system parameters
#define ocl_cfg1            0x3C4 // R/W OCL system parameters
#define irq1_en0            0x3C7 // R/W Interrupt Mask Set Bits[7:0] of [15:0] for IRQ1
#define irq1_en1            0x3C8 // R/W Interrupt Mask Set Bits[15:8] of [15:0] for IRQ1
#define irq2_en0            0x3C9 // R/W Interrupt Mask Set Bits[7:0] of [15:0] for IRQ2
#define irq2_en1            0x3CA // R/W Interrupt Mask Set Bits[15:8] of [15:0] for IRQ2
#define irq1_src0           0x3CB // R/W Interrupt Source Bits[7:0] of [15:0] for IRQ
#define irq1_src1           0x3CC // R/W Interrupt Source Bits[15:8] of [15:0] for IRQ
#define ocl_bw0             0x3D2 // R/W OCL system parameters
#define ocl_bw1             0x3D3 // R/W OCL system parameters
#define ocl_bw2             0x3D4 // R/W OCL system parameters
#define ocl_bw3             0x3D5 // R/W OCL system parameters
#define ocl_bw4             0x3D6 // R/W OCL system parameters
#define ocl_bws             0x3D7 // R/W OCL system parameters
#define ocl_cfg13           0x3E0 // R/W OCL system parameters
#define gp_drv              0x3E3 // R/W GPIO and SPI I/O pads drive strength configuration
#define bm_cfg              0x3E6 // R/W Battery monitor threshold voltage setting
#define tx_fsk_test         0x3F0 // R/W TX GFSK/FSK SPORT test mode configuration
#define preamble_num_validate 0x3F3 // R/W Preamble validation
#define sfd_15_4            0x3F4 // R/W Option to set nonstandard SFD
#define afc_cfg             0x3F7 // R/W AFC mode and polarity configuration
#define afc_ki_kp           0x3F8 // R/W AFC ki and kp
#define afc_range           0x3F9 // R/W AFC range
#define afc_read            0x3FA // R/W AFC frequency error readback

SPI.begin();// Inicializa la comunicación SPI
