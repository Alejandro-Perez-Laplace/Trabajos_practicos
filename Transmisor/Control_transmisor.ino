#include <SPI.h>
#define ext_ctrl     0x100  //R/W External LNA/PA and internal PA control configuration bits
#define fsk_preamble 0x102 //R/W GFSK/FSK preamble length configuration
#define cca1         0x105 //R/W RSSI threshold for CCA
#define cca2         0x106 //R/W CCA mode configuration
#define buffercfg    0x107 //R/W RX and TX Buffer configuration
#define pkt_cfg      0x108 //R/W Firmware download module enable/FCS/CRC control
#define delaycfg0    0x109 //R/W RC_RX command to SFD or SWD search delay
0x10A
delaycfg1
R/W
RC_TX command to TX state delay
0x10B
delaycfg2
R/W
MAC delay extension
0x10C
sync_word0
R/W
Sync Word Bits[7:0] of [23:0]
0x10D
sync_word1
R/W
Sync Word Bits[15:8] of [23:0]
0x10E
sync_word2
R/W
Sync Word Bits[23:16] of [23:0]
0x10F
sync_config
R/W
Sync word configuration
0x111
fsk_preamble_config
R/W
GFSK/FSK preamble configuration
0x13E
rc_cfg
R/W
Packet/SPORT mode configuration
0x300
ch_freq0
R/W
Channel frequency settings—low byte
0x301
ch_freq1
R/W
Channel frequency settings—middle byte
0x302
ch_freq2
R/W
Channel frequency settings—two MSBs
0x304
tx_fd
R/W
Transmit frequency deviation register
0x305
dm_cfg0
R/W
Receive discriminator bandwidth register
0x306
tx_m
R/W
Gaussian and preemphasis filter configuration
0x30C
rrb
R
RSSI readback register
0x30D
lrb
R
Signal quality indicator quality readback register
0x30E
dr0
R/W
Data rate [bps/100], Bits[15:8] of [15:0]
0x30F
dr1
R/W
Data rate [bps/100], Bits[7:0] of [15:0]
0x313
prampg
R/W
PRAM page
0x314
txpb
R/W
Transmit packet storage base address
0x315
rxpb
R/W
Receive packet storage base address
0x316
tmr_cfg0
R/W
Wake-up timer configuration register—high byte
0x317
tmr_cfg1
R/W
Wake-up timer configuration register—low byte
0x318
tmr_rld0
R/W
Wake-up timer value register—high byte
0x319
tmr_rld1
R/W
Wake-up timer value register—low byte
0x31A
tmr_ctrl
R/W
Wake-up timer timeout flag configuration register
0x31B
wuc_32khzosc_status
R
32 kHz oscillator/WUC status
0x31E
pd_aux
R/W
Battery monitor and external PA bias enable
0x32C
gp_cfg
R/W
GPIO configuration
0x32D
gp_out
R/W
GPIO configuration
0x335
synt
R/W
Synthesizer lock time
0x33D
rc_cal_cfg
R/W
RC calibration setting
0x353
vco_band_ovrw
R/W
Overwrite value for the VCO frequency band.
0x354
vco_idac_ovrw
R/W
Overwrite value for the VCO bias current DAC.
0x355
vco_ovwr_cfg
R/W
VCO calibration settings overwrite enable
0x36E
pa_bias
R/W
PA bias control
0x36F
vco_cal_cfg
R/W
VCO calibration parameters
0x371
xto26_trim_cal
R/W
26 MHz crystal oscillator configuration
0x380
vco_band_rb
R
Readback VCO band after calibration
SPI.begin();// Inicializa la comunicación SPI
