#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdint.h>

// Macros to handle error checking
#define STOP_ON_ERROR(result)\
{\
    if (result != RESULT_SUCCESS ){\
        print_error(result);\
        goto stop;\
    }\
}

// Channel definitions
#define CHAN0 0x01 << 0
#define CHAN1 0x01 << 1
#define CHAN2 0x01 << 2
#define CHAN3 0x01 << 3
#define CHAN4 0x01 << 4
#define CHAN5 0x01 << 5
#define CHAN6 0x01 << 6
#define CHAN7 0x01 << 7
#define MAX_CHAN_ARRAY_LENGTH 32

// Timeout definitions
#define WAIT_INDEFINITELY   -1
#define RETURN_IMMEDIATELY  0

// Read definitions
#define READ_ALL_AVAILABLE  -1

#ifdef __cplusplus
extern "C" {
#endif

void convert_options_to_string(uint32_t options, char* options_str);
void convert_trigger_mode_to_string(uint8_t trigger_mode, char* trigger_mode_str);
void convert_input_mode_to_string(uint8_t mode, char* mode_str);
void convert_input_range_to_string(uint8_t range, char* range_str);
void convert_tc_type_to_string(uint8_t tc_type, char* tc_type_str);
void convert_chan_mask_to_string(uint32_t channel_mask, char* chans_str);
int convert_chan_mask_to_array(uint32_t channel_mask, int chans[]);
void print_error(int result);
void resetCursor();
void clearEOL();
void cursorUp();
void flush_stdin(void);
int enter_press();
int select_hat_device(uint16_t hat_filter_id, uint8_t* address);

#ifdef __cplusplus
}
#endif

#endif

