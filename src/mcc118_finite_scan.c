#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <daqhats/daqhats.h>
#include "daqhats_utils.h"
#include "mcc118_finite_scan.h"

int     result  = RESULT_SUCCESS;
uint8_t address = 0;

char channel_string[512];
char options_str[512];
char display_header[512];

// Set the channel mask which is used by the library function
// mcc118_a_in_scan_start to specify the channels to acquire.
// The functions below, will parse the channel mask into a
// character string for display purposes.
uint8_t channel_mask = {CHAN0 | CHAN1 | CHAN2 | CHAN3 | CHAN4 | CHAN5 | CHAN6 | CHAN7 };
convert_chan_mask_to_string(channel_mask, channel_string);

int max_channel_array_length = mcc118_info()->NUM_AI_CHANNELS;
int channel_array[max_channel_array_length];
uint8_t num_channels = convert_chan_mask_to_array(channel_mask,
    channel_array);

uint32_t samples_per_channel = 10000;
uint32_t buffer_size = samples_per_channel * num_channels;
double read_buf[buffer_size];
int total_samples_read = 0;

int32_t read_request_size = 500;
double timeout = 5.0;

double scan_rate = 1000.0;
double actual_scan_rate = 0.0;
mcc118_a_in_scan_actual_rate(num_channels, scan_rate, &actual_scan_rate);

uint32_t options = OPTS_DEFAULT;

uint16_t read_status = 0;
uint32_t samples_read_per_channel = 0;


int setup(){

	// Select an MCC118 HAT device to use. Stop on Error
    if (select_hat_device(HAT_ID_MCC_118, &address)) return -1;

	// Open a connection to each device
	result = mcc118_open(address);

	convert_options_to_string(options, options_str);

	return 0;
}

double* finite_scan(){
	double ch_vals[num_channels];
	for (int ch = 0; ch < num_channels; ch++) ch_vals[ch]=0;

	// Configure and start the scan.
	result = mcc118_a_in_scan_start(address, channel_mask, samples_per_channel,
	    scan_rate, options);

	// Continuously update the display value until enter key is pressed
    // or the number of samples requested has been read.
    while ( ( result                        == RESULT_SUCCESS) && 
            ((read_status & STATUS_RUNNING) == STATUS_RUNNING) )
    {
    	// Read the specified number of samples.
    	result = mcc118_a_in_scan_read(address, &read_status, read_request_size,
    	    timeout, read_buf, buffer_size, &samples_read_per_channel);
    	// values are stored in read_buf

    	// Keep track of how many samples have been acquired
    	total_samples_read += samples_read_per_channel;

    	// Once we've read at least one sample
    	if (samples_read_per_channel > 0)
    	{
    		// Find the location of recent data in the buffer
    	    int index = samples_read_per_channel * num_channels - num_channels;

    	    // Keep a running sum of readings for each channel
    	    for (int ch = 0; ch < num_channels; ch++) ch_vals[ch]+=read_buf[index + ch];
    	}
    }

    // Average the sum of readings
    for (int ch = 0; ch < num_channels; ch++) ch_vals[ch]=ch_vals[ch]/total_samples_read;

    // Stop the scan after all samples have been acquired
	print_error(mcc118_a_in_scan_stop(address));
    print_error(mcc118_a_in_scan_cleanup(address));

    return ch_vals;
}

int finalize(){
    print_error(mcc118_close(address));
	return 0;
}

int main(){
	double* vals;
	setup();
	vals = finite_scan();
	for (int ch = 0; ch < 8; ch++)
	{
	    printf("CH %i: val= %f\n",ch,vals[ch]);
	}
	finalize();
	return 0;
}
