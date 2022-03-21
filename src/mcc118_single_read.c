#include "mcc118_single_read.h"

uint8_t address;
uint8_t ch  = 0;
uint32_t options = OPTS_DEFAULT;
double value;

char display_string[256] = "";
char c;

int result              = RESULT_SUCCESS;
int samples_per_channel = 0;
int sample_interval     = 500;  // ms
int mcc118_num_channels = 0;

int setup(){
	// Pull the number of channels for this board
	mcc118_num_channels = mcc118_info()->NUM_AI_CHANNELS;

	// // Ensure low_chan and high_chan are valid
	// if ((low_chan  >= mcc118_num_channels) || 
	//     (high_chan >= mcc118_num_channels))
	// {
	//     fprintf(stderr, "Error: Invalid channel - must be 0 - %d.\n",
	//         mcc118_num_channels - 1);
	//     return -1;
	// }
	// if (low_chan > high_chan)
	// {
	//     fprintf(stderr, "Error: Invalid channels - "
	//         "high_chan must be greater than or equal to low_chan\n");
	//     return -1;
	// }

	// Determine the address of the device to be used
	if (select_hat_device(HAT_ID_MCC_118, &address) != 0)
	{
	    return -1;
	}

	// Open a connection to each device
	result = mcc118_open(address);
	// STOP_ON_ERROR(result);

	printf("\nMCC 118 single data value read example\n");
	printf("    Function demonstrated: mcc118_a_in_read\n");
	// printf("    Channels: %d - %d\n", low_chan, high_chan);
	convert_options_to_string(options, display_string);
	printf("    Options: %s\n", display_string);

// stop:
//     printf("Error in setup():\n");
//     result = mcc118_close(address);
//     print_error(result);

	return 0;
}

double* single_read(){
	static double ch_vals[8];

	// Read a single value from each selected channel
	int idx = 0;
	for (ch = 0; ch < 8; ch++)
	{
	    result = mcc118_a_in_read(address, ch, options, &value);
	    // STOP_ON_ERROR(result);
	    ch_vals[idx] = value; idx++;
	}

	usleep(sample_interval * 1000);

// stop:
// 	printf("Error in single_read():\n");
//     result = mcc118_close(address);
//     print_error(result);
//     for (ch = 0; ch < 8; ch++)
// 	{
// 	    ch_vals[idx] = -999.9; idx++;
// 	}

	return ch_vals;
}

int finalize(){
	result = mcc118_close(address);
    print_error(result);
	return 0;
}

int main(){
	double* vals;
	setup();
	vals = single_read();
	for (ch = 0; ch < 8; ch++)
	{
	    printf("CH %i: val= %f\n",ch,vals[ch]);
	}
	finalize();
	return 0;
}