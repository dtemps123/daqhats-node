#ifndef MCC118SINGLEREAD
#define MCC118SINGLEREAD

#include "/home/pi/daqhats/examples/c/daqhats_utils.h"

int     setup();//uint8_t low_chan, uint8_t high_chan);
double* single_read();//uint8_t low_chan, uint8_t high_chan); 
int     finalize();
int     main();

#endif // MCC118SINGLEREAD
