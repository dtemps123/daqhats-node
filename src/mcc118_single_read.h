#ifndef MCC118SINGLEREAD
#define MCC118SINGLEREAD

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int     setup();//uint8_t low_chan, uint8_t high_chan);
double* single_read();//uint8_t low_chan, uint8_t high_chan); 
int     finalize();
int     main();

#ifdef __cplusplus
}
#endif

#endif // MCC118SINGLEREAD
