import numpy as np
import scipy.signal as signal
import pylab as pl

# Calculate the coefficients for a pure fixed point
# integer filter

# sampling rate
fs = 1000

# cutoffs
f1 = 45
f2 = 55

# scaling factor in bits
q = 14
# scaling factor as facor...
scaling_factor = 2**q

# let's generate a sequence of 2nd order IIR filters
sos = signal.butter(2,[f1/fs*2,f2/fs*2],'stop',output='sos')

# print coefficients
for biquad in sos:
    int_coeffs = np.round(biquad * scaling_factor)
    for int_coeff in int_coeffs:
        print(int(int_coeff),",",sep="",end="")
    print(q)

# plot the frequency response
b,a = signal.sos2tf(sos)
w,h = signal.freqz(b,a)
pl.plot(w/np.pi/2*fs,np.abs(h))
pl.show()
