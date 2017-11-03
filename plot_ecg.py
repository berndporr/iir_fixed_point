# plots all ECG channels
# recorded with the Attys: www.attys.tech
#
import numpy as np
import pylab as pl
#
unfiltered = np.loadtxt('ecg2.dat');
filtered = np.loadtxt('ecg_filtered.dat');
#
pl.title('Fixed point filtering demo');
# unfiltered
pl.subplot(211);
pl.plot(unfiltered[:,2]);
pl.xlabel('time/sec');
pl.ylabel('unfiltered/raw ADC units');
# filtered
pl.subplot(212);
pl.plot(filtered[:,1]);
pl.xlabel('time/sec');
pl.ylabel('filtered/raw ADC units');
pl.show();
