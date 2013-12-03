// This is the only include you need
#include "DirectFormI.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <assert.h>

// Notch filter, 2nd order bandstop which means 2 biquad filters
// 50Hz notch frequency, sampling rate 1kHz
//
// octave command to get the IIR coefficients:
// [b,a] = butter(2, [45/1000*2, 55/1000*2], 'stop');
//
// octave command to generate the coefficients for the two biquad filters:
// tf2sos(b,a)
//   b0       b1         b2        a0       a1         a2
//   1.00000  -1.90305   1.00000   1.00000  -1.84459   0.95363
//   1.00000  -1.90305   1.00000   1.00000  -1.87702   0.95947

int main (int,char**)
{
	// scale coefficients by 2^14 so that we max out the dynamic
	// range of short int
	int q = 14;
	// create the scaling factor
	float qf = 1 << q;
	// create the two biquad filters:
	// the coefficients turn into short int
	DirectFormI biquad1(1*qf, // b0
			    -1.90305*qf, // b1
			    1*qf, // b2
			    -1.84459*qf, // a1
			    0.95363*qf, // a2
			    q);

	DirectFormI biquad2(1*qf, // b0
			    -1.90305*qf, // b1
			    1*qf, // b2
			    -1.87702*qf, // a1
			    0.95947*qf, // a2
			    q);
	
	FILE *finput = fopen("ecg.dat","rt");
	assert(finput != NULL);
	FILE *foutput = fopen("ecg_filtered.dat","wt");
	assert(foutput != NULL);
	for(;;) 
	{
		// the data file has 3 channels and time
		short x1,x2,x3,y;
		int t;
		if (fscanf(finput,"%d %hd %hd %hd\n",&t,&x1,&x2,&x3)<1) break;
		y = biquad1.filter(x2);
		y = biquad2.filter(y);
		fprintf(foutput,"%d %hd\n",t,y);
	}
	fclose(finput);
	fclose(foutput);
	fprintf(stderr,"Written the filtered ECG to 'ecg_filtered.dat'\n");
}
