# plots the unfiltered and filtered ECG in
# raw integer units. The ADC had a resolution
# 12 bits.
import numpy as np
import pylab as pl
#
unfiltered = np.loadtxt('ecg2.dat');
filtered = np.loadtxt('ecg2_filtered.dat');
#
pl.title('Fixed point filtering demo');
# unfiltered
pl.subplot(211);
pl.plot(unfiltered[:,2]);
pl.xlabel('samples');
pl.ylabel('unfiltered/raw ADC units');
# filtered
pl.subplot(212);
pl.plot(filtered[:,1]);
pl.xlabel('samples');
pl.ylabel('filtered/raw ADC units');
pl.show();
