#ifndef MCC118FINITESCAN
#define MCC118FINITESCAN

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int     setup();//uint8_t low_chan, uint8_t high_chan);
double* finite_scan();//uint8_t low_chan, uint8_t high_chan); 
int     finalize();
int     main();

#ifdef __cplusplus
}
#endif

#endif // MCC118FINITESCAN
